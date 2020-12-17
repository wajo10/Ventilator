/* Copyright 2020, RespiraWorks

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "controller.h"

#include "pid.h"
#include "vars.h"
#include <math.h>

static constexpr Duration LOOP_PERIOD = milliseconds(10);

// Inputs - set from external debug program, read but never modified here.
static DebugFloat
    dbg_air_volume_kp("air_volume_kp",
                        "Proportional gain for AIR outer loop volume PID",
                        0.75f);
static DebugFloat
    dbg_air_volume_ki("air_volume_ki",
                        "Integral gain for AIR outer loop volume PID",
                        20.f);

static DebugFloat
    dbg_air_volume_kd("air_volume_kd",
                        "Derivative gain for AIR outer loop volume PID",
                        0.075f);

// //Ziegler-Nichols Outer Loop Pressure values: ku = 0.9, Tu = 0.04
static DebugFloat
    dbg_air_pressure_kp("air_pressure_kp",
                        "Proportional gain for AIR outer loop pressure PID",
                        0.4f);
static DebugFloat
    dbg_air_pressure_ki("air_pressure_ki",
                        "Integral gain for AIR outer loop pressure PID", 20.f);

static DebugFloat
    dbg_air_pressure_kd("air_pressure_kd",
                        "Derivative gain for AIR outer loop pressure PID");

static DebugFloat dbg_psol_kp("psol_kp", "Proportional gain for O2 psol PID",
                              0.04f);
static DebugFloat dbg_psol_ki("psol_ki", "Integral gain for O2 psol PID",
                              20.0f);
static DebugFloat dbg_psol_kd("psol_kd", "Derivative gain for O2 psol PID", 0);

static DebugFloat dbg_fio2_kp("fio2_kp", "Proportional gain for O2 psol PID",
                              4.0f);
static DebugFloat dbg_fio2_ki("fio2_ki", "Integral gain for O2 psol PID", 1.0f);
static DebugFloat dbg_fio2_kd("fio2_kd", "Derivative gain for O2 psol PID", 0);

static DebugFloat
    dbg_air_flow_kp("air_flow_kp",
                    "Proportional gain for AIR inner loop flow PID", 0.1f);
static DebugFloat dbg_air_flow_ki("air_flow_ki",
                                  "Integral gain for AIR inner loop flow PID",
                                  20.0f);
static DebugFloat dbg_air_flow_kd("air_flow_kd",
                                  "Derivative gain for AIR inner loop flow PID",
                                  0);

static DebugFloat dbg_fio2_setpoint("fio2_setpoint",
                                    "FiO2 setpoint [0.0, 1.0]");

// experimental: debug for flow controller testing
static DebugFloat dbg_air_flow_setpoint("air_flow_setpoint",
                                        "Setpoint for Air Flow Controller", 0);

static DebugFloat dbg_air_flow_lps("air_flow_lps",
                                   "Measured Air Flow in liters per sec", 0);

static DebugFloat dbg_forced_blower_power(
    "forced_blower_power",
    "Force the blower fan to a particular power [0,1].  Specify a value "
    "outside this range to let the controller control it.",
    -1.f);
static DebugFloat dbg_forced_exhale_valve_pos(
    "forced_exhale_valve_pos",
    "Force the exhale valve to a particular position [0,1].  Specify a value "
    "outside this range to let the controller control it.",
    -1.f);
static DebugFloat dbg_forced_blower_valve_pos(
    "forced_blower_valve_pos",
    "Force the blower valve to a particular position [0,1].  Specify a value "
    "outside this range to let the controller control it.",
    -1.f);
static DebugFloat dbg_forced_psol_pos(
    "forced_psol_pos",
    "Force the O2 psol to a particular position [0,1].  (Note that psol.cpp "
    "scales this further; see psol_pwm_closed and psol_pwm_open.)  Specify a "
    "value outside this range to let the controller control the psol.",
    -1.f);

// Unchanging outputs - read from external debug program, never modified here.
static DebugUInt32 dbg_per("loop_period", "Loop period, read-only (usec)",
                           static_cast<uint32_t>(LOOP_PERIOD.microseconds()));

// Outputs - read from external debug program, modified here.
static DebugFloat dbg_sp("pc_setpoint", "Pressure control setpoint (cmH2O)");
static DebugFloat dbg_vol("vol_setpoint", "Volume control setpoint (cubic_m)");
static DebugFloat dbg_flowsp("flow_setpoint", "Flow control setpoint (lps)");
static DebugFloat dbg_net_flow("net_flow", "Net flow rate, cc/sec");
static DebugFloat dbg_volume("volume", "Patient volume, ml");
static DebugFloat
    dbg_net_flow_uncorrected("net_flow_uncorrected",
                             "Net flow rate w/o correction, cc/sec");
static DebugFloat dbg_volume_uncorrected("uncorrected_volume",
                                         "Patient volume w/o correction, ml");
static DebugFloat dbg_flow_correction("flow_correction",
                                      "Correction to flow, cc/sec");

// TODO: If we had a notion of read-only DebugVars, we could call this
// blower_valve_ki, which would be kind of nice?  Alternatively, if we had a
// notion of DebugVars that a user had set/pinned to a certain value, we could
// use this as a read/write param -- read it, and write it unless the user set
// it, in which case, use that value.
static DebugFloat dbg_air_pressure_computed_ki(
    "air_pressure_computed_ki",
    "Integral gain for outer loop pressure PID.  READ "
    "ONLY - This value is gain-scheduled.",
    10.0f);

static DebugUInt32 dbg_breath_id("breath_id",
                                 "ID of the current breath, read-only", 0);

Controller::Controller()
    : air_volume_pid_(dbg_air_volume_kp.Get(),
                        dbg_air_volume_ki.Get(),
                        dbg_air_volume_kd.Get(), ProportionalTerm::ON_ERROR,
                        DifferentialTerm::ON_MEASUREMENT, /*output_min=*/0.f,
                        /*output_max=*/1.0f),
      air_pressure_pid_(dbg_air_pressure_kp.Get(),
                        dbg_air_pressure_computed_ki.Get(),
                        dbg_air_pressure_kd.Get(), ProportionalTerm::ON_ERROR,
                        DifferentialTerm::ON_MEASUREMENT, /*output_min=*/0.f,
                        /*output_max=*/1.0f),
      psol_pid_(dbg_psol_kp.Get(), dbg_psol_ki.Get(), dbg_psol_kd.Get(),
                ProportionalTerm::ON_ERROR, DifferentialTerm::ON_MEASUREMENT,
                /*output_min=*/0.f, /*output_max=*/1.f),
      fio2_pid_(dbg_fio2_kp.Get(), dbg_fio2_ki.Get(), dbg_fio2_kd.Get(),
                ProportionalTerm::ON_ERROR, DifferentialTerm::ON_MEASUREMENT,
                /*output_min=*/-1.0f, /*output_max=*/1.f),
      air_flow_pid_(dbg_air_flow_kp.Get(), dbg_air_flow_ki.Get(),
                    dbg_air_flow_kd.Get(), ProportionalTerm::ON_ERROR,
                    DifferentialTerm::ON_MEASUREMENT,
                    /*output_min=*/0.0f, /*output_max=*/1.2f) {}

/*static*/ Duration Controller::GetLoopPeriod() { return LOOP_PERIOD; }

std::pair<ActuatorsState, ControllerState>
Controller::Run(Time now, const VentParams &params,
                const SensorReadings &sensor_readings) {
  VolumetricFlow uncorrected_net_flow =
      sensor_readings.inflow - sensor_readings.outflow;
  flow_integrator_->AddFlow(now, uncorrected_net_flow);
  uncorrected_flow_integrator_->AddFlow(now, uncorrected_net_flow);

  Volume patient_volume = flow_integrator_->GetVolume();
  VolumetricFlow net_flow =
      uncorrected_net_flow + flow_integrator_->FlowCorrection();

  BlowerSystemState desired_state = fsm_.DesiredState(
      now, params, {.patient_volume = patient_volume, .net_flow = net_flow});

  if (desired_state.is_end_of_breath) {
    // The "correct" volume at the breath boundary is 0.
    flow_integrator_->NoteExpectedVolume(ml(0));
    breath_id_ = now.microsSinceStartup();
  }

  // Precision loss 64->32 bits ok: we only care about equality of these values,
  // not their absolute value, and the top 32 bits will change with each new
  // breath.
  // TODO: Maybe we should just make breath id a 32-bit value.
  dbg_breath_id.Set(static_cast<uint32_t>(breath_id_));

  // Gain scheduling of blower Ki based on PIP and PEEP settings.  Artisanally
  // hand-tuned by Edwin.
  //
  // Note that we use desired_state.pip/peep and not params.pip/peep because
  // desired_state updates at breath boundaries, whereas params updates
  // whenever the user clicks the touchscreen.

  /*
  // Gain Scheduler
  // >> This feature is currently disabled in the experimental nested loop
  //    controller because it didn't seem to be needed.  It can be re-enabled
  //    if desired in future tuning.
  float air_pressure_ki = std::clamp(
      (desired_state.pip - desired_state.peep).cmH2O() - 5.0f, 10.0f, 20.0f);
        dbg_blower_valve_computed_ki.Set(air_pressure_ki);
  */

  air_pressure_pid_.SetKP(dbg_air_pressure_kp.Get());
  air_pressure_pid_.SetKI(dbg_air_pressure_ki.Get());
  air_pressure_pid_.SetKD(dbg_air_pressure_kd.Get());
  psol_pid_.SetKP(dbg_psol_kp.Get());
  psol_pid_.SetKI(dbg_psol_ki.Get());
  psol_pid_.SetKD(dbg_psol_kd.Get());
  fio2_pid_.SetKP(dbg_fio2_kp.Get());
  fio2_pid_.SetKI(dbg_fio2_ki.Get());
  fio2_pid_.SetKD(dbg_fio2_kd.Get());
  dbg_fio2_setpoint.Set(params.fio2);
  air_flow_pid_.SetKP(dbg_air_flow_kp.Get());
  air_flow_pid_.SetKI(dbg_air_flow_ki.Get());
  air_flow_pid_.SetKD(dbg_air_flow_kd.Get());
  dbg_air_flow_lps.Set(sensor_readings.inflow.liters_per_sec());

  ActuatorsState actuators_state;

  switch (params.mode) {
  case VentMode_OFF:
    break;
  case VentMode_PRESSURE_CONTROL:
  case VentMode_PRESSURE_ASSIST:
  case VentMode_PRESSURE_REG_VC:
  case VentMode_PRESSURE_SUPPORT:
  case VentMode_SPONTANEOUS_BREATHS:
  case VentMode_PC_SIMV:
  case VentMode_BIPAP:
    if (desired_state.pressure_setpoint == std::nullopt) {
      // System disabled.  Disable blower, close inspiratory pinch valve, and
      // open expiratory pinch valve.  This way if someone is hooked up, they can
      // breathe through the expiratory branch, and they can't contaminate the
      // inspiratory branch.
      //
      // If the pinch valves are not yet homed, this will home them and then move
      // them to the desired positions.
      air_pressure_pid_.Reset();
      psol_pid_.Reset();
      fio2_pid_.Reset();
      air_flow_pid_.Reset();

      actuators_state = {
        .fio2_valve = 0,
        .blower_power = 0,
        .blower_valve = 0,
        .exhale_valve = 1,
      };
      ventilator_was_on_ = false;
    } else {
      if (!ventilator_was_on_) {
        // reset volume integrators
        flow_integrator_.emplace();
        uncorrected_flow_integrator_.emplace();
      }

      // Delivering air + oxygen mixes from 21 to 59%.
      if (params.fio2 < 0.6) {
        psol_pid_.Reset();

        // Successive Loop Closure: pressure on outer loop, flow on inner loop
        // Pressure command >> Flow command >> Actuator command
        float flow_cmd =
          air_pressure_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
              desired_state.pressure_setpoint->kPa());

        float blower_valve = air_flow_pid_.Compute(
            now, sensor_readings.inflow.liters_per_sec(), flow_cmd);

        // Fio2 controller with feed-forward
        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        actuators_state = {
          .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
              fio2_coupling_value,
              0.0f, 1.0f),
          // In normal mode, blower is always full power; pid controls pressure
          // by actuating the blower pinch valve.
          .blower_power = 1.f,
          .blower_valve = std::clamp(
              blower_valve + 0.05f, 0.0f,
              1.0f), // always keep the valve a little open for better response
          // coupled control: exhale valve tracks flow command
          .exhale_valve = std::clamp(1.0f - 0.55f * flow_cmd - 0.4f, 0.f, 1.f),
        };
      } else {
        // Delivering air + oxygen mixes from 60 to 100%
        air_pressure_pid_.Reset();

        // Single loop on PSOL for now, because PSOL flow sensor not implemented
        // yet
        float psol_valve =
          psol_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
              desired_state.pressure_setpoint->kPa());

        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        float blower_valve =
          air_flow_pid_.Compute(now, sensor_readings.inflow.liters_per_sec(),
              psol_valve * (1 - fio2_coupling_value));

        actuators_state = {
          // Force psol to stay very slightly open to avoid the discontinuity
          // caused by valve hysteresis at very low command.  The exhale valve
          // compensates for this intentional leakage by staying open when the
          // psol valve is closed.
          .fio2_valve = std::clamp(psol_valve + 0.05f, 0.0f, 1.0f),
          .blower_power = 1.0f,
          .blower_valve = std::clamp(blower_valve, 0.0f, 1.0f),
          .exhale_valve = 1.0f - 0.6f * psol_valve - 0.4f,
        };
      }
      // Start controlling pressure.
      ventilator_was_on_ = true;
    }
    break;
  case VentMode_HIGH_FLOW_NASAL_CANNULA:
    if (desired_state.flow_setpoint == std::nullopt) {
      // System disabled.  Disable blower, close inspiratory pinch valve, and
      // open expiratory pinch valve.  This way if someone is hooked up, they can
      // breathe through the expiratory branch, and they can't contaminate the
      // inspiratory branch.
      //
      // If the pinch valves are not yet homed, this will home them and then move
      // them to the desired positions.
      air_pressure_pid_.Reset();
      psol_pid_.Reset();
      fio2_pid_.Reset();
      air_flow_pid_.Reset();

      actuators_state = {
        .fio2_valve = 0,
        .blower_power = 0,
        .blower_valve = 0,
        .exhale_valve = 1,
      };
      ventilator_was_on_ = false;
    } else {
      if (!ventilator_was_on_) {
        // reset volume integrators
        flow_integrator_.emplace();
        uncorrected_flow_integrator_.emplace();
      }

      // Delivering air + oxygen mixes from 21 to 59%.
      if (params.fio2 < 0.6) {
        psol_pid_.Reset();

        float blower_valve = air_flow_pid_.Compute(
            now, sensor_readings.inflow.liters_per_sec(),
            desired_state.flow_setpoint->liters_per_sec());

        // Fio2 controller with feed-forward
        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        actuators_state = {
          .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
              fio2_coupling_value,
              0.0f, 1.0f),
          // In normal mode, blower is always full power; pid controls pressure
          // by actuating the blower pinch valve.
          .blower_power = 1.f,
          .blower_valve = std::clamp(
              blower_valve + 0.05f, 0.0f,
              1.0f), // always keep the valve a little open for better response
          // coupled control: exhale valve tracks flow command
          .exhale_valve = std::clamp(blower_valve + 0.05f, 0.f, 1.f),
        };
      } else {
        // Delivering air + oxygen mixes from 60 to 100%
        air_flow_pid_.Reset();

        // Single loop on PSOL for now, because PSOL flow sensor not implemented
        // yet
        float psol_valve = psol_pid_.Compute(
            now, net_flow.liters_per_sec(),
            desired_state.flow_setpoint->liters_per_sec());

        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        float blower_valve =
          air_flow_pid_.Compute(now, sensor_readings.inflow.liters_per_sec(),
              psol_valve * (1 - fio2_coupling_value));

        actuators_state = {
          // Force psol to stay very slightly open to avoid the discontinuity
          // caused by valve hysteresis at very low command.  The exhale valve
          // compensates for this intentional leakage by staying open when the
          // psol valve is closed.
          .fio2_valve = std::clamp(psol_valve + 0.05f, 0.0f, 1.0f),
          .blower_power = 1.0f,
          .blower_valve = std::clamp(blower_valve, 0.0f, 1.0f),
          .exhale_valve = 1.0f - 0.6f * psol_valve - 0.4f,
        };
      }
      // Start controlling pressure.
      ventilator_was_on_ = true;
    }
    break;
  case VentMode_VOLUME_CONTROL:
  case VentMode_VOLUME_ASSIST:
    if (desired_state.volume_setpoint == std::nullopt) {
      // System disabled.  Disable blower, close inspiratory pinch valve, and
      // open expiratory pinch valve.  This way if someone is hooked up, they can
      // breathe through the expiratory branch, and they can't contaminate the
      // inspiratory branch.
      //
      // If the pinch valves are not yet homed, this will home them and then move
      // them to the desired positions.
      air_volume_pid_.Reset();
      air_pressure_pid_.Reset();
      psol_pid_.Reset();
      fio2_pid_.Reset();
      air_flow_pid_.Reset();

      actuators_state = {
        .fio2_valve = 0,
        .blower_power = 0,
        .blower_valve = 0,
        .exhale_valve = 1,
      };
      ventilator_was_on_ = false;
    } else {
      if (!ventilator_was_on_) {
        // reset volume integrators
        flow_integrator_.emplace();
        uncorrected_flow_integrator_.emplace();
      }

      // Delivering air + oxygen mixes from 21 to 59%.
      if (params.fio2 < 0.6) {
        float flow_cmd;

        psol_pid_.Reset();

        if (!desired_state.is_in_exhale) {
          air_pressure_pid_.Reset();
          // Successive Loop Closure: volume on outer loop, flow on inner loop
          // Volume command >> Flow command >> Actuator command
          flow_cmd = air_volume_pid_.Compute(now, patient_volume.ml(),
              desired_state.volume_setpoint->ml());
        } else {
          air_volume_pid_.Reset();
          // Successive Loop Closure: pressure on outer loop, flow on inner loop
          // Pressure command >> Flow command >> Actuator command
          flow_cmd =
            air_pressure_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
                desired_state.pressure_setpoint->kPa());
        }

        float blower_valve = air_flow_pid_.Compute(
            now, sensor_readings.inflow.liters_per_sec(), flow_cmd);

        // Fio2 controller with feed-forward
        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        if (!desired_state.is_in_exhale) {
          actuators_state = {
            .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
                fio2_coupling_value,
                0.0f, 1.0f),
            // In normal mode, blower is always full power; pid controls pressure
            // by actuating the blower pinch valve.
            .blower_power = 1.f,
            .blower_valve = std::clamp(blower_valve, 0.0f,
                1.0f), // always keep the valve a little open for better response
            // coupled control: exhale valve tracks flow command
            .exhale_valve = std::clamp(1.0f - 0.60f * blower_valve, 0.f, 1.f),
          };
        } else {
          actuators_state = {
            .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
                fio2_coupling_value,
                0.0f, 1.0f),
            // In normal mode, blower is always full power; pid controls pressure
            // by actuating the blower pinch valve.
            .blower_power = 1.f,
            .blower_valve = std::clamp(
                blower_valve + 0.05f, 0.0f,
                1.0f), // always keep the valve a little open for better response
            // coupled control: exhale valve tracks flow command
            .exhale_valve = std::clamp(1.0f - 0.55f * flow_cmd - 0.4f, 0.f, 1.f),
          };
        }
      } else {
        float psol_valve;

        // Delivering air + oxygen mixes from 60 to 100%
        air_pressure_pid_.Reset();
        air_volume_pid_.Reset();

        // Single loop on PSOL for now, because PSOL flow sensor not implemented
        // yet
        if (!desired_state.is_in_exhale) {
          psol_valve = psol_pid_.Compute(now, patient_volume.ml(),
              desired_state.volume_setpoint->ml());
        } else {
          psol_valve =
            psol_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
                desired_state.pressure_setpoint->kPa());
        }

        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        float blower_valve =
          air_flow_pid_.Compute(now, sensor_readings.inflow.liters_per_sec(),
              psol_valve * (1 - fio2_coupling_value));

        actuators_state = {
          // Force psol to stay very slightly open to avoid the discontinuity
          // caused by valve hysteresis at very low command.  The exhale valve
          // compensates for this intentional leakage by staying open when the
          // psol valve is closed.
          .fio2_valve = std::clamp(psol_valve + 0.05f, 0.0f, 1.0f),
          .blower_power = 1.0f,
          .blower_valve = std::clamp(blower_valve, 0.0f, 1.0f),
          .exhale_valve = 1.0f - 0.6f * psol_valve - 0.4f,
        };
      }
      // Start controlling pressure.
      ventilator_was_on_ = true;
    }
    break;
  case VentMode_CPAP:
    if (desired_state.flow_setpoint == std::nullopt) {
      // System disabled.  Disable blower, close inspiratory pinch valve, and
      // open expiratory pinch valve.  This way if someone is hooked up, they can
      // breathe through the expiratory branch, and they can't contaminate the
      // inspiratory branch.
      //
      // If the pinch valves are not yet homed, this will home them and then move
      // them to the desired positions.
      air_pressure_pid_.Reset();
      psol_pid_.Reset();
      fio2_pid_.Reset();
      air_flow_pid_.Reset();

      actuators_state = {
        .fio2_valve = 0,
        .blower_power = 0,
        .blower_valve = 0,
        .exhale_valve = 1,
      };
      ventilator_was_on_ = false;
    } else {
      if (!ventilator_was_on_) {
        // reset volume integrators
        flow_integrator_.emplace();
        uncorrected_flow_integrator_.emplace();
      }

      // Delivering air + oxygen mixes from 21 to 59%.
      if (params.fio2 < 0.6) {
        float blower_valve;
        float flow_cmd;

        psol_pid_.Reset();

        if (!desired_state.is_in_exhale) {
          air_pressure_pid_.Reset();
          // Successive Loop Closure: volume on outer loop, flow on inner loop
          // Volume command >> Flow command >> Actuator command
          blower_valve = air_flow_pid_.Compute(
                  now, sensor_readings.inflow.liters_per_sec(),
                  desired_state.flow_setpoint->liters_per_sec());
        } else {
          // Successive Loop Closure: pressure on outer loop, flow on inner loop
          // Pressure command >> Flow command >> Actuator command
          flow_cmd =
            air_pressure_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
                desired_state.pressure_setpoint->kPa());
          blower_valve = air_flow_pid_.Compute(
              now, sensor_readings.inflow.liters_per_sec(), flow_cmd);
        }
        // Fio2 controller with feed-forward
        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        if (!desired_state.is_in_exhale) {
          actuators_state = {
            .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
                fio2_coupling_value,
                0.0f, 1.0f),
            // In normal mode, blower is always full power; pid controls pressure
            // by actuating the blower pinch valve.
            .blower_power = 1.f,
            .blower_valve = std::clamp(
                blower_valve + 0.05f, 0.0f,
                1.0f), // always keep the valve a little open for better response
            // coupled control: exhale valve tracks flow command
            .exhale_valve = std::clamp(blower_valve + 0.05f, 0.f, 1.f),
          };
        } else {
          actuators_state = {
            .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
                fio2_coupling_value,
                0.0f, 1.0f),
            // In normal mode, blower is always full power; pid controls pressure
            // by actuating the blower pinch valve.
            .blower_power = 1.f,
            .blower_valve = std::clamp(
                blower_valve + 0.05f, 0.0f,
                1.0f), // always keep the valve a little open for better response
            // coupled control: exhale valve tracks flow command
            .exhale_valve = std::clamp(1.0f - 0.55f * flow_cmd - 0.4f, 0.f, 1.f),
          };
        }
      } else {
        float psol_valve;

        // Delivering air + oxygen mixes from 60 to 100%
        air_flow_pid_.Reset();
        air_pressure_pid_.Reset();

        // Single loop on PSOL for now, because PSOL flow sensor not implemented
        // yet
        if (!desired_state.is_in_exhale) {
          psol_valve = psol_pid_.Compute(
                  now, sensor_readings.inflow.liters_per_sec(),
                  desired_state.flow_setpoint->liters_per_sec());
        } else {
          psol_valve =
            psol_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
                desired_state.pressure_setpoint->kPa());
        }

        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        float blower_valve =
          air_flow_pid_.Compute(now, sensor_readings.inflow.liters_per_sec(),
              psol_valve * (1 - fio2_coupling_value));

        actuators_state = {
          // Force psol to stay very slightly open to avoid the discontinuity
          // caused by valve hysteresis at very low command.  The exhale valve
          // compensates for this intentional leakage by staying open when the
          // psol valve is closed.
          .fio2_valve = std::clamp(psol_valve + 0.05f, 0.0f, 1.0f),
          .blower_power = 1.0f,
          .blower_valve = std::clamp(blower_valve, 0.0f, 1.0f),
          .exhale_valve = 1.0f - 0.6f * psol_valve - 0.4f,
        };
      }
      // Start controlling pressure.
      ventilator_was_on_ = true;
    }
    break;
  case VentMode_VC_SIMV:
    if (desired_state.volume_setpoint == std::nullopt) {
      // System disabled.  Disable blower, close inspiratory pinch valve, and
      // open expiratory pinch valve.  This way if someone is hooked up, they can
      // breathe through the expiratory branch, and they can't contaminate the
      // inspiratory branch.
      //
      // If the pinch valves are not yet homed, this will home them and then move
      // them to the desired positions.
      air_volume_pid_.Reset();
      air_pressure_pid_.Reset();
      psol_pid_.Reset();
      fio2_pid_.Reset();
      air_flow_pid_.Reset();

      actuators_state = {
        .fio2_valve = 0,
        .blower_power = 0,
        .blower_valve = 0,
        .exhale_valve = 1,
      };
      ventilator_was_on_ = false;
    } else {
      if (!ventilator_was_on_) {
        // reset volume integrators
        flow_integrator_.emplace();
        uncorrected_flow_integrator_.emplace();
      }

      // Delivering air + oxygen mixes from 21 to 59%.
      if (params.fio2 < 0.6) {
        float flow_cmd;

        psol_pid_.Reset();

        if (!desired_state.is_in_exhale) {
          air_pressure_pid_.Reset();
          // Successive Loop Closure: volume on outer loop, flow on inner loop
          // Volume command >> Flow command >> Actuator command
          flow_cmd = air_volume_pid_.Compute(now, patient_volume.ml(),
              desired_state.volume_setpoint->ml());
        } else {
          air_volume_pid_.Reset();
          // Successive Loop Closure: pressure on outer loop, flow on inner loop
          // Pressure command >> Flow command >> Actuator command
          flow_cmd =
            air_pressure_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
                desired_state.pressure_setpoint->kPa());
        }

        float blower_valve = air_flow_pid_.Compute(
            now, sensor_readings.inflow.liters_per_sec(), flow_cmd);

        // Fio2 controller with feed-forward
        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        if (!desired_state.is_in_exhale) {
          actuators_state = {
            .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
                fio2_coupling_value,
                0.0f, 1.0f),
            // In normal mode, blower is always full power; pid controls pressure
            // by actuating the blower pinch valve.
            .blower_power = 1.f,
            .blower_valve = std::clamp(blower_valve, 0.0f,
                1.0f), // always keep the valve a little open for better response
            // coupled control: exhale valve tracks flow command
            .exhale_valve = std::clamp(1.0f - 0.60f * blower_valve, 0.f, 1.f),
          };
        } else {
          actuators_state = {
            .fio2_valve = std::clamp(sensor_readings.inflow.liters_per_sec() *
                fio2_coupling_value,
                0.0f, 1.0f),
            // In normal mode, blower is always full power; pid controls pressure
            // by actuating the blower pinch valve.
            .blower_power = 1.f,
            .blower_valve = std::clamp(
                blower_valve + 0.05f, 0.0f,
                1.0f), // always keep the valve a little open for better response
            // coupled control: exhale valve tracks flow command
            .exhale_valve = std::clamp(1.0f - 0.55f * flow_cmd - 0.4f, 0.f, 1.f),
          };
        }
      } else {
        float psol_valve;

        // Delivering air + oxygen mixes from 60 to 100%
        air_pressure_pid_.Reset();
        air_volume_pid_.Reset();

        // Single loop on PSOL for now, because PSOL flow sensor not implemented
        // yet
        if (!desired_state.is_in_exhale) {
          psol_valve = psol_pid_.Compute(now, patient_volume.ml(),
              desired_state.volume_setpoint->ml());
        } else {
          psol_valve =
            psol_pid_.Compute(now, sensor_readings.patient_pressure.kPa(),
                desired_state.pressure_setpoint->kPa());
        }

        float fio2_coupling_value =
          std::clamp(params.fio2 + fio2_pid_.Compute(now, sensor_readings.fio2,
                params.fio2),
              0.0f, 1.0f); // just a little bit of feed-forward

        float blower_valve =
          air_flow_pid_.Compute(now, sensor_readings.inflow.liters_per_sec(),
              psol_valve * (1 - fio2_coupling_value));

        actuators_state = {
          // Force psol to stay very slightly open to avoid the discontinuity
          // caused by valve hysteresis at very low command.  The exhale valve
          // compensates for this intentional leakage by staying open when the
          // psol valve is closed.
          .fio2_valve = std::clamp(psol_valve + 0.05f, 0.0f, 1.0f),
          .blower_power = 1.0f,
          .blower_valve = std::clamp(blower_valve, 0.0f, 1.0f),
          .exhale_valve = 1.0f - 0.6f * psol_valve - 0.4f,
        };
      }
      // Start controlling pressure.
      ventilator_was_on_ = true;
    }
    break;
  }

  ControllerState controller_state = {
      .pressure_setpoint = desired_state.pressure_setpoint.value_or(kPa(0)),
      .patient_volume = patient_volume,
      .net_flow = net_flow,
      .flow_correction = flow_integrator_->FlowCorrection(),
      .breath_id = breath_id_,
  };

  dbg_sp.Set(desired_state.pressure_setpoint.value_or(kPa(0)).cmH2O());
  dbg_vol.Set(desired_state.volume_setpoint.value_or(cubic_m(0)).ml());
  dbg_flowsp.Set(desired_state.flow_setpoint.value_or(cubic_m_per_sec(0)).liters_per_sec());
  dbg_net_flow.Set(controller_state.net_flow.ml_per_sec());
  dbg_net_flow_uncorrected.Set(
      (sensor_readings.inflow - sensor_readings.outflow).ml_per_sec());
  dbg_volume.Set(controller_state.patient_volume.ml());
  dbg_volume_uncorrected.Set(uncorrected_flow_integrator_->GetVolume().ml());
  dbg_flow_correction.Set(flow_integrator_->FlowCorrection().ml_per_sec());

  // Handle DebugVars that force the actuators.
  auto set_force = [](const DebugFloat &var, auto &state) {
    float v = var.Get();
    if (v >= 0 && v <= 1) {
      state = v;
    }
  };
  set_force(dbg_forced_blower_power, actuators_state.blower_power);
  set_force(dbg_forced_blower_valve_pos, actuators_state.blower_valve);
  set_force(dbg_forced_exhale_valve_pos, actuators_state.exhale_valve);
  set_force(dbg_forced_psol_pos, actuators_state.fio2_valve);

  return {actuators_state, controller_state};
}

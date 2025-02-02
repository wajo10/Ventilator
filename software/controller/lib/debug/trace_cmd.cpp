
/* Copyright 2020-2021, RespiraWorks

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

#include "commands.h"

namespace Debug::Command {

ErrorCode TraceHandler::Process(Context *context) {
  // The first byte of data is always required, this
  // gives the sub-command.
  if (context->request_length < 1) return ErrorCode::MissingData;

  Subcommand subcommand{context->request[0]};

  switch (subcommand) {
    // Sub-command FlushTrace is used to flush the trace buffer
    // It also disables the trace
    case Subcommand::Flush: {
      trace_->flush();
      context->response_length = 0;
      *(context->processed) = true;
      return ErrorCode::None;
    }

    // Sub-command DownloadTrace is used to read data from the buffer
    case Subcommand::Download:
      return ReadTraceBuffer(context);

    case Subcommand::Start:
      trace_->start();
      context->response_length = 0;
      *(context->processed) = true;
      return ErrorCode::None;

    case Subcommand::Stop:
      trace_->stop();
      context->response_length = 0;
      *(context->processed) = true;
      return ErrorCode::None;

    case Subcommand::GetVarId:
      return GetTraceVar(context);

    case Subcommand::SetVarId:
      return SetTraceVar(context);

    case Subcommand::GetPeriod:
      // response (trace period) is 32 bits (4 bytes) long
      if (context->max_response_length < 4) return ErrorCode::NoMemory;
      u32_to_u8(trace_->period(), context->response);
      context->response_length = 4;
      *(context->processed) = true;
      return ErrorCode::None;

    case Subcommand::SetPeriod:
      // trace period is a 32 bits int, meaning the request (including subcommand)
      // is 5 bytes long
      if (context->request_length < 5) return ErrorCode::MissingData;
      trace_->set_period(u8_to_u32(&(context->request[1])));
      context->response_length = 0;
      *(context->processed) = true;
      return ErrorCode::None;

    case Subcommand::CountSamples:
      // response (num samples) is 4 bytes long, make sure I have enough room
      if (context->max_response_length < 4) return ErrorCode::NoMemory;
      u32_to_u8(static_cast<uint32_t>(trace_->sample_count()), context->response);
      context->response_length = 4;
      *(context->processed) = true;
      return ErrorCode::None;

    default:
      return ErrorCode::InvalidData;
  }
}

ErrorCode TraceHandler::ReadTraceBuffer(Context *context) {
  // See how many active trace variables there are
  // This gives us our sample size;
  size_t var_count = trace_->active_variable_count();

  // If there aren't any active variables, I'm done
  if (!var_count) {
    context->response_length = 0;
    *(context->processed) = true;
    return ErrorCode::None;
  }

  // See how many samples I can return
  // First, find out how many I could based on the max value
  size_t max_samples =
      context->max_response_length / static_cast<size_t>(var_count * sizeof(uint32_t));

  // If there's not enough room for even one sample, return an error.
  // That really shouldn't happen
  if (max_samples == 0) {
    return ErrorCode::NoMemory;
  }

  // Find the total number of samples in the buffer
  size_t samples_count = trace_->sample_count();
  if (samples_count > max_samples) {
    samples_count = max_samples;
  }

  std::array<uint32_t, Trace::MaxVars> record;
  for (size_t sample = 0; sample < samples_count; sample++) {
    // This shouldn't fail since I've already confirmed
    // the number of elements in the buffer.  If it does
    // fail it's a bug.
    if (!trace_->get_next_record(&record, &var_count)) {
      break;
    }
    for (size_t variable = 0; variable < var_count; variable++) {
      u32_to_u8(record[variable], context->response);
      context->response += sizeof(uint32_t);
    }
  }

  context->response_length = static_cast<uint32_t>(samples_count * var_count * sizeof(uint32_t));
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode TraceHandler::SetTraceVar(Context *context) {
  // 3 extra bytes are required to provide variable index and variable ID
  if (context->request_length < 4) return ErrorCode::MissingData;
  // extract index and var_id from request
  uint8_t index = context->request[1];
  uint16_t var_id = u8_to_u16(&context->request[2]);
  if (!trace_->set_traced_variable(index, var_id)) {
    return ErrorCode::InvalidData;
  }
  // no response is required, only the error code
  context->response_length = 0;
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode TraceHandler::GetTraceVar(Context *context) {
  // 1 extra byte is required to provide variable index
  if (context->request_length < 2) return ErrorCode::MissingData;

  uint8_t index = context->request[1];

  // response (var ID) is 16 bits (2 bytes) long
  if (context->max_response_length < 2) return ErrorCode::NoMemory;
  context->response_length = 2;

  u16_to_u8(static_cast<uint16_t>(trace_->traced_variable(index)), context->response);
  *(context->processed) = true;
  return ErrorCode::None;
}

}  // namespace Debug::Command

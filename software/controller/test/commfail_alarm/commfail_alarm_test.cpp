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

#include "commfail_alarm.h"
#include "gtest/gtest.h"

// To test Handler function
TEST(CommFailAlarmTest, AlarmRaiseHandler) {
  Time ts = microsSinceStartup(0); // start
  CommFailAlarm cfa;

  cfa.Initialize(ts);
  // testing line: if (current_timestamp > lastrx_timestamp)
  // triggered_ = status;
  EXPECT_FALSE(cfa.Handler(ts, ts));
  EXPECT_FALSE(cfa.Handler(ts, ts + milliseconds(0)));
  EXPECT_FALSE(cfa.Handler(ts, ts + milliseconds(99)));
  EXPECT_FALSE(cfa.Handler(ts, ts + milliseconds(100)));
  EXPECT_FALSE(cfa.Handler(ts, ts + milliseconds(101)));
  EXPECT_FALSE(cfa.Handler(ts, ts + milliseconds(200)));
  EXPECT_FALSE(cfa.Handler(ts + milliseconds(0), ts));
  // testing line: status = CommunicationResumed(current_timestamp);
  EXPECT_FALSE(cfa.Handler(ts + milliseconds(99), ts));
  EXPECT_FALSE(cfa.Handler(ts + milliseconds(100), ts));
  // testing line: status = CommunicationFailed(current_timestamp);
  EXPECT_TRUE(cfa.Handler(ts + milliseconds(101), ts));
  EXPECT_TRUE(cfa.Handler(ts + milliseconds(200), ts));
}

// To test CommunicationFailed function
TEST(CommFailAlarmTest, RaiseAlarm) {
  // testing with class default values triggered_{false}, trigger_count_{0}
  {
    constexpr Time ts = microsSinceStartup(0); // start
    CommFailAlarm cfa;

    cfa.Initialize(ts);
    // by default triggered_ = false; trigger_count_ = 0,
    // testing below branches:
    // if (!triggered_)
    //   if (trigger_count_ < kTriggerCountThreshold) {
    //     trigger_count_++;
    //     if (trigger_count_ == kTriggerCountThreshold) {
    EXPECT_TRUE(cfa.CommunicationFailed(ts));
    // after above line executed: trigger_count_ = 1, triggered_ = true,
    // re-run the line same
    EXPECT_TRUE(cfa.CommunicationFailed(ts));
    // after above line executed: values should be same
    // trigger_count_ = 1, triggered_ = true,

    // EXPECT_FALSE scenario for CommunicationFailed() will never occur
  }

  // testing with class variables modified by calling Handler()
  {
    constexpr Time ts = microsSinceStartup(0); // start
    CommFailAlarm cfa;

    cfa.Initialize(ts);
    // by default triggered_ = false; trigger_count_ = 0,
    EXPECT_FALSE(cfa.Handler(ts + milliseconds(99), ts));
    // after above line executed: defaults should be same
    // triggered_ = false, trigger_count_ = 0
    EXPECT_TRUE(cfa.Handler(ts + milliseconds(101), ts));
    // after above line executed: trigger_count_ = 1, triggered_ = true,
    EXPECT_TRUE(cfa.CommunicationFailed(ts));
    // after above line executed: trigger_count_ = 1, triggered_ = true,

    // EXPECT_FALSE scenario for CommunicationFailed() will never occur
  }
}

// To test CommunicationResumed function
TEST(CommFailAlarmTest, ClearAlarm) {
  // testing with class default values triggered_{false}, trigger_count_{0}
  {
    constexpr Time ts = microsSinceStartup(0); // start
    CommFailAlarm cfa;

    cfa.Initialize(ts);
    // by default triggered_ = false; trigger_count_ = 0,
    // testing line: if (triggered_)
    EXPECT_FALSE(cfa.CommunicationResumed(ts));
    // after above line executed: defaults should be same
    // triggered_ = false, trigger_count_ = 0

    // EXPECT_TRUE scenario for CommunicationResumed() will never occur
  }

  // testing with class variables modified by calling Handler()
  {
    constexpr Time ts = microsSinceStartup(0); // start
    CommFailAlarm cfa;

    cfa.Initialize(ts);
    // by default triggered_ = false; trigger_count_ = 0,
    EXPECT_FALSE(cfa.Handler(ts + milliseconds(99), ts));
    // after above line executed: defaults should be same
    // triggered_ = false, trigger_count_ = 0
    EXPECT_TRUE(cfa.Handler(ts + milliseconds(101), ts));
    // after above line executed: trigger_count_ = 1, triggered_ = true,
    EXPECT_FALSE(cfa.CommunicationResumed(ts));
    // after above line executed: trigger_count_ = 0, triggered_ = false,

    // EXPECT_TRUE scenario for CommunicationResumed() will never occur
  }
}

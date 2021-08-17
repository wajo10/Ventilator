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
#include "vars.h"
#include "gtest/gtest.h"
#include <array>
#include <stdint.h>

namespace Debug::Command {

TEST(VarHandler, GetVarInfo) {
  uint32_t value = 0xDEADBEEF;
  const char *name = "name";
  const char *help = "help string";
  const char *format = "format";
  const char *unit = "unit";
  DebugVar var(name, VarAccess::ReadOnly, &value, unit, help, format);

  // expected result is hand-built from format given in var_cmd.cpp
  flatbuffers::FlatBufferBuilder builder(1024);
  auto expected_builder = DebugProtocol::CreateGetVarInfoResponse(
    builder,
    static_cast<uint8_t>(VarType::UInt32),
    static_cast<uint8_t>(VarAccess::ReadOnly),
    0,
    static_cast<uint8_t>(strlen(name)),
    static_cast<uint8_t>(strlen(format)),
    static_cast<uint8_t>(strlen(help)),
    static_cast<uint8_t>(strlen(unit)),
    builder.CreateString(name),
    builder.CreateString(format),
    builder.CreateString(help),
    builder.CreateString(unit)
  );
  builder.Finish(expected_builder);
  uint8_t *expected = builder.GetBufferPointer();
  uint32_t expected_len = builder.GetSize();

  uint16_t id = var.GetId();

  auto req_builder = DebugProtocol::CreateGetVarRequest(
    builder,
    DebugProtocol::VarSubcmd::GetInfo,
    id
  );
  builder.Finish(req_builder);
  uint8_t *req = builder.GetBufferPointer();
  uint32_t req_len = builder.GetSize();

  bool processed{false};
  Context context = {.request = req,
                     .request_length = req_len,
                     .response = nullptr,
                     .max_response_length = 150,
                     .response_length = 0,
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context));
  EXPECT_TRUE(processed);
  for (size_t i = 0; i < expected_len; ++i) {
    EXPECT_EQ(context.response[i], expected[i]);
  }
}

TEST(VarHandler, GetVar) {
  uint32_t value = 0xDEADBEEF;
  DebugVar var("name", VarAccess::ReadWrite, &value, "units", "help");

  // Test that a GET command obtains the variable's value.
  flatbuffers::FlatBufferBuilder builder(1024);
  auto expected_builder = DebugProtocol::CreateGetVarResponse(
    builder,
    value
  );
  builder.Finish(expected_builder);
  uint8_t *expected = builder.GetBufferPointer();
  uint32_t expected_len = builder.GetSize();

  uint16_t id = var.GetId();

  auto req_builder = DebugProtocol::CreateGetVarRequest(
    builder,
    DebugProtocol::VarSubcmd::Get,
    id
  );
  builder.Finish(req_builder);
  uint8_t *req = builder.GetBufferPointer();
  uint32_t req_len = builder.GetSize();

  bool processed{false};
  Context context = {.request = req,
                     .request_length = req_len,
                     .response = nullptr,
                     .max_response_length = expected_len,
                     .response_length = 0,
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context));
  EXPECT_TRUE(processed);
  EXPECT_EQ(expected_len, context.response_length);

  for (size_t i = 0; i < expected_len; ++i) {
    EXPECT_EQ(context.response[i], expected[i]);
  }
}

TEST(VarHandler, SetVar) {
  uint32_t value = 0xDEADBEEF;
  DebugVar var("name", VarAccess::ReadWrite, &value, "units", "help");

  uint32_t new_value = 0xCAFEBABE;

  // Test that a SET command changes the variable's value.
  uint16_t id = var.GetId();

  flatbuffers::FlatBufferBuilder builder(1024);
  auto req_builder = DebugProtocol::CreateSetVarRequest(
    builder,
    DebugProtocol::VarSubcmd::Set,
    id,
    new_value
  );
  builder.Finish(req_builder);
  uint8_t *req = builder.GetBufferPointer();
  uint32_t req_len = builder.GetSize();

  bool processed{false};
  Context context = {.request = req,
                     .request_length = req_len,
                     .response = nullptr,
                     .max_response_length = 0,
                     .response_length = 0,
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context));
  EXPECT_TRUE(processed);
  EXPECT_EQ(0, context.response_length);


  EXPECT_EQ(new_value, value);
}

TEST(VarHandler, GetVarCount) {
  uint32_t value = 0xDEADBEEF;
  DebugVar dummy("name", VarAccess::ReadWrite, &value, "units");

  // Test that GetVarCount command obtains the number of defined variables
  flatbuffers::FlatBufferBuilder builder(1024);
  auto expected_builder = DebugProtocol::CreateGetVarCountResponse(
    builder,
    DebugVarBase::GetVarCount()
  );
  builder.Finish(expected_builder);
  uint8_t *expected = builder.GetBufferPointer();
  uint32_t expected_len = builder.GetSize();

  auto req_builder = DebugProtocol::CreateGetVarCountRequest(
    builder,
    DebugProtocol::VarSubcmd::GetCount
  );
  builder.Finish(req_builder);
  uint8_t *req = builder.GetBufferPointer();
  uint32_t req_len = builder.GetSize();

  bool processed{false};
  Context context = {.request = req,
                     .request_length = req_len,
                     .response = nullptr,
                     .max_response_length = expected_len,
                     .response_length = 0,
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context));
  EXPECT_TRUE(processed);
  EXPECT_EQ(20, context.response_length);

  for (size_t i = 0; i < expected_len; ++i) {
    EXPECT_EQ(context.response[i], expected[i]);
  }}

TEST(VarHandler, Errors) {
  uint32_t value = 0xDEADBEEF;
  DebugUInt32 var("name", VarAccess::ReadWrite, value, "units", "help");
  uint8_t id[2];
  u16_to_u8(var.GetId(), id);
  DebugUInt32 var_readonly("name", VarAccess::ReadOnly, value, "units", "help");
  uint8_t id_readonly[2];
  u16_to_u8(var_readonly.GetId(), id_readonly);

  std::vector<std::tuple<std::vector<uint8_t>, ErrorCode>> requests = {
      {{}, ErrorCode::MissingData},  // Missing subcommand
      {{4}, ErrorCode::InvalidData}, // Invalid subcommand
      {{0, 0xFF, 0xFF}, ErrorCode::UnknownVariable},
      {{1, 0xFF, 0xFF}, ErrorCode::UnknownVariable},
      {{2, 0xFF, 0xFF}, ErrorCode::UnknownVariable},
      {{0, 1}, ErrorCode::MissingData},
      {{1, 1}, ErrorCode::MissingData},
      {{2, 1}, ErrorCode::MissingData},
      {{0, id[0], id[1]}, ErrorCode::NoMemory},
      {{1, id[0], id[1]}, ErrorCode::NoMemory},
      {{3}, ErrorCode::NoMemory},
      {{2, id[0], id[1], 0xCA, 0xFE, 0x00}, ErrorCode::MissingData},
      {{2, id_readonly[0], id_readonly[1], 0xCA, 0xFE, 0x00, 0x00},
       ErrorCode::InternalError},
  };

  for (auto &[request, error] : requests) {
    // response size 3 to provoke No Memory error once all other checks are OK
    std::array<uint8_t, 3> response;
    bool processed{false};
    Context context = {.request = request.data(),
                       .request_length = static_cast<uint32_t>(request.size()),
                       .response = response.data(),
                       .max_response_length = response.size(),
                       .response_length = 0,
                       .processed = &processed};
    EXPECT_EQ(error, VarHandler().Process(&context));
    EXPECT_FALSE(processed);
    EXPECT_EQ(context.response_length, 0);
  }
}

} // namespace Debug::Command

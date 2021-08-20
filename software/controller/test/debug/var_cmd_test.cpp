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

#include <stdint.h>

#include <array>

#include "commands.h"
#include "gtest/gtest.h"
#include "vars.h"

namespace Debug::Command {

TEST(VarHandler, GetVarInfo) {
  uint32_t value = 0xDEADBEEF;
  const char *name = "name";
  const char *help = "help string";
  const char *format = "format";
  const char *unit = "unit";
  Debug::Variable::Primitive32 var(name, Debug::Variable::Access::ReadOnly, &value, unit, help, format);
  uint16_t id = var.id();

  flatbuffers::FlatBufferBuilder b;
  b.ForceDefaults(true);

  // expected result is hand-built from format given in var_cmd.cpp
  auto exp_builder = DebugFlatbuf::CreateGetVarInfo(
      b, static_cast<uint8_t>(Debug::Variable::Access::ReadOnly), b.CreateString("name"),
      b.CreateString("format"), b.CreateString("help string"),
      b.CreateString("unit"));
  b.Finish(exp_builder);
  uint8_t *exp = b.GetBufferPointer();
  uint32_t exp_size = b.GetSize();
  b.Clear();

  auto varaccess_builder = DebugFlatbuf::CreateVarAccessData(
      b, DebugFlatbuf::VarSubcmd::GetInfo, id);
  auto req_builder = DebugFlatbuf::CreateRequest(
      b, DebugFlatbuf::CmdCode::Variable, DebugFlatbuf::CmdData::VarAccessData,
      varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 50> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = exp_size + 1,
                     .processed = &processed};
  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);
  for (size_t i = 0; i < exp_size; i++) {
    EXPECT_EQ(context.response[i], exp[i]);
  }
}

TEST(VarHandler, GetVar) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::Primitive32 var("name", Debug::Variable::Access::ReadWrite, &value, "units",
                                   "help");
  uint16_t id = var.id();

  // Test that a GET command obtains the variable's value.
  flatbuffers::FlatBufferBuilder b;
  auto exp_builder = DebugFlatbuf::CreateInt(b, value);
  b.Finish(exp_builder);
  uint8_t *exp = b.GetBufferPointer();
  uint32_t exp_size = b.GetSize();
  b.Clear();

  auto varaccess_builder =
      DebugFlatbuf::CreateVarAccessData(b, DebugFlatbuf::VarSubcmd::Get, id);
  auto req_builder = DebugFlatbuf::CreateRequest(
      b, DebugFlatbuf::CmdCode::Variable, DebugFlatbuf::CmdData::VarAccessData,
      varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 4> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = exp_size,
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);

  for (size_t i = 0; i < exp_size; i++) {
    EXPECT_EQ(context.response[i], exp[i]);
  }
}

TEST(VarHandler, SetVar) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::Primitive32 var("name", Debug::Variable::Access::ReadWrite, &value, "units",
                                   "help");
  uint16_t id = var.id();

  uint32_t new_value = 0xCAFEBABE;

  // Test that a SET command changes the variable's value.
  flatbuffers::FlatBufferBuilder b;
  auto varaccess_builder = DebugFlatbuf::CreateVarAccessData(
      b, DebugFlatbuf::VarSubcmd::Set, id, new_value);
  auto req_builder = DebugFlatbuf::CreateRequest(
      b, DebugFlatbuf::CmdCode::Variable, DebugFlatbuf::CmdData::VarAccessData,
      varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 0> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = std::size(response),
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);
  EXPECT_EQ(0, context.response_length);

  EXPECT_EQ(new_value, value);
}

TEST(VarHandler, GetVarCount) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::Primitive32 dummy("name", Debug::Variable::Access::ReadWrite, &value, "units");

  // Test that GetVarCount command obtains the number of defined variables
  flatbuffers::FlatBufferBuilder b;
  auto exp_builder = DebugFlatbuf::CreateInt(b, VarHandler::Subcommand::GetCount);
  b.Finish(exp_builder);
  uint8_t *exp = b.GetBufferPointer();
  uint32_t exp_size = b.GetSize();
  b.Clear();

  auto varaccess_builder =
      DebugFlatbuf::CreateVarAccessData(b, DebugFlatbuf::VarSubcmd::GetCount);
  auto req_builder = DebugFlatbuf::CreateRequest(
      b, DebugFlatbuf::CmdCode::Variable, DebugFlatbuf::CmdData::VarAccessData,
      varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 4> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = exp_size,
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);

  for (size_t i = 0; i < exp_size; i++) {
    EXPECT_EQ(context.response[i], exp[i]);
  }
}
/*
TODO: Refactor error test with flatbuffer implementation
TEST(VarHandler, Errors) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::UInt32 var("name", Debug::Variable::Access::ReadWrite, value, "units", "help");
  uint8_t id[2];
  u16_to_u8(var.id(), id);
  Debug::Variable::UInt32 var_readonly("name", Debug::Variable::Access::ReadOnly, value, "units",
                                       "help");
  uint8_t id_readonly[2];
  u16_to_u8(var_readonly.id(), id_readonly);

  std::vector<std::tuple<std::vector<uint8_t>, ErrorCode>> requests = {
      {{}, ErrorCode::MissingData},   // Missing subcommand
      {{4}, ErrorCode::InvalidData},  // Invalid subcommand
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
      {{2, id_readonly[0], id_readonly[1], 0xCA, 0xFE, 0x00, 0x00}, ErrorCode::InternalError},
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
*/
} // namespace Debug::Command

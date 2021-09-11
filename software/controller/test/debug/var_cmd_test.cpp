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
  Debug::Variable::Primitive32 var(name, DebugFB::VarAccess::ReadOnly, &value, unit, help, format);
  uint16_t id = var.id();

  flatbuffers::FlatBufferBuilder b;
  b.ForceDefaults(true);

  auto varaccess_builder = DebugFB::CreateVarAccessData(b, DebugFB::VarSubcmd::GetInfo, id);
  auto req_builder = DebugFB::CreateRequest(
      b, DebugFB::CmdCode::Variable, DebugFB::CmdData::VarAccessData, varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 100> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = std::size(response),
                     .processed = &processed};
  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);

  const DebugFB::GetVarInfoResponse *res =
      flatbuffers::GetRoot<DebugFB::GetVarInfoResponse>(response.data());
  EXPECT_EQ(res->name()->c_str(), name);
  EXPECT_EQ(res->help()->c_str(), help);
  EXPECT_EQ(res->fmt()->c_str(), format);
  EXPECT_EQ(res->unit()->c_str(), unit);
}

TEST(VarHandler, GetVar) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::Primitive32 var("name", DebugFB::VarAccess::ReadWrite, &value, "units", "help");
  uint16_t id = var.id();

  // Test that a GET command obtains the variable's value.
  flatbuffers::FlatBufferBuilder b;
  b.ForceDefaults(true);

  auto varaccess_builder = DebugFB::CreateVarAccessData(b, DebugFB::VarSubcmd::Get, id);
  auto req_builder = DebugFB::CreateRequest(
      b, DebugFB::CmdCode::Variable, DebugFB::CmdData::VarAccessData, varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 100> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = std::size(response),
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);

  const DebugFB::UInt *res = flatbuffers::GetRoot<DebugFB::UInt>(response.data());
  EXPECT_EQ(res->val(), value);
}

TEST(VarHandler, SetVar) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::Primitive32 var("name", DebugFB::VarAccess::ReadWrite, &value, "units", "help");
  uint16_t id = var.id();

  uint32_t new_value = 0xCAFEBABE;

  // Test that a SET command changes the variable's value.
  flatbuffers::FlatBufferBuilder b;
  auto varaccess_builder_set =
      DebugFB::CreateVarAccessData(b, DebugFB::VarSubcmd::Set, id, new_value);
  auto req_builder =
      DebugFB::CreateRequest(b, DebugFB::CmdCode::Variable, DebugFB::CmdData::VarAccessData,
                             varaccess_builder_set.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 0> response_set;
  bool processed{false};
  Context context_set = {.request = req,
                         .response = response_set.data(),
                         .max_response_length = std::size(response_set),
                         .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context_set, b));
  EXPECT_TRUE(processed);
  EXPECT_EQ(0, context_set.response_length);

  // Use Get to check if the value was correctly updated
  auto varaccess_builder_get = DebugFB::CreateVarAccessData(b, DebugFB::VarSubcmd::Get, id);
  auto req_builder_get =
      DebugFB::CreateRequest(b, DebugFB::CmdCode::Variable, DebugFB::CmdData::VarAccessData,
                             varaccess_builder_get.Union());
  b.Finish(req_builder_get);
  req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 100> response_get;
  processed = false;
  Context context_get = {.request = req,
                         .response = response_get.data(),
                         .max_response_length = std::size(response_get),
                         .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context_get, b));
  EXPECT_TRUE(processed);

  const DebugFB::UInt *res = flatbuffers::GetRoot<DebugFB::UInt>(response_get.data());
  EXPECT_EQ(res->val(), new_value);
}

TEST(VarHandler, GetVarCount) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::Primitive32 dummy("name", DebugFB::VarAccess::ReadWrite, &value, "units");

  // Test that GetVarCount command obtains the number of defined variables
  flatbuffers::FlatBufferBuilder b;
  auto varaccess_builder = DebugFB::CreateVarAccessData(b, DebugFB::VarSubcmd::GetCount);
  auto req_builder = DebugFB::CreateRequest(
      b, DebugFB::CmdCode::Variable, DebugFB::CmdData::VarAccessData, varaccess_builder.Union());
  b.Finish(req_builder);
  uint8_t *req = b.GetBufferPointer();
  b.Clear();

  std::array<uint8_t, 100> response;
  bool processed{false};
  Context context = {.request = req,
                     .response = response.data(),
                     .max_response_length = std::size(response),
                     .processed = &processed};

  EXPECT_EQ(ErrorCode::None, VarHandler().Process(&context, b));
  EXPECT_TRUE(processed);

  const DebugFB::UInt *res = flatbuffers::GetRoot<DebugFB::UInt>(response.data());
  EXPECT_EQ(res->val(), Debug::Variable::Registry::singleton().count());
}
/*
TODO: Refactor error test with flatbuffer implementation
TEST(VarHandler, Errors) {
  uint32_t value = 0xDEADBEEF;
  Debug::Variable::UInt32 var("name", DebugFB::VarAccess::ReadWrite, value, "units", "help");
  uint8_t id[2];
  u16_to_u8(var.id(), id);
  Debug::Variable::UInt32 var_readonly("name", DebugFB::VarAccess::ReadOnly, value, "units",
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
}  // namespace Debug::Command

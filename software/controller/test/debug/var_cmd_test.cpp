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
      builder, static_cast<uint8_t>(VarType::UInt32),
      static_cast<uint8_t>(VarAccess::ReadOnly), 0,
      static_cast<uint8_t>(strlen(name)), static_cast<uint8_t>(strlen(format)),
      static_cast<uint8_t>(strlen(help)), static_cast<uint8_t>(strlen(unit)),
      builder.CreateString(name), builder.CreateString(format),
      builder.CreateString(help), builder.CreateString(unit));
  builder.Finish(expected_builder);
  uint8_t *expected = builder.GetBufferPointer();
  uint32_t expected_len = builder.GetSize();

  uint16_t id = var.GetId();
  DebugProtocol::GetVarRequest cmddata = DebugProtocol::GetVarRequest(id);
  auto cmddata_ = builder.CreateStruct(cmddata);

  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable,
      DebugProtocol::VarSubcmd::GetInfo,
      DebugProtocol::VarRequest::GetVarRequest, cmddata_.Union());
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
  auto expected_builder = DebugProtocol::CreateGetVarResponse(builder, value);
  builder.Finish(expected_builder);
  uint8_t *expected = builder.GetBufferPointer();
  uint32_t expected_len = builder.GetSize();

  uint16_t id = var.GetId();
  DebugProtocol::GetVarRequest cmddata = DebugProtocol::GetVarRequest(id);
  auto cmddata_ = builder.CreateStruct(cmddata);

  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable, DebugProtocol::VarSubcmd::Get,
      DebugProtocol::VarRequest::GetVarRequest, cmddata_.Union());
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

// Tests SetVar
TEST(VarHandler, SetVar) {
  uint32_t value = 0xDEADBEEF;
  DebugVar var("name", VarAccess::ReadWrite, &value, "units", "help");

  uint32_t new_value = 0xCAFEBABE;

  // Test that a SET command changes the variable's value.
  uint16_t id = var.GetId();

  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::SetVarRequest cmddata =
      DebugProtocol::SetVarRequest(id, new_value);
  auto cmddata_ = builder.CreateStruct(cmddata);

  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable, DebugProtocol::VarSubcmd::Set,
      DebugProtocol::VarRequest::SetVarRequest, cmddata_.Union());
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

// Tests GetVarCount
TEST(VarHandler, GetVarCount) {
  uint32_t value = 0xDEADBEEF;
  DebugVar dummy("name", VarAccess::ReadWrite, &value, "units");

  // Test that GetVarCount command obtains the number of defined variables
  flatbuffers::FlatBufferBuilder builder(1024);
  auto expected_builder = DebugProtocol::CreateGetVarCountResponse(
      builder, DebugVarBase::GetVarCount());
  builder.Finish(expected_builder);
  uint8_t *expected = builder.GetBufferPointer();
  uint32_t expected_len = builder.GetSize();

  auto req_builder =
      DebugProtocol::CreateRequest(builder, DebugProtocol::CmdCode::Variable,
                                   DebugProtocol::VarSubcmd::GetCount);
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
  }
}

// Tests a request with no subcommand
TEST(VarHandler, MissingSubcmd) {
  flatbuffers::FlatBufferBuilder builder(1024);
  auto req_builder = DebugProtocol::CreateRequest(builder);
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
  EXPECT_EQ(ErrorCode::MissingData, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests GetVarInfo with an unknown variable
TEST(VarHandler, GetInfoUnknownVariable) {
  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::GetVarRequest cmddata = DebugProtocol::GetVarRequest(0xFF);
  auto cmddata_ = builder.CreateStruct(cmddata);
  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable,
      DebugProtocol::VarSubcmd::GetInfo,
      DebugProtocol::VarRequest::GetVarRequest, cmddata_.Union());
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
  EXPECT_EQ(ErrorCode::UnknownVariable, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests GetVar with an unknown variable
TEST(VarHandler, GetUnknownVariable) {
  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::GetVarRequest cmddata = DebugProtocol::GetVarRequest(0xFF);
  auto cmddata_ = builder.CreateStruct(cmddata);
  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable, DebugProtocol::VarSubcmd::Get,
      DebugProtocol::VarRequest::GetVarRequest, cmddata_.Union());
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
  EXPECT_EQ(ErrorCode::UnknownVariable, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests SetVar with an unknown variable
TEST(VarHandler, SetUnknownVariable) {
  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::SetVarRequest cmddata =
      DebugProtocol::SetVarRequest(0xFF, 0xFF);
  auto cmddata_ = builder.CreateStruct(cmddata);
  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable, DebugProtocol::VarSubcmd::Set,
      DebugProtocol::VarRequest::SetVarRequest, cmddata_.Union());
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
  EXPECT_EQ(ErrorCode::UnknownVariable, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests GetVarInfo when response doesn't have enough memory
TEST(VarHandler, GetVarInfoNoMemory) {
  uint32_t value = 0xDEADBEEF;
  DebugUInt32 var("name", VarAccess::ReadWrite, value, "units", "help");
  uint16_t id = var.GetId();

  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::GetVarRequest cmddata = DebugProtocol::GetVarRequest(id);
  auto cmddata_ = builder.CreateStruct(cmddata);
  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable,
      DebugProtocol::VarSubcmd::GetInfo,
      DebugProtocol::VarRequest::GetVarRequest, cmddata_.Union());
  builder.Finish(req_builder);
  uint8_t *req = builder.GetBufferPointer();
  uint32_t req_len = builder.GetSize();

  bool processed{false};
  Context context = {.request = req,
                     .request_length = req_len,
                     .response = nullptr,
                     .max_response_length =
                         0, // TODO: Choose an appropriate length
                     .response_length = 0,
                     .processed = &processed};
  EXPECT_EQ(ErrorCode::NoMemory, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests GetVar when response doesn't have enough memory
TEST(VarHandler, GetVarNoMemory) {
  uint32_t value = 0xDEADBEEF;
  DebugUInt32 var("name", VarAccess::ReadWrite, value, "units", "help");
  uint16_t id = var.GetId();

  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::GetVarRequest cmddata = DebugProtocol::GetVarRequest(id);
  auto cmddata_ = builder.CreateStruct(cmddata);
  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable, DebugProtocol::VarSubcmd::Get,
      DebugProtocol::VarRequest::GetVarRequest, cmddata_.Union());
  builder.Finish(req_builder);
  uint8_t *req = builder.GetBufferPointer();
  uint32_t req_len = builder.GetSize();

  bool processed{false};
  Context context = {.request = req,
                     .request_length = req_len,
                     .response = nullptr,
                     .max_response_length =
                         0, // TODO: Choose an appropriate length
                     .response_length = 0,
                     .processed = &processed};
  EXPECT_EQ(ErrorCode::NoMemory, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests GetVarCount when response doesn't have enough memory
TEST(VarHandler, GetVarCountNoMemory) {
  uint32_t value = 0xDEADBEEF;
  DebugUInt32 var("name", VarAccess::ReadWrite, value, "units", "help");
  DebugUInt32 var_readonly("name", VarAccess::ReadOnly, value, "units", "help");

  flatbuffers::FlatBufferBuilder builder(1024);
  auto req_builder =
      DebugProtocol::CreateRequest(builder, DebugProtocol::CmdCode::Variable,
                                   DebugProtocol::VarSubcmd::GetCount);
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

  EXPECT_EQ(ErrorCode::NoMemory, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// Tests SetVar on a readonly variable
TEST(VarHandler, VarReadOnly) {
  uint32_t value = 0xDEADBEEF;
  DebugUInt32 var_readonly("name", VarAccess::ReadOnly, value, "units", "help");
  uint16_t id_readonly = var_readonly.GetId();

  flatbuffers::FlatBufferBuilder builder(1024);
  DebugProtocol::SetVarRequest cmddata =
      DebugProtocol::SetVarRequest(id_readonly, 0xFF);
  auto cmddata_ = builder.CreateStruct(cmddata);
  auto req_builder = DebugProtocol::CreateRequest(
      builder, DebugProtocol::CmdCode::Variable, DebugProtocol::VarSubcmd::Set,
      DebugProtocol::VarRequest::SetVarRequest, cmddata_.Union());
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

  EXPECT_EQ(ErrorCode::InternalError, VarHandler().Process(&context));
  EXPECT_FALSE(processed);
  EXPECT_EQ(context.response_length, 0);
}

// NOTE 1: The SetVarRequest buffer object has a 32-bit unsigned int storing the
// 32-bit set value, receiving fewer than 4 bytes is an invalid case. NOTE 2:
// Since we're using a DebugProtocol::VarSubcmd enum instead of raw subcommand
// codes, an invalid subcommand is not a valid case

} // namespace Debug::Command

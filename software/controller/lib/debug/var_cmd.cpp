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
#include <stdint.h>
#include <string.h>

namespace Debug::Command {

ErrorCode VarHandler::Process(Context *context) {

  // The subcommand is required
  // A VarRequest with a subcommand and ID takes 20 bits 
  if (context->request_length < 20)
    return ErrorCode::MissingData;

  DebugProtocol::VarSubcmd subcommand{flatbuffers::GetRoot<DebugProtocol::VarRequest>(context->request)->subcmd()};

  switch (subcommand) {
  // Return info about one of the variables.
  case DebugProtocol::VarSubcmd::GetInfo:
    return GetVarInfo(context);

  case DebugProtocol::VarSubcmd::Get:
    return GetVar(context);

  case DebugProtocol::VarSubcmd::Set:
    return SetVar(context);

  case DebugProtocol::VarSubcmd::GetCount:
    return GetVarCount(context);

  default:
    return ErrorCode::InvalidData;
  }
}

// Return info about one of the variables.
// The 16-bit variable ID is passed in.  These IDs are
// automatically assigned as variables are registered in the
// system starting with 0.  The Python code can read them
// all out until it gets an error code indicating that the
// passed ID is invalid.
ErrorCode VarHandler::GetVarInfo(Context *context) {

  // We expect a 16-bit ID to be passed
  // A GetVarRequest with a subcommand and ID takes 20 bits 
  if (context->request_length < 24)
    return ErrorCode::MissingData;

  auto context_req = flatbuffers::GetRoot<DebugProtocol::VarRequest>(context->request);
  auto cmddata = context_req->request_as_GetVarRequest();

  uint16_t var_id = cmddata->vid();

  const auto *var = DebugVar::FindVar(var_id);
  if (!var)
    return ErrorCode::UnknownVariable;

  // The info I return consists of the following:
  // <type> - 1 byte variable type code
  // <access> - 1 byte gives the possible access to that variable (read only?)
  // <reserved> - 2 reserved bytes for things we think of later
  // <name len> - 1 byte gives length of variable name string
  // <fmt len>  - 1 byte gives length of formation string
  // <help len> - 1 byte gives length of help string
  // <unit len> - 1 byte gives length of unit string
  // <name> - variable length name string
  // <fmt>  - variable length format string
  // <help> - variable length help string
  // <unit> - variable length unit string
  // The strings are not null terminated.
  size_t name_length = strlen(var->GetName());
  size_t format_length = strlen(var->GetFormat());
  size_t help_length = strlen(var->GetHelp());
  size_t unit_length = strlen(var->GetUnits());

  // Fail if the strings are too large to fit.
  if (context->max_response_length <
      8 + name_length + format_length + help_length + unit_length)
    return ErrorCode::NoMemory;

  flatbuffers::FlatBufferBuilder builder(1024);
  auto res_builder = DebugProtocol::CreateGetVarInfoResponse(
    builder,
    static_cast<uint8_t>(var->GetType()),
    static_cast<uint8_t>(var->GetAccess()),
    0,
    static_cast<uint8_t>(name_length),
    static_cast<uint8_t>(format_length),
    static_cast<uint8_t>(help_length),
    static_cast<uint8_t>(unit_length),
    builder.CreateString(var->GetName()),
    builder.CreateString(var->GetFormat()),
    builder.CreateString(var->GetHelp()),
    builder.CreateString(var->GetUnits())
  );
  builder.Finish(res_builder);
  uint8_t *res = builder.GetBufferPointer();
  uint32_t res_len = builder.GetSize();

  context->response = res;
  context->response_length = res_len;
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode VarHandler::GetVar(Context *context) {
  // We expect a 16-bit ID to be passed
  // A GetVarRequest with a subcommand and ID takes 20 bits 
  if (context->request_length < 20)
    return ErrorCode::MissingData;

  auto context_req = flatbuffers::GetRoot<DebugProtocol::VarRequest>(context->request);
  auto cmddata = context_req->request_as_GetVarRequest();
  uint16_t var_id = cmddata->vid();

  auto *var = DebugVar::FindVar(var_id);
  if (!var)
    return ErrorCode::UnknownVariable;

  if (context->max_response_length < 20)
    return ErrorCode::NoMemory;

  flatbuffers::FlatBufferBuilder builder(1024);
  auto res_builder = DebugProtocol::CreateGetVarResponse(
    builder,
    var->GetValue()
  );
  builder.Finish(res_builder);
  uint8_t *res = builder.GetBufferPointer();
  uint32_t res_len = builder.GetSize();

  context->response = res;
  context->response_length = res_len;
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode VarHandler::SetVar(Context *context) {
  // We expect a 16-bit ID to be passed
  // A SetVarRequest with a subcommand, ID, and value takes 28 bits 
  if (context->request_length < 28)
    return ErrorCode::MissingData;

  auto context_req = flatbuffers::GetRoot<DebugProtocol::VarRequest>(context->request);
  auto cmddata = context_req->request_as_SetVarRequest();
  uint16_t var_id = cmddata->vid();

  auto *var = DebugVar::FindVar(var_id);
  if (!var)
    return ErrorCode::UnknownVariable;

  if (!var->WriteAllowed())
    return ErrorCode::InternalError;

  var->SetValue(cmddata->value());
  context->response_length = 0;
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode VarHandler::GetVarCount(Context *context) {
  if (context->max_response_length < 20)
    return ErrorCode::NoMemory;

  flatbuffers::FlatBufferBuilder builder(1024);
  auto res_builder = DebugProtocol::CreateGetVarCountResponse(
    builder,
    DebugVarBase::GetVarCount()
  );
  builder.Finish(res_builder);
  uint8_t *res = builder.GetBufferPointer();
  uint32_t res_len = builder.GetSize();

  context->response = res;
  context->response_length = res_len;
  *(context->processed) = true;
  return ErrorCode::None;
}

} // namespace Debug::Command

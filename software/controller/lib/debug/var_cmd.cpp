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
#include <string.h>

#include "commands.h"
#include "vars.h"

namespace Debug::Command {

ErrorCode VarHandler::Process(Context *context, flatbuffers::FlatBufferBuilder &b) {
  const DebugFB::Request *req{flatbuffers::GetRoot<DebugFB::Request>(context->request)};
  const DebugFB::VarAccessData *cmddata{req->cmddata_as_VarAccessData()};

  // We expect a sub-command.
  if (!flatbuffers::IsFieldPresent(cmddata, DebugFB::VarAccessData::VT_SUBCMD))
    return ErrorCode::MissingData;

  DebugFB::VarSubcmd subcommand{cmddata->subcmd()};

  switch (subcommand) {
    // Return info about one of the variables.
    case DebugFB::VarSubcmd::GetInfo:
      return GetVarInfo(context, b);

    case DebugFB::VarSubcmd::Get:
      return GetVar(context, b);

    case DebugFB::VarSubcmd::Set:
      return SetVar(context, b);

    case DebugFB::VarSubcmd::GetCount:
      return GetVarCount(context, b);

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
ErrorCode VarHandler::GetVarInfo(Context *context, flatbuffers::FlatBufferBuilder &b) {
  const DebugFB::Request *req{flatbuffers::GetRoot<DebugFB::Request>(context->request)};
  const DebugFB::VarAccessData *cmddata{req->cmddata_as_VarAccessData()};

  // We expect a 16-bit ID to be passed
  if (!flatbuffers::IsFieldPresent(cmddata, DebugFB::VarAccessData::VT_VID))
    return ErrorCode::MissingData;

  uint16_t var_id{cmddata->vid()};

  const auto *var = Variable::Registry::singleton().find(var_id);
  if (!var) return ErrorCode::UnknownVariable;

  // The info I return consists of the following:
  // <type> - 1 byte variable type code
  // <access> - 1 byte gives the possible access to that variable (read only?)
  // <reserved> - 2 reserved bytes for things we think of later
  // <name> - variable length name string
  // <fmt>  - variable length format string
  // <help> - variable length help string
  // <unit> - variable length unit string
  // The strings are not null terminated.

  auto res = DebugFB::CreateGetVarInfoResponse(
      b, var->type(), var->access(), b.CreateString(var->name()), b.CreateString(var->format()),
      b.CreateString(var->help()), b.CreateString(var->units()));
  b.Finish(res);
  uint8_t *buff = b.GetBufferPointer();
  uint32_t buff_size = b.GetSize();
  b.Clear();

  // Fail if the strings are too large to fit.
  if (context->max_response_length < buff_size) return ErrorCode::NoMemory;

  memcpy(context->response, buff, buff_size);
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode VarHandler::GetVar(Context *context, flatbuffers::FlatBufferBuilder &b) {
  const DebugFB::Request *req{flatbuffers::GetRoot<DebugFB::Request>(context->request)};
  const DebugFB::VarAccessData *cmddata{req->cmddata_as_VarAccessData()};

  // We expect a 16-bit ID to be passed
  if (!flatbuffers::IsFieldPresent(cmddata, DebugFB::VarAccessData::VT_VID))
    return ErrorCode::MissingData;

  uint16_t var_id{cmddata->vid()};

  auto *var = Variable::Registry::singleton().find(var_id);
  if (!var) return ErrorCode::UnknownVariable;

  auto res = DebugFB::CreateUInt(b, var->get_value());
  b.Finish(res);
  uint8_t *buff = b.GetBufferPointer();
  uint32_t buff_size = b.GetSize();

  // Fail if the strings are too large to fit.
  if (context->max_response_length < buff_size) return ErrorCode::NoMemory;

  memcpy(context->response, buff, buff_size);
  context->response_length = buff_size;
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode VarHandler::SetVar(Context *context, flatbuffers::FlatBufferBuilder &b) {
  const DebugFB::Request *req{flatbuffers::GetRoot<DebugFB::Request>(context->request)};
  const DebugFB::VarAccessData *cmddata{req->cmddata_as_VarAccessData()};

  // We expect a 16-bit ID to be passed
  if (!flatbuffers::IsFieldPresent(cmddata, DebugFB::VarAccessData::VT_VID))
    return ErrorCode::MissingData;

  uint16_t var_id{cmddata->vid()};

  auto *var = Variable::Registry::singleton().find(var_id);
  if (!var) return ErrorCode::UnknownVariable;

  // We expect a value to write to the variable
  if (!flatbuffers::IsFieldPresent(cmddata, DebugFB::VarAccessData::VT_VAL))
    return ErrorCode::MissingData;

  if (!var->write_allowed()) return ErrorCode::InternalError;

  var->set_value(cmddata->val());
  *(context->processed) = true;
  return ErrorCode::None;
}

ErrorCode VarHandler::GetVarCount(Context *context, flatbuffers::FlatBufferBuilder &b) {
  auto res = DebugFB::CreateUInt(b, Debug::Variable::Registry::singleton().count());
  b.Finish(res);
  uint8_t *buff = b.GetBufferPointer();
  uint32_t buff_size = b.GetSize();
  b.Clear();

  if (context->max_response_length < buff_size) return ErrorCode::NoMemory;

  memcpy(context->response, buff, buff_size);
  *(context->processed) = true;
  return ErrorCode::None;
}

}  // namespace Debug::Command

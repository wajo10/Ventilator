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

#pragma once

#include <stdint.h>

#include "network_protocol.pb.h"

// This module periodically sends messages to the GUI device and receives
// messages from the GUI.  The only way it communicates with other modules is
// by modifying the gui_status pointer in CommsHandler.

void CommsInit();

// `controller_status` should be the controller's current status.  It's sent
// periodically to the GUI.  When we receive a message from the GUI, we update
// gui_status accordingly.
void CommsHandler(const ControllerStatus &controller_status, GuiStatus *gui_status);

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

// \TODO: abstract this better so we don't have to expose registers

#pragma once

/******************************************************************
 * Serial port to GUI
 * [RM] Chapter 38 defines the USART registers.
 *****************************************************************/

#include "circular_buffer.h"
#include "uart_regs.h"

class UART {
 public:
  explicit UART(UartReg *r);

  void Init(uint32_t cpu_frequency_hz, uint32_t baud);

  // This is the interrupt handler for the UART.
  void ISR();

  // Read up to len bytes and store them in the passed buffer.
  // This function does not block, so if less then len bytes
  // are available it will only return the available bytes
  // Returns the number of bytes actually read.
  uint16_t Read(char *buf, uint16_t len);

  // Write up to len bytes to the buffer.
  // This function does not block, so if there isn't enough
  // space to write len bytes, then only a partial write
  // will occur.
  // The number of bytes actually written is returned.
  uint16_t Write(const char *buf, uint16_t len);

  // Return the number of bytes currently in the
  // receive buffer and ready to be read.
  uint16_t RxFull();

  // Returns the number of free locations in the
  // transmit buffer.
  uint16_t TxFree();

 private:
  CircularBuffer<uint8_t, 128> rx_data_;
  CircularBuffer<uint8_t, 128> tx_data_;
  UartReg *const uart_;
};

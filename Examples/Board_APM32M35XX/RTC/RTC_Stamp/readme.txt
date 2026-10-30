/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.0
 *
 * @date        2024-05-30
 *
 * @attention
 *
 *  Copyright (C) 2024 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

&par Example Description

This example shows how to write/read data to/from RTC Backup data registers and
demonstrates the Tamper detection feature.

The associated firmware performs the following:
1. It configures the Tamper pin to be falling edge, and enables the Tamper interrupt.
2. It writes the data to all RTC Backup data registers
3. On applying a low level on the RTC_AF1 pin (PC.13, connected to Tamper button),
   the RTC backup data registers are reset and the Tamper interrupt is generated.

 phenomenon :
  - If Tamper1 interrupt happen, LED2 is on
  - If Tamper2 interrupt happen, LED3 is on
  - Time and Backup data are displayed in serial assistant.

The USART1 is configured as follows:
    - TX:PA9, RX:PA10
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

&par Hardware Description
  - Close J2 and J3
  - Close J6 and J8

&par Directory contents

  - RTC/RTC_Stamp/Source/apm32m35xx_int.c             Interrupt handlers
  - RTC/RTC_Stamp/Source/main.c                      Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

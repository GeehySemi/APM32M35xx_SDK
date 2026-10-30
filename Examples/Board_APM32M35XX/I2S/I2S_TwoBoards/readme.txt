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

This example provides a small application in which system sends and receives data by polling
though using I2S firmware library. All received information will be displayed by serial assistant.

To use this example, you need to load it on two APM32M35XX boards (let's call them Board master
and Board slave). Then connect these two boards through I2S lines and must master and slave connect
to the same GND.

After the program is downloaded, please reset the motherboard and then reset the slave.When compare
buffer is the same, the Board slave LED2 is on.The phenomenon of data interaction process can be
displayed using serial assistant.

The USART1 is configured as follows:
  - TX:PA9, RX:PA10
  - BaudRate = 115200 baud
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Hardware Description

             Master      Slave
  - WS        PA4         PA4
  - CK        PA5         PA5
  - SD        PA7         PA7

  - Open J12
  - Close J2 and J3
  - Close J6 and J8

&par Directory contents

  - I2S/I2S_TwoBoards/I2S_TwoBoards_Slave/Source/apm32m35xx_int.c          Interrupt handlers
  - I2S/I2S_TwoBoards/I2S_TwoBoards_Slave/Source/main.c                   Main program
  - I2S/I2S_TwoBoards/I2S_TwoBoards_Master/Source/apm32m35xx_int.c         Interrupt handlers
  - I2S/I2S_TwoBoards/I2S_TwoBoards_Master/Source/main.c                  Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

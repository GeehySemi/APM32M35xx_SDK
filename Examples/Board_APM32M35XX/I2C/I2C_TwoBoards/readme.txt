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

This example shows how to control I2C devices and communicate between two different boards.

To use this example, you need to load the same software into two APM32M35XX boards(let's call
them  Board master and Board Slave) then connect these two boards through I2C lines and GND.

 - At startup, Boards master and slave are both in slave receiver mode and wait for messages
   to be received.
 - When KEY1 is pressed on Board master, the master transmitter sents "Hello master" to Board slave.
   The message is displayed on serial assistant through USART1.
 - When KEY1 is pressed on Board slave, the slave transmitter sents "Hello master" to Board master.
   The message is displayed on serial assistant through USART1.

The USART1 is configured as follows:
    - TX:PA9, RX:PA10
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

&par Hardware Description

      I2C     BOARD1    BOARD2
    - SCL      PB8       PB8     (External Pull up resistance)
    - SDA      PB9       PB9     (External Pull up resistance)

    - Open J14 and J16
    - Close J2 and J3
    - Close J6 and J8

&par Directory contents

  - I2C/I2C_TwoBoards/I2C_TwoBoards_Master/Source/apm32m35xx_int.c      Interrupt handlers
  - I2C/I2C_TwoBoards/I2C_TwoBoards_Master/Source/main.c               Main program
  - I2C/I2C_TwoBoards/I2C_TwoBoards_Slave/Source/apm32m35xx_int.c       Interrupt handlers
  - I2C/I2C_TwoBoards/I2C_TwoBoards_Slave/Source/main.c                Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

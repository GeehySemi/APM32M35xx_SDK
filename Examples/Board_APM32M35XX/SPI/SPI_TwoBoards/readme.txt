·/*!
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
though using SPI firmware library. All received information will be displayed by serial assistant.

To use this example, you need to load it on two APM32M35XX boards (let's call
them Board master and Board slave). Then connect these two boards through SPI lines and
must master and slave connect to the same GND.
When compare buffer is the same, the LED2 is on.
The phenomenon of data interaction process can be displayed using serial assistant.

                Master       Slave
    CLK           PA5         PA5
    NSS           PA4         PA4
    MISO          PA6         PA6
    MOSI          PA7         PA7
  - Close J2 and J3
  - Close J6 and J8

  - USART1（TX:PA9、RX:PA10） configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - SPI/SPI_TwoBoards/slave/Source/apm32m35xx_int.c       Interrupt handlers
  - SPI/SPI_TwoBoards/slave/Source/main.c                     Main program
  - SPI/SPI_TwoBoards/master/Source/apm32m35xx_int.c    Interrupt handlers
  - SPI/SPI_TwoBoards/master/Source/main.c                  Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

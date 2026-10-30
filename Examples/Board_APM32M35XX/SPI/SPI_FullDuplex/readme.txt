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

This demo is based on the APM32M35XX board, it shows how to use SPI peripheral.
by making a master/slave full duplex communication between the SPI and the UART2.
The phenomenon of serial assistant can display information from USART1.

Connect UART1 and SPI pins as follows:
  UART2 TX    (PA2)   to SPI MOSI (PA7)
  UART2 RX    (PA3)   to SPI MISO (PA6)
  UART2 CLK   (PA4)   to SPI SCK  (PA5)
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

  - SPI/SPI_FullDuplex/Source/apm32m35xx_int.c       Interrupt handlers
  - SPI/SPI_FullDuplex/Source/main.c                     Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

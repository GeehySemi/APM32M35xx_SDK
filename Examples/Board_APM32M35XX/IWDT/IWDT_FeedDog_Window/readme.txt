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

The example aims to show how to update the IWDG reload counter at special window period
After IWDT initializes, System enters into infinite loop and resets when feeding dog not in
window period.In the same time ,System will output information to serial assistant to display
system status.
  The IWDG counter is refreshed in the eint interrupt when press the KEY1 in window value to
prevent a IWDG reset.
  - EXTI Line1(KEY1)

  - USART1（Tx：PA9，Rx：PA10） configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

  - Close J2 and J3
  - Close J6 and J8

&par Directory contents

  - IWDT/IWDT_FeedDog_Window/Source/apm32m35xx_int.c     Interrupt handlers
  - IWDT/IWDT_FeedDog_Window/Source/main.c                      Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

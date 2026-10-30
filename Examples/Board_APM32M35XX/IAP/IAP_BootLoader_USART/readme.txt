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

The example aim to show how to configure a bootloader firmware to IAP.
When device connets to HyperTerminal right, a usart menu will show to user.
The menu as follow:

***************************************************************
*      APM32M35XX In-Application Programming Application       *
*                                              (Version 1.0.0)*
***************************************************************

** Please select an operation item
*  1.Download Flash application 1 -----------------------> 1  *
*  2.Upload Flash application 1   -----------------------> 2  *
*  3.Jump to user application 1   -----------------------> 3  *
*  4.Download Flash application 2 -----------------------> 4  *
*  5.Upload Flash application 2   -----------------------> 5  *
*  6.Jump to user application 2   -----------------------> 6  *
***************************************************************

&par Hardware Description

  - USART1 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Hardware Description
  - Close J2
  - Open J3
  - Close J6 and J8

&par Directory contents

  - IAP/IAP_BootLoader_USART/Source/apm32m35xx_int.c        Interrupt handlers
  - IAP/IAP_BootLoader_USART/Source/main.c                      Main program
  - IAP/IAP_BootLoader_USART/Source/bsp_usart.c            USART Configuration
  - IAP/IAP_BootLoader_USART/Source/bsp_flash.c            Flash handlers
  - IAP/IAP_BootLoader_USART/Source/common.c               Common functions
  - IAP/IAP_BootLoader_USART/Source/menu.c                 UART Menu
  - IAP/IAP_BootLoader_USART/Source/ymodem.c               Ymodem protocol handlers

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

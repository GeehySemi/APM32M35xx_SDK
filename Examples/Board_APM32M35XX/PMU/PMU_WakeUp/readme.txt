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

This example shows how to enter the system by external interrupt to
  - STANDBY mode and wake-up from this mode either with the RESET or give PC13 a rising edge to recover.
  - SLEEP mode and wake-up from this mode either with the RESET or give PA6 a falling edge to recover.
  - STOP mode and wake-up from this mode with the RESET.

phenomenon :
  - If press KEY1(SLEEP mode): LED2 is on ,while LED3 remain in the previous state.
     After giving PA6 a falling edge ,system running from reset state.
  - If press KET2(STANDBY mode): LED2 and LED3 are off. After giving PC13 a rising edge,system continue running.
  - If low down PA7(STOP  mode): LED2 and LED3 remain in the previous state. After reset, system recover to normal state.

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

  - PMU/PMU/Source/apm32m35xx_int.c              Interrupt handlers
  - PMU/PMU/Source/main.c                       Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

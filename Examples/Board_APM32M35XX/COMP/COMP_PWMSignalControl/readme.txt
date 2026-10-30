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

This example shows how to use the comparator. COMP2 non-inverting input connect
to PA5. And COMP2 inverting input is internally connected to VREFINT(1.22V) which is
used to compare with PA5 input.

  - External voltage should be connected to PA5.

  - Connect an oscilloscope to TMR1 channel PA8 to display waveform.

  - While PA5 is lower than VREFINT (1.22V), PWM signal is displayed on PA8.
   -While PA5 is higher than VREFINT, PA8 is in high level.

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

  - COMP/COMP_PWMSignalControl/Source/apm32m35xx_int.c          Interrupt handlers
  - COMP/COMP_PWMSignalControl/Source/main.c                   Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

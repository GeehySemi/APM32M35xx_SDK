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

This example shows how to use M0CP peripheral to complete CORDIC rotate operation.
Press KEY1 to start test. If operation is done,USART1 peripheral will print information.

The input of Z data range : [-32768, 32767],the real angel = 180*Z/32768
X,Y is the amplitude for Z, the range is : [-32768, 32767].
The data of X,Y should be same ,or X = 0, or Y = 0 ;
The result of Z data range : [-32768, 32767],the real result data = Z/amplitude
But the result range of the function which is cos(z)+sin(z) is for [-1.414,1.414]
so the amplitude should < 32768/1.414. In this example ,the amplitude = 16838.

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

  - M0CP/M0CP_RotateCORDIC/Source/apm32m35xx_int.c       Interrupt handlers
  - M0CP/M0CP_RotateCORDIC/Source/main.c                Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - ECLIPSE V4.24

&par Hardware and Software environment

  - This example runs on APM32M35XX MINI Devices.

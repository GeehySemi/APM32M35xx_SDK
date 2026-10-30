/*!
 * @file        system_apm32m35xx.h
 *
 * @brief       CMSIS Cortex-M0 Device Peripheral Access Layer System Source File
 *
 * @details     This file contains the system clock configuration for APM32M35xx devices.
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

/* Define to prevent recursive inclusion */
#ifndef __SYSTEM_APM32M35XX_H
#define __SYSTEM_APM32M35XX_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32M35XX_System
  @{
*/

/** @defgroup System_Macros Macros
  @{
  */

/**@} end of group System_Macros */

/** @defgroup System_Enumerations Enumerations
  @{
  */

/**@} end of group System_Enumerations */

/** @defgroup System_Structures Structures
  @{
  */

/**@} end of group System_Structures */

/** @defgroup System_Variables Variables
  @{
*/

/* System Clock Frequency (Core Clock) */
extern uint32_t SystemCoreClock;

/**@} end of group System_Variables */

/** @defgroup System_Functions Functions
  @{
*/

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/**@} end of group System_Functions */
/**@} end of group APM32M35XX_System */
/**@} end of group CMSIS */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32M35XX_H */

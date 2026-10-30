/*!
 * @file        bsp_delay.h
 *
 * @brief       Header for bsp_delay.c module
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
#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

/* Includes */
#include "apm32m35xx.h"
#include "apm32m35xx_misc.h"

/** @addtogroup Boards
  @{
*/

/** @addtogroup Board_APM32M35XX
  @{
*/

/** @defgroup APM32M35XX_Variables
  @{
  */

/* extern variables*/
extern uint32_t cntUs;
extern uint32_t cntMs;

/**@} end of group APM32M35XX_Variables*/

/** @defgroup APM32M35XX_Fuctions
  @{
  */


/* function declaration*/
void APM_DelayInit(void);

/* Delay*/
void APM_DelayMs(__IO uint32_t nms);
void APM_DelayUs(__IO uint32_t nus);
#endif

/**@} end of group APM32M35XX_Functions */
/**@} end of group Board_APM32M35XX */
/**@} end of group Boards */

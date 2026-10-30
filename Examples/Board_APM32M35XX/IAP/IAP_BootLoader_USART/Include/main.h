/*!
 * @file        main.h
 *
 * @brief       Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "board.h"
#include "apm32m35xx.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_eint.h"
#include "apm32m35xx_fmc.h"
#include "apm32m35xx_usart.h"
#include "apm32m35xx_misc.h"

#include "bsp_usart.h"
#include "bsp_flash.h"
#include "common.h"
#include "ymodem.h"
#include "menu.h"

#define VECT_TAB_OFFSET                     0x00000000

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_USART
  @{
  */

/** @defgroup IAP_BootLoader_USART_Variables Variables
  @{
  */

/*!
 * @brief    function hook
 */
typedef  void (*pFunction)(void);

extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;

/**@} end of group IAP_BootLoader_USART_Variables*/

/** @defgroup IAP_BootLoader_USART_Functions Functions
  @{
  */
void Led_Init(void);
void Delay(uint32_t count);
void Jump_to_App(uint8_t Application);

/**@} end of group IAP_BootLoader_USART_Functions */
/**@} end of group IAP_BootLoader_USART */
/**@} end of group Examples */

#ifdef __cplusplus
}
#endif

#endif

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
#include <stdio.h>
#include "Board.h"
#include "bsp_delay.h"
#include "apm32m35xx.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_usart.h"
#include "apm32m35xx_misc.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup USART_Interrupt
  @{
  */

/** @defgroup USART_Interrupt_Functions Functions
  @{
  */

void USART_Receive_Isr(void);
void USART_Send_Isr(void);

/**@} end of group USART_Interrupt_Functions */
/**@} end of group USART_Interrupt */
/**@} end of group Examples */

#ifdef __cplusplus
}
#endif

#endif

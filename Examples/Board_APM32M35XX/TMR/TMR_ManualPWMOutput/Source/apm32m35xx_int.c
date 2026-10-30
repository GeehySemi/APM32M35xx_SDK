/*!
 * @file        apm32m35xx_int.c
 *
 * @brief       Main Interrupt Service Routines
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

/* Includes */
#include "apm32m35xx_int.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup TMR_ManualPWMOutput
  @{
  */

/** @defgroup TMR_ManualPWMOutput_INT_Functions INT_Functions
  @{
  */

/*!
 * @brief        This function handles NMI exception
 *
 * @param        None
 *
 * @retval       None
 *
 * @note
 */
void NMI_Handler(void)
{
}

/*!
 * @brief        This function handles Hard Fault exception
 *
 * @param        None
 *
 * @retval       None
 *
 * @note
 */
void HardFault_Handler(void)
{
}

/*!
 * @brief        This function handles SVCall exception
 *
 * @param        None
 *
 * @retval       None
 *
 * @note
 */
void SVC_Handler(void)
{
}

/*!
 * @brief        This function handles PendSV_Handler exception
 *
 * @param        None
 *
 * @retval       None
 *
 * @note
 */
void PendSV_Handler(void)
{
}

/*!
 * @brief        This function handles SysTick Handler
 *
 * @param        None
 *
 * @retval       None
 *
 * @note
 */
void SysTick_Handler(void)
{
}

/*!
 * @brief        This function handles SysTick Handler
 *
 * @param        None
 *
 * @retval       None
 *
 * @note
 */
void EINT0_1_IRQHandler(void)
{
    if (APM_MINI_PBGetState(BUTTON_KEY1) == RESET)
    {
        TMR_OutputChannelPolarity(TMR1, TMR_OUTPUT_CHANNEL_1, TMR_OUTPUT_POLARITY_HIGH);
        TMR_OutputChannelMode(TMR1, TMR_OUTPUT_CHANNEL_1, TMR_OUTPUT_MODE_POLARITY);
        while (APM_MINI_PBGetState(BUTTON_KEY1) == RESET);
        TMR_OutputChannelMode(TMR1, TMR_OUTPUT_CHANNEL_1, TMR_OUTPUT_MODE_PWM);
    }
    else if (APM_MINI_PBGetState(BUTTON_KEY2) == RESET)
    {
        TMR_OutputChannelPolarity(TMR1, TMR_OUTPUT_CHANNEL_1, TMR_OUTPUT_POLARITY_LOW);
        TMR_OutputChannelMode(TMR1, TMR_OUTPUT_CHANNEL_1, TMR_OUTPUT_MODE_POLARITY);
        while (APM_MINI_PBGetState(BUTTON_KEY2) == RESET);
        TMR_OutputChannelMode(TMR1, TMR_OUTPUT_CHANNEL_1, TMR_OUTPUT_MODE_PWM);
    }
    EINT_ClearIntFlag(EINT_LINE0 | EINT_LINE1);
}

/**@} end of group TMR_ManualPWMOutput_INT_Functions */
/**@} end of group TMR_ManualPWMOutput */
/**@} end of group Examples */

/*!
 * @file        main.c
 *
 * @brief       Main program body
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
#include "main.h"

/** @addtogroup Examples
  * @brief TMR_SinglePulse examples
  @{
  */

/** @addtogroup TMR_SinglePulse
  @{
  */

/** @defgroup TMR_SinglePulse_Macros Macros
  @{
*/

/**@} end of group TMR_SinglePulse_Macros*/

/** @defgroup TMR_SinglePulse_Variables Variables
  @{
  */

/**@} end of group TMR_SinglePulse_Variables*/

/** @defgroup TMR_SinglePulse_Functions Functions
  @{
  */

/* TMR Init */
void APM_MINI_TMR3_Init(void);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
int main(void)
{
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_TMR3_Init();
    APM_DelayInit();

    /* Turn LED2 on */
    APM_MINI_LEDOn(LED2);
    /* Turn LED3 off */
    APM_MINI_LEDOff(LED3);

    for (;;)
    {
        APM_DelayMs(200);
        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       TMR3 Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR3_Init()
{
    TMR_TimeBase_T  timeBaseConfig;
    GPIO_Config_T   gpioconfig;
    TMR_OCConfig_T  occonfig;

    /* Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

    /* Connect TMR3 to CH1 CH2 */
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_6;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioconfig);

    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN1);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /* Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /* Set divider = 47.So TMR1 clock freq ~= 48/(47 + 1) = 1MHZ */
    timeBaseConfig.div = 47 ;
    /* Set counter = 1000 */
    timeBaseConfig.period = 1000;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;
    TMR_ConfigTimeBase(TMR3, &timeBaseConfig);

    /* PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /* Idle State is reset */
    occonfig.OC_Idlestate  = TMR_OCIDLESTATE_RESET;
    /* NIdle State is reset */
    occonfig.OC_NIdlestate = TMR_OCNIDLESTATE_RESET;
    /* Enable CH1N ouput */
    occonfig.OC_OutputNState =  TMR_OUTPUT_NSTATE_ENABLE;
    /* Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /* CH1 polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /* CH1N polarity is high */
    occonfig.OC_NPolarity = TMR_OC_NPOLARITY_HIGH;
    /* Set compare value = 500 */
    occonfig.Pulse = 500;
    TMR_OC1Config(TMR3, &occonfig);

    /* Set One Pulse Mode */
    TMR_SelectOnePulseMode(TMR3, TMR_OPMODE_SINGLE);
    /* Enable TMR3 */
    TMR_Enable(TMR3);
}

/**@} end of group TMR_SinglePulse_Functions */
/**@} end of group TMR_SinglePulse */
/**@} end of group Examples */

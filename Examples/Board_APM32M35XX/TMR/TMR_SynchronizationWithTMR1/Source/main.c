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
  * @brief TMR_SynchronizationWithTMR1 examples
  @{
  */

/** @addtogroup TMR_SynchronizationWithTMR1
  @{
  */

/** @defgroup TMR_SynchronizationWithTMR1_Functions Functions
  @{
  */

/* TMR Init */
void APM_MINI_TMR_Synchronization_Init(void);

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
    APM_MINI_TMR_Synchronization_Init();
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
 * @brief       TMR synchronization Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR_Synchronization_Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    GPIO_Config_T   gpioconfig;
    TMR_OCConfig_T  occonfig;

    /* Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

    /*  Connect TMR3 to CH1 */
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_6 | GPIO_PIN_8;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioconfig);

    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN1);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_PIN2);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /* Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /* Set divider = 0 .So TMR1 clock freq ~= 48/(0+1) = 48MHZ */
    timeBaseConfig.div = 0x0;
    /* Set counter = 47 */
    timeBaseConfig.period = 47;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter = 0x00;
    TMR_ConfigTimeBase(TMR1, &timeBaseConfig);

    /* Set counter = 1000 */
    timeBaseConfig.period = 1000;
    TMR_ConfigTimeBase(TMR3, &timeBaseConfig);

    /* PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /* Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /* CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /* Set compare value = 23 */
    occonfig.Pulse = 23;
    TMR_OC1Config(TMR1, &occonfig);
    /* Set the master slave mode */
    TMR_EnableMasterSlaveMode(TMR1);
    /* Set master mode */
    TMR_SelectOutputTrigger1(TMR1, TMR_TRGOSOURCE_UPDATE);

    TMR_EnablePWMOutputs(TMR1);

    /* PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /* Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /* CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /* Set compare value = 499 */
    occonfig.Pulse = 499;
    TMR_OC1Config(TMR3, &occonfig);

    /* Set Slave Mode*/
    TMR_SelectSlaveMode(TMR3, TMR_SLAVEMODE_GATED);
    /* Set Input Trigger*/
    TMR_SelectInputTrigger(TMR3, TMR_TS_ITR0);

    /*  Enable TMR3 */
    TMR_Enable(TMR3);
    /*  Enable TMR1 */
    TMR_Enable(TMR1);
}

/**@} end of group TMR_SynchronizationWithTMR1_Functions */
/**@} end of group TMR_SynchronizationWithTMR1 */
/**@} end of group Examples */

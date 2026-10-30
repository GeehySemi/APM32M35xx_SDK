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
#include "bsp_delay.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_misc.h"
#include "apm32m35xx_comp.h"
#include "apm32m35xx_tmr.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief COMP control PWM signal examples
  @{
  */

/** @addtogroup COMP_PWMSignalControl
  @{
  */

/** @defgroup COMP_PWMSignalControl_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group COMP_PWMSignalControl_Macros*/

/** @defgroup COMP_PWMSignalControl_Functions Functions
  @{
  */

void APM_MINI_Init(void);
/* COMP init */
void COMP_Init(void);
/* TMR init */
void TMR_Init(void);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    APM_MINI_Init();

    COMP_Init();

    TMR_Init();

    printf("This is an example of COMP control PWM signal \r\n");

    while (1)
    {
        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(500);
    }
}

/*!
 * @brief       Init MINI board
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_Init(void)
{
    /* Init delay function */
    APM_DelayInit();
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    APM_MINI_COMInit(COM1);
}

/*!
 * @brief       COMP Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void COMP_Init(void)
{
    GPIO_Config_T   gpioConfig;
    COMP_Config_T   compConfig;

    /* Enable GPIOA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);

    /* Configure PA5 is connected to COMP2 non inverting input */
    GPIO_ConfigStructInit(&gpioConfig);
    gpioConfig.mode    = GPIO_MODE_AN;
    gpioConfig.pupd    = GPIO_PUPD_NO;
    gpioConfig.pin     = GPIO_PIN_5;
    GPIO_Config(GPIOA, &gpioConfig);

    /* Enable COMP clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /*  Configure COMP2 */
    COMP_ConfigStructInit(&compConfig);
    compConfig.invertingInput = COMP_INVERTING_INPUT_VREFINT;
    compConfig.output      = COMP_OUTPUT_TIM1BKIN;
    compConfig.outputPol   = COMP_OUTPUTPOL_NONINVERTED;
    compConfig.hysterrsis  = COMP_HYSTERRSIS_NO;
    compConfig.mode        = COMP_MODE_VERYLOW;
    COMP_Config(COMP_SELECT_COMP2, &compConfig);

    /* Enable COMP2 */
    COMP_Enable(COMP_SELECT_COMP2);
}

/*!
 * @brief       TMR Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR_Init(void)
{
    GPIO_Config_T   gpioConfig;
    TMR_BDTInit_T   structure;
    TMR_TimeBase_T  tmrstruct;
    TMR_OCConfig_T  OCcongigStruct;

    /* Enable GPIOA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);

    /* Enable TMR1 clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);

    /* TMR1 channel 1 (PA8) configuration */
    GPIO_ConfigStructInit(&gpioConfig);
    gpioConfig.mode    = GPIO_MODE_AF;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.pupd    = GPIO_PUPD_PU;
    gpioConfig.speed   = GPIO_SPEED_50MHz;
    gpioConfig.pin     = GPIO_PIN_8;
    GPIO_Config(GPIOA, &gpioConfig);

    /* Enable PA8 alternate function for TMR1 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_PIN2);

    /* TMR base configuration */
    TMR_ConfigTimeBaseStruct(&tmrstruct);
    tmrstruct.clockDivision     = TMR_CKD_DIV1;
    tmrstruct.counterMode       = TMR_COUNTER_MODE_UP;
    tmrstruct.div               = 0;
    tmrstruct.period            = 100;
    tmrstruct.repetitionCounter = 0;
    TMR_ConfigTimeBase(TMR1, &tmrstruct);

    /* PWM mode is channel 1 Configuration */
    TMR_OCConfigStructInit(&OCcongigStruct);
    OCcongigStruct.OC_Mode         = TMR_OC_MODE_PWM2;
    OCcongigStruct.Pulse           = 50;
    OCcongigStruct.OC_Idlestate    = TMR_OCIDLESTATE_SET;
    OCcongigStruct.OC_NIdlestate   = TMR_OCNIDLESTATE_RESET;
    OCcongigStruct.OC_OutputState  = TMR_OUTPUT_STATE_ENABLE;
    OCcongigStruct.OC_OutputNState = TMR_OUTPUT_NSTATE_ENABLE;
    OCcongigStruct.OC_Polarity     = TMR_OC_POLARITY_LOW;
    OCcongigStruct.OC_NPolarity    = TMR_OC_NPOLARITY_LOW;
    TMR_OC1Config(TMR1, &OCcongigStruct);

    /* Automatic Output enable, Break, dead time and lock configuration*/
    TMR_ConfigBDTStructInit(&structure);
    structure.RMOS_State      = TMR_RMOS_STATE_ENABLE;
    structure.IMOS_State      = TMR_IMOS_STATE_ENABLE;
    structure.lockLevel       = TMR_LOCK_LEVEL_1;
    structure.deadTime        = 11;
    structure.breakState      = TMR_BREAK_STATE_ENABLE;
    structure.breakPolarity   = TMR_BREAK_POLARITY_HIGH;
    structure.automaticOutput = TMR_AUTOMATIC_OUTPUT_ENABLE;
    TMR_ConfigBDT(TMR1, &structure);

    /* Enable PWM output */
    TMR_EnablePWMOutputs(TMR1);

    /* Enable TMR1 */
    TMR_Enable(TMR1);
}


#if defined (__CC_ARM) || defined (__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @param       *f:  pointer to a FILE that can recording all information
*              needed to control a stream
*
* @retval      The characters that need to be send.
*
* @note
*/
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

#elif defined (__GNUC__)

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @retval      The characters that need to be send.
*
* @note
*/
int __io_putchar(int ch)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return ch;
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       file:  Meaningless in this function.
*
* @param       *ptr:  Buffer pointer for data to be sent.
*
* @param       len:  Length of data to be sent.
*
* @retval      The characters that need to be send.
*
* @note
*/
int _write(int file, char* ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

#else
#warning Not supported compiler type
#endif

/**@} end of group COMP_PWMSignalControl_Functions */
/**@} end of group COMP_PWMSignalControl */
/**@} end of group Examples */

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
#include "apm32m35xx_eint.h"
#include "apm32m35xx_syscfg.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_misc.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief EINT examples
  @{
  */

/** @addtogroup EINT
  @{
  */

/** @defgroup EINT_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group EINT_Macros*/

/** @defgroup EINT_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void EINT_Init(void);

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

    EINT_Init();

    printf("This is an example of EINT sampling \r\n");

    while (1)
    {

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

    APM_MINI_COMInit(COM1);
}

/*!
 * @brief       EINT initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void EINT_Init(void)
{
    GPIO_Config_T gpioConfig;
    EINT_Config_T eintConfig;

    /* Enable the BUTTON Clock */
    RCM_EnableAHBPeriphClock(KEY1_BUTTON_GPIO_CLK);
    RCM_EnableAHBPeriphClock(KEY2_BUTTON_GPIO_CLK);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* Configure Button pin as input floating */
    gpioConfig.mode = GPIO_MODE_IN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    gpioConfig.pin = KEY1_BUTTON_PIN;
    GPIO_Config(KEY1_BUTTON_GPIO_PORT, &gpioConfig);

    gpioConfig.pin = KEY2_BUTTON_PIN;
    GPIO_Config(KEY2_BUTTON_GPIO_PORT, &gpioConfig);

    /* Configure GPIO pin used as EINT Line */
    SYSCFG_EINTLine(SYSCFG_PORT_GPIOA, SYSCFG_PIN_1);
    SYSCFG_EINTLine(SYSCFG_PORT_GPIOA, SYSCFG_PIN_0);

    /* Configure Button exit line */
    eintConfig.line    =  KEY1_BUTTON_EXTI_LINE;
    eintConfig.lineCmd =  ENABLE;
    eintConfig.mode    =  EINT_MODE_INTERRUPT;
    eintConfig.trigger =  EINT_TRIGGER_FALLING;
    EINT_Config(&eintConfig);

    eintConfig.line    =  KEY2_BUTTON_EXTI_LINE;
    EINT_Config(&eintConfig);

    /* Configure NVIC_IRQRequest */
    NVIC_EnableIRQRequest(EINT0_1_IRQn, 0x0F);
}

/**
 * @brief       The interrupt will happen when the button is press ,
 *              and the Led will be on
 *
 * @param       None
 *
 * @retval      None
 */
void EINT_Isr(void)
{

    if (EINT_ReadStatusFlag(KEY1_BUTTON_EXTI_LINE) == SET)
    {
        APM_MINI_LEDToggle(LED2);
        while(GPIO_ReadInputBit(KEY1_BUTTON_GPIO_PORT, KEY1_BUTTON_PIN) == RESET)
        {
            APM_DelayMs(10);
        }
        EINT_ClearStatusFlag(KEY1_BUTTON_EXTI_LINE);
    }

    if (EINT_ReadStatusFlag(KEY2_BUTTON_EXTI_LINE) == SET)
    {
        APM_MINI_LEDToggle(LED3);
        while(GPIO_ReadInputBit(KEY2_BUTTON_GPIO_PORT, KEY2_BUTTON_PIN) == RESET)
        {
            APM_DelayMs(10);
        }

        EINT_ClearStatusFlag(KEY2_BUTTON_EXTI_LINE);
    }
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

/**@} end of group EINT_Functions */
/**@} end of group EINT */
/**@} end of group Examples */

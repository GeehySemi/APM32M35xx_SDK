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
  * @brief WWDT_OverTime examples
  @{
  */

/** @addtogroup WWDT_OverTime
  @{
  */

/** @defgroup WWDT_OverTime_Macros Macros
  @{
*/
/* printf function configs to USART1 */
#define DEBUG_USART  USART1

/**@} end of group WWDT_OverTime_Macros*/

/** @defgroup WWDT_OverTime_Variables Variables
  @{
  */
/* The OverTime is used to change the test way */
uint8_t is_OverTime = 0;

/**@} end of group WWDT_OverTime_Variables*/

/** @defgroup WWDT_OverTime_Functions Functions
  @{
  */

/* WWDT_Init */
void WWDT_Init(void);

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
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM1);

    /* Clear WWDTRST flag */
    if (RCM_ReadStatusFlag(RCM_FLAG_WWDTRST) != RESET)
    {
        APM_MINI_LEDOn(LED3);
        RCM_ClearStatusFlag();
    }

    APM_DelayInit();
    WWDT_Init();
    printf("\r\n System reset \r\n");

    while (1)
    {
        if (is_OverTime == RESET)
        {
            APM_MINI_LEDToggle(LED2);
            /* Delay about 25ms , 21.4ms<25ms<29.2ms ,Refresh allowed, system still running */
            APM_DelayMs(25);
            WWDT_ConfigCounter(127);
            printf("running\r\n");
        }

        if (is_OverTime == SET)
        {
            /* Delay about 50ms , 29.2ms<50ms ,Refresh not allowed, system reset */
            APM_DelayMs(50);
            WWDT_ConfigCounter(127);
        }
    }
}

/*!
 * @brief       WWDT configuration
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WWDT_Init(void)
{
    /* Enable WWDT clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_WWDT);

    /* WWDT TimeBase =  PCLK (72MHz)/4096)/8 = 2.19KHz (~456 us)  */
    WWDT_SetTimebase(WWDT_DIV_8);

    /* Set Window value to 80; WWDT counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated  */
    WWDT_ConfigWindowValue(80);

    /* Enable WWDG and set counter value to 127, WWDT timeout = ~456 us * 64 = 29.2 ms
     In this case the refresh window is: ~456us * (127-80)= 21.4ms < refresh window < ~456 * 64 = 29.2ms*/
    WWDT_Enable(127);
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

/**@} end of group WWDT_OverTime_Functions */
/**@} end of group WWDT_OverTime */
/**@} end of group Examples */

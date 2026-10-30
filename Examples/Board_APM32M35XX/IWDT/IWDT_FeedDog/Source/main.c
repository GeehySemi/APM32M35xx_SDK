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
  * @brief IWDT_FeedDog examples
  @{
  */

/** @addtogroup IWDT_FeedDog
  @{
  */

/** @defgroup IWDT_FeedDog_Macros Macros
  @{
*/
/* printf function configs to USART1*/
#define DEBUG_USART     USART1

/**@} end of group IWDT_FeedDog_Macros*/

/** @defgroup IWDT_FeedDog_Functions Functions
  @{
  */

/* IWDT_Init */
void IWDT_Init(void);

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
    APM_DelayInit();

    IWDT_Init();
    printf("System Reset\r\n");

    while (1)
    {
        /* delay about 0.5 second */
        APM_DelayMs(500);
        APM_MINI_LEDToggle(LED2);
        IWDT_Refresh();
        printf("running\r\n");
    }
}

/*!
 * @brief       IWDT configuration
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDT_Init(void)
{
    /* clear IWDTRST Flag */
    if (RCM_ReadStatusFlag(RCM_FLAG_IWDTRST) != RESET)
    {
        RCM_ClearStatusFlag();
    }
    /* set IWDT Write Access */
    IWDT_EnableWriteAccess();
    /* set IWDT Divider*/
    IWDT_ConfigDivider(IWDT_DIV_32);
    /* set IWDT Reloader */
    IWDT_ConfigReload(40000 / 32);
    /* Refresh */
    IWDT_Refresh();
    /* Enable IWDT */
    IWDT_Enable();
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

/**@} end of group IWDT_FeedDog_Functions */
/**@} end of group IWDT_FeedDog */
/**@} end of group Examples */

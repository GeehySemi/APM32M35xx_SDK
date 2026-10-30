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
  * @brief USART_Polling examples
  @{
  */

/** @addtogroup USART_Polling
  @{
  */

/** @defgroup USART_Polling_Macros Macros
  @{
*/
/* printf function configs to USART1 */
#define DEBUG_USART         USART1

#define DATA_BUF_SIZE       (32)

/**@} end of group USART_Polling_Macros*/

/** @defgroup USART_Polling_Variables Variables
  @{
  */

/* USART1 receive buffer */
uint8_t rxDataBufUSART1[DATA_BUF_SIZE] = {0};
/* USART2 transmit buffer */
uint8_t txDataBufUSART2[DATA_BUF_SIZE] = {0};

/**@} end of group USART_Polling_Variables*/

/** @defgroup USART_Polling_Functions Functions
  @{
  */

/* USART Write Data */
void USART_Write(USART_T* usart, uint8_t* dat);
/* Buffer compare */
BOOL BufferCompare(uint8_t* buf1, uint8_t* buf2, uint8_t size);

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
    BOOL state = TRUE;

    /* Init txDataBufUSART2 */
    for (int i = 0; i < DATA_BUF_SIZE; i++)
    {
        txDataBufUSART2[i] = i;
    }

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM1);
    APM_MINI_COMInit(COM2);
    APM_DelayInit();
    USART_DisableInterrupt(MINI_COM1, USART_INT_RXBNEIE);

    printf("test\r\n");

    for (int i = 0; i < DATA_BUF_SIZE; i++)
    {
        /* Wait until end of transmission */
        while (USART_ReadStatusFlag(USART2, USART_FLAG_TXBE) == RESET);
        USART_TxData(USART2, txDataBufUSART2[i]);

        /* Wait until end of reception */
        while (USART_ReadStatusFlag(USART1, USART_FLAG_RXBNE) == RESET);
        rxDataBufUSART1[i] = USART_RxData(USART1);
    }

    /* Verify data */
    state = BufferCompare(rxDataBufUSART1, txDataBufUSART2, DATA_BUF_SIZE);

    /* Data is ok then turn off LED2 */
    if (state == TRUE)
    {
        APM_MINI_LEDOn(LED2);
        printf("The DATA IS PASS, LED2 ON\r\n");
    }

    while (1)
    {
        APM_MINI_LEDToggle(LED3);
        APM_DelayMs(200);
    }
}

/*!
 * @brief        serial port tramsimt data
 *
 * @param        pointer to date that need to be sent
 *
 * @retval       None
 *
 * @note
 */
void USART_Write(USART_T* usart, uint8_t* dat)
{
    /* Enable USART_INT_TXCIE */
    USART_EnableInterrupt(MINI_COM1, USART_INT_TXCIE);

    while (*dat)
    {
        while (USART_ReadStatusFlag(usart, USART_FLAG_TXBE) == RESET);

        USART_TxData(usart, *dat++);
    }

    USART_DisableInterrupt(MINI_COM1, USART_INT_TXCIE);
}

/*!
 * @brief       Compares two buffers
 *
 * @param       buf1:    First buffer to be compared
 *
 * @param       buf1:    Second buffer to be compared
 *
 * @param       size:    Buffer size
 *
 * @retval      Return TRUE if buf1 = buf2. If not then return FALSE
 *
 * @note
 */
BOOL BufferCompare(uint8_t* buf1, uint8_t* buf2, uint8_t size)
{
    uint8_t i;

    for (i = 0; i < size; i++)
    {
        if (buf1[i] != buf2[i])
        {
            return FALSE;
        }
    }

    return TRUE;
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

/**@} end of group USART_Polling_Functions */
/**@} end of group USART_Polling */
/**@} end of group Examples */

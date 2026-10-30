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
#include "apm32m35xx_m0cp.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_misc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** @addtogroup Examples
  * @brief M0CP division signed examples
  @{
  */

/** @addtogroup M0CP_DivSigned
  @{
  */

/** @defgroup M0CP_DivSigned_Macros Macros
  @{
*/

/* printf using USART1 */
#define DEBUG_USART             USART1

/**@} end of group M0CP_DivSigned_Macros */

/** @defgroup M0CP_DivSigned_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void M0CP_Init(void);

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
    int32_t resultTemp[2];
    int32_t divisor = 0;
    int32_t dividend = 0;
    uint32_t time = 0;

    APM_MINI_Init();

    M0CP_Init();

    printf("This is an example of M0CP division signed \r\n");

    printf("Press KEY1 to start test.\r\n");

    while (1)
    {
        if (APM_MINI_PBGetState(BUTTON_KEY1) == 0)
        {
            /* set random seed */
            srand(time);
            divisor = -(rand() / 100000);
            dividend = rand() / 1000;

            if (divisor == 0)
            {
                divisor -= 1;
            }

#if M0CP_USE_FAST_IQ
            M0CP_Fast_IQDivSigned(divisor, dividend, resultTemp);

            printf("%d / %d = %d remainder = %d\r\n", dividend, divisor, resultTemp[0], resultTemp[1]);
#else
            /* Prepare operation data */
            if (M0CP_IQDivSigned(divisor, dividend, resultTemp) != M0CP_OK)
            {

                printf("M0CP timeout\r\n");
            }
            else
            {
                printf("%d / %d = %d remainder = %d\r\n", dividend, divisor, resultTemp[0], resultTemp[1]);
            }
#endif
            while (APM_MINI_PBGetState(BUTTON_KEY1) == 0);
        }
        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(200);
        time++;
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
 * @brief       M0CP initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void M0CP_Init(void)
{
    M0CP_Config_T m0cpConfigStruct;

    /* Load firmware from Flash to SRAM */
    M0CP_Firmware_Init();

    /* Reset M0CP */
    RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_M0CP);
    RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_M0CP);

    /* Enable M0CP clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_M0CP);

    /* Init M0CP hardware */
    M0CP_HardInit();

    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);
    /* Disable M0CP TX interrupt */
    M0CP_DisableInterrupt(M0CP_INT_TX);

    /* Wait for M0CP to be ready */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_BUSY) == SET)
    {

    }

    M0CP_ConfigStructInit(&m0cpConfigStruct);

    /* Configure M0CP */
    m0cpConfigStruct.algebraMode        = M0CP_ALG_DIV_SIGNED;
    m0cpConfigStruct.bankAutoConv       = M0CP_BANK_CONV_SOFTWARE;
    m0cpConfigStruct.bankRegGroup       = M0CP_BANK_REG_GROUP_0;
    m0cpConfigStruct.fixedPoint         = M0CP_FP_Q15;
    M0CP_Config(&m0cpConfigStruct);
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

/**@} end of group M0CP_DivSigned_Functions */
/**@} end of group M0CP_DivSigned */
/**@} end of group Examples */

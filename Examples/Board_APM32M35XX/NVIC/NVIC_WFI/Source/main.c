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
#include "apm32m35xx_eint.h"
#include "apm32m35xx_misc.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief NVIC WFI examples
  @{
  */

/** @addtogroup NVIC_WFI
  @{
  */

/** @defgroup NVIC_WFI_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1
/* define KEY1,KEY2 EXTI LINE */
#define KEY1_BUTTON_EXTI_LINE   EINT_LINE0

/**@} end of group NVIC_WFI_Macros*/

/** @defgroup NVIC_WFI_Variables Variables
  @{
  */
/* used to indicate interrupt status*/
uint8_t intStatus;

/**@} end of group NVIC_WFI_Variables*/

/** @defgroup NVIC_WFI_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void GPIO_Init(void);

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

    /* Configure NVIC_IRQRequest */
    NVIC_EnableIRQRequest(EINT0_1_IRQn, 1);

    printf("This is an example of NVIC WFI \r\n");

    while (1)
    {
        if (intStatus == 1)
        {
            APM_MINI_LEDOff(LED2);
            APM_MINI_LEDOff(LED3);

            printf("enter sleep mode successfully, push KEY1 to wake up device.\r\n\r\n");
            /* Wait fot interrupt */
            __WFI();

            printf("exit sleep mode successfully!\r\n\r\n");
            intStatus = 0;

            printf("running...\r\n");
        }

        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);

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
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);
    APM_MINI_COMInit(COM1);
}

/**
 * @brief       The interrupt will happen when the button 1 is press
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function should put into EINT0_1_IRQHandler()
 */
void EINT_Isr(void)
{
    if (EINT_ReadStatusFlag(KEY1_BUTTON_EXTI_LINE) == SET)
    {
        intStatus = 0X1 & ~(intStatus);
        while(GPIO_ReadInputBit(KEY1_BUTTON_GPIO_PORT, KEY1_BUTTON_PIN) == RESET)
        {
            APM_DelayMs(10);
        }
        EINT_ClearStatusFlag(KEY1_BUTTON_EXTI_LINE);
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
/**@} end of group NVIC_WFI_Functions */
/**@} end of group NVIC_WFI */
/**@} end of group Examples */

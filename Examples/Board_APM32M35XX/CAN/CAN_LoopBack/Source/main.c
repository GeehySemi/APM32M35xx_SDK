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
#include "apm32m35xx_can.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_misc.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief Can loopback examples
  @{
  */

/** @addtogroup CAN_LoopBack
  @{
  */

/** @defgroup CAN_LoopBack_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group CAN_LoopBack_Macros*/

/** @defgroup CAN_LoopBack_Enumerates Enumerates
  @{
  */

/*!
 * @brief       CAN communication status
 */
typedef enum
{
    CAN_OK,
    CAN_ERROR,
    CAN_BUSY,
} CAN_STA_T;

/**@} end of group CAN_LoopBack_Enumerates_Enumerates*/

/** @defgroup CAN_LoopBack_Variables Variables
  @{
  */

__IO CAN_STA_T flag = CAN_ERROR;

/**@} end of group CAN_LoopBack_Variables*/

/** @defgroup CAN_LoopBack_Functions Functions
  @{
  */

void APM_MINI_Init(void);
CAN_STA_T CAN_LoopBack(void);

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

    printf("This is an example of CAN loopback \r\n");

    printf("Press KEY1 to start test.\r\n");

    while (1)
    {
        if (APM_MINI_PBGetState(BUTTON_KEY1) == 0)
        {
            if (CAN_LoopBack() == CAN_OK)
            {
                printf("RxMessage Status: SUCCEED\r\n");
            }
            else
            {
                printf("RxMessage Status: FAILED\r\n");
            }

            while (APM_MINI_PBGetState(BUTTON_KEY1) == 0);
        }

        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(200);
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
 * @brief       CAN loopback
 *
 * @param       None
 *
 * @retval      status code
 *
 */
CAN_STA_T CAN_LoopBack(void)
{
    uint32_t timeout = 0;

    CAN_Config_T          canConfig;
    CAN_FilterConfig_T    filterConfig;
    CAN_Tx_Message        TxMessage;

    /* Enable CAN clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN);

    CAN_Reset();

    /* Enable FIF0 message pending interrupt */
    CAN_EnableInterrupt(CAN_INT_F0MP);

    /* CAN configuration */
    CAN_ConfigStructInit(&canConfig);
    canConfig.autoBusOffManage = DISABLE;
    canConfig.autoWakeUpMode   = DISABLE;
    canConfig.nonAutoRetran    = DISABLE;
    canConfig.timeTrigComMode  = DISABLE;
    canConfig.txFIFOPriority   = DISABLE;
    canConfig.rxFIFOLockMode   = DISABLE;
    canConfig.mode             = CAN_MODE_LOOPBACK;
    canConfig.syncJumpWidth    = CAN_SJW_1;
    canConfig.timeSegment1     = CAN_TIME_SEGMENT1_9;
    canConfig.timeSegment2     = CAN_TIME_SEGMENT2_8;
    canConfig.prescaler        = 4;
    CAN_Config(&canConfig);

    /* CAN filter configuration */
    filterConfig.filterIdHigh     = 0x0000;
    filterConfig.filterIdLow      = 0x0000;
    filterConfig.filterMaskIdHigh = 0x0000;
    filterConfig.filterMaskIdLow  = 0x0000;
    filterConfig.filterFIFO       = CAN_FIFO_0;
    filterConfig.filterNumber     = CAN_FILTER_NUMBER_1;
    filterConfig.filterMode       = CAN_FILTER_MODE_IDMASK;
    filterConfig.filterScale      = CAN_FILTER_SCALE_32BIT;
    filterConfig.filterActivation = ENABLE;
    CAN_ConfigFilter(&filterConfig);

    /* CAN Tx Message configuration */
    TxMessage.stanID         = 0x0000;
    TxMessage.extenID        = 0x1111;
    TxMessage.typeID         = CAN_TYPEID_EXT;
    TxMessage.remoteTxReq    = CAN_RTXR_DATA;
    TxMessage.dataLengthCode = 2;
    TxMessage.data[0]        = 0x55;
    TxMessage.data[1]        = 0xAA;
    CAN_TxMessage(&TxMessage);

    /* NVIC configuration */
    NVIC_EnableIRQRequest(CAN_IRQn, 0);

    flag = CAN_BUSY;
    timeout = 0;
    while ((timeout < 0xFFF) && (flag == CAN_BUSY))
    {
        timeout++;
    }

    if (timeout >= 0xFFF)
    {
        flag = CAN_ERROR;
    }

    CAN_DisableInterrupt(CAN_INT_F0MP);

    return flag;
}

/*!
 * @brief       CAN IRQ callback
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void CAN_Isr(void)
{
    CAN_Rx_Message RxMessage;

    if (CAN_ReadIntFlag(CAN_INT_F0MP) == SET)
    {
        RxMessage.stanID           = 0x0000;
        RxMessage.extenID          = 0x0000;
        RxMessage.typeID           = CAN_TYPEID_STD;
        RxMessage.dataLengthCode   = 0;
        RxMessage.filterMatchIndex = 0;
        RxMessage.data[0]          = 0x00;
        RxMessage.data[1]          = 0x00;

        CAN_RxMessage(CAN_FIFO_0, &RxMessage);

        if ((RxMessage.extenID == 0x1111) && (RxMessage.typeID == CAN_TYPEID_EXT)
                && (RxMessage.dataLengthCode == 2) && (RxMessage.data[1] | (RxMessage.data[0] << 8)) == 0x55AA)
        {
            flag = CAN_OK;
        }
        else
        {
            flag = CAN_ERROR;
        }
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

/**@} end of group CAN_LoopBack_Functions */
/**@} end of group CAN_LoopBack */
/**@} end of group Examples */

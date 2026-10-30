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
#include "apm32m35xx_dma.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_misc.h"
#include "apm32m35xx_syscfg.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief DMA memory to memory examples
  @{
  */

/** @addtogroup DMA_USART
  @{
  */

/** @defgroup DMA_USART_Macros Macros
  @{
*/

/* printf using USART1 */
#define DEBUG_USART             USART1
#define BufSize 0x0F

/**@} end of group DMA_USART_Macros*/

/** @defgroup DMA_USART_Variables Variables
  @{
  */

/* USART TX Buf*/
uint8_t DMA_USART_TxBuf[BufSize];
/* USART RX Buf*/
uint8_t DMA_USART_RxBuf[BufSize];

/**@} end of group DMA_USART_Variables*/

/** @defgroup DMA_USART_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void DMA_Init(uint32_t* RxBuf);
uint8_t Buffercmp(const uint8_t* pBuffer, uint8_t* pBuffer1, uint8_t BufferLength);

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

    /* Init TxBuf*/
    for (int i = 0; i < BufSize; i++)
    {
        DMA_USART_TxBuf[i] = i;
    }

    DMA_Init((uint32_t*)DMA_USART_RxBuf);

    USART_EnableDMA(USART1, USART_DMA_REQUEST_RX);

    /* data from usart2 send to usart1 */
    for (int i = 0; i < BufSize; i++)
    {
        /* USART send data*/
        while (USART_ReadStatusFlag(USART2, USART_FLAG_TXBE) == RESET);
        USART_TxData(USART2, DMA_USART_TxBuf[i]);
    }
    APM_DelayMs(50);
    /* Data is ok then turn off LED2 */
    if (Buffercmp(DMA_USART_TxBuf, DMA_USART_RxBuf, BufSize) != FALSE)
    {
        APM_MINI_LEDOff(LED2);
    }
    while (1);
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
    APM_MINI_COMInit(COM2);
    APM_MINI_COMInit(COM1);
    APM_MINI_LEDOn(LED2);
    APM_MINI_LEDOn(LED3);
}

/*!
 * @brief       DMA initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void DMA_Init(uint32_t* RxBuf)
{
    /* Enable DMA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA);
    /* DMA Configure */
    DMA_Config_T dmaConfig;
    /* size of buffer*/
    dmaConfig.bufferSize = BufSize;
    /* set memory Data Size*/
    dmaConfig.memoryDataSize = DMA_MEMORY_DATASIZE_BYTE;
    /* Set peripheral Data Size*/
    dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATASIZE_BYTE;
    /* Enable Memory Address increase*/
    dmaConfig.memoryInc = DMA_MEMORY_INC_ENABLE;
    /* Disable Peripheral Address increase*/
    dmaConfig.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    /* Reset Circular Mode*/
    dmaConfig.circular = DMA_CIRCULAR_DISABLE;
    /* Disable M2M*/
    dmaConfig.memoryTomemory = DMA_M2M_DISABLE;
    /* set priority*/
    dmaConfig.priority = DMA_PRIORITY_LEVEL_HIGHT;
    /* read from memory*/
    dmaConfig.direction = DMA_DIR_PERIPHERAL;
    /* Set memory Address*/
    dmaConfig.memoryAddress = (uint32_t)RxBuf;
    /* Set Peripheral Address*/
    dmaConfig.peripheralAddress = (uint32_t)&USART1->RXDATA;

    DMA_Config(DMA_CHANNEL_3, &dmaConfig);
    /* Clear DMA TF flag*/
    DMA_ClearIntFlag(DMA_INT_FLAG_TF3);
    /* Enable DMA Interrupt*/
    DMA_EnableInterrupt(DMA_CHANNEL_3, DMA_INT_TFIE);

    NVIC_EnableIRQRequest(DMA_CH2_3_IRQn, 2);

    USART_ClearStatusFlag(USART1, USART_FLAG_TXC);

    DMA_Enable(DMA_CHANNEL_3);
}


/*!
 * @brief       Compares two buffers
 *
 * @param       pBuffer
 *
 * @param       pBuffer

 * @retval      SUCCESS: pBuffer identical to pBuffer1. ERROR: pBuffer differs from pBuffer1
 *
 */
uint8_t Buffercmp(const uint8_t* pBuffer, uint8_t* pBuffer1, uint8_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return ERROR;
        }

        pBuffer++;
        pBuffer1++;
    }

    return SUCCESS;
}
/*!
 * @brief       DMA_Interrupt
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void DMA_Isr(void)
{
    if (DMA_ReadStatusFlag(DMA_FLAG_TF3))
    {
        /* do something*/
        DMA_ClearStatusFlag(DMA_FLAG_TF3);
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

/**@} end of group DMA_USART_Functions */
/**@} end of group DMA_USART */
/**@} end of group Examples */

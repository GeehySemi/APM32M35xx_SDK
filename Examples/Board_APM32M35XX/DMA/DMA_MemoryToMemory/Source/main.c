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

/** @addtogroup DMA_MemoryToMemory
  @{
  */

/** @defgroup DMA_MemoryToMemory_Macros Macros
  @{
*/

/* printf using USART1 */
#define DEBUG_USART             USART1
#define BUFFER_SIZE             32

/**@} end of group DMA_MemoryToMemory_Macros*/

/** @defgroup DMA_MemoryToMemory_Variables Variables
  @{
  */

uint32_t sourceDataBuffer[BUFFER_SIZE] =
{
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
    0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
    0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
    0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
    0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};

uint32_t destinationBuffer[BUFFER_SIZE];
volatile uint32_t currDataCounterBegin = 0;
volatile uint32_t currDataCounterEnd = 1;
/**@} end of group DMA_MemoryToMemory_Variables*/

/** @defgroup DMA_MemoryToMemory_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void DMA_Init(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

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

    DMA_Init();

    printf("This is an example of DMA memory to memory \r\n");

    while (currDataCounterEnd);

    if (Buffercmp(sourceDataBuffer, destinationBuffer, BUFFER_SIZE))
    {
        APM_MINI_LEDOn(LED2);
        printf("Transmit success.\r\n");
    }
    else
    {
        APM_MINI_LEDOn(LED3);
        printf("Transmit error.\r\n");
    }

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
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    APM_MINI_COMInit(COM1);

    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOff(LED3);
}

/*!
 * @brief       DMA initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void DMA_Init(void)
{
    DMA_Config_T    dmaConfigStruct;

    /* Enable DMA AHB clock interface */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA);

    dmaConfigStruct.peripheralAddress = (uint32_t)sourceDataBuffer;
    dmaConfigStruct.memoryAddress = (uint32_t)destinationBuffer;
    dmaConfigStruct.direction = DMA_DIR_PERIPHERAL;
    dmaConfigStruct.bufferSize = BUFFER_SIZE;
    dmaConfigStruct.peripheralInc = DMA_PERIPHERAL_INC_ENABLE;
    dmaConfigStruct.memoryInc = DMA_MEMORY_INC_ENABLE;
    dmaConfigStruct.peripheralDataSize = DMA_PERIPHERAL_DATASIZE_WORD;
    dmaConfigStruct.memoryDataSize = DMA_MEMORY_DATASIZE_WORD;
    dmaConfigStruct.circular = DMA_CIRCULAR_DISABLE;
    dmaConfigStruct.priority = DMA_PRIORITY_LEVEL_HIGHT;
    dmaConfigStruct.memoryTomemory = DMA_M2M_ENABLE;

    DMA_Config(DMA_CHANNEL_1, &dmaConfigStruct);

    DMA_EnableInterrupt(DMA_CHANNEL_1, DMA_INT_TFIE);

    currDataCounterBegin = DMA_ReadDataNumber(DMA_CHANNEL_1);

    DMA_Enable(DMA_CHANNEL_1);

    NVIC_EnableIRQRequest(DMA_CH1_IRQn, 2);
}

/*!
 * @brief       DMA interrupt callback
 *
 * @param       None
 *
 * @retval      None
 */
void DMA_Isr(void)
{
    if (DMA_ReadIntFlag(DMA_INT_FLAG_TF1))
    {
        currDataCounterEnd = DMA_ReadDataNumber(DMA_CHANNEL_1);

        DMA_ClearIntFlag(DMA_INT_FLAG_TF1);
    }
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
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
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

/**@} end of group DMA_MemoryToMemory_Functions */
/**@} end of group DMA_MemoryToMemory */
/**@} end of group Examples */

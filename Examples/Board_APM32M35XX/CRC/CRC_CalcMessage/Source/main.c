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
#include "apm32m35xx_crc.h"
#include "apm32m35xx_rcm.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief CRC calculate message examples
  @{
  */

/** @addtogroup CRC_CalcMessage
  @{
  */

/** @defgroup CRC_CalcMessage_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group CRC_CalcMessage_Macros*/

/** @defgroup CRC_CalcMessage_Enumerates Enumerates
  @{
  */

/**
 * @brief   CRC operation status
 */
typedef enum
{
    CRC_OK,
    CRC_ERR,
} CRC_STA_T;

/**@} end of group CRC_CalcMessage_Enumerates_Enumerates*/

/** @defgroup CRC_CalcMessage_Variables Variables
  @{
  */

/* CRC calculate Buffer*/
const uint32_t CRCBuffer[] =
{
    0x4ad47ab7, 0x6a961a71, 0x0a503a33, 0x2a12dbfd, 0xfbbfeb9e, 0x9b798b58,
    0xbb3bab1a, 0x6ca67c87, 0x5cc52c22, 0x3c030c60, 0x1c41edae, 0xfd8fcdec,
    0xad2abd0b, 0x8d689d49, 0x7e976eb6, 0x5ed54ef4, 0x2e321e51, 0x0e70ff9f,
    0xefbedfdd, 0xcffcbf1b, 0x9f598f78, 0x918881a9, 0xb1caa1eb, 0xd10cc12d,
    0xe16f1080, 0x00a130c2, 0x20e35004, 0x40257046, 0x83b99398, 0xa3fbb3da,
    0xc33dd31c, 0xe37ff35e, 0x129022f3, 0x32d24235, 0x52146277, 0x7256b5ea,
};

/**@} end of group CRC_CalcMessage_Variables*/

/** @defgroup CRC_CalcMessage_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void CRC_Init(void);
CRC_STA_T CRC_CalcMessage(uint32_t* result);

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
    /* CRC value*/
    uint32_t computedCRC = 0;

    APM_MINI_Init();

    CRC_Init();

    printf("This is an example of CRC calculate message \r\n");

    printf("Press KEY1 to start test.\r\n");

    while (1)
    {
        if (APM_MINI_PBGetState(BUTTON_KEY1) == 0)
        {
        	CRC_ResetDATA();
            if (CRC_CalcMessage(&computedCRC) != CRC_OK)
            {
                printf("CRC error\r\n");
            }
            else
            {
                printf("CRC_Result : %08X\r\n", computedCRC);
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
 * @brief       CRC initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void CRC_Init(void)
{
    /* Enable CRC AHB clock interface */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_CRC);

    /* DeInit CRC peripheral */
    CRC_Reset();

    /* Init the INIT register */
    CRC_WriteInitRegister(0);
}

/*!
 * @brief       CRC calculate message
 *
 * @param       result: CRC result
 *
 * @retval      operation status
 *
 */
CRC_STA_T CRC_CalcMessage(uint32_t* result)
{
    CRC_STA_T errSta = CRC_OK;

    /* Calculate CRC Buffer*/
    CRC_CalculateBlockCRC((uint32_t*)CRCBuffer, sizeof(CRCBuffer) / sizeof(CRCBuffer[0]));

    /* Read CRC value*/
    *result = CRC_ReadCRC();

    return errSta;
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

/**@} end of group CRC_CalcMessage_Functions */
/**@} end of group CRC_CalcMessage */
/**@} end of group Examples */

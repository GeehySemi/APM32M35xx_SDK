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
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_rtc.h"
#include "apm32m35xx_pmu.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief RTC calendar examples
  @{
  */

/** @addtogroup RTC_Calendar
  @{
  */

/** @defgroup RTC_Calendar_Macros Macros
  @{
*/

/* printf using USART1 */
#define DEBUG_USART             USART1
#define RTC_BKP_VALUE           0xAA55

/**@} end of group RTC_Calendar_Macros*/

/** @defgroup RTC_Calendar_Variables Variables
  @{
  */

RTC_DATE_T DateStruct;
RTC_TIME_T TimeStruct;

/**@} end of group RTC_Calendar_Variables*/

/** @defgroup RTC_Calendar_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void RTC_ConfigDateTime(void);

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
    uint8_t prevTime;
    char dateStr[11];
    char timeStr[9];

    APM_MINI_Init();

    RTC_ConfigDateTime();

    printf("This is an example of RTC calendar \r\n");

    while (1)
    {
        /* Read last Time*/
        prevTime = TimeStruct.seconds;

        /* Read time*/
        RTC_ReadTime(RTC_FORMAT_BIN, &TimeStruct);

        /** Read Date */
        RTC_ReadDate(RTC_FORMAT_BIN, &DateStruct);

        /** If pass 1 second */
        if (prevTime != TimeStruct.seconds)
        {
            sprintf(dateStr, "20%02d-%02d-%02d", DateStruct.year, DateStruct.month, DateStruct.date);
            sprintf(timeStr, "%02d:%02d:%02d", TimeStruct.hours, TimeStruct.minutes, TimeStruct.seconds);

            printf("%s\r\n", dateStr);
            printf("%s\r\n", timeStr);

            RTC_WriteBackup(RTC_BAKP_DATA0, RTC->TIME);

            if ((TimeStruct.hours == 0) && (TimeStruct.minutes == 0) && (TimeStruct.seconds == 0))
            {
                RTC_WriteBackup(RTC_BAKP_DATA1, RTC->DATE);
            }
        }
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
 * @brief       RTC Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RTC_Init(void)
{
    RTC_Config_T Struct;

    /* Enable PMU Periph Clock*/
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);

    /* Backup Access*/
    PMU_EnableBackupAccess();

    /* Enable LSI */
    RCM_EnableLSI();

    /* Wait until LSI is ready*/
    while (RCM_ReadStatusFlag(RCM_FLAG_LSIRDY) == RESET)
    {
    }
    /* Select LICT as RCM clock*/
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);

    /* Enable RTC clock*/
    RCM_EnableRTCCLK();

    /* Disable RTC write Protection*/
    RTC_DisableWriteProtection();

    /* Wait Synchro*/
    RTC_WaitForSynchro();

    /* set LSI Prediv */
    RTC_ConfigStructInit(&Struct);
    Struct.AsynchPrediv = 0x63;
    Struct.SynchPrediv  = 0x18F;

    RTC_Config(&Struct);
}

/*!
 * @brief       RTC configure date and time
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RTC_ConfigDateTime(void)
{
    uint32_t date;
    uint32_t time;

    /* RTC Reset */
    RTC_Init();
    RTC_Reset();
    RTC_Init();

    /* RTC Enable Init*/
    RTC_EnableInit();

    RTC_ConfigDateStructInit(&DateStruct);

    /* First time Init*/
    if (RTC_ReadBackup(RTC_BAKP_DATA4) != RTC_BKP_VALUE)
    {
        /* Init Date 22/8/22/5*/
        DateStruct.year =  22;
        DateStruct.month = 8;
        DateStruct.date =  26;
        DateStruct.weekday = 5;
        RTC_ConfigDate(RTC_FORMAT_BIN, &DateStruct);
        APM_DelayMs(10);

        TimeStruct.H12 = 12;
        TimeStruct.hours = 23;
        TimeStruct.minutes = 59;
        TimeStruct.seconds = 50;
        RTC_ConfigTime(RTC_FORMAT_BIN, &TimeStruct);

        RTC_WriteBackup(RTC_BAKP_DATA1, RTC->DATE);
        RTC_WriteBackup(RTC_BAKP_DATA0, RTC->TIME);

        RTC_WriteBackup(RTC_BAKP_DATA4, RTC_BKP_VALUE);
    }
    /* Read Date information from Backup*/
    else
    {
        time = RTC_ReadBackup(RTC_BAKP_DATA0);
        TimeStruct.hours = time >> 16;
        TimeStruct.minutes = (time >> 8) & 0xff;
        TimeStruct.seconds = (time) & 0xff;
        RTC_ConfigTime(RTC_FORMAT_BCD, &TimeStruct);
        APM_DelayMs(10);

        date = RTC_ReadBackup(RTC_BAKP_DATA1);
        DateStruct.year =  date >> 16;
        DateStruct.month = (date >> 8) & 0x0f;
        DateStruct.date =  date & 0xff;
        DateStruct.weekday = (date >> 13) & 0x07;
        RTC_ConfigDate(RTC_FORMAT_BCD, &DateStruct);
    }

    /* Exit RTC init mode */
    RTC_DisableInit();
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

/**@} end of group RTC_Calendar_Functions */
/**@} end of group RTC_Calendar */
/**@} end of group Examples */

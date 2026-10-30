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
#include "apm32m35xx_misc.h"
#include "apm32m35xx_rtc.h"
#include "apm32m35xx_pmu.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief RTC alarm examples
  @{
  */

/** @addtogroup RTC_Alarm
  @{
  */

/** @defgroup RTC_Alarm_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group RTC_Alarm_Macros*/

/** @defgroup RTC_Alarm_Functions Functions
  @{
  */

void APM_MINI_Init(void);
/* RTC Init */
void RTC_Init(void);
/* RTC Alarm Init */
void RTC_AlarmsConfig(void);

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

    printf("This is an example of RTC alarm \r\n");

    /* Enable the PWR clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);

    /* Allow access to RTC */
    PMU_EnableBackupAccess();

    /* Enable the LSI OSC */
    RCM_EnableLSI();

    /* Reset RTC*/
    RTC_Reset();

    /* Config RTC */
    RTC_Init();

    /* Config Alarm*/
    RTC_AlarmsConfig();

    printf("Please wait 5 second\r\n");

    APM_DelayMs(50);

    /* Alarm Enable */
    RTC_EnableAlarm();
    APM_MINI_LEDOn(LED2);

    /* Wait until time out */
    while (RTC_ReadStatusFlag(RTC_FLAG_ALRF) == RESET);

    printf("RTC alarm time out\r\n");

    APM_MINI_LEDOff(LED2);

    while (1)
    {
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
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    APM_MINI_COMInit(COM1);
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

    /* Enable the PWR clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);

    /* Allow access to RTC */
    PMU_EnableBackupAccess();

    /* Enable the LSI OSC */
    RCM_EnableLSI();

    /* Wait till LSI is ready */
    while (RCM_ReadStatusFlag(RCM_FLAG_LSIRDY) == RESET)
    {
    }
    /* Select the RTC Clock Source */
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);

    /* Enable RTC Clock */
    RCM_EnableRTCCLK();

    /* Disable Write Proctection */
    RTC_DisableWriteProtection();

    /* Wait Synchro */
    RTC_WaitForSynchro();

    RTC_ConfigStructInit(&Struct);

    RTC_Config(&Struct);
}

/*!
 * @brief       Config Alarm
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RTC_AlarmsConfig(void)
{
    RTC_TIME_T TimeStruct;
    RTC_ALARM_T AlarmStruct;

    /* Config Alarm */
    RTC_ConfigAlarmStructInit(&AlarmStruct);
    AlarmStruct.AlarmMask = 0x80808000;
    AlarmStruct.time.seconds = 5;
    AlarmStruct.time.hours = 0;
    AlarmStruct.time.minutes = 0;
    RTC_ConfigAlarm(RTC_FORMAT_BIN, &AlarmStruct);

    /* Config Time */
    TimeStruct.H12 = RTC_H12_AM;
    TimeStruct.hours = 0;
    TimeStruct.minutes = 0;
    TimeStruct.seconds = 0;
    RTC_ConfigTime(RTC_FORMAT_BIN, &TimeStruct);
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

/**@} end of group RTC_Alarm_Functions */
/**@} end of group RTC_Alarm */
/**@} end of group Examples */

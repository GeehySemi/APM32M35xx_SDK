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
#include "apm32m35xx_fmc.h"
#include "apm32m35xx_pmu.h"
#include "apm32m35xx_eint.h"
#include <stdio.h>


/** @addtogroup Examples
  * @brief FMC_LowPowerReset examples
  @{
  */

/** @addtogroup FMC_LowPowerReset
  @{
  */

/** @defgroup FMC_LowPowerReset_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1
#define STANDBYMODE 1
/**@} end of group FMC_LowPowerResetMacros*/

/** @defgroup FMC_LowPowerReset_Variables Variables
  @{
  */
uint32_t sysTick = 0;

/**@} end of group FMC_LowPowerReset_Variables*/

/** @defgroup FMC_LowPowerReset_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void Delay_Init(void);
void delay_ms(uint32_t count);
void LP_Reset_Open(void);
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
    printf("This is an example of low power reset by FMC \r\n");

    /* Unlock Flash for Clear or Write*/
    FMC_Unlock();
    FMC_UnlockOptionByte();
    LP_Reset_Open();

    /* Lock Flash*/
    FMC_Lock();
    printf("low power mode in three seconds and reset\r\n");
    delay_ms(3000);
#if STANDBYMODE
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
    if (PMU_ReadStatusFlag(PMU_FLAG_WUPF) == 1)
    {
        PMU_ClearStatusFlag(PMU_FLAG_WUPF);
    }
    PMU_EnterSTANDBYMode();
#else
    PMU_EnterSTOPMode(PMU_REGULATOR_ON, PMU_STOPENTRY_WFI);

#endif

    while (1)
    {
    }
}


/*!
 * @brief       Open low power reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void LP_Reset_Open(void)
{
    FMC_UserConfig_T userstruct;
    userstruct.iwdtSw = FMC_OB_IWDT_SW;
    userstruct.stdbyce = FMC_OB_STDBY_NRST;
    userstruct.stopce = FMC_OB_STOP_NRST;

#if STANDBYMODE
    if (FMC->OBCS_B.RSTSTDB == 1)
    {
        userstruct.stdbyce = FMC_OB_STDBY_RESET;
        FMC_EraseOptionByte();
        FMC_ConfigOptionByteUser(&userstruct);
        FMC_LaunchOptionByte();
    }
#else
    if (FMC->OBCS_B.RSTSTOP == 1)
    {
        userstruct.stopce = FMC_OB_STOP_RESET;
        FMC_EraseOptionByte();
        FMC_ConfigOptionByteUser(&userstruct);
        FMC_LaunchOptionByte();
    }

#endif
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
    Delay_Init();
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM1);
}

/*!
 * @brief       Delay_Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void Delay_Init(void)
{
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        while (1);
    }
}

/*!
 * @brief       Delay_ms
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void delay_ms(uint32_t count)
{
    sysTick = count;
    while (sysTick);

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

/**@} end of group FMC_LowPowerReset_Functions */
/**@} end of group FMC_LowPowerReset */
/**@} end of group Examples */

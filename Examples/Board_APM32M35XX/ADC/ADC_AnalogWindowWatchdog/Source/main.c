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
#include "apm32m35xx_adc.h"
#include "apm32m35xx_misc.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_rcm.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief ADC analog window watchdog examples
  @{
  */

/** @addtogroup ADC_AnalogWindowWatchdog
  @{
  */

/** @defgroup ADC_AnalogWindowWatchdog_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/* The analog watchdog High threshold */
#define awhtVoltage  0xA00

/* The analog watchdog low threshold */
#define awltVoltage  0x800

/**@} end of group ADC_AnalogWindowWatchdog_Macros*/

/** @defgroup ADC_AnalogWindowWatchdog_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void ADC_Init(void);

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

    ADC_Init();

    printf("This is an example of ADC continuous conversion \r\n");

    printf("The analog watchdog High threshold : %d mV\r\n", (awhtVoltage * 3300) / 4096);
    printf("The analog watchdog low threshold  : %d mV\r\n", (awltVoltage * 3300) / 4096);

    /* Wait until ADC is ready */
    while (!ADC_ReadStatusFlag(ADC_FLAG_ADRDY));
    ADC_StartConversion();

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
 * @brief       ADC AnalogWatchdog Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_AnalogWatchdogInit(void)
{
    /* Enables the analog watchdog */
    ADC_EnableAnalogWatchdog();

    /* set analog watchdog low threshold*/
    ADC_AnalogWatchdogLowThreshold(awltVoltage);

    /* set analog watchdog High threshold*/
    ADC_AnalogWatchdogHighThreshold(awhtVoltage);

    /* Enables the Analog Watchdog Single Channel */
    ADC_EnableAnalogWatchdogSingleChannel();

    /* ADC analog watchdog channel selection : AWD Channel 4*/
    ADC_AnalogWatchdogSingleChannel(ADC_ANALG_WDT_CHANNEL_4);
}

/*!
 * @brief       ADC initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void ADC_Init(void)
{
    GPIO_Config_T gpioConfig;
    ADC_Config_T  adcConfig;

    /* RCM Enable */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* GPIO Configuration */
    gpioConfig.pin = GPIO_PIN_0;
    gpioConfig.mode = GPIO_MODE_AN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &gpioConfig);

    /* ADC Configuration */
    ADC_Reset();
    ADC_ConfigStructInit(&adcConfig);

    /* Set resolution*/
    adcConfig.resolution    = ADC_RESOLUTION_12B;
    /* Set dataAlign */
    adcConfig.dataAlign     = ADC_DATA_ALIGN_RIGHT;
    /* Set scanDir */
    adcConfig.scanDir       = ADC_SCAN_DIR_UPWARD;
    /* Set convMode continous */
    adcConfig.convMode      = ADC_CONVERSION_CONTINUOUS;
    /* Set extTrigConv */
    adcConfig.extTrigConv1  = ADC_EXT_TRIG_CONV_TRG0;
    /* Set TrigEdge */
    adcConfig.extTrigEdge1  = ADC_EXT_TRIG_EDGE_NONE;

    ADC_Config(&adcConfig);
    ADC_ConfigChannel(ADC_CHANNEL_4, ADC_SAMPLE_TIME_239_5);

    /* ADC AnalogWatchdog Init */
    ADC_AnalogWatchdogInit();

    /* Enable Interrupt */
    ADC_EnableInterrupt(ADC_INT_CS);
    ADC_EnableInterrupt(ADC_INT_AWD);

    NVIC_EnableIRQRequest(ADC_COMP_IRQn, 2);

    /* Calibration */
    ADC_ReadCalibrationFactor();
    /* Enable ADC */
    ADC_Enable();
}

/*!
 * @brief       ADC Isr
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_Isr(void)
{
    uint32_t adcData = 0;
    uint32_t voltage = 0;

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CS) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_CS);
        /* Read ADC Conversion value */
        adcData = ADC_ReadConversionValue();
        /*  voltage(mV) =  adcData * (3300mV / 4095) */
        voltage = (adcData * 3300) / 4095;
        /* output to serial port */
        printf("voltage : %d  mV\r\n", voltage);
    }

    if (ADC_ReadIntFlag(ADC_INT_FLAG_AWD) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_AWD);

        if (adcData < awltVoltage)
        {
            APM_MINI_LEDOn(LED2);
            APM_MINI_LEDOff(LED3);
        }
        else if (adcData > awhtVoltage)
        {
            APM_MINI_LEDOff(LED2);
            APM_MINI_LEDOn(LED3);
        }
    }

    APM_DelayMs(500);
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

/**@} end of group ADC_AnalogWindowWatchdog_Functions */
/**@} end of group ADC_AnalogWindowWatchdog */
/**@} end of group Examples */

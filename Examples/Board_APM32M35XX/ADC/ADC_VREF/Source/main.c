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
  * @brief ADC continuous conversion VREF examples
  @{
  */

/** @addtogroup ADC_VREF
  @{
  */

/** @defgroup ADC_VREF_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group ADC_VREF_Macros*/

/** @defgroup ADC_VREF_Functions Functions
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

    printf("This is an example of ADC VREF \r\n");

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
    ADC_Config_T  adcConfig;

    /* RCM Enable*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* ADC Configuration */
    ADC_Reset();
    ADC_ConfigStructInit(&adcConfig);
    /* Set resolution*/
    adcConfig.resolution    = ADC_RESOLUTION_12B;
    /* Set dataAlign*/
    adcConfig.dataAlign     = ADC_DATA_ALIGN_RIGHT;
    /* Set scanDir*/
    adcConfig.scanDir       = ADC_SCAN_DIR_UPWARD;
    /* Set convMode continous*/
    adcConfig.convMode      = ADC_CONVERSION_CONTINUOUS;
    /* Set extTrigConv*/
    adcConfig.extTrigConv1  = ADC_EXT_TRIG_CONV_TRG0;
    /* Set TrigEdge*/
    adcConfig.extTrigEdge1  = ADC_EXT_TRIG_EDGE_NONE;

    ADC_Config(&adcConfig);
    ADC_ConfigChannel(ADC_CHANNEL_17, ADC_SAMPLE_TIME_239_5);
    /* Enable Interrupt*/
    ADC_EnableInterrupt(ADC_INT_CS);

    NVIC_EnableIRQRequest(ADC_COMP_IRQn, 2);

    /* Enable VREFINT*/
    ADC_EnableVrefint();

    /* Calibration*/
    ADC_ReadCalibrationFactor();
    /* Enable ADC*/
    ADC_Enable();
}

/*!
 * @brief       ADC interrupt callback
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into ADC_COMP_IRQHandler in apm32m35xx_int.c
 */
void ADC_Isr(void)
{
    uint32_t adcData = 0;
    float voltage = 0.0;

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CS) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_CS);
        /* Read ADC Conversion value */
        adcData = ADC_ReadConversionValue();

        voltage = ((float)adcData / 4095) * 3300;

        /* output to serial port */
        printf("Vref voltage : %.3f mV\r\n", voltage);

        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(500);
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

/**@} end of group ADC_VREF_Functions */
/**@} end of group ADC_VREF */
/**@} end of group Examples */

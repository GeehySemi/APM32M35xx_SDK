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
#include "apm32m35xx_adc.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_misc.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief DMA ADC examples
  @{
  */

/** @addtogroup DMA_ADC
  @{
  */

/** @defgroup DMA_ADC_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/**@} end of group DMA_ADC_Macros*/

/** @defgroup DMA_ADC_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void ADC_Init(void);
void APM_DMA_Init(uint32_t* buffer);

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
    /* ADC value */
    uint32_t adcConvertedValue = 0;
    float voltageValue = 0.0;

    APM_MINI_Init();

    ADC_Init();

    APM_DMA_Init(&adcConvertedValue);

    printf("This is an example of DMA ADC sampling \r\n");

    /* start conversion*/
    while (!ADC_ReadStatusFlag(ADC_FLAG_ADRDY));
    ADC_StartConversion();

    while (1)
    {
        voltageValue = (float)adcConvertedValue / 4096 * 3.3;
        printf("AD convert value = 0x%04X \r\n", adcConvertedValue);
        printf("AD voltage value = %f V \r\n", voltageValue);

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

    /* RCM Enable*/
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

    ADC_ConfigChannel(ADC_CHANNEL_4, ADC_SAMPLE_TIME_239_5);

    /* Calibration*/
    ADC_ReadCalibrationFactor();

    ADC_EnableDMA();
    ADC_DMARequestMode(ADC_DMA_MODE_CIRCULAR);
    /* Enable ADC*/
    ADC_Enable();
}

/*!
* @brief       ADC DMA Init
*
* @param       buffer:point DMA data buffer
*
* @retval      None
*
*/
void APM_DMA_Init(uint32_t* buffer)
{
    /* DMA Configure */
    DMA_Config_T dmaConfig;

    /* Enable DMA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA);

    /* size of buffer*/
    dmaConfig.bufferSize = 1;
    /* set memory Data Size*/
    dmaConfig.memoryDataSize = DMA_MEMORY_DATASIZE_HALFWORD;
    /* Set peripheral Data Size*/
    dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATASIZE_HALFWORD;
    /* Enable Memory Address increase*/
    dmaConfig.memoryInc = DMA_MEMORY_INC_DISABLE;
    /* Disable Peripheral Address increase*/
    dmaConfig.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    /* Reset Circular Mode*/
    dmaConfig.circular = DMA_CIRCULAR_ENABLE;
    /* Disable M2M*/
    dmaConfig.memoryTomemory = DMA_M2M_DISABLE;
    /* set priority*/
    dmaConfig.priority = DMA_PRIORITY_LEVEL_HIGHT;
    /* read from peripheral*/
    dmaConfig.direction = DMA_DIR_PERIPHERAL;
    /* Set memory Address*/
    dmaConfig.memoryAddress = (uint32_t)buffer;
    /* Set Peripheral Address*/
    dmaConfig.peripheralAddress = (uint32_t)&ADC->DATA;

    DMA_Config(DMA_CHANNEL_1, &dmaConfig);
    /* Clear DMA TF flag*/
    DMA_ClearIntFlag(DMA_INT_FLAG_TF1);
    /* Enable DMA Interrupt*/
    DMA_EnableInterrupt(DMA_CHANNEL_1, DMA_INT_TFIE);

    NVIC_EnableIRQRequest(DMA_CH1_IRQn, 2);

    DMA_Enable(DMA_CHANNEL_1);
}

/*!
 * @brief       DMA_Interrupt
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into DMA1_CH1_IRQHandler in apm32m35xx_int.c
 */
void DMA_Isr(void)
{
    if (DMA_ReadStatusFlag(DMA_FLAG_TF1))
    {
        /* do something */
        DMA_ClearStatusFlag(DMA_FLAG_TF1);
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

/**@} end of group DMA_ADC_Functions */
/**@} end of group DMA_ADC */
/**@} end of group Examples */

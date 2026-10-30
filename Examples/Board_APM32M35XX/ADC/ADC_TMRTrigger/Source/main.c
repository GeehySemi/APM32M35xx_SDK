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
#include "apm32m35xx_dma.h"
#include "apm32m35xx_tmr.h"
#include <stdio.h>
#include <string.h>


/** @addtogroup Examples
  * @brief ADC TMR trigger continuous conversion examples
  @{
  */

/** @addtogroup ADC_TMRTrigger
  @{
  */

/** @defgroup ADC_TMRTrigger_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/* save adc data*/
#define ADC_CH_SIZE             5
#define ADC_DR_ADDR         ((uint32_t)ADC_BASE + 0x40)

/**@} end of group ADC_TMRTrigger_Macros*/

/** @defgroup ADC_TMRTrigger_Variables Variables
  @{
  */
uint16_t adcData[ADC_CH_SIZE];

/**@} end of group ADC_TMRTrigger_Variables*/

/** @defgroup ADC_TMRTrigger_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void ADC_Init(void);
void TMR_Init(void);

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

    TMR_Init();

    printf("This is an example of TMR to trigger ADC continuous conversion \r\n");

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
 * @brief     DMA Init
 *
 * @param     None
 *
 * @retval    None
 */
void DMA_Init(void)
{
    /* DMA Configure */
    DMA_Config_T dmaConfig;

    /* Enable DMA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA);

    /* Set Peripheral Address */
    dmaConfig.peripheralAddress = ADC_DR_ADDR;
    /* Set memory Address */
    dmaConfig.memoryAddress = (uint32_t)&adcData;
    /* read from peripheral */
    dmaConfig.direction = DMA_DIR_PERIPHERAL;
    /* size of buffer*/
    dmaConfig.bufferSize = ADC_CH_SIZE;
    /* Disable Peripheral Address increase */
    dmaConfig.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    /* Enable Memory Address increase */
    dmaConfig.memoryInc = DMA_MEMORY_INC_ENABLE;
    /* Set peripheral Data Size */
    dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATASIZE_HALFWORD;
    /* set memory Data Size */
    dmaConfig.memoryDataSize = DMA_MEMORY_DATASIZE_HALFWORD;
    /* Reset Circular Mode */
    dmaConfig.circular = DMA_CIRCULAR_ENABLE;
    /* Disable M2M */
    dmaConfig.memoryTomemory = DMA_M2M_DISABLE;
    /* set priority */
    dmaConfig.priority = DMA_PRIORITY_LEVEL_HIGHT;

    DMA_Config(DMA_CHANNEL_1, &dmaConfig);

    DMA_Enable(DMA_CHANNEL_1);
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

    ADC_ClockMode(ADC_CLOCK_MODE_ASYNCLK);

    /* RCM Enable*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* GPIO Configuration */
    gpioConfig.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_0;
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
    /* Set extTrigConv1 as TIMER 1 CC4*/
    adcConfig.extTrigConv1  = ADC_EXT_TRIG_CONV_TRG1;
    /* Set TrigEdge1*/
    adcConfig.extTrigEdge1  = ADC_EXT_TRIG_EDGE_RISING;

    ADC_Config(&adcConfig);

    /* ADC channel Convert configuration */
    ADC_ConfigChannel(ADC_CHANNEL_0, ADC_SAMPLE_TIME_1_5);
    ADC_ConfigChannel(ADC_CHANNEL_1, ADC_SAMPLE_TIME_1_5);
    ADC_ConfigChannel(ADC_CHANNEL_2, ADC_SAMPLE_TIME_1_5);
    ADC_ConfigChannel(ADC_CHANNEL_3, ADC_SAMPLE_TIME_1_5);
    ADC_ConfigChannel(ADC_CHANNEL_4, ADC_SAMPLE_TIME_1_5);

    ADC_EnableInterrupt(ADC_INT_CS);

    NVIC_EnableIRQRequest(ADC_COMP_IRQn, 2);

    /* Config DMA*/
    DMA_Init();

    /* Calibration*/
    ADC_ReadCalibrationFactor();

    /* Enable ADC DMA*/
    ADC_EnableDMA();
    ADC_DMARequestMode(ADC_DMA_MODE_CIRCULAR);
    /* Enable ADC*/
    ADC_Enable();
}

/*!
 * @brief       TMR initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void TMR_Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_OCConfig_T  ocConfig;

    /* Enable Clock*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);

    TMR_Reset(TMR1);
    TMR_ConfigTimeBaseStruct(&timeBaseConfig);
    TMR_OCConfigStructInit(&ocConfig);

    /* Time base configuration */
    timeBaseConfig.period           = 10000;
    timeBaseConfig.div              = 7200;
    timeBaseConfig.clockDivision    = TMR_CKD_DIV1;
    timeBaseConfig.counterMode      = TMR_COUNTER_MODE_UP;
    TMR_ConfigTimeBase(TMR1, &timeBaseConfig);

    /* Output compare PWM mode configuration */
    ocConfig.OC_Mode        = TMR_OC_MODE_PWM1;
    ocConfig.OC_OutputState = TMR_OUTPUT_STATE_ENABLE;
    ocConfig.Pulse          = 0x01;
    TMR_OC4Config(TMR1, &ocConfig);

    /* Enable TMR1 */
    TMR_Enable(TMR1);

    TMR_EnablePWMOutputs(TMR1);
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
    float voltage;
    uint8_t index;

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CS) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_CS);

        for (index = 0; index < ADC_CH_SIZE; index++)
        {
            voltage = (adcData[index] * 3300.0) / 4095.0;

            printf("ADC CH[%d] voltage = %.3f mV\r\n", index, voltage);
        }
        printf("\r\n");

        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(1000);
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

/**@} end of group ADC_TMRTrigger_Functions */
/**@} end of group ADC_TMRTrigger */
/**@} end of group Examples */

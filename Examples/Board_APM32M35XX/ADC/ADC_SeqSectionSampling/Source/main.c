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
  * @brief ADC SeqSection Sampling examples
  @{
  */

/** @addtogroup ADC_SeqSectionSampling
  @{
  */

/** @defgroup ADC_SeqSectionSampling_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART             USART1

/* save adc data*/
#define ADC_CH_SIZE             5

/**@} end of group ADC_SeqSectionSampling_Macros*/

/** @defgroup ADC_SeqSectionSampling_Functions Functions
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
    printf("This is an example of ADC sequence subsection sampling \r\n");

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
    adcConfig.convMode      = ADC_CONVERSION_SINGLE;
    /* Set extTrigConv1 as TIMER 2 TRGO*/
    adcConfig.extTrigConv1  = ADC_EXT_TRIG_CONV_TRG2;
    /* Set TrigEdge1*/
    adcConfig.extTrigEdge1  = ADC_EXT_TRIG_EDGE_RISING;
    /* Set extTrigConv2 as TIMER 3 TRGO*/
    adcConfig.extTrigConv2  = ADC_EXT_TRIG_CONV_TRG3;
    /* Set TrigEdge2*/
    adcConfig.extTrigEdge2  = ADC_EXT_TRIG_EDGE_RISING;
    /* Set extTrigConv3 as TIMER 4 TRGO*/
    adcConfig.extTrigConv3  = ADC_EXT_TRIG_CONV_TRG4;
    /* Set TrigEdge3*/
    adcConfig.extTrigEdge3  = ADC_EXT_TRIG_EDGE_RISING;
    /* Enable SEQ*/
    adcConfig.seqMode       = ADC_SEQ_MODE_ENABLE;
    /* Set SEQ gap time unit: PCLK*/
    adcConfig.seqGapTime    = 0;

    ADC_Config(&adcConfig);

    /* ADC channel Convert configuration */
    ADC_ConfigChannel(ADC_CHANNEL_0, ADC_SAMPLE_TIME_239_5);
    ADC_ConfigChannel(ADC_CHANNEL_1, ADC_SAMPLE_TIME_239_5);
    ADC_ConfigChannel(ADC_CHANNEL_2, ADC_SAMPLE_TIME_239_5);
    ADC_ConfigChannel(ADC_CHANNEL_3, ADC_SAMPLE_TIME_239_5);
    ADC_ConfigChannel(ADC_CHANNEL_4, ADC_SAMPLE_TIME_239_5);

    /* Set sequential section as 3 */
    ADC_ConfigSeqSection(ADC_SEQ_SEC_3);

    ADC_ConfigSeqSectionTime(ADC_SEQ_SEC_1, ADC_SEQ_SEC_TX_1);
    ADC_ConfigSeqSectionTime(ADC_SEQ_SEC_2, ADC_SEQ_SEC_TX_2);
    ADC_ConfigSeqSectionTime(ADC_SEQ_SEC_3, ADC_SEQ_SEC_TX_3);

    /* section 1 */
    ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SEC_TX_1, ADC_SEQ_SEC_CHANNEL_0);

    /* section 2 */
    ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SEC_TX_2, ADC_SEQ_SEC_CHANNEL_1);
    ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SEC_TX_3, ADC_SEQ_SEC_CHANNEL_0);

    /* section 3 */
    ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SEC_TX_4, ADC_SEQ_SEC_CHANNEL_2);
    ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SEC_TX_5, ADC_SEQ_SEC_CHANNEL_3);
    ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SEC_TX_6, ADC_SEQ_SEC_CHANNEL_4);

    ADC_EnableInterrupt(ADC_INT_CS | ADC_INT_CSSN1 | ADC_INT_CSSN2 | ADC_INT_CSSN3);

    NVIC_EnableIRQRequest(ADC_COMP_IRQn, 2);


    /* Calibration */
    ADC_ReadCalibrationFactor();

    /* Enable ADC */
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

    /* Enable Clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR2 | RCM_APB1_PERIPH_TMR3 | RCM_APB1_PERIPH_TMR4);
    TMR_ConfigTimeBaseStruct(&timeBaseConfig);

    /* Time base configuration */
    timeBaseConfig.period           = 10000 / 1;
    timeBaseConfig.div              = 7200;
    timeBaseConfig.clockDivision    = TMR_CKD_DIV1;
    timeBaseConfig.counterMode      = TMR_COUNTER_MODE_UP;
    TMR_ConfigTimeBase(TMR2, &timeBaseConfig);
    timeBaseConfig.period           = 10000 / 2;
    TMR_ConfigTimeBase(TMR3, &timeBaseConfig);
    timeBaseConfig.period           = 10000 / 4;
    TMR_ConfigTimeBase(TMR4, &timeBaseConfig);
    /* TRGO2 */
    TMR_SelectOutputTrigger1(TMR2, TMR_TRGOSOURCE_UPDATE);
    /* TRGO3 */
    TMR_SelectOutputTrigger1(TMR3, TMR_TRGOSOURCE_UPDATE);
    /* TRGO4 */
    TMR_SelectOutputTrigger1(TMR4, TMR_TRGOSOURCE_UPDATE);

    /* Enable TMR2 TMR3 TMR4 */
    TMR_Enable(TMR2);
    TMR_Enable(TMR3);
    TMR_Enable(TMR4);
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
    uint8_t index;

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CS) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_CS);

        for (index = 0; index <= ADC_CH_SIZE; index++)
        {

            printf("SEQ DATA[%d]:%d\r\n", index, ADC->SEQ_DATA_B[index].DATA);
        }
        printf("\r\n");

    }
    if (ADC_ReadIntFlag(ADC_INT_FLAG_CSSN1) == SET)
    {
        printf("CSSN1 INT\r\n");
        ADC_ClearIntFlag(ADC_INT_FLAG_CSSN1);
    }

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CSSN2) == SET)
    {
        printf("CSSN2 INT\r\n");
        ADC_ClearIntFlag(ADC_INT_FLAG_CSSN2);
    }

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CSSN3) == SET)
    {
        printf("CSSN3 INT\r\n");
        ADC_ClearIntFlag(ADC_INT_FLAG_CSSN3);
    }

    APM_MINI_LEDToggle(LED2);
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

/**@} end of group ADC_SeqSectionSampling_Functions */
/**@} end of group ADC_SeqSectionSampling */
/**@} end of group Examples */

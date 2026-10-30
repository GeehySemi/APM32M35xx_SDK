/*!
 * @file        apm32m35xx_adc.c
 *
 * @brief       This file contains all the functions for the ADC peripheral
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
#include "apm32m35xx_adc.h"
#include "apm32m35xx_rcm.h"

/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup ADC_Driver
  @{
*/

/** @defgroup ADC_Macros Macros
  @{
*/

/**@} end of group ADC_Macros */

/** @defgroup ADC_Enumerations Enumerations
  @{
*/

/**@} end of group ADC_Enumerations */

/** @defgroup ADC_Structures Structures
  @{
*/

/**@} end of group ADC_Structures */

/** @defgroup ADC_Variables Variables
  @{
*/

/**@} end of group ADC_Variables */

/** @defgroup ADC_Functions Functions
  @{
*/

/*!
 * @brief     Set the ADC peripheral registers to their default reset values
 *
 * @param     None
 *
 * @retval    None
 */
void ADC_Reset(void)
{
    RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_ADC);
    RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_ADC);
}

/*!
 * @brief       Config the ADC peripheral according to the specified parameters in the adcConfig
 *
 * @param       adcConfig:  Pointer to a ADC_Config_T structure that
 *                          contains the configuration information for the ADC peripheral
 *
 * @retval      None
 */
void ADC_Config(ADC_Config_T* adcConfig)
{
    ADC->CFG1_B.DATARESCFG  = adcConfig->resolution;
    ADC->CFG1_B.DALIGCFG    = adcConfig->dataAlign;
    ADC->CFG1_B.SCANSEQDIR  = adcConfig->scanDir;
    ADC->CFG1_B.CMODESEL    = adcConfig->convMode;
    ADC->CFG2_B.SEQEN       = adcConfig->seqMode;
    ADC->CFG2_B.TGAP        = adcConfig->seqGapTime;
    ADC->CFG1_B.EXTPOLSEL1  = adcConfig->extTrigEdge1;
    ADC->CFG1_B.EXTTRGSEL1  = adcConfig->extTrigConv1;
    ADC->CFG3_B.EXTPOLSEL2  = adcConfig->extTrigEdge2;
    ADC->CFG3_B.EXTTRGSEL2  = adcConfig->extTrigConv2;
    ADC->CFG3_B.EXTPOLSEL3  = adcConfig->extTrigEdge3;
    ADC->CFG3_B.EXTTRGSEL3  = adcConfig->extTrigConv3;
}

/*!
 * @brief       Fills each adcConfig member with its default value
 *
 * @param       adcConfig:  Pointer to a ADC_Config_T structure which will be initialized
 *
 * @retval      None
 */
void ADC_ConfigStructInit(ADC_Config_T* adcConfig)
{
    adcConfig->resolution   = ADC_RESOLUTION_12B;
    adcConfig->dataAlign    = ADC_DATA_ALIGN_RIGHT;
    adcConfig->scanDir      = ADC_SCAN_DIR_UPWARD;
    adcConfig->convMode     = ADC_CONVERSION_SINGLE;
    adcConfig->seqMode      = ADC_SEQ_MODE_DISABLE;
    adcConfig->seqGapTime   = 0;
    adcConfig->extTrigConv1 = ADC_EXT_TRIG_CONV_TRG0;
    adcConfig->extTrigEdge1 = ADC_EXT_TRIG_EDGE_NONE;
    adcConfig->extTrigConv2 = ADC_EXT_TRIG_CONV_TRG0;
    adcConfig->extTrigEdge2 = ADC_EXT_TRIG_EDGE_NONE;
    adcConfig->extTrigConv3 = ADC_EXT_TRIG_CONV_TRG0;
    adcConfig->extTrigEdge3 = ADC_EXT_TRIG_EDGE_NONE;
}

/*!
 * @brief       Enable the ADC peripheral
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_Enable(void)
{
    ADC->CTRL_B.ADCEN = BIT_SET;
}

/*!
 * @brief       Disable the ADC peripheral
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_Disable(void)
{
    ADC->CTRL_B.ADCD = BIT_SET;
}

/*!
 * @brief       Configure the ADC to either be clocked by the asynchronous clock
 *
 * @param       clockmode: selects the ADC clock mode.
 *                         The parameter can be one of following values:
 *                         @arg ADC_CLOCK_MODE_ASYNCLK:       ADC Asynchronous clock mode
 *                         @arg ADC_CLOCK_MODE_SYNCLKDIV2:    Synchronous clock mode divided by 2
 *                         @arg ADC_CLOCK_MODE_SYNCLKDIV4:    Synchronous clock mode divided by 4
 *
 * @retval      None
 */
void ADC_ClockMode(ADC_CLOCK_MODE_T clockMode)
{
    ADC->CFG2_B.CLKCFG = (uint32_t)clockMode;
}

/*!
 * @brief       Enables the jitter when the ADC is clocked by PCLK div2 or div4
 *
 * @param       jitter: They are replaced by PCLK div2 or div4
 *                      The parameter can be one of following values:
 *                      @arg ADC_JITTER_PCLKDIV2:    ADC clocked by PCLK div2
 *                      @arg ADC_JITTER_PCLKDIV4:    ADC clocked by PCLK div4
 *
 * @retval      None
 */
void ADC_EnableJitter(ADC_JITTER_T jitter)
{
    ADC->CFG2_B.CLKCFG |= (uint32_t)jitter;
}

/*!
 * @brief       Disables the jitter when the ADC is clocked by PCLK div2 or div4
 *
 * @param       jitter: They are replaced by PCLK div2 or div4
 *                      The parameter can be one of following values:
 *                      @arg ADC_JITTER_PCLKDIV2:    ADC clocked by PCLK div2
 *                      @arg ADC_JITTER_PCLKDIV4:    ADC clocked by PCLK div4
 * @retval      None
 */
void ADC_DisableJitter(ADC_JITTER_T jitter)
{
    ADC->CFG2_B.CLKCFG &= (uint32_t)~jitter;
}

/*!
 * @brief       Enables the Auto Power Off mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableAutoPowerOff(void)
{
    ADC->CFG1_B.AOEN = BIT_SET;
}

/*!
 * @brief       Disables the Auto Power Off mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableAutoPowerOff(void)
{
    ADC->CFG1_B.AOEN = BIT_RESET;
}

/*!
 * @brief       Enables the Auto-delayed conversion mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableWaitMode(void)
{
    ADC->CFG1_B.WAITCEN = BIT_SET;
}

/*!
 * @brief       Disables the Auto-delayed conversion mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableWaitMode(void)
{
    ADC->CFG1_B.WAITCEN = BIT_RESET;
}

/*!
 * @brief       Enables the analog watchdog
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableAnalogWatchdog(void)
{
    ADC->CFG1_B.AWDEN = BIT_SET;
}

/*!
 * @brief       Disables the analog watchdog
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableAnalogWatchdog(void)
{
    ADC->CFG1_B.AWDEN = BIT_RESET;
}

/*!
 * @brief       The analog watchdog low threshold
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_AnalogWatchdogLowThreshold(uint16_t lowThreshold)
{
    ADC->AWDT_B.AWDLT = (uint16_t)lowThreshold;
}

/*!
 * @brief       The analog watchdog High threshold
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_AnalogWatchdogHighThreshold(uint16_t highThreshold)
{
    ADC->AWDT_B.AWDHT = (uint16_t)highThreshold;
}

/*!
 * @brief       Configures the analog watchdog guarded single channel
 *
 * @param       channel:    ADC analog watchdog channel selection
 *                          The parameter can be one of following values:
 *                          @arg ADC_ANALG_WDT_CHANNEL_0: AWD Channel 0
 *                          @arg ADC_ANALG_WDT_CHANNEL_1: AWD Channel 1
 *                          @arg ADC_ANALG_WDT_CHANNEL_2: AWD Channel 2
 *                          @arg ADC_ANALG_WDT_CHANNEL_3: AWD Channel 3
 *                          @arg ADC_ANALG_WDT_CHANNEL_4: AWD Channel 4
 *                          @arg ADC_ANALG_WDT_CHANNEL_5: AWD Channel 5
 *                          @arg ADC_ANALG_WDT_CHANNEL_6: AWD Channel 6
 *                          @arg ADC_ANALG_WDT_CHANNEL_7: AWD Channel 7
 *                          @arg ADC_ANALG_WDT_CHANNEL_8: AWD Channel 8
 *                          @arg ADC_ANALG_WDT_CHANNEL_12: AWD Channel 12
 *                          @arg ADC_ANALG_WDT_CHANNEL_13: AWD Channel 13
 *                          @arg ADC_ANALG_WDT_CHANNEL_14: AWD Channel 14
 *                          @arg ADC_ANALG_WDT_CHANNEL_15: AWD Channel 15
 *                          @arg ADC_ANALG_WDT_CHANNEL_16: AWD Channel 16 is TempSensor
 *                          @arg ADC_ANALG_WDT_CHANNEL_17: AWD Channel 17 is Vrefint
 *                          @arg ADC_ANALG_WDT_CHANNEL_18: AWD Channel 18 is 1/2 VDD
 *
 * @retval      None
 */
void ADC_AnalogWatchdogSingleChannel(uint32_t channel)
{
    ADC->CFG1_B.AWDCHSEL = channel;
}

/*!
 * @brief       Enables the Analog Watchdog Single Channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableAnalogWatchdogSingleChannel(void)
{
    ADC->CFG1_B.AWDCHEN = BIT_SET;
}

/*!
 * @brief       Disables the Analog Watchdog Single Channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableAnalogWatchdogSingleChannel(void)
{
    ADC->CFG1_B.AWDCHEN = BIT_RESET;
}

/*!
 * @brief       Enables the temperature sensor channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableTempSensor(void)
{
    ADC->CCFG_B.TSEN = BIT_SET;
}

/*!
 * @brief       Disables the temperature sensor channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableTempSensor(void)
{
    ADC->CCFG_B.TSEN = BIT_RESET;
}

/*!
 * @brief       Enables the vrefint channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableVrefint(void)
{
    ADC->CCFG_B.VREFEN = BIT_SET;
}

/*!
 * @brief       Disables the vrefint channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableVrefint(void)
{
    ADC->CCFG_B.VREFEN = BIT_RESET;
}

/*!
 * @brief       Enables the half of VDD channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableHalfVDD(void)
{
    ADC->CCFG_B.HLAF_VDDEN = BIT_SET;
}

/*!
 * @brief       Disables the half of VDD channel
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableHalfVDD(void)
{
    ADC->CCFG_B.HLAF_VDDEN = BIT_RESET;
}

/*!
 * @brief       Configures for the selected ADC channel and its sampling time
 *
 * @param       channel:    the ADC channel
 *                          The parameter can be combination of following values:
 *                          @arg ADC_CHANNEL_0: channel 0
 *                          @arg ADC_CHANNEL_1: channel 1
 *                          @arg ADC_CHANNEL_2: channel 2
 *                          @arg ADC_CHANNEL_3: channel 3
 *                          @arg ADC_CHANNEL_4: channel 4
 *                          @arg ADC_CHANNEL_5: channel 5
 *                          @arg ADC_CHANNEL_6: channel 6
 *                          @arg ADC_CHANNEL_7: channel 7
 *                          @arg ADC_CHANNEL_8: channel 8
 *                          @arg ADC_CHANNEL_12: channel 12
 *                          @arg ADC_CHANNEL_13: channel 13
 *                          @arg ADC_CHANNEL_14: channel 14
 *                          @arg ADC_CHANNEL_15: channel 15
 *                          @arg ADC_CHANNEL_16: channel 16 is TempSensor
 *                          @arg ADC_CHANNEL_17: channel 17 is Vrefint
 *                          @arg ADC_CHANNEL_18: channel 18 is 1/2 VDD
 * @param       sampleTime: the ADC sampling time
 *                          The parameter can be one of following values:
 *                          @arg ADC_SAMPLE_TIME_1_5:   ADC 1.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_7_5:   ADC 7.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_13_5:  ADC 13.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_28_5:  ADC 28.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_41_5:  ADC 41.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_55_5:  ADC 55.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_71_5:  ADC 71.5 clock cycles
 *                          @arg ADC_SAMPLE_TIME_239_5: ADC 239.5 clock cycles
 *
 * @retval      None
 */
void ADC_ConfigChannel(uint32_t channel, uint8_t sampleTime)
{
    ADC->CHSEL |= (uint32_t)channel;

    ADC->SMPTIM |= (uint8_t)sampleTime;
}

/*!
 * @brief       Configures for the section number of sequencial
 *
 * @param       section:    the section number of ADC sequencial
 *                          The parameter can be combination of following values:
 *                          @arg ADC_SEQ_SEC_1: 1 section
 *                          @arg ADC_SEQ_SEC_2: 2 section
 *                          @arg ADC_SEQ_SEC_3: 3 section
 * @retval      None
 */
void ADC_ConfigSeqSection(ADC_SEQ_SECTION_T section)
{
    ADC->SEQ_NUM_B.SEQ_NUM = section;
}

/*!
 * @brief       Configures for the sequencial section transmission time
 *
 * @param       section:    the ADC sequencial section
 *                          The parameter can be combination of following values:
 *                          @arg ADC_SEQ_SEC_1: 1 section
 *                          @arg ADC_SEQ_SEC_2: 2 section
 *                          @arg ADC_SEQ_SEC_3: 3 section
 * @param       time:       the ADC sequencial section transmission time
 *                          The parameter can be combination of following values:
 *                          @arg ADC_SEQ_SEC_TX_1: transmission 1 time
 *                          @arg ADC_SEQ_SEC_TX_2: transmission 2 time
 *                          @arg ADC_SEQ_SEC_TX_3: transmission 3 time
 *                          @arg ADC_SEQ_SEC_TX_4: transmission 4 time
 *                          @arg ADC_SEQ_SEC_TX_5: transmission 5 time
 *                          @arg ADC_SEQ_SEC_TX_6: transmission 6 time
 *                          @arg ADC_SEQ_SEC_TX_7: transmission 7 time
 *                          @arg ADC_SEQ_SEC_TX_8: transmission 8 time
 *                          @arg ADC_SEQ_SEC_TX_9: transmission 9 time
 *                          @arg ADC_SEQ_SEC_TX_10: transmission 10 time
 *                          @arg ADC_SEQ_SEC_TX_11: transmission 11 time
 *                          @arg ADC_SEQ_SEC_TX_12: transmission 12 time
 *                          @arg ADC_SEQ_SEC_TX_13: transmission 13 time
 *                          @arg ADC_SEQ_SEC_TX_14: transmission 14 time
 *                          @arg ADC_SEQ_SEC_TX_15: transmission 15 time
 *                          @arg ADC_SEQ_SEC_TX_16: transmission 16 time
 *                          @arg ADC_SEQ_SEC_TX_17: transmission 17 time
 *                          @arg ADC_SEQ_SEC_TX_18: transmission 18 time
 *                          @arg ADC_SEQ_SEC_TX_19: transmission 19 time
 * @retval      None
 */
void ADC_ConfigSeqSectionTime(ADC_SEQ_SECTION_T section, ADC_SEQ_SECTION_TIME_T time)
{
    if (section == ADC_SEQ_SEC_1)
    {
        ADC->SEQ_NUM_B.SEQ_NUM1 = time;
    }
    else if (section == ADC_SEQ_SEC_2)
    {
        ADC->SEQ_NUM_B.SEQ_NUM2 = time;
    }
    else if (section == ADC_SEQ_SEC_3)
    {
        ADC->SEQ_NUM_B.SEQ_NUM3 = time;
    }
}

/*!
 * @brief       Configures for the number of channels converted for the time
 *
 * @param       time:       the ADC sequencial section transmission time
 *                          The parameter can be combination of following values:
 *                          @arg ADC_SEQ_SEC_TX_1: transmission 1 time
 *                          @arg ADC_SEQ_SEC_TX_2: transmission 2 time
 *                          @arg ADC_SEQ_SEC_TX_3: transmission 3 time
 *                          @arg ADC_SEQ_SEC_TX_4: transmission 4 time
 *                          @arg ADC_SEQ_SEC_TX_5: transmission 5 time
 *                          @arg ADC_SEQ_SEC_TX_6: transmission 6 time
 *                          @arg ADC_SEQ_SEC_TX_7: transmission 7 time
 *                          @arg ADC_SEQ_SEC_TX_8: transmission 8 time
 *                          @arg ADC_SEQ_SEC_TX_9: transmission 9 time
 *                          @arg ADC_SEQ_SEC_TX_10: transmission 10 time
 *                          @arg ADC_SEQ_SEC_TX_11: transmission 11 time
 *                          @arg ADC_SEQ_SEC_TX_12: transmission 12 time
 *                          @arg ADC_SEQ_SEC_TX_13: transmission 13 time
 *                          @arg ADC_SEQ_SEC_TX_14: transmission 14 time
 *                          @arg ADC_SEQ_SEC_TX_15: transmission 15 time
 *                          @arg ADC_SEQ_SEC_TX_16: transmission 16 time
 *                          @arg ADC_SEQ_SEC_TX_17: transmission 17 time
 *                          @arg ADC_SEQ_SEC_TX_18: transmission 18 time
 *                          @arg ADC_SEQ_SEC_TX_19: transmission 19 time
 * @param       channel:    the number of channels converted for the time
 *                          The parameter can be combination of following values:
 *                          @arg ADC_SEQ_SEC_CHANNEL_0: convert channel 0
 *                          @arg ADC_SEQ_SEC_CHANNEL_1: convert channel 1
 *                          @arg ADC_SEQ_SEC_CHANNEL_2: convert channel 2
 *                          @arg ADC_SEQ_SEC_CHANNEL_3: convert channel 3
 *                          @arg ADC_SEQ_SEC_CHANNEL_4: convert channel 4
 *                          @arg ADC_SEQ_SEC_CHANNEL_5: convert channel 5
 *                          @arg ADC_SEQ_SEC_CHANNEL_6: convert channel 6
 *                          @arg ADC_SEQ_SEC_CHANNEL_7: convert channel 7
 *                          @arg ADC_SEQ_SEC_CHANNEL_8: convert channel 8
 *                          @arg ADC_SEQ_SEC_CHANNEL_12: convert channel 12
 *                          @arg ADC_SEQ_SEC_CHANNEL_13: convert channel 13
 *                          @arg ADC_SEQ_SEC_CHANNEL_14: convert channel 14
 *                          @arg ADC_SEQ_SEC_CHANNEL_15: convert channel 15
 *                          @arg ADC_SEQ_SEC_CHANNEL_16: convert channel 16
 *                          @arg ADC_SEQ_SEC_CHANNEL_17: convert channel 17
 *                          @arg ADC_SEQ_SEC_CHANNEL_18: convert channel 18
* @retval      None
 */
void ADC_ConfigSeqSectionTimeChannel(ADC_SEQ_SECTION_TIME_T time, ADC_SEQ_SECTION_CHANNEL_T channel)
{
    if (time < ADC_SEQ_SEC_TX_7)
    {
        ADC->SEQ_CHANNEL1 |= (channel << 5 * time);
    }
    else if ((time >= ADC_SEQ_SEC_TX_7) && (time < ADC_SEQ_SEC_TX_13))
    {
        ADC->SEQ_CHANNEL2 |= (channel << 5 * (time - ADC_SEQ_SEC_TX_7));
    }
    else if ((time >= ADC_SEQ_SEC_TX_13) && (time < ADC_SEQ_SEC_TX_19))
    {
        ADC->SEQ_CHANNEL3 |= (channel << 5 * (time - ADC_SEQ_SEC_TX_13));
    }
    else
    {
        ADC->SEQ_CHANNEL4 |= (channel << 5 * (time - ADC_SEQ_SEC_TX_19));
    }
}

/*!
 * @brief       Returns the last ADC sequencial section conversion result data
 *
 * @param       index:      index of convert data
 *                          The parameter can be combination of following values:
 *                          @arg ADC_SEQ_SEC_DATA_0: sequencial section convert data 0
 *                          @arg ADC_SEQ_SEC_DATA_1: sequencial section convert data 1
 *                          @arg ADC_SEQ_SEC_DATA_2: sequencial section convert data 2
 *                          @arg ADC_SEQ_SEC_DATA_3: sequencial section convert data 3
 *                          @arg ADC_SEQ_SEC_DATA_4: sequencial section convert data 4
 *                          @arg ADC_SEQ_SEC_DATA_5: sequencial section convert data 5
 *                          @arg ADC_SEQ_SEC_DATA_6: sequencial section convert data 6
 *                          @arg ADC_SEQ_SEC_DATA_7: sequencial section convert data 7
 *                          @arg ADC_SEQ_SEC_DATA_8: sequencial section convert data 8
 *                          @arg ADC_SEQ_SEC_DATA_9: sequencial section convert data 9
 *                          @arg ADC_SEQ_SEC_DATA_10: sequencial section convert data 10
 *                          @arg ADC_SEQ_SEC_DATA_11: sequencial section convert data 11
 *                          @arg ADC_SEQ_SEC_DATA_12: sequencial section convert data 12
 *                          @arg ADC_SEQ_SEC_DATA_13: sequencial section convert data 13
 *                          @arg ADC_SEQ_SEC_DATA_14: sequencial section convert data 14
 *                          @arg ADC_SEQ_SEC_DATA_15: sequencial section convert data 15
 *                          @arg ADC_SEQ_SEC_DATA_16: sequencial section convert data 16
 *                          @arg ADC_SEQ_SEC_DATA_17: sequencial section convert data 17
 *                          @arg ADC_SEQ_SEC_DATA_18: sequencial section convert data 18
 *
 * @retval      The sequencial section data conversion value
 */
uint16_t ADC_ReadSeqSecConvValue(ADC_SEQ_SECTION_DATA_T index)
{
    return ((uint16_t)ADC->SEQ_DATA[index]);
}

/*!
 * @brief       Enables the continuous mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableContinuousMode(void)
{
    ADC->CFG1_B.CMODESEL = BIT_SET;
}

/*!
 * @brief       Disables the continuous mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableContinuousMode(void)
{
    ADC->CFG1_B.CMODESEL = BIT_RESET;
}

/*!
 * @brief       Enables the discontinuous mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableDiscMode(void)
{
    ADC->CFG1_B.DISCEN = BIT_SET;
}

/*!
 * @brief       Disables the discontinuous mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableDiscMode(void)
{
    ADC->CFG1_B.DISCEN = BIT_RESET;
}

/*!
 * @brief       Enables the Overrun mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableOverrunMode(void)
{
    ADC->CFG1_B.OVRMAG = BIT_SET;
}

/*!
 * @brief       Disables the Overrun mode
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableOverrunMode(void)
{
    ADC->CFG1_B.OVRMAG = BIT_RESET;
}

/*!
 * @brief       ADC Read Calibration Factor
 *
 * @param       None
 *
 * @retval      ADC Calibration factor
 */
uint32_t ADC_ReadCalibrationFactor(void)
{
    uint32_t temp = 0, counter = 0, status = 0;

    ADC->CTRL_B.CAL = BIT_SET;

    do
    {
        status =  ADC->CTRL_B.CAL;
        counter++;
    }
    while ((counter != CALIBRATION_TIMEOUT) && (status != 0x00));

    if ((uint32_t)(ADC->CTRL_B.CAL) == RESET)
    {
        temp = ADC->DATA;
    }
    else
    {
        temp = 0x00000000;
    }

    return temp;
}

/*!
 * @brief       ADC stop conversion command
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_StopConversion(void)
{
    ADC->CTRL_B.STOPCEN = BIT_SET;
}

/*!
 * @brief       ADC start conversion command
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_StartConversion(void)
{
    ADC->CTRL_B.STARTCEN = BIT_SET;
}

/*!
 * @brief       Returns the last ADC conversion result data
 *
 * @param       None
 *
 * @retval      The Data conversion value
 */
uint16_t ADC_ReadConversionValue(void)
{
    return ((uint16_t)ADC->DATA);
}

/*!
 * @brief       Enables the ADC DMA request
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_EnableDMA(void)
{
    ADC->CFG1_B.DMAEN = BIT_SET;
}

/*!
 * @brief       Disables the ADC DMA request
 *
 * @param       None
 *
 * @retval      None
 */
void ADC_DisableDMA(void)
{
    ADC->CFG1_B.DMAEN = BIT_RESET;
}

/*!
 * @brief       ADC DMA Request Mode
 *
 * @param       DMARequestMode: Direct memery access configuration .
 *                              The parameter can be one of following values:
 *                              @arg ADC_DMA_MODE_ONESHOUT:    ADC DMA Mode Select one shot
 *                              @arg ADC_DMA_MODE_CIRCULAR:    ADC DMA Mode Select circular
 *
 * @retval      None
 */
void ADC_DMARequestMode(ADC_DMA_MODE_T DMARequestMode)
{
    ADC->CFG1_B.DMACFG = (uint8_t)DMARequestMode;
}

/*!
 * @brief       Enables the specified interrupts
 *
 * @param       interrupt:  Specifies the ADC interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg ADC_INT_ADRDY:    ADC ready interrupt
 *                          @arg ADC_INT_CSMP:     End of sampling interrupt
 *                          @arg ADC_INT_CC:       End of conversion interrupt
 *                          @arg ADC_INT_CS:       End of sequence interrupt
 *                          @arg ADC_INT_OVR:      ADC overrun interrupt
 *                          @arg ADC_INT_AWD:      Analog watchdog interrupt
 *                          @arg ADC_INT_CSSN3:    NUM.3 of sequential section sampling finish interrupt
 *                          @arg ADC_INT_CSSN1:    NUM.1 of sequential section sampling finish interrupt
 *                          @arg ADC_INT_CSSN2:    NUM.2 of sequential section sampling finish interrupt
 *
 * @retval      None
 */
void ADC_EnableInterrupt(uint32_t interrupt)
{
    ADC->IEN |= (uint32_t)interrupt;
}

/*!
 * @brief       Disable the specified interrupts
 *
 * @param       interrupt:  Specifies the ADC interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg ADC_INT_ADRDY:    ADC ready interrupt
 *                          @arg ADC_INT_CSMP:     End of sampling interrupt
 *                          @arg ADC_INT_CC:       End of conversion interrupt
 *                          @arg ADC_INT_CS:       End of sequence interrupt
 *                          @arg ADC_INT_OVR:      ADC overrun interrupt
 *                          @arg ADC_INT_AWD:      Analog watchdog interrupt
 *                          @arg ADC_INT_CSSN3:    NUM.3 of sequential section sampling finish interrupt
 *                          @arg ADC_INT_CSSN1:    NUM.1 of sequential section sampling finish interrupt
 *                          @arg ADC_INT_CSSN2:    NUM.2 of sequential section sampling finish interrupt
 *
 * @retval      None
 */
void ADC_DisableInterrupt(uint32_t interrupt)
{
    ADC->IEN &= (uint32_t)~interrupt;
}

/*!
 * @brief       Checks whether the specified ADC flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be one of the following values:
 *                      @arg ADC_FLAG_ADCON:    ADC enable flag
 *                      @arg ADC_FLAG_ADCOFF:   ADC disable flag
 *                      @arg ADC_FLAG_ADCSTA:   ADC start conversion flag
 *                      @arg ADC_FLAG_ADCSTOP:  ADC stop conversion flag
 *                      @arg ADC_FLAG_ADCCAL:   ADC calibration flag
 *                      @arg ADC_FLAG_ADRDY:    ADC ready flag
 *                      @arg ADC_FLAG_CSMP:     End of sampling flag
 *                      @arg ADC_FLAG_CC:       End of conversion flag
 *                      @arg ADC_FLAG_CS:       End of sequence flag
 *                      @arg ADC_FLAG_OVR:      ADC overrun flag
 *                      @arg ADC_FLAG_AWD:      Analog watchdog flag
 *                      @arg ADC_FLAG_CSSN3:    NUM.3 of sequential section sampling finish interrupt flag
 *                      @arg ADC_FLAG_CSSN1:    NUM.1 of sequential section sampling finish interrupt flag
 *                      @arg ADC_FLAG_CSSN2:    NUM.2 of sequential section sampling finish interrupt flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t ADC_ReadStatusFlag(ADC_FLAG_T flag)
{
    uint32_t status;

    if ((uint32_t)(flag & 0x01000000))
    {
        status = ADC->CTRL & 0xFEFFFFFF;
    }
    else
    {
        status = ADC->STS;
    }

    if ((status & flag) != (uint32_t)RESET)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified ADC flag
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be any combination of the following values:
 *                      @arg ADC_FLAG_ADRDY:    ADC ready flag
 *                      @arg ADC_FLAG_CSMP:     End of sampling flag
 *                      @arg ADC_FLAG_CC:       End of conversion flag
 *                      @arg ADC_FLAG_CS:       End of sequence flag
 *                      @arg ADC_FLAG_OVR:      ADC overrun flag
 *                      @arg ADC_FLAG_AWD:      Analog watchdog flag
 *                      @arg ADC_FLAG_CSSN3:    NUM.3 of sequential section sampling finish interrupt flag
 *                      @arg ADC_FLAG_CSSN1:    NUM.1 of sequential section sampling finish interrupt flag
 *                      @arg ADC_FLAG_CSSN2:    NUM.2 of sequential section sampling finish interrupt flag
 *
 * @retval      None
 */
void ADC_ClearStatusFlag(uint32_t flag)
{
    ADC->STS = (uint32_t)flag;
}

/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       flag:   Specifies the ADC interrupt pending bit to check
 *                      The parameter can be one of following values:
 *                      @arg ADC_INT_FLAG_ADRDY:    ADC ready interrupt
 *                      @arg ADC_INT_FLAG_CSMP:     End of sampling interrupt
 *                      @arg ADC_INT_FLAG_CC:       End of conversion interrupt
 *                      @arg ADC_INT_FLAG_CS:       End of sequence interrupt
 *                      @arg ADC_INT_FLAG_OVR:      ADC overrun interrupt
 *                      @arg ADC_INT_FLAG_AWD:      Analog watchdog interrupt
 *                      @arg ADC_FLAG_CSSN3:        NUM.3 of sequential section sampling finish interrupt
 *                      @arg ADC_FLAG_CSSN1:        NUM.1 of sequential section sampling finish interrupt
 *                      @arg ADC_FLAG_CSSN2:        NUM.2 of sequential section sampling finish interrupt
 *
 * @retval      None
 */
uint8_t ADC_ReadIntFlag(ADC_INT_FLAG_T flag)
{
    uint16_t intEnable;
    uint16_t intStatus;

    intEnable = (uint16_t)(ADC->IEN & (uint32_t)flag);

    intStatus = (uint16_t)(ADC->STS & (uint32_t)flag);

    if (intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clears the specified interrupt pending bits
 *
 * @param       flag:   Specifies the ADC interrupt pending bit to check
 *                      The parameter can be combination of following values:
 *                      @arg ADC_INT_FLAG_ADRDY:    ADC ready interrupt
 *                      @arg ADC_INT_FLAG_CSMP:     End of sampling interrupt
 *                      @arg ADC_INT_FLAG_CC:       End of conversion interrupt
 *                      @arg ADC_INT_FLAG_CS:       End of sequence interrupt
 *                      @arg ADC_INT_FLAG_OVR:      ADC overrun interrupt
 *                      @arg ADC_INT_FLAG_AWD:      Analog watchdog interrupt
 *                      @arg ADC_FLAG_CSSN3:        NUM.3 of sequential section sampling finish interrupt
 *                      @arg ADC_FLAG_CSSN1:        NUM.1 of sequential section sampling finish interrupt
 *                      @arg ADC_FLAG_CSSN2:        NUM.2 of sequential section sampling finish interrupt
 *
 * @retval      None
 */

void ADC_ClearIntFlag(uint32_t flag)
{
    ADC->STS = flag;
}

/**@} end of group ADC_Functions */
/**@} end of group ADC_Driver */
/**@} end of group APM32M35XX_StdPeriphDriver */

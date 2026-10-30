/*!
 * @file        apm32m35xx_tmr.h
 *
 * @brief       This file contains all the functions prototypes for the TMR firmware library
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

/* Define to prevent recursive inclusion */
#ifndef __APM32M35XX_TMR_H
#define __APM32M35XX_TMR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32m35xx.h"

/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup TMR_Driver
  @{
*/

/** @defgroup TMR_Macros Macros
  @{
*/

/**@} end of group TMR_Macros */

/** @defgroup  TMR_Enumerations Enumerations
  @{
*/

/**
 * @brief   Counter_Mode
 */
typedef enum
{
    TMR_COUNTER_MODE_UP = 0,
    TMR_COUNTER_MODE_DOWN = 1,
    TMR_COUNTER_MODE_CENTERALIGNED1 = 2,
    TMR_COUNTER_MODE_CENTERALIGNED2 = 4,
    TMR_COUNTER_MODE_CENTERALIGNED3 = 6
} TMR_COUNTER_MODE_T;

/**
 * @brief   Clock_Division_CKD
 */
typedef enum
{
    TMR_CKD_DIV1 = 0,
    TMR_CKD_DIV2 = 1,
    TMR_CKD_DIV4 = 2
} TMR_CKD_T;

/**
 * @brief   Prescaler_Reload_Mode
 */
typedef enum
{
    TMR_PRESCALER_RELOAD_UPDATA = 0,
    TMR_PRESCALER_RELOAD_IMMEDIATE = 1
} TMR_PRESCALER_RELOAD_T;

/**
 * @brief    TMR UpdateSource
 */
typedef enum
{
    TMR_UPDATE_SOURCE_GLOBAL = 0,
    TMR_UPDATE_SOURCE_REGULAR = 1
} TMR_UPDATE_SOURCE_T;

/**
 * @brief    TMR OPMode
 */
typedef enum
{
    TMR_OPMODE_REPETITIVE = 0,
    TMR_OPMODE_SINGLE = 1
} TMR_OPMODE_T;

/**
 * @brief TMR Specifies the Off-State selection used in Run mode
 */
typedef enum
{
    TMR_RMOS_STATE_DISABLE = 0,
    TMR_RMOS_STATE_ENABLE = 1
} TMR_RMOS_STATE_T;

/**
 * @brief TMR Closed state configuration in idle mode
 */
typedef enum
{
    TMR_IMOS_STATE_DISABLE = 0,
    TMR_IMOS_STATE_ENABLE = 1
} TMR_IMOS_STATE_T;

/**
 * @brief TMR Protect mode configuration values
 */
typedef enum
{
    TMR_LOCK_LEVEL_OFF = 0,
    TMR_LOCK_LEVEL_1 = 1,
    TMR_LOCK_LEVEL_2 = 2,
    TMR_LOCK_LEVEL_3 = 3
} TMR_LOCK_LEVEL_T;

/**
 * @brief TMR break state
 */
typedef enum
{
    TMR_BREAK_STATE_DISABLE,
    TMR_BREAK_STATE_ENABLE
} TMR_BREAK_STATE_T;

/**
 * @brief TMR Specifies the Break Input pin polarity.
 */
typedef enum
{
    TMR_BREAK_POLARITY_LOW,
    TMR_BREAK_POLARITY_HIGH
} TMR_BREAK_POLARITY_T;

/**
 * @brief TMR Automatic Output feature is enable or disable
 */
typedef enum
{
    TMR_AUTOMATIC_OUTPUT_DISABLE,
    TMR_AUTOMATIC_OUTPUT_ENABLE
} TMR_AUTOMATIC_OUTPUT_T;

/**
 * @brief TMR_Output_Compare_and_PWM_modes
 */
typedef enum
{
    TMR_OC_MODE_TMRING     = 0x00,
    TMR_OC_MODE_ACTIVE     = 0x01,
    TMR_OC_MODE_INACTIVE   = 0x02,
    TMR_OC_MODE_TOGGEL     = 0x03,
    TMR_OC_MODE_LOWLEVEL   = 0x04,
    TMR_OC_MODE_HIGHLEVEL  = 0x05,
    TMR_OC_MODE_PWM1       = 0x06,
    TMR_OC_MODE_PWM2       = 0x07
} TMR_OC_MODE_T;

/**
 * @brief TMR_Output_Compare_state
 */
typedef enum
{
    TMR_OUTPUT_STATE_DISABLE,
    TMR_OUTPUT_STATE_ENABLE
} TMR_OC_OUTPUT_STATE_T;

/**
 * @brief TMR_Output_Compare_N_state
 */
typedef enum
{
    TMR_OUTPUT_NSTATE_DISABLE,
    TMR_OUTPUT_NSTATE_ENABLE
} TMR_OC_OUTPUT_NSTATE_T;

/**
 * @brief TMR_Output_Compare_Polarity
 */
typedef enum
{
    TMR_OC_POLARITY_HIGH,
    TMR_OC_POLARITY_LOW
} TMR_OC_POLARITY_T;

/**
 * @brief TMR_Output_Compare_N_Polarity
 */
typedef enum
{
    TMR_OC_NPOLARITY_HIGH,
    TMR_OC_NPOLARITY_LOW
} TMR_OC_NPOLARITY_T;

/**
 * @brief TMR_Output_Compare_Idle_State
 */
typedef enum
{
    TMR_OCIDLESTATE_RESET,
    TMR_OCIDLESTATE_SET
} TMR_OC_IDLE_STATE_T;

/**
 * @brief TMR_Output_Compare_N_Idle_State
 */
typedef enum
{
    TMR_OCNIDLESTATE_RESET,
    TMR_OCNIDLESTATE_SET
} TMR_OC_NIDLE_STATE_T;

/**
 * @brief TMR Input Capture Init structure definition
 */
typedef enum
{
    TMR_CHANNEL_1 = 0x0000,
    TMR_CHANNEL_2 = 0x0004,
    TMR_CHANNEL_3 = 0x0008,
    TMR_CHANNEL_4 = 0x000C,
    TMR_CHANNEL_5 = 0x0010
} TMR_CHANNEL_T;

/**
 * @brief TMR Output Init structure definition
 */
typedef enum
{
    TMR_OUTPUT_CHANNEL_1 = 0x0001,
    TMR_OUTPUT_CHANNEL_2 = 0x0004,
    TMR_OUTPUT_CHANNEL_3 = 0x0010,
    TMR_OUTPUT_CHANNEL_4 = 0x0040,
    TMR_OUTPUT_CHANNEL_5 = 0x0080
} TMR_OUTPUT_CHANNEL_T;

/**
 * @brief    TMR ForcedAction
 */
typedef enum
{
    TMR_FORCEDACTION_INACTIVE = 0x04,
    TMR_FORCEDACTION_ACTIVE   = 0x05
} TMR_FORCED_ACTION_T;

/**
 * @brief    TMR Output_Compare_Preload_State
 */
typedef enum
{
    TMR_OC_PRELOAD_DISABLE,
    TMR_OC_PRELOAD_ENABLE
} TMR_OC_PRELOAD_T;

/**
 * @brief    TMR Output_Compare_Fast_State
 */
typedef enum
{
    TMR_OCFAST_DISABLE,
    TMR_OCFAST_ENABLE
} TMR_OCFAST_T;

/**
 * @brief    TMR Output_Compare_Clear_State
 */
typedef enum
{
    TMR_OCCLER_DISABLE,
    TMR_OCCLER_ENABLE
} TMR_OCCLER_T;

/**
 * @brief    TMR_OCReferenceClear Clear source
 */
typedef enum
{
    TMR_OCCS_OCREFCLR,
    TMR_OCCS_ETRF
} TMR_OCCSEL_T;

/**
 * @brief TMR Input_Capture_Polarity
 */
typedef enum
{
    TMR_IC_POLARITY_RISING   = 0x00,
    TMR_IC_POLARITY_FALLING  = 0x02,
    TMR_IC_POLARITY_BOTHEDGE = 0x0A
} TMR_IC_POLARITY_T;

/**
 * @brief TMR Input_Capture_Selection
 */
typedef enum
{
    TMR_IC_SELECTION_DIRECT_TI   = 0x01,
    TMR_IC_SELECTION_INDIRECT_TI = 0x02,
    TMR_IC_SELECTION_TRC         = 0x03
} TMR_IC_SELECTION_T;

/**
 * @brief TMR_Input_Capture_Prescaler
 */
typedef enum
{
    TMR_ICPSC_DIV1 = 0x00,
    TMR_ICPSC_DIV2 = 0x01,
    TMR_ICPSC_DIV4 = 0x02,
    TMR_ICPSC_DIV8 = 0x03
} TMR_IC_PRESCALER_T;

/**
 * @brief    TMR_interrupt_sources
 */
typedef enum
{
    TMR_INT_UPDATE = 0x0001,
    TMR_INT_CH1    = 0x0002,
    TMR_INT_CH2    = 0x0004,
    TMR_INT_CH3    = 0x0008,
    TMR_INT_CH4    = 0x0010,
    TMR_INT_CCU    = 0x0020,
    TMR_INT_TRG    = 0x0040,
    TMR_INT_BRK    = 0x0080
} TMR_INT_T;

/**
 * @brief    TMR_event_sources
 */
typedef enum
{
    TMR_EVENT_UPDATE = 0x0001,
    TMR_EVENT_CH1    = 0x0002,
    TMR_EVENT_CH2    = 0x0004,
    TMR_EVENT_CH3    = 0x0008,
    TMR_EVENT_CH4    = 0x0010,
    TMR_EVENT_CCU    = 0x0020,
    TMR_EVENT_TRG    = 0x0040,
    TMR_EVENT_BRK    = 0x0080
} TMR_EVENT_T;

/**
 * @brief    TMR_interrupt_flag
 */
typedef enum
{
    TMR_INT_FLAG_UPDATE = 0x0001,
    TMR_INT_FLAG_CH1    = 0x0002,
    TMR_INT_FLAG_CH2    = 0x0004,
    TMR_INT_FLAG_CH3    = 0x0008,
    TMR_INT_FLAG_CH4    = 0x0010,
    TMR_INT_FLAG_CCU    = 0x0020,
    TMR_INT_FLAG_TRG    = 0x0040,
    TMR_INT_FLAG_BRK    = 0x0080
} TMR_INT_FLAG_T;

/**
 * @brief    TMR Flag
 */
typedef enum
{
    TMR_FLAG_UPDATE  = 0x0001,
    TMR_FLAG_CH1     = 0x0002,
    TMR_FLAG_CH2     = 0x0004,
    TMR_FLAG_CH3     = 0x0008,
    TMR_FLAG_CH4     = 0x0010,
    TMR_FLAG_CCU     = 0x0020,
    TMR_FLAG_TRG     = 0x0040,
    TMR_FLAG_BRK     = 0x0080,
    TMR_FLAG_CH1OC   = 0x0200,
    TMR_FLAG_CH2OC   = 0x0400,
    TMR_FLAG_CH3OC   = 0x0800,
    TMR_FLAG_CH4OC   = 0x1000
} TMR_FLAG_T;

/**
 * @brief    TMR DMA Base Address
 */
typedef enum
{
    TMR_DMABASE_CTRL1   = 0x0000,
    TMR_DMABASE_CTRL2   = 0x0001,
    TMR_DMABASE_SMCTRL  = 0x0002,
    TMR_DMABASE_DIEN    = 0x0003,
    TMR_DMABASE_STS     = 0x0004,
    TMR_DMABASE_SCEG    = 0x0005,
    TMR_DMABASE_CCM1    = 0x0006,
    TMR_DMABASE_CCM2    = 0x0007,
    TMR_DMABASE_CHCTRL  = 0x0008,
    TMR_DMABASE_CNT     = 0x0009,
    TMR_DMABASE_DIV     = 0x000A,
    TMR_DMABASE_AUTORLD = 0x000B,
    TMR_DMABASE_REPCNT  = 0x000C,
    TMR_DMABASE_CH1CC   = 0x000D,
    TMR_DMABASE_CH2CC   = 0x000E,
    TMR_DMABASE_CH3CC   = 0x000F,
    TMR_DMABASE_CH4CC   = 0x0010,
    TMR_DMABASE_BDT     = 0x0011,
    TMR_DMABASE_DMAB    = 0x0012
} TMR_DMA_BASE_ADDERSS_T;

/**
 * @brief    TMR DMA Burst Lenght
 */
typedef enum
{
    TMR_DMA_BURSTLENGHT_1TRANSFER   = 0x0000,
    TMR_DMA_BURSTLENGHT_2TRANSFERS  = 0x0100,
    TMR_DMA_BURSTLENGHT_3TRANSFERS  = 0x0200,
    TMR_DMA_BURSTLENGHT_4TRANSFERS  = 0x0300,
    TMR_DMA_BURSTLENGHT_5TRANSFERS  = 0x0400,
    TMR_DMA_BURSTLENGHT_6TRANSFERS  = 0x0500,
    TMR_DMA_BURSTLENGHT_7TRANSFERS  = 0x0600,
    TMR_DMA_BURSTLENGHT_8TRANSFERS  = 0x0700,
    TMR_DMA_BURSTLENGHT_9TRANSFERS  = 0x0800,
    TMR_DMA_BURSTLENGHT_10TRANSFERS = 0x0900,
    TMR_DMA_BURSTLENGHT_11TRANSFERS = 0x0A00,
    TMR_DMA_BURSTLENGHT_12TRANSFERS = 0x0B00,
    TMR_DMA_BURSTLENGHT_13TRANSFERS = 0x0C00,
    TMR_DMA_BURSTLENGHT_14TRANSFERS = 0x0D00,
    TMR_DMA_BURSTLENGHT_15TRANSFERS = 0x0E00,
    TMR_DMA_BURSTLENGHT_16TRANSFERS = 0x0F00,
    TMR_DMA_BURSTLENGHT_17TRANSFERS = 0x1000,
    TMR_DMA_BURSTLENGHT_18TRANSFERS = 0x1100,
} TMR_DMA_BURST_LENGHT_T;

/**
 * @brief    TMR DMA Soueces
 */
typedef enum
{
    TMR_DMA_UPDATE    = 0x0100,
    TMR_DMA_CH1       = 0x0200,
    TMR_DMA_CH2       = 0x0400,
    TMR_DMA_CH3       = 0x0800,
    TMR_DMA_CH4       = 0x1000,
    TMR_DMA_CCU       = 0x2000,
    TMR_DMA_TRG       = 0x4000
} TMR_DMA_SOUCES_T;

/**
 * @brief    TMR Internal_Trigger_Selection
 */
typedef enum
{
    TMR_TS_ITR0     = 0x00,
    TMR_TS_ITR1     = 0x01,
    TMR_TS_ITR2     = 0x02,
    TMR_TS_ITR3     = 0x03,
    TMR_TS_TI1F_ED  = 0x04,
    TMR_TS_TI1FP1   = 0x05,
    TMR_TS_TI2FP2   = 0x06,
    TMR_TS_ETRF     = 0x07
} TMR_INPUT_TRIGGER_SOURCE_T;

/**
 * @brief    TMR  The external Trigger Prescaler.
 */
typedef enum
{
    TMR_ExtTRGPSC_OFF   = 0x00,
    TMR_EXTTRGPSC_DIV2  = 0x01,
    TMR_EXTTRGPSC_DIV4  = 0x02,
    TMR_EXTTRGPSC_DIV8  = 0x03
} TMR_EXTTRG_PRESCALER_T;

/**
 * @brief    TMR External_Trigger_Polarity
 */
typedef enum
{
    TMR_EXTTRGPOLARITY_INVERTED      = 0x01,
    TMR_EXTTGRPOLARITY_NONINVERTED   = 0x00
} TMR_EXTTRG_POLARITY_T;

/**
 * @brief    TMR OPMode
 */
typedef enum
{
    TMR_TRGOSOURCE_RESET,
    TMR_TRGOSOURCE_ENABLE,
    TMR_TRGOSOURCE_UPDATE,
    TMR_TRGOSOURCE_OC1,
    TMR_TRGOSOURCE_OC1REF,
    TMR_TRGOSOURCE_OC2REF,
    TMR_TRGOSOURCE_OC3REF,
    TMR_TRGOSOURCE_OC4REF,
    TMR_TRGOSOURCE_SZESPE,
    TMR_TRGOSOURCE_OC5REF,
    TMR_TRGOSOURCE_OC4REF_BOTHEDGE,
    TMR_TRGOSOURCE_OCREF_BOTHEDGE,
    TMR_TRGOSOURCE_OC4REF_OC5REF_UP,
    TMR_TRGOSOURCE_OC4REF_OC5REF_DOWN,
    TMR_TRGOSOURCE_OC4REF_UP_OC5REF_DOWN,
    TMR_TRGOSOURCE_OC4REF_DOWN_OC5REF_UP
} TMR_TRGOSOURCE_T;

/**
 * @brief    TMR OPMode
 */
typedef enum
{
    TMR_SLAVEMODE_RESET     = 0x04,
    TMR_SLAVEMODE_GATED     = 0x05,
    TMR_SLAVEMODE_TRIGGER   = 0x06,
    TMR_SLAVEMODE_EXTERNALL = 0x07
} TMR_SLAVEMODE_T;

/**
 * @brief    TMR Encoder_Mode
 */
typedef enum
{
    TMR_ENCODER_MODE_TI1      = 0x01,
    TMR_ENCODER_MODE_TI2      = 0x02,
    TMR_ENCODER_MODE_TI12     = 0x03
} TMR_ENCODER_MODE_T;

/**
 * @brief    TMR Remap Select
 */
typedef enum
{
    TMR_REMAP_GPIO      = 0x00,
    TMR_REMAP_RTC_CLK   = 0x01,
    TMR_REMAP_HSEDiv32  = 0x02,
    TMR_REMAP_MCO       = 0x03
} TMR_REMAP_T;

/**
 * @brief    TMR External Brake Input Filter
 */
typedef enum
{
    TMR_BKF_DISABLE,
    TMR_BKF_DIV1_N2,
    TMR_BKF_DIV1_N4,
    TMR_BKF_DIV1_N8,
    TMR_BKF_DIV2_N6,
    TMR_BKF_DIV2_N8,
    TMR_BKF_DIV4_N6,
    TMR_BKF_DIV4_N8,
    TMR_BKF_DIV8_N6,
    TMR_BKF_DIV8_N8,
    TMR_BKF_DIV16_N5,
    TMR_BKF_DIV16_N6,
    TMR_BKF_DIV16_N8,
    TMR_BKF_DIV32_N5,
    TMR_BKF_DIV32_N6,
    TMR_BKF_DIV32_N8
} TMR_BKF_T;

/**
 * @brief    TMR Channel Data Selection
 */
typedef enum
{
    TMR_CHANNEL_DATA_0_15,
    TMR_CHANNEL_DATA_16_31,
    TMR_CHANNEL_DATA_32_47
} TMR_CHANNEL_DATA_T;

/**
 * @brief    TMR Channel N Data Selection
 */
typedef enum
{
    TMR_CHANNEL_N_DATA_16_31,
    TMR_CHANNEL_N_DATA_48_63,
    TMR_CHANNEL_N_DATA_80_95
} TMR_CHANNEL_N_DATA_T;

/**
 * @brief    TMR PWM Cycle Select
 */
typedef enum
{
    TMR_M0CP_CYCLE_AUTORLD_SHADOW,
    TMR_M0CP_CYCLE_AUTORLD
} TMR_M0CP_CYCLE_T;

/**
 * @brief    TMR M0CP Buffer Select
 */
typedef enum
{
    TMR_M0CP_BUFFER_NEXT,
    TMR_M0CP_BUFFER_NOW
} TMR_M0CP_BUFFER_T;

/**
 * @brief    TMR M0CP PDCON Select
 */
typedef enum
{
    TMR_M0CP_PDCON_RESET,
    TMR_M0CP_PDCON_SET
} TMR_M0CP_PDCON_T;

/**
 * @brief    TMR M0CP Update Select
 */
typedef enum
{
    TMR_M0CP_UPDATE_RESET,
    TMR_M0CP_UPDATE_SET
} TMR_M0CP_UPDATE_T;

/**
 * @brief    TMR Output Channel Control
 */
typedef enum
{
    TMR_OUTPUT_MODE_PWM,
    TMR_OUTPUT_MODE_POLARITY
} TMR_OUTPUT_MODE_T;

/**
 * @brief    TMR Output Channel Polarity
 */
typedef enum
{
    TMR_OUTPUT_POLARITY_LOW,
    TMR_OUTPUT_POLARITY_HIGH
} TMR_OUTPUT_POLARITY_T;


/**
 * @brief    TMR Output Buffer Select
 */
typedef enum
{
    TMR_OUTPUT_BUFFER_NOW,
    TMR_OUTPUT_BUFFER_NEXT
} TMR_OUTPUT_BUFFER_T;

/**
 * @brief    TMR TRGO Signal Select
 */
typedef enum
{
    TMR_TRGO1_SIGNAL,
    TMR_TRGO2_SIGNAL,
    TMR_TRGO3_SIGNAL
} TMR_TRGO_SIGNAL_T;

/**
 * @brief    TMR TRGO Signal Generate Select
 */
typedef enum
{
    TMR_NO_GENERATE_TRGO,
    TMR_GENERATE_TRGO
} TMR_TRGO_GENERATE_T;

/**@} end of group TMR_Enumerations*/

/** @defgroup TMR_Structures Structures
  @{
*/

/**
  * @brief  TMR Time Base Init structure definition
  * @note   This sturcture is used with all TMRx.
  */
typedef struct
{
    uint16_t              div;
    TMR_COUNTER_MODE_T    counterMode;
    uint32_t              period;
    TMR_CKD_T             clockDivision;
    uint8_t               repetitionCounter;
} TMR_TimeBase_T;

/**
 * @brief    TMR BDT structure definition
 */
typedef struct
{
    TMR_RMOS_STATE_T        RMOS_State;
    TMR_IMOS_STATE_T        IMOS_State;
    TMR_LOCK_LEVEL_T        lockLevel;
    uint8_t                 deadTime;
    TMR_BREAK_STATE_T       breakState;
    TMR_BREAK_POLARITY_T    breakPolarity;
    TMR_AUTOMATIC_OUTPUT_T  automaticOutput;
} TMR_BDTInit_T;
/**
 * @brief    TMR Config struct definition
 */
typedef struct
{
    TMR_OC_MODE_T           OC_Mode;            /*!< Specifies the TMR mode */
    TMR_OC_OUTPUT_STATE_T   OC_OutputState;     /*!< Specifies the TMR Output Compare state */
    TMR_OC_OUTPUT_NSTATE_T  OC_OutputNState;    /*!< Specifies the TMR complementary Output Compare state */
    /*!< @note This parameter is valid only for TMR1 */
    TMR_OC_POLARITY_T       OC_Polarity;        /*!< Specifies the output polarity. */
    TMR_OC_NPOLARITY_T      OC_NPolarity;       /*!< Specifies the complementary output polarity */
    /*!< @note This parameter is valid only for TMR1 */
    TMR_OC_IDLE_STATE_T     OC_Idlestate;       /*!< Specifies the TMR Output Compare pin state during Idle state */
    /*!< @note This parameter is valid only for TMR1 */
    TMR_OC_NIDLE_STATE_T    OC_NIdlestate;      /*!< Specifies the TMR Output Compare pin state during Idle state */
    /*!< @note This parameter is valid only for TMR1 */
    uint16_t              Pulse;                /*!< Specifies the pulse value to be loaded into the Capture Compare Register. */

} TMR_OCConfig_T;

/**
 * @brief    TMR Input Capture Config struct definition
 */
typedef struct
{
    TMR_CHANNEL_T channel;          /*!<  Specifies the TMR channel */
    TMR_IC_POLARITY_T ICpolarity;   /*!< Specifies the active edge of the input signal */
    TMR_IC_SELECTION_T ICselection; /*!<  Specifies the input */
    TMR_IC_PRESCALER_T ICprescaler; /*!<  Specifies the Input Capture Prescaler */
    uint16_t  ICfilter;             /*!< Specifies the input capture filter */

} TMR_ICConfig_T;

/**@} end of group TMR_Structures*/

/** @defgroup TMR_Variables Variables
  @{
*/

/**@} end of group TMR_Variables */

/** @defgroup  TMR_Functions Functions
  @{
*/
/* TimeBase management */
void TMR_Reset(TMR_T* TMRx);
void TMR_ConfigTimeBase(TMR_T* TMRx, TMR_TimeBase_T* timeBaseConfig);
void TMR_ConfigTimeBaseStruct(TMR_TimeBase_T* timeBaseConfig);
void TMR_ConfigDIV(TMR_T* TMRx, uint16_t div, TMR_PRESCALER_RELOAD_T mode);
void TMR_ConfigCounterMode(TMR_T* TMRx, TMR_COUNTER_MODE_T mode);
void TMR_SetCounter(TMR_T* TMRx, uint32_t counter);
void TMR_SetAutoReload(TMR_T* TMRx, uint32_t autoReload);
uint32_t TMR_ReadCounter(TMR_T* TMRx);
uint32_t TMR_ReadDiv(TMR_T* TMRx);
void TMR_EnableNGUpdate(TMR_T* TMRx);
void TMR_DisableNGUpdate(TMR_T* TMRx);
void TMR_ConfigUPdateRequest(TMR_T* TMRx, TMR_UPDATE_SOURCE_T source);
void TMR_EnableAUTOReload(TMR_T* TMRx);
void TMR_DisableAUTOReload(TMR_T* TMRx);
void TMR_SetClockDivision(TMR_T* TMRx, TMR_CKD_T clockDivision);
void TMR_Enable(TMR_T* TMRx);
void TMR_Disable(TMR_T* TMRx);
void TMR_ConfigBDT(TMR_T* TMRx, TMR_BDTInit_T* structure);
void TMR_ConfigBDTStructInit(TMR_BDTInit_T* structure);

void TMR_EnablePWMOutputs(TMR_T* TMRx);
void TMR_DisablePWMOutputs(TMR_T* TMRx);

void TMR_OC1Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC2Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC3Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC4Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC5Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OCConfigStructInit(TMR_OCConfig_T* OCcongigStruct);

void TMR_SelectOCxMode(TMR_T* TMRx, TMR_CHANNEL_T channel, TMR_OC_MODE_T mode);
void TMR_SelectSlaveMode(TMR_T* TMRx, TMR_SLAVEMODE_T mode);
void TMR_SelectOnePulseMode(TMR_T* TMRx, TMR_OPMODE_T OPMode);

void TMR_SetCompare1(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare1N(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare2(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare2N(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare3(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare3N(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare4(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare5(TMR_T* TMRx, uint32_t compare);

void TMR_ForcedOC1Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC2Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC3Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC4Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC5Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);

void TMR_EnableCCPreload(TMR_T* TMRx);
void TMR_DisableCCPreload(TMR_T* TMRx);

void TMR_OC1PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC2PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC3PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC4PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC5PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);

void TMR_OC1FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC2FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC3FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC4FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC5FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);

void TMR_OC1PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC1NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_OC2PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC2NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_OC3PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC3NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_OC4PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC5PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);

void TMR_SelectOCREFClear(TMR_T* TMRx, TMR_OCCSEL_T OCReferenceClear);

void TMR_EnableCCxChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_DisableCCxChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_EnableCCxNChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_DisableCCxNChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);

void TMR_EnableAUTOReload(TMR_T* TMRx);
void TMR_DisableAUTOReload(TMR_T* TMRx);
void TMR_EnableSelectCOM(TMR_T* TMRx);
void TMR_DisableSelectCOM(TMR_T* TMRx);

void TMR_ICConfig(TMR_T* TMRx, TMR_ICConfig_T* ICconfigstruct);
void TMR_ICConfigStructInit(TMR_ICConfig_T* ICconfigstruct);

void TMR_PWMConfig(TMR_T* TMRx, TMR_ICConfig_T* ICconfigstruct);

uint16_t TMR_ReadCaputer1(TMR_T* TMRx);
uint16_t TMR_ReadCaputer1N(TMR_T* TMRx);
uint16_t TMR_ReadCaputer2(TMR_T* TMRx);
uint16_t TMR_ReadCaputer2N(TMR_T* TMRx);
uint16_t TMR_ReadCaputer3(TMR_T* TMRx);
uint16_t TMR_ReadCaputer3N(TMR_T* TMRx);
uint16_t TMR_ReadCaputer4(TMR_T* TMRx);
uint16_t TMR_ReadCaputer5(TMR_T* TMRx);

void TMR_SetIC1Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);
void TMR_SetIC2Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);
void TMR_SetIC3Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);
void TMR_SetIC4Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);

/* Interrupts and Event management functions */
void TMR_EnableInterrupt(TMR_T* TMRx, uint16_t interrupt);
void TMR_DisableInterrupt(TMR_T* TMRx, uint16_t interrupt);
void TMR_GenerateEvent(TMR_T* TMRx, uint16_t event);

uint16_t TMR_ReadStatusFlag(TMR_T* TMRx, TMR_FLAG_T flag);
void TMR_ClearStatusFlag(TMR_T* TMRx, uint16_t flag);
uint16_t TMR_ReadIntFlag(TMR_T* TMRx,  TMR_INT_FLAG_T flag);
void TMR_ClearIntFlag(TMR_T* TMRx,  uint16_t flag);

void TMR_ConfigDMA(TMR_T* TMRx, TMR_DMA_BASE_ADDERSS_T address, TMR_DMA_BURST_LENGHT_T lenght);
void TMR_EnableDMASoure(TMR_T* TMRx, uint16_t souces);
void TMR_DisableDMASoure(TMR_T* TMRx, uint16_t souces);
void TMR_EnableCCDMA(TMR_T* TMRx);
void TMR_DisableCCDMA(TMR_T* TMRx);

/* Clocks management */
void TMR_ConfigInternalClock(TMR_T* TMRx);
void TMR_ConfigITRxExternalClock(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input);
void TMR_ConfigTIxExternalClock(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input,
                                TMR_IC_POLARITY_T ICpolarity, uint16_t ICfilter);
void TMR_ConfigExternalClockMode1(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                                  TMR_EXTTRG_POLARITY_T polarity, uint16_t filter);
void TMR_ConfigExternalClockMode2(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                                  TMR_EXTTRG_POLARITY_T polarity, uint16_t filter);
/* Synchronization management */
void TMR_SelectInputTrigger(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input);
void TMR_SelectOutputTrigger1(TMR_T* TMRx, TMR_TRGOSOURCE_T source);
void TMR_SelectOutputTrigger2(TMR_T* TMRx, TMR_TRGOSOURCE_T source);
void TMR_SelectOutputTrigger3(TMR_T* TMRx, TMR_TRGOSOURCE_T source);
void TMR_EnableMasterSlaveMode(TMR_T* TMRx);
void TMR_DisableMasterSlaveMode(TMR_T* TMRx);
void TMR_ConfigExternalTrigger(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                               TMR_EXTTRG_POLARITY_T polarity, uint16_t filter);

/* Specific interface management */
void TMR_ConfigEncodeInterface(TMR_T* TMRx, TMR_ENCODER_MODE_T encodeMode, TMR_IC_POLARITY_T IC1Polarity,
                               TMR_IC_POLARITY_T IC2Polarity);
void TMR_EnableHallSensor(TMR_T* TMRx);
void TMR_DisableHallSensor(TMR_T* TMRx);

void TMR_EnableAsymmetricPWMChannelOutput(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_DisableAsymmetricPWMChannelOutput(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_WhenCounterZeroSelectTRGO(TMR_T* TMRx, TMR_TRGO_SIGNAL_T TRGOx, TMR_TRGO_GENERATE_T state);
void TMR_WhenCounterMatchesSelectTRGO(TMR_T* TMRx, TMR_TRGO_SIGNAL_T TRGOx, TMR_TRGO_GENERATE_T state);
void TMR_ExternalBrakeInputFilter(TMR_T* TMRx, TMR_BKF_T filter);
void TMR_ChannelxDataSelect(TMR_T* TMRx, TMR_CHANNEL_T channel, TMR_CHANNEL_DATA_T dataBit);
void TMR_ChannelxNDataSelect(TMR_T* TMRx, TMR_CHANNEL_T channel, TMR_CHANNEL_N_DATA_T dataBit);
void TMR_SelectM0CPPWMCycleMode(TMR_T* TMRx, TMR_M0CP_CYCLE_T cycleMode);
void TMR_SelectM0CPBuffMode(TMR_T* TMRx, TMR_M0CP_BUFFER_T buffMode);
void TMR_SelectM0CPPDCONMode(TMR_T* TMRx, TMR_M0CP_PDCON_T pdconMode);
void TMR_SelectM0CPUpdateMode(TMR_T* TMRx, TMR_M0CP_UPDATE_T updateMode);
void TMR_SelectOutputBufferMode(TMR_T* TMRx, TMR_OUTPUT_BUFFER_T buffMode);
void TMR_OutputChannelMode(TMR_T* TMRx, TMR_OUTPUT_CHANNEL_T channel, TMR_OUTPUT_MODE_T mode);
void TMR_OutputChannelNMode(TMR_T* TMRx, TMR_OUTPUT_CHANNEL_T channel, TMR_OUTPUT_MODE_T mode);
void TMR_OutputChannelPolarity(TMR_T* TMRx, TMR_OUTPUT_CHANNEL_T channel, TMR_OUTPUT_POLARITY_T polarity);
void TMR_OutputChannelNPolarity(TMR_T* TMRx, TMR_OUTPUT_CHANNEL_T channel, TMR_OUTPUT_POLARITY_T polarity);

/**@} end of group TMR_Functions*/
/**@} end of group TMR_Driver */
/**@} end of group APM32M35XX_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32M35XX_TMR_H */

/*!
 * @file        apm32m35xx_rcm.h
 *
 * @brief       This file contains all the functions prototypes for the RCM firmware library
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
#ifndef __APM32M35XX_RCM_H
#define __APM32M35XX_RCM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32m35xx.h"

/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup RCM_Driver
  @{
*/

/** @defgroup RCM_Macros Macros
  @{
*/

/**@} end of group RCM_Macros */

/** @defgroup RCM_Enumerations Enumerations
  @{
*/

/**
 * @brief   HSE enum
 */
typedef enum
{
    RCM_HSE_CLOSE   = 0x00,
    RCM_HSE_OPEN    = 0x01,
    RCM_HSE_BYPASS  = 0x05,
} RCM_HSE_T;

/**
 * @brief   System clock select
 */
typedef enum
{
    RCM_PLL_SEL_HSI_DIV2,
    RCM_PLL_SEL_HSE,
} RCM_PLL_SEL_T;

/**
 * @brief   PLL multiplication factor
 */
typedef enum
{
    RCM_PLLMF_2,
    RCM_PLLMF_3,
    RCM_PLLMF_4,
    RCM_PLLMF_5,
    RCM_PLLMF_6,
    RCM_PLLMF_7,
    RCM_PLLMF_8,
    RCM_PLLMF_9,
    RCM_PLLMF_10,
    RCM_PLLMF_11,
    RCM_PLLMF_12,
    RCM_PLLMF_13,
    RCM_PLLMF_14,
    RCM_PLLMF_15,
    RCM_PLLMF_16,
} RCM_PLLMF_T;

/**
 * @brief   RCM clock division
 */
typedef enum
{
    RCM_CLK_DIV_1,
    RCM_CLK_DIV_2,
    RCM_CLK_DIV_3,
    RCM_CLK_DIV_4,
    RCM_CLK_DIV_5,
    RCM_CLK_DIV_6,
    RCM_CLK_DIV_7,
    RCM_CLK_DIV_8,
    RCM_CLK_DIV_9,
    RCM_CLK_DIV_10,
    RCM_CLK_DIV_11,
    RCM_CLK_DIV_12,
    RCM_CLK_DIV_13,
    RCM_CLK_DIV_14,
    RCM_CLK_DIV_15,
    RCM_CLK_DIV_16,
} RCM_CLK_DIV_T;

/**
 * @brief   Clock output control
 */
typedef enum
{
    RCM_COC_NO_CLOCK = 0,
    RCM_COC_HSI14 = 1,
    RCM_COC_LSI = 2,
    RCM_COC_SYSCLK = 4,
    RCM_COC_HSI = 5,
    RCM_COC_HSE = 6,
    RCM_COC_PLLCLK_DIV_2 = 7,
} RCM_COCCLK_T;

/**
 * @brief   System clock select
 */
typedef enum
{
    RCM_SYSCLK_SEL_HSI,
    RCM_SYSCLK_SEL_HSE,
    RCM_SYSCLK_SEL_PLL,
} RCM_SYSCLK_SEL_T;

/**
 * @brief   AHB divider Number
 */
typedef enum
{
    RCM_SYSCLK_DIV_1 = 7,
    RCM_SYSCLK_DIV_2,
    RCM_SYSCLK_DIV_4,
    RCM_SYSCLK_DIV_8,
    RCM_SYSCLK_DIV_16,
    RCM_SYSCLK_DIV_64,
    RCM_SYSCLK_DIV_128,
    RCM_SYSCLK_DIV_256,
    RCM_SYSCLK_DIV_512,
} RCM_AHBDIV_T;

/**
 * @brief   APB divider Number
 */
typedef enum
{
    RCM_HCLK_DIV_1 = 3,
    RCM_HCLK_DIV_2,
    RCM_HCLK_DIV_4,
    RCM_HCLK_DIV_8,
    RCM_HCLK_DIV_16
} RCM_APBDIV_T;

/**
 * @brief   I2C clock source selectio
 */
typedef enum
{
    RCM_I2CCLK_HSI,
    RCM_I2CCLK_SYSCLK,
} RCM_I2CCLK_T;

/**
 * @brief   USART clock source selectio
 */
typedef enum
{
    RCM_USART1CLK_PCLK    = ((uint32_t)0x00010000),
    RCM_USART1CLK_SYSCLK  = ((uint32_t)0x00010001),
    RCM_USART1CLK_HSI     = ((uint32_t)0x00010003),
} RCM_USARTCLK_T;

/**
 * @brief   RTC clock select
 */
typedef enum
{
    RCM_RTCCLK_LSI = 0x02,
    RCM_RTCCLK_HSE_DIV_32
} RCM_RTCCLK_T;

/**
 * @brief   AHB peripheral
 */
typedef enum
{
    RCM_AHB_PERIPH_DMA      = BIT0,
    RCM_AHB_PERIPH_SRAM     = BIT2,
    RCM_AHB_PERIPH_FPU      = BIT4,
    RCM_AHB_PERIPH_CRC      = BIT6,
    RCM_AHB_PERIPH_GPIOA    = BIT17,
    RCM_AHB_PERIPH_GPIOB    = BIT18,
    RCM_AHB_PERIPH_GPIOC    = BIT19,
    RCM_AHB_PERIPH_GPIOF    = BIT22,
    RCM_AHB_PERIPH_M0CP     = BIT24,
} RCM_AHB_PERIPH_T;

/**
 * @brief   APB2 peripheral
 */
typedef enum
{
    RCM_APB2_PERIPH_SYSCFG  = BIT0,
    RCM_APB2_PERIPH_ADC     = BIT9,
    RCM_APB2_PERIPH_TMR1    = BIT11,
    RCM_APB2_PERIPH_SPI     = BIT12,
    RCM_APB2_PERIPH_USART1  = BIT14,
    RCM_APB2_PERIPH_TMR7    = BIT16,
    RCM_APB2_PERIPH_DBGMCU  = BIT22,
} RCM_APB2_PERIPH_T;

/**
 * @brief   APB1 peripheral
 */
typedef enum
{
    RCM_APB1_PERIPH_TMR2    = BIT0,
    RCM_APB1_PERIPH_TMR3    = BIT1,
    RCM_APB1_PERIPH_TMR6    = BIT4,
    RCM_APB1_PERIPH_TMR4    = BIT8,
    RCM_APB1_PERIPH_WWDT    = BIT11,
    RCM_APB1_PERIPH_USART2  = BIT17,
    RCM_APB1_PERIPH_I2C     = BIT21,
    RCM_APB1_PERIPH_CAN     = BIT25,
    RCM_APB1_PERIPH_PMU     = BIT28,
} RCM_APB1_PERIPH_T;

/**
 * @brief   RCM Interrupt Source
 */
typedef enum
{
    RCM_INT_LSIRDY      = BIT0,      /*!< LSI ready interrupt */
    RCM_INT_HSIRDY      = BIT2,      /*!< HSI ready interrupt */
    RCM_INT_HSERDY      = BIT3,      /*!< HSE ready interrupt */
    RCM_INT_PLLRDY      = BIT4,      /*!< PLL ready interrupt */
    RCM_INT_HSI14RDY    = BIT5,      /*!< HSI14 ready interrupt */
    RCM_INT_CSS         = BIT7       /*!< Clock security system interrupt */
} RCM_INT_T;

/**
 * @brief   RCM FLAG define
 */
typedef enum
{
    RCM_FLAG_HSIRDY     = 0x001,      /*!< HSI Ready Flag */
    RCM_FLAG_HSERDY     = 0x011,      /*!< HSE Ready Flag */
    RCM_FLAG_PLLRDY     = 0x019,      /*!< PLL Ready Flag */
    RCM_FLAG_LSIRDY     = 0x201,      /*!< LSI Ready Flag */
    RCM_FLAG_V18PRRST   = 0x217,      /*!< Software reset flag */
    RCM_FLAG_OBRST      = 0x219,      /*!< Option byte loader reset flag */
    RCM_FLAG_PINRST     = 0x21A,      /*!< PIN reset flag */
    RCM_FLAG_PWRRST     = 0x21B,      /*!< POR/PDR reset flag */
    RCM_FLAG_SWRST      = 0x21C,      /*!< Software reset flag */
    RCM_FLAG_IWDTRST    = 0x21D,      /*!< Independent watchdog reset flag */
    RCM_FLAG_WWDTRST    = 0x21E,      /*!< Window watchdog reset flag */
    RCM_FLAG_LPRRST     = 0x21F,      /*!< Low-power reset flag */
    RCM_FLAG_HSI14RDY   = 0x301,      /*!< HSI14 Ready Flag */
} RCM_FLAG_T;

/**@} end of group RCM_Enumerations*/

/** @defgroup RCM_Structures Structures
  @{
*/

/**@} end of group RCM_Structures */

/** @defgroup RCM_Variables Variables
  @{
*/

/**@} end of group RCM_Variables */

/** @defgroup RCM_Fuctions Fuctions
  @{
*/

void RCM_Reset(void);

void RCM_ConfigHSE(RCM_HSE_T state);
uint8_t RCM_WaitHSEReady(void);
void RCM_SetHSITrim(uint8_t HSITrim);
void RCM_EnableHSI(void);
void RCM_DisableHSI(void);

void RCM_SetHSI14Trim(uint8_t HSI14Trim);
void RCM_EnableHSI14(void);
void RCM_DisableHSI14(void);
void RCM_EnableHSI14ADC(void);
void RCM_DisableHSI14ADC(void);

void RCM_EnableLSI(void);
void RCM_DisableLSI(void);

void RCM_ConfigPLL(RCM_PLL_SEL_T pllSelect, RCM_PLLMF_T pllMf);
void RCM_EnablePLL(void);
void RCM_DisablePLL(void);

void RCM_ConfigCLKDIV(RCM_CLK_DIV_T state);

void RCM_EnableCCS(void);
void RCM_DisableCCS(void);

void RCM_ConfigCOC(RCM_COCCLK_T cocClock);

void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect);
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void);

void RCM_ConfigAHB(RCM_AHBDIV_T AHBDiv);
void RCM_ConfigAPB(RCM_APBDIV_T APBDiv);
void RCM_ConfigI2CCLK(RCM_I2CCLK_T I2CCLk);
void RCM_ConfigUSARTCLK(RCM_USARTCLK_T USARTClk);

uint32_t RCM_ReadSYSCLKFreq(void);
uint32_t RCM_ReadHCLKFreq(void);
uint32_t RCM_ReadPCLKFreq(void);
uint32_t RCM_ReadADCCLKFreq(void);

uint32_t RCM_ReadI2CCLKFreq(void);
uint32_t RCM_ReadUSART1CLKFreq(void);

void RCM_ConfigRTCCLK(RCM_RTCCLK_T RTCClk);
void RCM_EnableRTCCLK(void);
void RCM_DisableRTCCLK(void);

void RCM_EnableRTCReset(void);
void RCM_DisableRTCReset(void);

void RCM_EnableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph);

void RCM_EnableAHBPeriphReset(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphReset(uint32_t AHBPeriph);
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph);

void RCM_EnableInterrupt(uint8_t interrupt);
void RCM_DisableInterrupt(uint8_t interrupt);
uint16_t RCM_ReadStatusFlag(RCM_FLAG_T flag);
void RCM_ClearStatusFlag(void);
uint8_t RCM_ReadIntFlag(RCM_INT_T flag);
void RCM_ClearIntFlag(uint8_t flag);

/**@} end of group RCM_Functions */
/**@} end of group RCM_Driver */
/**@} end of group APM32M35XX_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32M35XX_RCM_H */

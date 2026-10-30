/*!
 * @file        apm32m35xx_rcm.h
 *
 * @brief       This file contains all the RCM firmware functions
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
#include "apm32m35xx_rcm.h"

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

/** @defgroup RCM_Enumerates Enumerates
  @{
  */

/**@} end of group RCM_Enumerates */

/** @defgroup RCM_Structures Structures
  @{
  */

/**@} end of group RCM_Structures */

/** @defgroup RCM_Variables Variables
  @{
  */

/**@} end of group RCM_Variables */

/** @defgroup RCM_Functions Functions
  @{
  */

/*!
 * @brief   Resets the clock configuration
 *
 * @param   None
 *
 * @retval  None
 */
void RCM_Reset(void)
{
    /* Set HSIEN bit */
    RCM->CTRL1_B.HSIEN = BIT_SET;
    RCM->CFG1 &= (uint32_t)0x08FFB80C;
    RCM->CTRL1 &= (uint32_t)0xFEF6FFFF;
    RCM->CTRL1_B.HSEBCFG = BIT_RESET;
    RCM->CFG1 &= (uint32_t)0xFFC0FFFF;
    RCM->CFG2 &= (uint32_t)0xFFFFFFF0;
    RCM->CFG3 &= (uint32_t)0xFFFFFEEC;
    RCM->CTRL2_B.HSI14EN = BIT_RESET;

    /* Disable all interrupts and clear pending bits */
    RCM->INT = 0x00FF0000;
}

/*!
 * @brief       Configures HSE
 *
 * @param       state:   state of the HSE
 *                       This parameter can be one of the following values:
 *                       @arg RCM_HSE_OPEN: turn ON the HSE oscillator
 *                       @arg RCM_HSE_BYPASS: HSE oscillator bypassed with external clock
 *
 * @retval      None
 *
 * @note        HSE can not be stopped if it is used directly or through the PLL as system clock
 */
void RCM_ConfigHSE(RCM_HSE_T state)
{
    RCM->CTRL1_B.HSEEN = BIT_RESET;

    RCM->CTRL1_B.HSEBCFG = BIT_RESET;

    if (state == RCM_HSE_OPEN)
    {
        RCM->CTRL1_B.HSEEN = BIT_SET;
    }
    else if (state == RCM_HSE_BYPASS)
    {
        RCM->CTRL1_B.HSEBCFG = BIT_SET;
        RCM->CTRL1_B.HSEEN = BIT_SET;
    }
}

/*!
 * @brief       Waits for HSE be ready
 *
 * @param       None
 *
 * @retval      SUCCESS     HSE oscillator is stable and ready to use
 *              ERROR       HSE oscillator not yet ready
 */
uint8_t RCM_WaitHSEReady(void)
{
    __IO uint32_t cnt;

    for (cnt = 0; cnt < HSE_STARTUP_TIMEOUT; cnt++)
    {
        if (RCM->CTRL1_B.HSERDYFLG == BIT_SET)
        {
            /* delay 2 ms */
            SystemCoreClockUpdate();
            uint32_t ctrl_bkp = SysTick->CTRL;
            uint32_t load_bkp = SysTick->LOAD;
            SysTick->CTRL &= 0xFFFFFFFFA;
            SysTick->VAL = 0;
            SysTick->LOAD = SystemCoreClock / 500;
            SysTick->CTRL |= 0x5;
            while((SysTick->CTRL & 0x10000) != 0x10000);
            SysTick->LOAD = load_bkp;
            SysTick->CTRL = ctrl_bkp;

            return SUCCESS;
        }
    }

    return ERROR;
}

/*!
 * @brief       Set HSI trimming value
 *
* @param        HSITrim:    HSI trimming value
 *                          This parameter must be a number between 0 and 0x1F.
 *
 * @retval      None
 */
void RCM_SetHSITrim(uint8_t HSITrim)
{
    RCM->CTRL1_B.HSITRM = HSITrim;
}

/*!
 * @brief       Enable HSI
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        HSI can not be stopped if it is used directly or through the PLL as system clock
 */
void RCM_EnableHSI(void)
{
    RCM->CTRL1_B.HSIEN = BIT_SET;
}

/*!
 * @brief       Disable HSI
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        HSI can not be stopped if it is used directly or through the PLL as system clock
 */
void RCM_DisableHSI(void)
{
    RCM->CTRL1_B.HSIEN = BIT_RESET;
}

/*!
 * @brief       Set HSI14 trimming value
 *
 * @param        HSI14TRM:  HSI trimming value
 *                            This parameter must be a number between 0 and 0x1F.
 *
 * @retval      None
 */
void RCM_SetHSI14Trim(uint8_t HSI14Trim)
{
    RCM->CTRL2_B.HSI14TRM = HSI14Trim;
}

/*!
 * @brief       Enable HSI14
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableHSI14(void)
{
    RCM->CTRL2_B.HSI14EN = BIT_SET;
}

/*!
 * @brief       Disable HSI14
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableHSI14(void)
{
    RCM->CTRL2_B.HSI14EN = BIT_RESET;
}

/*!
 * @brief       Enable HSI14 ADC
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_EnableHSI14ADC(void)
{
    RCM->CTRL2_B.HSI14TO = BIT_SET;
}

/*!
 * @brief       Disable HSI14 ADC
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RCM_DisableHSI14ADC(void)
{
    RCM->CTRL2_B.HSI14TO = BIT_RESET;
}

/*!
 * @brief       Enable LSI
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        LSI can not be stopped if the IWDT is running
 */
void RCM_EnableLSI(void)
{
    RCM->CSTS_B.LSIEN = BIT_SET;
}

/*!
 * @brief       Disable LSI
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        LSI can not be stopped if the IWDT is running
 */
void RCM_DisableLSI(void)
{
    RCM->CSTS_B.LSIEN = BIT_RESET;
}

/*!
 * @brief       Configures the PLL clock source and multiplication factor
 *
 * @param       pllSelect:   PLL entry clock source select
 *                           This parameter can be one of the following values:
 *                           @arg RCM_PLL_SEL_HSI_DIV2: HSI clock divided by 2 selected as PLL clock source
 *                           @arg RCM_PLL_SEL_HSE: HSE/CLKDIV1 selected as PLL clock entry
 *
 * @param       pllMf:       PLL multiplication factor
 *                           This parameter can be RCM_PLLMF_x where x:[2,16]
 *
 * @retval      None
 *
 * @note
 */
void RCM_ConfigPLL(RCM_PLL_SEL_T pllSelect, RCM_PLLMF_T pllMf)
{
    RCM->CFG1_B.PLLMULCFG = pllMf;
    RCM->CFG1_B.PLLSRCSEL = pllSelect;
}

/*!
 * @brief       Enables PLL
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        The PLL can not be disabled if it is used as system clock
 */
void RCM_EnablePLL(void)
{
    RCM->CTRL1_B.PLLEN = BIT_SET;
}

/*!
 * @brief       Disable PLL
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        The PLL can not be disabled if it is used as system clock
 */
void RCM_DisablePLL(void)
{
    RCM->CTRL1_B.PLLEN = BIT_RESET;
}

/*!
 * @brief       Configures the CLK division factor
 *
 * @param       state:   specifies the PLLDIVCFG clock division factor.
 *                       This parameter can be RCM_CLK_Divx where x:[1,16]
 *
 * @retval      None
 *
 * @note        This function must be used only when the PLL is disabled
 */
void RCM_ConfigCLKDIV(RCM_CLK_DIV_T state)
{
    RCM->CFG2_B.PLLDIVCFG = state;
}

/*!
 * @brief        Enable Clock Security System
 *
 * @param        None
 *
 * @retval       None
 */
void RCM_EnableCCS(void)
{
    RCM->CTRL1_B.CSSEN = BIT_SET;
}

/*!
 * @brief        Disable Clock Security System
 *
 * @param        None
 *
 * @retval       None
 */
void RCM_DisableCCS(void)
{
    RCM->CTRL1_B.CSSEN = BIT_RESET;
}

/*!
 * @brief       Selects clock ouput source
 *
 * @param       cocClock:  specifies the clock source to output
 *                         This parameter can be one of the following values:
 *                         @arg RCM_COC_NO_CLOCK:     No clock selected.
 *                         @arg RCM_COC_HSI14:        HSI14 oscillator clock selected.
 *                         @arg RCM_COC_LSI:          LSI oscillator clock selected.
 *                         @arg RCM_COC_SYSCLK:       System clock selected.
 *                         @arg RCM_COC_HSI:          HSI oscillator clock selected.
 *                         @arg RCM_COC_HSE:          HSE oscillator clock selected.
 *                         @arg RCM_COC_PLLCLK_DIV_2: PLL clock divided by 2 selected.
 *
 * @retval      None
 */
void RCM_ConfigCOC(RCM_COCCLK_T cocClock)
{
    RCM->CFG1_B.MCOSEL = cocClock;
}

/*!
 * @brief       Configures the system clock
 *
 * @param       sysClkSelect:   specifies the clock source used as system clock
 *                              This parameter can be one of the following values:
 *                              @arg RCM_SYSCLK_SEL_HSI:    HSI selected as system clock source
 *                              @arg RCM_SYSCLK_SEL_HSE:    HSE selected as system clock source
 *                              @arg RCM_SYSCLK_SEL_PLL:    PLL selected as system clock source
 *
 * @retval      None
 */
void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect)
{
    RCM->CFG1_B.SCLKSEL = sysClkSelect;
}

/*!
 * @brief       returns the clock source used as system clock
 *
 * @param       None
 *
 * @retval      The clock source used as system clock
 */
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void)
{
    RCM_SYSCLK_SEL_T sysClock;

    sysClock = (RCM_SYSCLK_SEL_T)RCM->CFG1_B.SCLKSELSTS;

    return sysClock;
}

/*!
 * @brief       Configures the AHB clock
 *
 * @param       AHBDiv:   AHB divider number. This clock is derived from the system clock (SYSCLK)
 *                        This parameter can be one of the following values:
 *                        @arg RCM_SYSCLK_DIV_1:   AHB clock = SYSCLK
 *                        @arg RCM_SYSCLK_DIV_2:   AHB clock = SYSCLK/2
 *                        @arg RCM_SYSCLK_DIV_4:   AHB clock = SYSCLK/4
 *                        @arg RCM_SYSCLK_DIV_8:   AHB clock = SYSCLK/8
 *                        @arg RCM_SYSCLK_DIV_16:  AHB clock = SYSCLK/16
 *                        @arg RCM_SYSCLK_DIV_64:  AHB clock = SYSCLK/64
 *                        @arg RCM_SYSCLK_DIV_128: AHB clock = SYSCLK/128
 *                        @arg RCM_SYSCLK_DIV_256: AHB clock = SYSCLK/256
 *                        @arg RCM_SYSCLK_DIV_512: AHB clock = SYSCLK/512
 *
 * @retval      None
 */
void RCM_ConfigAHB(RCM_AHBDIV_T AHBDiv)
{
    RCM->CFG1_B.AHBPSC = AHBDiv;
}

/*!
 * @brief       Configures the APB clock
 *
 * @param       APBDiv:   defines the APB clock divider. This clock is derived from the AHB clock (HCLK)
 *                        This parameter can be one of the following values:
 *                        @arg RCM_HCLK_DIV_1:  APB clock = HCLK
 *                        @arg RCM_HCLK_DIV_2:  APB clock = HCLK/2
 *                        @arg RCM_HCLK_DIV_4:  APB clock = HCLK/4
 *                        @arg RCM_HCLK_DIV_8:  APB clock = HCLK/8
 *                        @arg RCM_HCLK_DIV_16: APB clock = HCLK/16
 *
 * @retval      None
 */
void RCM_ConfigAPB(RCM_APBDIV_T APBDiv)
{
    RCM->CFG1_B.APB1PSC = APBDiv;
}

/*!
 * @brief       Configures the I2C clock
 *
 * @param       I2CClk:   defines the I2C clock source. This clock is derived
 *                        from the HSI or System clock.
 *                        This parameter can be one of the following values:
 *                        @arg RCM_I2CCLK_HSI:    I2C clock = HSI
 *                        @arg RCM_I2CCLK_SYSCLK: I2C clock = System Clock
 *
 * @retval      None
 */
void RCM_ConfigI2CCLK(RCM_I2CCLK_T I2CClk)
{
    RCM->CFG3_B.I2CSEL = I2CClk;
}

/*!
 * @brief       Configures the USART clock (USARTCLK)
 *
 * @param       USARTClk: defines the USART clock source. This clock is derived
 *                        from the HSI or System clock.
 *                        This parameter can be one of the following values:
 *                        @arg RCM_USART1CLK_PCLK:   USART1 clock = APB Clock (PCLK)
 *                        @arg RCM_USART1CLK_SYSCLK: USART1 clock = System Clock
 *                        @arg RCM_USART1CLK_HSI:    USART1 clock = HSI Clock
 *
 * @retval      None
 */
void RCM_ConfigUSARTCLK(RCM_USARTCLK_T USARTClk)
{
    if (USARTClk >> 16 == 1)
    {
        RCM->CFG3_B.USART1SEL = (uint32_t)(USARTClk & 0x00000003);
    }
}

/*!
 * @brief       Read frequency of SYSCLK
 *
 * @param       None
 *
 * @retval      Return frequency of SYSCLK
 */
uint32_t RCM_ReadSYSCLKFreq(void)
{
    uint32_t sysClock, pllMull, plldiv, pllSource;

    sysClock = RCM->CFG1_B.SCLKSEL;

    switch (sysClock)
    {
        case RCM_SYSCLK_SEL_HSI:
            sysClock = HSI_VALUE;
            break;

        case RCM_SYSCLK_SEL_HSE:
            sysClock = HSE_VALUE;
            break;

        case RCM_SYSCLK_SEL_PLL:
            pllMull = RCM->CFG1_B.PLLMULCFG + 2;
            pllSource = RCM->CFG1_B.PLLSRCSEL;
            plldiv = RCM->CFG2_B.PLLDIVCFG + 1;

            if (pllSource == 0x00)
            {
                sysClock = (HSI_VALUE >> 1) * pllMull;
            }
            else if (pllSource == 0x01)
            {
                sysClock = (HSE_VALUE / plldiv) * pllMull;
            }
            break;

        default:
            sysClock  = HSI_VALUE;
            break;
    }

    return sysClock;
}

/*!
 * @brief       Read frequency of HCLK(AHB)
 *
 * @param       None
 *
 * @retval      Return frequency of HCLK
 */
uint32_t RCM_ReadHCLKFreq(void)
{
    uint32_t divider;
    uint32_t sysClk, hclk;
    uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sysClk = RCM_ReadSYSCLKFreq();
    divider = AHBPrescTable[RCM->CFG1_B.AHBPSC];
    hclk = sysClk >> divider;

    return hclk;
}

/*!
 * @brief       Read frequency of PCLK
 *
 * @param       None
 *
 * @retval      PCLK1   return frequency of PCLK
 */
uint32_t RCM_ReadPCLKFreq(void)
{
    uint32_t hclk, pclk, divider;
    uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    hclk = RCM_ReadHCLKFreq();

    divider = APBPrescTable[RCM->CFG1_B.APB1PSC];
    pclk = hclk >> divider;

    return pclk;
}

/*!
 * @brief       Read frequency of ADC CLK
 *
 * @param       None
 *
 * @retval      Return frequency of ADC CLK
 */
uint32_t RCM_ReadADCCLKFreq(void)
{
    uint32_t adcClk, pclk;

    pclk = RCM_ReadPCLKFreq();

    if (RCM->CFG3_B.ADCSEL)
    {
        if (RCM->CFG1_B.ADCPSC)
        {
            adcClk = pclk >> 2;
        }
        else
        {
            adcClk = pclk >> 1;
        }
    }
    else
    {
        adcClk = HSI14_VALUE;
    }

    return adcClk;
}

/*!
 * @brief       Read frequency of I2C CLK
 *
 * @param       None
 *
 * @retval      Return frequency of I2C CLK
 */
uint32_t RCM_ReadI2CCLKFreq(void)
{
    uint32_t i2cClk, sysClk;

    sysClk = RCM_ReadSYSCLKFreq();

    if (RCM->CFG3_B.I2CSEL)
    {
        i2cClk = sysClk;
    }
    else
    {
        i2cClk = HSI_VALUE;
    }

    return i2cClk;
}

/*!
 * @brief       Read frequency of USART1 CLK
 *
 * @param       None
 *
 * @retval      Return frequency of USART1 CLK
 */
uint32_t RCM_ReadUSART1CLKFreq(void)
{
    uint32_t usart1Clk = 0;

    if (RCM->CFG3_B.USART1SEL == 0x00)
    {
        usart1Clk = RCM_ReadPCLKFreq();
    }
    else if (RCM->CFG3_B.USART1SEL == 0x01)
    {
        usart1Clk = RCM_ReadSYSCLKFreq();
    }
    else if (RCM->CFG3_B.USART1SEL == 0x03)
    {
        usart1Clk = HSI_VALUE;
    }

    return usart1Clk;
}

/*!
 * @brief       Configures the RTC clock (RTCCLK)
 *
 * @param       RTCClk:   specifies the RTC clock source
 *                        This parameter can be one of the following values:
 *                        @arg RCM_RTCCLK_LSI:       LSI selected as RTC clock
 *                        @arg RCM_RTCCLK_HSE_DIV_32: HSE divided by 32 selected as RTC clock
 *
 * @retval      None
 *
 * @note        Once the RTC clock is selected it can't be changed unless the Backup domain is reset
 */
void RCM_ConfigRTCCLK(RCM_RTCCLK_T RTCClk)
{
    RCM->RTCCTRL_B.RTCSRCSEL = RTCClk;
}

/*!
 * @brief       Enables the RTC clock
 *
 * @param       None
 *
 * @retval      None
 */
void RCM_EnableRTCCLK(void)
{
    RCM->RTCCTRL_B.RTCCLKEN = BIT_SET;
}

/*!
 * @brief       Disables the RTC clock
 *
 * @param       None
 *
 * @retval      None
 */
void RCM_DisableRTCCLK(void)
{
    RCM->RTCCTRL_B.RTCCLKEN = BIT_RESET;
}

/*!
 * @brief       Enable the RTC domain reset
 *
 * @param       None
 *
 * @retval      None
 */
void RCM_EnableRTCReset(void)
{
    RCM->RTCCTRL_B.RTCRST = BIT_SET;
}

/*!
 * @brief       Disable the RTC domain reset
 *
 * @param       None
 *
 * @retval      None
 */
void RCM_DisableRTCReset(void)
{
    RCM->RTCCTRL_B.RTCRST = BIT_RESET;
}

/*!
 * @brief       Enables AHB peripheral clock
 *
 * @param       AHBPeriph:   specifies the AHB peripheral to gates its clock
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_AHB_PERIPH_DMA    : DMA clock
 *                           @arg RCM_AHB_PERIPH_SRAM   : SRAM clock
 *                           @arg RCM_AHB_PERIPH_FPU    : FPU clock
 *                           @arg RCM_AHB_PERIPH_CRC    : CRC clock
 *                           @arg RCM_AHB_PERIPH_GPIOA  : GPIOA clock
 *                           @arg RCM_AHB_PERIPH_GPIOB  : GPIOB clock
 *                           @arg RCM_AHB_PERIPH_GPIOC  : GPIOC clock
 *                           @arg RCM_AHB_PERIPH_GPIOF  : GPIOF clock
 *                           @arg RCM_AHB_PERIPH_M0CP   : M0CP clock
 *
 * @retval      None
 */
void RCM_EnableAHBPeriphClock(uint32_t AHBPeriph)
{
    RCM->AHBCLKEN |= AHBPeriph;
}

/*!
 * @brief       Disable AHB peripheral clock
 *
 * @param       AHBPeriph:   specifies the AHB peripheral to gates its clock
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_AHB_PERIPH_DMA    : DMA clock
 *                           @arg RCM_AHB_PERIPH_SRAM   : SRAM clock
 *                           @arg RCM_AHB_PERIPH_FPU    : FPU clock
 *                           @arg RCM_AHB_PERIPH_CRC    : CRC clock
 *                           @arg RCM_AHB_PERIPH_GPIOA  : GPIOA clock
 *                           @arg RCM_AHB_PERIPH_GPIOB  : GPIOB clock
 *                           @arg RCM_AHB_PERIPH_GPIOC  : GPIOC clock
 *                           @arg RCM_AHB_PERIPH_GPIOF  : GPIOF clock
 *                           @arg RCM_AHB_PERIPH_M0CP   : M0CP clock
 *
 * @retval      None
 */
void RCM_DisableAHBPeriphClock(uint32_t AHBPeriph)
{
    RCM->AHBCLKEN &= (uint32_t)~AHBPeriph;
}

/*!
 * @brief       Enable the High Speed APB (APB2) peripheral clock
 *
 * @param       APB2Periph:  specifies the APB2 peripheral to gates its clock
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB2_PERIPH_SYSCFG    : SYSCFG clock
 *                           @arg RCM_APB2_PERIPH_ADC       : ADC clock
 *                           @arg RCM_APB2_PERIPH_TMR1      : TMR1 clock
 *                           @arg RCM_APB2_PERIPH_SPI       : SPI clock
 *                           @arg RCM_APB2_PERIPH_USART1    : USART1 clock
 *                           @arg RCM_APB2_PERIPH_TMR7      : TMR7 clock
 *                           @arg RCM_APB2_PERIPH_DBGMCU    : DBGMCU clock
 *
 * @retval      None
 */
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph)
{
    RCM->APBCLKEN2 |= APB2Periph;
}

/*!
 * @brief       Disable the High Speed APB (APB2) peripheral clock
 *
 * @param       APB2Periph:  specifies the APB2 peripheral to gates its clock
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB2_PERIPH_SYSCFG    : SYSCFG clock
 *                           @arg RCM_APB2_PERIPH_ADC       : ADC clock
 *                           @arg RCM_APB2_PERIPH_TMR1      : TMR1 clock
 *                           @arg RCM_APB2_PERIPH_SPI       : SPI clock
 *                           @arg RCM_APB2_PERIPH_USART1    : USART1 clock
 *                           @arg RCM_APB2_PERIPH_TMR7      : TMR7 clock
 *                           @arg RCM_APB2_PERIPH_DBGMCU    : DBGMCU clock
 *
 * @retval      None
 */
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph)
{
    RCM->APBCLKEN2 &= (uint32_t)~APB2Periph;
}

/*!
 * @brief       Enable the Low Speed APB (APB1) peripheral clock
 *
 * @param       APB1Periph:  specifies the APB1 peripheral to gates its clock
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB1_PERIPH_TMR2:   TMR2 clock
 *                           @arg RCM_APB1_PERIPH_TMR3:   TMR3 clock
 *                           @arg RCM_APB1_PERIPH_TMR6:   TMR6 clock
 *                           @arg RCM_APB1_PERIPH_TMR4:  TMR4 clock
 *                           @arg RCM_APB1_PERIPH_WWDT:   WWDG clock
 *                           @arg RCM_APB1_PERIPH_USART2: USART2 clock
 *                           @arg RCM_APB1_PERIPH_I2C:   I2C clock
 *                           @arg RCM_APB1_PERIPH_CAN:    CAN clock
 *                           @arg RCM_APB1_PERIPH_PMU:    PMU clock
 *
 * @retval      None
 */
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph)
{
    RCM->APBCLKEN1 |= APB1Periph;
}

/*!
 * @brief       Disable the Low Speed APB (APB1) peripheral clock
 *
 * @param       APB1Periph:  specifies the APB1 peripheral to gates its clock
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB1_PERIPH_TMR2:   TMR2 clock
 *                           @arg RCM_APB1_PERIPH_TMR3:   TMR3 clock
 *                           @arg RCM_APB1_PERIPH_TMR6:   TMR6 clock
 *                           @arg RCM_APB1_PERIPH_TMR4:  TMR4 clock
 *                           @arg RCM_APB1_PERIPH_WWDT:   WWDG clock
 *                           @arg RCM_APB1_PERIPH_USART2: USART2 clock
 *                           @arg RCM_APB1_PERIPH_I2C:   I2C clock
 *                           @arg RCM_APB1_PERIPH_CAN:    CAN clock
 *                           @arg RCM_APB1_PERIPH_PMU:    PMU clock
 *
 * @retval      None
 */
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph)
{
    RCM->APBCLKEN1 &= (uint32_t)~APB1Periph;
}

/*!
 * @brief       Enable Low Speed AHB peripheral reset
 *
 * @param       AHBPeriph:   specifies the AHB peripheral to reset
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_AHB_PERIPH_GPIOA: GPIOA reset
 *                           @arg RCM_AHB_PERIPH_GPIOB: GPIOB reset
 *                           @arg RCM_AHB_PERIPH_GPIOC: GPIOC reset
 *                           @arg RCM_AHB_PERIPH_GPIOF: GPIOF reset
 *                           @arg RCM_AHB_PERIPH_M0CP:   M0CP reset
 *
 * @retval      None
 */
void RCM_EnableAHBPeriphReset(uint32_t AHBPeriph)
{
    RCM->AHBRST |= AHBPeriph;
}

/*!
 * @brief       Disable Low Speed AHB peripheral reset
 *
 * @param       AHBPeriph:   specifies the AHB peripheral to reset
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_AHB_PERIPH_GPIOA: GPIOA reset
 *                           @arg RCM_AHB_PERIPH_GPIOB: GPIOB reset
 *                           @arg RCM_AHB_PERIPH_GPIOC: GPIOC reset
 *                           @arg RCM_AHB_PERIPH_GPIOF: GPIOF reset
 *                           @arg RCM_AHB_PERIPH_M0CP:   M0CP reset
 *
 * @retval      None
 */
void RCM_DisableAHBPeriphReset(uint32_t AHBPeriph)
{
    RCM->AHBRST &= (uint32_t)~AHBPeriph;
}

/*!
 * @brief       Enable Low Speed APB (APB1) peripheral reset
 *
 * @param       APB1Periph:  specifies the APB1 peripheral to reset
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB1_PERIPH_TMR2:   TMR2 clock
 *                           @arg RCM_APB1_PERIPH_TMR3:   TMR3 clock
 *                           @arg RCM_APB1_PERIPH_TMR6:   TMR6 clock
 *                           @arg RCM_APB1_PERIPH_TMR4:  TMR4 clock
 *                           @arg RCM_APB1_PERIPH_WWDT:   WWDG clock
 *                           @arg RCM_APB1_PERIPH_USART2: USART2 clock
 *                           @arg RCM_APB1_PERIPH_I2C:   I2C clock
 *                           @arg RCM_APB1_PERIPH_CAN:    CAN clock
 *                           @arg RCM_APB1_PERIPH_PMU:    PMU clock
 *
 * @retval      None
 */
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph)
{
    RCM->APBRST1 |= APB1Periph;
}

/*!
 * @brief       Disable Low Speed APB (APB1) peripheral reset
 *
 * @param       APB1Periph:  specifies the APB1 peripheral to reset
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB1_PERIPH_TMR2:   TMR2 clock
 *                           @arg RCM_APB1_PERIPH_TMR3:   TMR3 clock
 *                           @arg RCM_APB1_PERIPH_TMR6:   TMR6 clock
 *                           @arg RCM_APB1_PERIPH_TMR4:  TMR4 clock
 *                           @arg RCM_APB1_PERIPH_WWDT:   WWDG clock
 *                           @arg RCM_APB1_PERIPH_USART2: USART2 clock
 *                           @arg RCM_APB1_PERIPH_I2C:   I2C clock
 *                           @arg RCM_APB1_PERIPH_CAN:    CAN clock
 *                           @arg RCM_APB1_PERIPH_PMU:    PMU clock
 *
 * @retval      None
 */
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph)
{
    RCM->APBRST1 &= (uint32_t)~APB1Periph;
}

/*!
 * @brief       Enable High Speed APB (APB2) peripheral reset
 *
 * @param       APB2Periph:  specifies the APB2 peripheral to reset
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB2_PERIPH_SYSCFG    : SYSCFG clock
 *                           @arg RCM_APB2_PERIPH_ADC       : ADC clock
 *                           @arg RCM_APB2_PERIPH_TMR1      : TMR1 clock
 *                           @arg RCM_APB2_PERIPH_SPI       : SPI clock
 *                           @arg RCM_APB2_PERIPH_USART1    : USART1 clock
 *                           @arg RCM_APB2_PERIPH_TMR7      : TMR7 clock
 *                           @arg RCM_APB2_PERIPH_DBGMCU    : DBGMCU clock
 *
 * @retval      None
 */
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph)
{
    RCM->APBRST2 |= APB2Periph;
}

/*!
 * @brief       Disable High Speed APB (APB2) peripheral reset
 *
 * @param       APB2Periph:  specifies the APB2 peripheral to reset
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_APB2_PERIPH_SYSCFG    : SYSCFG clock
 *                           @arg RCM_APB2_PERIPH_ADC       : ADC clock
 *                           @arg RCM_APB2_PERIPH_TMR1      : TMR1 clock
 *                           @arg RCM_APB2_PERIPH_SPI       : SPI clock
 *                           @arg RCM_APB2_PERIPH_USART1    : USART1 clock
 *                           @arg RCM_APB2_PERIPH_TMR7      : TMR7 clock
 *                           @arg RCM_APB2_PERIPH_DBGMCU    : DBGMCU clock
 *
 * @retval      None
 */
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph)
{
    RCM->APBRST2 &= (uint32_t)~APB2Periph;
}

/*!
 * @brief       Enable the specified RCM interrupts
 *
 * @param       interrupt:   specifies the RCM interrupt source to check
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_INT_LSIRDY:    LSI ready interrupt
 *                           @arg RCM_INT_HSIRDY:    HSI ready interrupt
 *                           @arg RCM_INT_HSERDY:    HSE ready interrupt
 *                           @arg RCM_INT_PLLRDY:    PLL ready interrupt
 *                           @arg RCM_INT_HSI14RDY:  HSI14 ready interrupt
 *
 * @retval  None
 */
void RCM_EnableInterrupt(uint8_t interrupt)
{
    RCM->INT |= (interrupt << 8);
}

/*!
 * @brief       Disable the specified RCM interrupts
 *
 * @param       interrupt:   specifies the RCM interrupt source to check
 *                           This parameter can be any combination of the following values:
 *                           @arg RCM_INT_LSIRDY:    LSI ready interrupt
 *                           @arg RCM_INT_HSIRDY:    HSI ready interrupt
 *                           @arg RCM_INT_HSERDY:    HSE ready interrupt
 *                           @arg RCM_INT_PLLRDY:    PLL ready interrupt
 *                           @arg RCM_INT_HSI14RDY:  HSI14 ready interrupt
 *
 * @retval  None
 */
void RCM_DisableInterrupt(uint8_t interrupt)
{
    RCM->INT &= ~(interrupt << 8);
}

/*!
 * @brief       Read the specified RCM flag status
 *
 * @param       flag:   specifies the flag to check
 *                      This parameter can be one of the following values:
 *                      @arg RCM_FLAG_HSIRDY:   HSI oscillator clock ready
 *                      @arg RCM_FLAG_HSERDY:   HSE oscillator clock ready
 *                      @arg RCM_FLAG_PLLRDY:   PLL clock ready
 *                      @arg RCM_FLAG_LSIRDY:   LSI oscillator clock ready
 *                      @arg RCM_FLAG_V18PRRST: V1.8 power domain reset
 *                      @arg RCM_FLAG_OBRST:    Option Byte Loader (OBL) reset
 *                      @arg RCM_FLAG_PINRST:   Pin reset
 *                      @arg RCM_FLAG_PWRRST:   POR/PDR reset
 *                      @arg RCM_FLAG_SWRST:    Software reset
 *                      @arg RCM_FLAG_IWDTRST:  Independent Watchdog reset
 *                      @arg RCM_FLAG_WWDTRST:  Window Watchdog reset
 *                      @arg RCM_FLAG_LPRRST:   Low Power reset
 *                      @arg RCM_FLAG_HSI14RDY: HSI14 clock ready
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint16_t RCM_ReadStatusFlag(RCM_FLAG_T flag)
{
    uint32_t reg, bit;

    bit = (uint32_t)(1 << (flag & 0xff));

    reg = (flag >> 8) & 0xff;

    switch (reg)
    {
        case 0:
            reg = RCM->CTRL1;
            break;

        case 1:
            reg = RCM->RTCCTRL;
            break;

        case 2:
            reg = RCM->CSTS;
            break;

        case 3:
            reg = RCM->CTRL2;
            break;

        default:
            break;
    }

    if (reg & bit)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clears the RCM reset flags
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        The reset flags are:
 *              RCM_FLAG_V18PRRST; RCM_FLAG_OBRST; RCM_FLAG_PINRST; RCM_FLAG_PWRRST;
 *              RCM_FLAG_SWRST; RCM_FLAG_IWDTRST; RCM_FLAG_WWDTRST; RCM_FLAG_LPRRST;
 */
void RCM_ClearStatusFlag(void)
{
    RCM->CSTS_B.RSTFLGCLR = BIT_SET;
}

/*!
 * @brief       Read the specified RCM interrupt Flag
 *
 * @param       flag:   specifies the RCM interrupt source to check
 *                      This parameter can be one of the following values:
 *                      @arg RCM_INT_LSIRDY:    LSI ready interrupt
 *                      @arg RCM_INT_HSIRDY:    HSI ready interrupt
 *                      @arg RCM_INT_HSERDY:    HSE ready interrupt
 *                      @arg RCM_INT_PLLRDY:    PLL ready interrupt
 *                      @arg RCM_INT_HSI14RDY:  HSI14 ready interrupt
 *                      @arg RCM_INT_CSS:       Clock Security System interrupt
 *
 * @retval      The new state of intFlag (SET or RESET)
 */
uint8_t RCM_ReadIntFlag(RCM_INT_T flag)
{
    uint8_t ret;

    ret = (RCM->INT& flag) ? SET : RESET;

    return  ret;
}

/*!
 * @brief       Clears the interrupt flag
 *
 * @param       flag:   specifies the RCM interrupt source to check
 *                      This parameter can be any combination of the following values:
 *                      @arg RCM_INT_LSIRDY:    LSI ready interrupt
 *                      @arg RCM_INT_HSIRDY:    HSI ready interrupt
 *                      @arg RCM_INT_HSERDY:    HSE ready interrupt
 *                      @arg RCM_INT_PLLRDY:    PLL ready interrupt
 *                      @arg RCM_INT_HSI14RDY:  HSI14 ready interrupt
 *                      @arg RCM_INT_CSS:       Clock Security System interrupt
 *
 * @retval      None
 */
void RCM_ClearIntFlag(uint8_t flag)
{
    uint32_t temp;

    temp = flag << 16;
    RCM->INT |= temp;
}

/**@} end of group RCM_Functions */
/**@} end of group RCM_Driver */
/**@} end of group APM32M35XX_StdPeriphDriver */

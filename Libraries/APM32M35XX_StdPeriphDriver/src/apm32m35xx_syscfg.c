/*!
 * @file        apm32m35xx_syscfg.c
 *
 * @brief       This file contains all the functions for the SYSCFG peripheral
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
#include "apm32m35xx_syscfg.h"

/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup SYSCFG_Driver
  @{
*/


/** @defgroup SYSCFG_Macros Macros
  @{
  */

/**@} end of group SYSCFG_Macros */

/** @defgroup SYSCFG_Enumerates Enumerates
  @{
  */

/**@} end of group SYSCFG_Enumerates */

/** @defgroup SYSCFG_Structures Structures
  @{
  */

/**@} end of group SYSCFG_Structures */

/** @defgroup SYSCFG_Variables Variables
  @{
  */

/**@} end of group SYSCFG_Variables */

/** @defgroup SYSCFG_Functions Functions
  @{
  */

/*!
 * @brief        Set SYSCFG CFG0/1 EINTCFG1/2/3/4 register to reset value
 *
 * @param        None
 *
 * @retval       None
 */
void SYSCFG_Reset(void)
{
    SYSCFG->CFG1 &= (uint32_t) SYSCFG_CFG1_MEMMODE;
    SYSCFG->EINTCFG1 = 0;
    SYSCFG->EINTCFG2 = 0;
    SYSCFG->EINTCFG3 = 0;
    SYSCFG->EINTCFG4 = 0;
}

/*!
 * @brief       SYSCFG Memory Remap selects
 *
 * @param       memory: selects the memory remapping
 *                      The parameter can be one of following values:
 *                      @arg SYSCFG_MEMORY_REMAP_FMC:      SYSCFG MemoryRemap Flash
 *                      @arg SYSCFG_MEMORY_REMAP_SYSTEM:   SYSCFG MemoryRemap SystemMemory
 *                      @arg SYSCFG_MEMORY_REMAP_SRAM:     SYSCFG MemoryRemap SRAM
 *
 * @retval      None
 */
void SYSCFG_MemoryRemapSelect(uint8_t memory)
{
    SYSCFG->CFG1_B.MMSEL = (uint8_t)memory;
}

/*!
 * @brief       Enables SYSCFG DMA Channel Remap
 *
 * @param       channel: selects the DMA channels remap.
 *                       The parameter can be any combination of following values:
 *                       @arg SYSCFG_DAM_REMAP_ADC:      ADC DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1TX: USART1 TX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1RX: USART1 RX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_SPI：     SPI DMA remap
 *                       @arg SYSCFG_DAM_REMAP_I2C：     I2C DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR1：    Timer 1 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR2：    Timer 2 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR3：    Timer 3 DMA remap
 *
 * @retval      None
 */
void SYSCFG_EnableDMAChannelRemap(uint32_t channel)
{
    SYSCFG->CFG1 |= (uint32_t)channel;
}

/*!
 * @brief       Disables SYSCFG DMA Channel Remap
 *
 * @param       channel: selects the DMA channels remap.
 *                       The parameter can be any combination of following values:
 *                       @arg SYSCFG_DAM_REMAP_ADC:      ADC DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1TX: USART1 TX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1RX: USART1 RX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_SPI：     SPI DMA remap
 *                       @arg SYSCFG_DAM_REMAP_I2C：     I2C DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR1：    Timer 1 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR2：    Timer 2 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR3：    Timer 3 DMA remap
 *
 * @retval      None
 */
void SYSCFG_DisableDMAChannelRemap(uint32_t channel)
{
    SYSCFG->CFG1 &= (uint32_t)~channel;
}

/*!
 * @brief       Enables SYSCFG I2C Fast Mode Plus
 *
 * @param       pin:     selects the pin.
 *                       The parameter can be combination of following values:
 *                       @arg SYSCFG_I2C_FMP_PB6:    I2C PB6 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB7:    I2C PB7 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB8:    I2C PB8 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB9:    I2C PB9 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PC4:    I2C PC4 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PC5:    I2C PC5 Fast mode plus
 *
 * @retval      None
 */
void SYSCFG_EnableI2CFastModePlus(uint32_t pin)
{
    SYSCFG->CFG1 |= (uint32_t)pin;
}

/*!
 * @brief       Disables SYSCFG I2C Fast Mode Plus
 *
 * @param       pin:     selects the pin.
 *                       The parameter can be combination of following values:
 *                       @arg SYSCFG_I2C_FMP_PB6:    I2C PB6 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB7:    I2C PB7 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB8:    I2C PB8 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB9:    I2C PB9 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PC4:    I2C PC4 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PC5:    I2C PC5 Fast mode plus
 *
 * @retval      None
 */
void SYSCFG_DisableI2CFastModePlus(uint32_t pin)
{
    SYSCFG->CFG1 &= (uint32_t)~pin;
}

/*!
 * @brief       Select the modulation envelope source
 *
 * @param       IRDAEnv: selects the envelope source
 *                       The parameter can be one of following values:
 *                       @arg SYSCFG_IRDA_ENV_TMR3:     Timer3 as IRDA Modulation envelope source
 *                       @arg SYSCFG_IRDA_ENV_USART1:    USART1 as IRDA Modulation envelope source
 *
 * @retval      None
 */
void SYSCFG_SelectIRDAEnv(SYSCFG_IRDA_ENV_T IRDAEnv)
{
    SYSCFG->CFG1 &= ~(0x000000C0);
    SYSCFG->CFG1 |= (IRDAEnv);
}

/*!
 * @brief       Selects the GPIO pin used as EINT Line.
 *
 * @param       port:   selects the port can be GPIOA/B/C/F
 *
 * @param       pin:    selects the pin can be SYSCFG_PIN_(0..15)
 *
 * @retval      None
 *
 */
void SYSCFG_EINTLine(SYSCFG_PORT_T port, SYSCFG_PIN_T pin)
{
    uint32_t status;

    status = (((uint32_t)0x0F) & port) << (0x04 * (pin & (uint8_t)0x03));

    if (pin <= 0x03)
    {
        SYSCFG->EINTCFG1 |= status;
    }
    else if ((0x04 <= pin) & (pin <= 0x07))
    {
        SYSCFG->EINTCFG2 |= status;
    }
    else if ((0x08 <= pin) & (pin <= 0x0B))
    {
        SYSCFG->EINTCFG3 |= status;
    }
    else if ((0x0C <= pin) & (pin <= 0x0F))
    {
        SYSCFG->EINTCFG4 |= status;
    }
}

/*!
 * @brief       Selected parameter to the break input of TMR1.
 *
 * @param       lock:   selects the configuration to break
 *                      The parameter can be one of following values:
 *                      @arg SYSCFG_LOCK_LOCKUP: Cortex-M0 LOCKUP bit
 *                      @arg SYSCFG_LOCK_PVD:  PVD lock enable bit
 *
 * @retval      None
 */
void SYSCFG_BreakLock(uint32_t lock)
{
    if (lock == SYSCFG_LOCK_LOCKUP)
    {
        SYSCFG->CFG2_B.LOCK = BIT_SET;
    }
    if (lock == SYSCFG_LOCK_PVD)
    {
        SYSCFG->CFG2_B.PVDLOCK = BIT_SET;
    }
}

/*!
 * @brief       Config data code cipher key
 *
 * @param       key:   data code cipher key
 *
 * @retval      None
 */
void SYSCFG_ConfigDCCKey(uint32_t key)
{
    SYSCFG->DCODE_B.DKEY = key;
}

/*!
 * @brief       Config instruction code cipher key
 *
 * @param       key:   data code cipher key
 *
 * @retval      None
 */
void SYSCFG_ConfigICCKey(uint32_t key)
{
    SYSCFG->ICODE_B.IKEY = key;
}

/*!
 * @brief       Enable data code cipher
 *
 * @param       None
 *
 * @retval      None
 */
void SYSCFG_EnableDataCipher(void)
{
    SYSCFG->CIPHEN_B.DCIPHEN = BIT_SET;
}

/*!
 * @brief       Disable data code cipher
 *
 * @param       None
 *
 * @retval      None
 */
void SYSCFG_DisableDataCipher(void)
{
    SYSCFG->CIPHEN_B.DCIPHEN = BIT_RESET;
}

/*!
 * @brief       Enable instruction code cipher
 *
 * @param       None
 *
 * @retval      None
 */
void SYSCFG_EnableInsCipher(void)
{
    SYSCFG->CIPHEN_B.ICIPHEN = BIT_SET;
}

/*!
 * @brief       Disable instruction code cipher
 *
 * @param       None
 *
 * @retval      None
 */
void SYSCFG_DisableInsCipher(void)
{
    SYSCFG->CIPHEN_B.ICIPHEN = BIT_RESET;
}

/**@} end of group SYSCFG_Functions */
/**@} end of group SYSCFG_Driver */
/**@} end of group APM32M35XX_StdPeriphDriver */

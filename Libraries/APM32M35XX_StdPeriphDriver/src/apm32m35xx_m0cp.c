/*!
 * @file        apm32m35xx_m0cp.c
 *
 * @brief       This file contains all the functions for the M0CP peripheral
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
#include "apm32m35xx_m0cp.h"

/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup M0CP_Driver
  @{
*/

/** @defgroup M0CP_Macros Macros
  @{
*/

/**@} end of group M0CP_Macros */

/** @defgroup M0CP_Enumerations Enumerations
  @{
*/

/**@} end of group M0CP_Enumerations */

/** @defgroup M0CP_Structures Structures
  @{
*/

/**@} end of group M0CP_Structures */

/** @defgroup M0CP_Variables Variables
  @{
*/

/**@} end of group M0CP_Variables */

/** @defgroup M0CP_Functions Functions
  @{
*/

/*!
 * @brief       Config the M0CP peripheral according to the specified parameters in the m0cpConfig
 *
 * @param       adcConfig:  Pointer to a M0CP_Config_T structure that
 *                          contains the configuration information for the ADC peripheral
 *
 * @retval      None
 */
void M0CP_Config(M0CP_Config_T* m0cpConfig)
{
    M0CP->CTRL_REG_B.ALG        = m0cpConfig->algebraMode;
    M0CP->CTRL_REG_B.BANKAUTO   = m0cpConfig->bankAutoConv;
    M0CP->CTRL_REG_B.BANKHSEL   = m0cpConfig->bankRegGroup;
    M0CP->CTRL_REG_B.QN         = m0cpConfig->fixedPoint;
    M0CP->CTRL_REG_B.CORDICOUT  = m0cpConfig->xyResultCORDIC;
    M0CP->CTRL_REG_B.SVPWMSEG   = m0cpConfig->segSVPWM;
    M0CP->CTRL_REG_B.SVPWMOUT   = m0cpConfig->outputSVPWM;
}

/*!
 * @brief       Fills each m0cpConfig member with its default value
 *
 * @param       adcConfig:  Pointer to a M0CP_Config_T structure which will be initialized
 *
 * @retval      None
 */
void M0CP_ConfigStructInit(M0CP_Config_T* m0cpConfig)
{
    m0cpConfig->algebraMode     = M0CP_ALG_NONE;
    m0cpConfig->bankAutoConv    = M0CP_BANK_CONV_SOFTWARE;
    m0cpConfig->bankRegGroup    = M0CP_BANK_REG_GROUP_0;
    m0cpConfig->fixedPoint      = M0CP_FP_Q15;
    m0cpConfig->xyResultCORDIC  = M0CP_CORDIC_XY;
    m0cpConfig->segSVPWM        = M0CP_SVPWM_SEG_7;
    m0cpConfig->outputSVPWM     = M0CP_SVPWM_OUT_DUTY;
}

/*!
 * @brief       M0CP set X register value
 *
 * @param       value:      Sets the M0CP X register value
 *
 * @retval      None
 *
 * @note        When the parameter is less than 32 bits or have sign, it should be configured
                with the correct symbol extension.
 */
void M0CP_SetRegX(int32_t value)
{
    M0CP->X_REG = value;
}

/*!
 * @brief       M0CP set Y register value
 *
 * @param       value:      Sets the M0CP Y register value
 *
 * @retval      None
 *
 * @note        When the parameter is less than 32 bits or have sign, it should be configured
                with the correct symbol extension.
 */
void M0CP_SetRegY(int32_t value)
{
    M0CP->Y_REG = value;
}

/*!
 * @brief       M0CP set Z register value
 *
 * @param       value:      Sets the M0CP Z register value
 *
 * @retval      None
 *
 * @note        When the parameter is less than 32 bits or have sign, it should be configured
                with the correct symbol extension.
 */
void M0CP_SetRegZ(int32_t value)
{
    M0CP->Z_REG = value;
}

/*!
 * @brief       M0CP set algorithm mode
 *
 * @param       operation:  Specifies the M0CP algorithm mode
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_ALG_NONE          : No select algebra mode
 *                          @arg M0CP_ALG_SVPWM         : SVPWM algebra mode
 *                          @arg M0CP_ALG_CORDIC_ROTATE : CORDIC rotate algebra mode
 *                          @arg M0CP_ALG_CORDIC_VECTOR : CORDIC vector algebra mode
 *                          @arg M0CP_ALG_SQUARE_ROOT   : Square root algebra mode
 *                          @arg M0CP_ALG_DIV_UNSIGNED  : Unsigned division algebra mode
 *                          @arg M0CP_ALG_DIV_SIGNED    : Signed division algebra mode
 *                          @arg M0CP_ALG_ATAN2         : atan2 algebra mode
 *
 * @retval      None
 */
void M0CP_ConfigAlgMode(M0CP_ALG_MODE_T operation)
{
    M0CP->CTRL_REG_B.ALG = operation;
}

/*!
 * @brief       M0CP set SVPWM segmentation
 *
 * @param       operation:  Specifies the M0CP SVPWM segmentation
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_SVPWM_SEG_7   : SVPWM 7 segmentation
 *                          @arg M0CP_SVPWM_SEG_5   : SVPWM 5 segmentation
 *
 * @retval      None
 */
void M0CP_ConfigSegSVPWM(M0CP_SVPWM_SEG_T segSVPWM)
{
    M0CP->CTRL_REG_B.SVPWMSEG   = segSVPWM;
}

/*!
 * @brief       M0CP configure Qn
 *
 * @param       fixedPoint:  Specifies the M0CP fixed point
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_FP_NONE: No fixed point
 *                          @arg M0CP_FP_Q1: Q1 fixed point
 *                          @arg M0CP_FP_Q2: Q2 fixed point
 *                          @arg M0CP_FP_Q3: Q3 fixed point
 *                          @arg M0CP_FP_Q4: Q4 fixed point
 *                          @arg M0CP_FP_Q5: Q5 fixed point
 *                          @arg M0CP_FP_Q6: Q6 fixed point
 *                          @arg M0CP_FP_Q7: Q7 fixed point
 *                          @arg M0CP_FP_Q8: Q8 fixed point
 *                          @arg M0CP_FP_Q9: Q9 fixed point
 *                          @arg M0CP_FP_Q10: Q10 fixed point
 *                          @arg M0CP_FP_Q11: Q11 fixed point
 *                          @arg M0CP_FP_Q12: Q12 fixed point
 *                          @arg M0CP_FP_Q13: Q13 fixed point
 *                          @arg M0CP_FP_Q14: Q14 fixed point
 *                          @arg M0CP_FP_Q15: Q15 fixed point
 *
 * @retval      None
 */
void M0CP_ConfigQn(M0CP_FIXED_POINT_T fixedPoint)
{
    M0CP->CTRL_REG_B.QN = fixedPoint;
}

/*!
 * @brief       M0CP select writting bank
 *
 * @param       bankRegGroup:  Specifies the M0CP bank register group
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_BANK_REG_GROUP_0: Bank register group 0
 *                          @arg M0CP_BANK_REG_GROUP_1: Bank register group 1
 *
 * @retval      None
 */
void M0CP_ConfigWriteBank(M0CP_BANK_REG_T bankRegGroup)
{
    M0CP->BANK_REG_B.BANKWSEL = bankRegGroup;
}

/*!
 * @brief       M0CP select reading bank
 *
 * @param       bankRegGroup:  Specifies the M0CP bank register group
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_BANK_REG_GROUP_0: Bank register group 0
 *                          @arg M0CP_BANK_REG_GROUP_1: Bank register group 1
 *
 * @retval      None
 */
void M0CP_ConfigReadBank(M0CP_BANK_REG_T bankRegGroup)
{
    M0CP->BANK_REG_B.BANKRSEL = bankRegGroup;
}

/*!
 * @brief       M0CP select operation bank
 *
 * @param       bankRegGroup:  Specifies the M0CP bank register group
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_BANK_REG_GROUP_0: Bank register group 0
 *                          @arg M0CP_BANK_REG_GROUP_1: Bank register group 1
 *
 * @retval      None
 */
void M0CP_ConfigOpBank(M0CP_BANK_REG_T bankRegGroup)
{
    M0CP->CTRL_REG_B.BANKHSEL = bankRegGroup;
}

/*!
 * @brief       M0CP read reversion
 *
 * @param       None
 *
 * @retval      reversion
 */
uint32_t M0CP_ReadReversion(void)
{
    return ((uint32_t)M0CP->REV_REG);
}

/*!
 * @brief       Enables the TX event
 *
 * @param       None
 *
 * @retval      None
 */
void M0CP_EnableTXEvent(void)
{
    M0CP->CTRL_REG_B.TXEVEN = BIT_SET;
}

/*!
 * @brief       Disables the TX event
 *
 * @param       None
 *
 * @retval      None
 */
void M0CP_DisableTXEvent(void)
{
    M0CP->CTRL_REG_B.TXEVEN = BIT_RESET;
}

/*!
 * @brief       Enables the specified interrupts
 *
 * @param       interrupt:  Specifies the M0CP interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_INT_TX:    Operation finish interrupt
 *
 * @retval      None
 */
void M0CP_EnableInterrupt(uint32_t interrupt)
{
    M0CP->TXIE_REG |= (uint32_t)interrupt;
}

/*!
 * @brief       Disables the specified interrupts
 *
 * @param       interrupt:  Specifies the M0CP interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg M0CP_INT_TX:    Operation finish interrupt
 *
 * @retval      None
 */
void M0CP_DisableInterrupt(uint32_t interrupt)
{
    M0CP->TXIE_REG &= (uint32_t)~interrupt;
}

/*!
 * @brief       Checks whether the specified M0CP flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be one of the following values:
 *                      @arg M0CP_FLAG_DONE     : M0CP operation finish flag
 *                      @arg M0CP_FLAG_BUSY     : M0CP operation busy flag
 *                      @arg M0CP_FLAG_DIVERR   : M0CP division error flag
 *                      @arg M0CP_FLAG_OVF      : M0CP overflow flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t M0CP_ReadStatusFlag(M0CP_FLAG_T flag)
{
    uint32_t status;

    if ((uint32_t)(flag & 0x10000))
    {
        status = M0CP->TXIR_REG & 0x00000001;
        status <<= 16;
    }
    else
    {
        status = M0CP->STAT_REG;
    }

    if ((status & flag) != (uint32_t)RESET)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified M0CP flag
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be any combination of the following values:
 *                      @arg M0CP_FLAG_DONE: M0CP operation finish flag
 *
 * @retval      None
 */
void M0CP_ClearStatusFlag(uint32_t flag)
{
    if ((uint32_t)(flag & 0x10000))
    {
        M0CP->TXIR_REG_B.DONE = BIT_SET;
    }
}

/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       flag:   Specifies the M0CP interrupt pending bit to check
 *                      The parameter can be one of following values:
 *                      @arg M0CP_INT_FLAG_DONE:    Operation finish interrupt flag
 *
 * @retval      M0CP interrupt flag status
 */
uint8_t M0CP_ReadIntFlag(M0CP_INT_FLAG_T flag)
{
    uint8_t intEnable;
    uint8_t intStatus;

    intEnable = (uint8_t)(M0CP->TXIE_REG & (uint32_t)flag);

    intStatus = (uint8_t)(M0CP->TXIS_REG & (uint32_t)flag);

    if (intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Load M0CP firmware from Flash to SRAM
 *
 * @param       None
 *
 * @retval      None
 */
void M0CP_Firmware_Init(void)
{
    unsigned int codecount = 0, code, time = 0;

    /* Load firmware from Flash to SRAM */
    for (codecount = 0; codecount <= 0x7FF; codecount++)
    {
        *(volatile unsigned char*)(M0CP_SRAM_ADDR + codecount)  = 0x0;
    }

    for (codecount = 0x0; codecount <= 0x3; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0x40; codecount <= 0x49; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0x80; codecount <= 0x94; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0xc0; codecount <= 0xdc; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0x100; codecount <= 0x105; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0x140; codecount <= 0x144; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0x180; codecount <= 0x184; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }

    for (codecount = 0x1c0; codecount <= 0x1fe; codecount++)
    {
        code = *(volatile unsigned int*)(M0CP_FLASH_ADDR + time * 4);

        *(volatile unsigned int*)(M0CP_SRAM_ADDR + codecount * 4)  = code;

        time++;
    }
}

#if M0CP_USE_FAST_IQ

/*!
 * @brief       M0CP fast IQ division signed
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[M0CP_X_INDEX]: quotient
 *              @arg result[M0CP_Y_INDEX]: remainder
 *
 * @retval      None
 *
 */
void M0CP_Fast_IQDivSigned(int32_t dividend, int32_t divisor,  int32_t* result)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_DIV_SI_FAST(dividend, divisor);

    /* Read quotient */
    result[M0CP_X_INDEX] = M0CP_ReadRegX();

    /* Read remainder */
    result[M0CP_Y_INDEX] = M0CP_ReadRegY();

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ division signed get quotient
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @retval      quotient
 *
 */
int32_t M0CP_Fast_IQDivSignedGetQuotient(int32_t dividend,int32_t divisor)
{
    uint32_t reg;
    int32_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_DIV_SI_FAST(dividend, divisor);

    result = (int32_t)M0CP_ReadRegX();

    NVIC->ISER[0] = reg;

    /* Read quotient */
    return result;
}

/*!
 * @brief       M0CP fast IQ division signed get remainder
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @retval      remainder
 *
 */
int32_t M0CP_Fast_IQDivSignedGetRemainder(int32_t dividend,int32_t divisor)
{
    uint32_t reg;
    int32_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_DIV_SI_FAST(dividend, divisor);

    result = (int32_t)M0CP_ReadRegY();

    NVIC->ISER[0] = reg;

    /* Read remainder */
    return result;
}

/*!
 * @brief       M0CP fast IQ division unsigned
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[M0CP_X_INDEX]: quotient
 *              @arg result[M0CP_Y_INDEX]: remainder
 *
 * @retval      None
 *
 */
void M0CP_Fast_IQDivUnsigned(uint32_t dividend, uint32_t divisor,  uint32_t* result)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_DIV_UN_FAST(dividend, divisor);

    /* Read quotient */
    result[M0CP_X_INDEX] = M0CP_ReadRegX();

    /* Read remainder */
    result[M0CP_Y_INDEX] = M0CP_ReadRegY();

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ division unsigned get quotient
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @retval      quotient
 *
 */
uint32_t M0CP_Fast_IQDivUnsignedGetQuotient(uint32_t dividend , uint32_t divisor)
{
    uint32_t reg;
    uint32_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_DIV_UN_FAST(dividend, divisor);

    /* Read quotient */
    result = M0CP_ReadRegX();

    NVIC->ISER[0] = reg;

    return result;
}

/*!
 * @brief       M0CP fast IQ division unsigned get remainder
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @retval      remainder
 *
 */
uint32_t M0CP_Fast_IQDivUnsignedGetRemainder(uint32_t dividend ,uint32_t divisor)
{
    uint32_t reg;
    uint32_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_DIV_UN_FAST(dividend, divisor);

    /* Read remainder */
    result = M0CP_ReadRegY();

    NVIC->ISER[0] = reg;

    return result;
}

/*!
 * @brief       M0CP fast IQ square root
 *
 * @param       input: square root input
 *
 * @retval      square root result
 *
 */
uint16_t M0CP_Fast_IQSquareRoot(uint32_t input)
{
    uint32_t reg;
    uint16_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SQUARE_FAST(input);

    /* Read result */
    result = (uint16_t)M0CP_ReadRegX();

    NVIC->ISER[0] = reg;

    return result;
}

/*!
 * @brief       M0CP fast IQ atan2
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @retval      result of atan2(y/x)
 *
 */
int16_t M0CP_Fast_IQAtan2(int32_t x, int32_t y)
{
    uint32_t reg;
    int16_t result;
    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_ATAN2_FAST(x, y, 0);

    result = (int16_t)M0CP_ReadRegZ();

    NVIC->ISER[0] = reg;

    /* Read result */
    return result;
}

/*!
 * @brief       M0CP fast IQ cos
 *
 * @param       z: parameter z
 *
 * @retval      result of cos(z)
 *
 * @note        result [-32768, 32767] <-> [cos(-PI), cos(PI)]
 */
int16_t M0CP_Fast_IQCos(int32_t z)
{
    uint32_t reg;
    int16_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_ROTATE_FAST(CORDIC_ROTATE_X, 0, z);

    result = (int16_t)M0CP_ReadRegX();

    NVIC->ISER[0] = reg;

    /* Read result */
    return result;
}

/*!
 * @brief       M0CP fast IQ cos division 2
 *
 * @param       z: parameter z
 *
 * @retval      result of cos(z)
 *
 * @note        result [-32768, 32767] <-> [cos(-PI), cos(PI)]
 */
int16_t M0CP_Fast_IQCosDiv2(int32_t z)
{
    uint32_t reg;
    int16_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_ROTATE_DIV2_FAST(CORDIC_ROTATE_X, 0, z);

    /* Read result */
    result = (int16_t)M0CP_ReadRegX();

    NVIC->ISER[0] = reg;

    return result;
}

/*!
 * @brief       M0CP fast IQ sin
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_Y_INDEX]: result of cos(z)
 *
 * @retval      None
 *
 * @note        result [-32768, 32767] <-> [cos(-PI), cos(PI)]
 *
 */
int16_t M0CP_Fast_IQSin(int32_t z)
{
    uint32_t reg;
    int16_t result;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_ROTATE_FAST(CORDIC_ROTATE_X, 0, z);

    /* Read result */
    result = (int16_t)M0CP_ReadRegY();

    NVIC->ISER[0] = reg;

    return result;
}

/*!
 * @brief       M0CP fast IQ sin division 2
 *
 * @param       z: parameter z
 *
 * @retval      result of cos(z)
 *
 * @note        result [-32768, 32767] <-> [cos(-PI), cos(PI)]
 *
 */
int16_t M0CP_Fast_IQSinDiv2(int32_t z)
{
    uint32_t reg;
    int16_t result;
    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_ROTATE_DIV2_FAST(CORDIC_ROTATE_X, 0, z);

    /* Read result */
    result = (int16_t)M0CP_ReadRegY();

    NVIC->ISER[0] = reg;

    return result;
}

/*!
 * @brief       M0CP fast IQ CORDIC rotate
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_X_INDEX]: reg X result
 *              @arg result[M0CP_Y_INDEX]: reg Y result
 *              @arg result[M0CP_Z_INDEX]: reg Z result
 *
 * @retval      None
 *
 */
void M0CP_Fast_IQRotateCORDIC(int16_t x, int16_t y, int16_t z, int16_t* result)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_ROTATE_FAST(x, y, z);

    /* Read result */
    result[M0CP_X_INDEX] = (int16_t)M0CP_ReadRegX();
    result[M0CP_Y_INDEX] = (int16_t)M0CP_ReadRegY();
    result[M0CP_Z_INDEX] = (int16_t)M0CP_ReadRegZ();

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ CORDIC rotate division 2
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_X_INDEX]: reg X result
 *              @arg result[M0CP_Y_INDEX]: reg Y result
 *              @arg result[M0CP_Z_INDEX]: reg Z result
 *
 * @retval      None
 *
 */
void M0CP_Fast_IQRotateCORDICDiv2(int32_t x, int32_t y, int32_t z, int16_t* result)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_ROTATE_DIV2_FAST(x, y, z);

    /* Read result */
    result[M0CP_X_INDEX] = (int16_t)M0CP_ReadRegX();
    result[M0CP_Y_INDEX] = (int16_t)M0CP_ReadRegY();
    result[M0CP_Z_INDEX] = (int16_t)M0CP_ReadRegZ();

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ CORDIC vector
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_X_INDEX]: reg X result
 *              @arg result[M0CP_Y_INDEX]: reg Y result
 *              @arg result[M0CP_Z_INDEX]: reg Z result
 *
 *
 * @retval      None
 *
 */
void M0CP_Fast_IQVectorCORDIC(int32_t x, int32_t y, int32_t z, int16_t* result)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_CORDIC_VECTOR_FAST(x, y, z);

    /* Read result */
    result[M0CP_X_INDEX] = (int16_t)M0CP_ReadRegX();
    result[M0CP_Y_INDEX] = (int16_t)M0CP_ReadRegY();
    result[M0CP_Z_INDEX] = (int16_t)M0CP_ReadRegZ();

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM7 counter Q15
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ca: SVPWM Ca
 *              @arg svpwmData->Cb: SVPWM Cb
 *              @arg svpwmData->Cc: SVPWM Cc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 *
 */
void M0CP_Fast_IQCounterQ15SVPWM7(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM7_COUNT_Q15_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ca = (uint16_t)M0CP_ReadRegX();
    svpwmData->Cb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Cc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM7 counter Q14
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ca: SVPWM Ca
 *              @arg svpwmData->Cb: SVPWM Cb
 *              @arg svpwmData->Cc: SVPWM Cc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 *
 */
void M0CP_Fast_IQCounterQ14SVPWM7(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM7_COUNT_Q14_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ca = (uint16_t)M0CP_ReadRegX();
    svpwmData->Cb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Cc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM5 counter Q15
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ca: SVPWM Ca
 *              @arg svpwmData->Cb: SVPWM Cb
 *              @arg svpwmData->Cc: SVPWM Cc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 *
 */
void M0CP_Fast_IQCounterQ15SVPWM5(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM5_COUNT_Q15_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ca = (uint16_t)M0CP_ReadRegX();
    svpwmData->Cb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Cc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM5 counter Q14
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ca: SVPWM Ca
 *              @arg svpwmData->Cb: SVPWM Cb
 *              @arg svpwmData->Cc: SVPWM Cc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 *
 */
void M0CP_Fast_IQCounterQ14SVPWM5(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM5_COUNT_Q14_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ca = (uint16_t)M0CP_ReadRegX();
    svpwmData->Cb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Cc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM7 duty Q15
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ta: SVPWM Ta
 *              @arg svpwmData->Tb: SVPWM Tb
 *              @arg svpwmData->Tc: SVPWM Tc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 */
void M0CP_Fast_IQDutyQ15SVPWM7(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM7_DUTY_Q15_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ta = (uint16_t)M0CP_ReadRegX();
    svpwmData->Tb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Tc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM7 duty Q14
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ta: SVPWM Ta
 *              @arg svpwmData->Tb: SVPWM Tb
 *              @arg svpwmData->Tc: SVPWM Tc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 */
void M0CP_Fast_IQDutyQ14SVPWM7(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM7_DUTY_Q14_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ta = (uint16_t)M0CP_ReadRegX();
    svpwmData->Tb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Tc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM5 duty Q15
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ta: SVPWM Ta
 *              @arg svpwmData->Tb: SVPWM Tb
 *              @arg svpwmData->Tc: SVPWM Tc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 */
void M0CP_Fast_IQDutyQ15SVPWM5(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM5_DUTY_Q15_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ta = (uint16_t)M0CP_ReadRegX();
    svpwmData->Tb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Tc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

/*!
 * @brief       M0CP fast IQ SVPWM5 duty Q14
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ta: SVPWM Ta
 *              @arg svpwmData->Tb: SVPWM Tb
 *              @arg svpwmData->Tc: SVPWM Tc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 */
void M0CP_Fast_IQDutyQ14SVPWM5(SVPWM_DATA_T* svpwmData)
{
    uint32_t reg;

    reg = NVIC->ISER[0];
    NVIC->ICER[0] = reg;

    M0CP_SVPWM5_DUTY_Q14_FAST(svpwmData->Ualpha, svpwmData->Ubeta);

    /* Read result */
    svpwmData->Ta = (uint16_t)M0CP_ReadRegX();
    svpwmData->Tb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Tc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    NVIC->ISER[0] = reg;
}

#endif

/*!
 * @brief       M0CP division signed
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[M0CP_X_INDEX]: quotient
 *              @arg result[M0CP_Y_INDEX]: remainder
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQDivSigned(int32_t divisor, int32_t dividend, int32_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_DIV_SI(dividend, divisor);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read quotient */
    result[M0CP_X_INDEX] = M0CP_ReadRegX();

    /* Read remainder */
    result[M0CP_Y_INDEX] = M0CP_ReadRegY();

    return errSta;
}

/*!
 * @brief       M0CP division signed get quotient
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[0]: quotient
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQDivSignedGetQuotient(int32_t divisor, int32_t dividend, int32_t* result)
{
    uint32_t timeout = 0;

    M0CP_STA_T errSta = M0CP_OK;

    M0CP_DIV_SI(dividend, divisor);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read quotient */
    result[0] = M0CP_ReadRegX();

    return errSta;
}

/*!
 * @brief       M0CP division signed get remainder
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[0]: remainder
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQDivSignedGetRemainder(int32_t divisor, int32_t dividend, int32_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_DIV_SI(dividend, divisor);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read remainder */
    result[0] = M0CP_ReadRegY();

    return errSta;
}

/*!
 * @brief       M0CP division unsigned
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[M0CP_X_INDEX]: quotient
 *              @arg result[M0CP_Y_INDEX]: remainder
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQDivUnsigned(uint32_t divisor, uint32_t dividend, uint32_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_DIV_UN(dividend, divisor);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read quotient */
    result[M0CP_X_INDEX] = M0CP_ReadRegX();

    /* Read remainder */
    result[M0CP_Y_INDEX] = M0CP_ReadRegY();

    return errSta;
}

/*!
 * @brief       M0CP division unsigned get quotient
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[0]: quotient
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQDivUnsignedGetQuotient(uint32_t divisor, uint32_t dividend, uint32_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_DIV_UN(dividend, divisor);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read quotient */
    result[0] = M0CP_ReadRegX();

    return errSta;
}

/*!
 * @brief       M0CP division unsigned get remainder
 *
 * @param       divisor: division divisor
 *
 * @param       dividend : division dividend
 *
 * @param       result: division operation result
 *              @arg result[0]: remainder
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQDivUnsignedGetRemainder(uint32_t divisor, uint32_t dividend, uint32_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_DIV_UN(dividend, divisor);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read remainder */
    result[0] = M0CP_ReadRegY();

    return errSta;
}

/*!
 * @brief       M0CP square root
 *
 * @param       input: square root input
 *
 * @param       result: operation result
 *              @arg result[M0CP_X_INDEX]: square root result
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQSquareRoot(uint32_t input, uint16_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_SQUARE(input);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    result[M0CP_X_INDEX] = (uint16_t)M0CP_ReadRegX();

    return errSta;
}

/*!
 * @brief       M0CP atan2
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @param       result
 *              @arg result[M0CP_Z_INDEX]: result of atan2(x)
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQAtan2(int32_t x, int32_t y, int16_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_CORDIC_VECTOR(x, y, 0);

    M0CP_StartOperation();

    /* Waitting operation done*/
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    *result = (int16_t)M0CP_ReadRegZ();

    return errSta;
}

/*!
 * @brief       M0CP cos
 *
 * @param       z: parameter z
 *
 * @param      result
 *              @arg result[M0CP_X_INDEX]: result of cos(z)
 *
 * @retval      M0CP operation status
 *
 * @note        result [-32768, 32767] <-> [cos(-PI), cos(PI)]
 */
M0CP_STA_T M0CP_IQCos(int32_t z, int16_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_CORDIC_ROTATE(CORDIC_ROTATE_X, 0, z);

    M0CP_StartOperation();

    /* Waitting operation done*/
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    *result = (int16_t)M0CP_ReadRegX();

    return errSta;
}

/*!
 * @brief       M0CP sin
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_Y_INDEX]: result of cos(z)
 *
 * @retval      M0CP operation status
 *
 * @note        result [-32768, 32767] <-> [cos(-PI), cos(PI)]
 *
 */
M0CP_STA_T M0CP_IQSin(int32_t z, int16_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_CORDIC_ROTATE(CORDIC_ROTATE_X, 0, z);

    M0CP_StartOperation();

    /* Waitting operation done*/
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    *result = (int16_t)M0CP_ReadRegY();

    return errSta;
}

/*!
 * @brief       M0CP CORDIC vector
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_X_INDEX]: reg X result
 *              @arg result[M0CP_Y_INDEX]: reg Y result
 *              @arg result[M0CP_Z_INDEX]: reg Z result
 *
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQVectorCORDIC(int32_t x, int32_t y, int32_t z, int16_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_CORDIC_VECTOR(x, y, z);

    M0CP_StartOperation();

    /* Waitting operation done*/
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    result[M0CP_X_INDEX] = (int16_t)M0CP_ReadRegX();
    result[M0CP_Y_INDEX] = (int16_t)M0CP_ReadRegY();
    result[M0CP_Z_INDEX] = (int16_t)M0CP_ReadRegZ();

    return errSta;
}

/*!
 * @brief       M0CP CORDIC rotate
 *
 * @param       x: parameter x
 *
 * @param       y: parameter y
 *
 * @param       z: parameter z
 *
 * @param       result
 *              @arg result[M0CP_X_INDEX]: reg X result
 *              @arg result[M0CP_Y_INDEX]: reg Y result
 *              @arg result[M0CP_Z_INDEX]: reg Z result
 *
 * @retval      M0CP operation status
 *
 */
M0CP_STA_T M0CP_IQRotateCORDIC(int32_t x, int32_t y, int32_t z, int16_t* result)
{
    uint32_t timeout = 0;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_CORDIC_ROTATE(x, y, z);

    M0CP_StartOperation();

    /* Waitting operation done*/
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    result[M0CP_X_INDEX] = (int16_t)M0CP_ReadRegX();
    result[M0CP_Y_INDEX] = (int16_t)M0CP_ReadRegY();
    result[M0CP_Z_INDEX] = (int16_t)M0CP_ReadRegZ();

    return errSta;
}

/*!
 * @brief       M0CP SVPWM duty
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ta: SVPWM Ta
 *              @arg svpwmData->Tb: SVPWM Tb
 *              @arg svpwmData->Tc: SVPWM Tc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @param       Qn: fixed point
 *
 * @param       seg: segmentation
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 */
M0CP_STA_T M0CP_IQDutySVPWM(SVPWM_DATA_T* svpwmData, M0CP_FIXED_POINT_T Qn, M0CP_SVPWM_SEG_T seg)
{
    uint32_t timeout = 0;
    uint16_t mulValSVPWM = SVPWM_MUL_VALUE;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_ConfigSegSVPWM(seg);
    M0CP_ConfigQn(Qn);

    mulValSVPWM >>= (M0CP_FP_Q15 - Qn);

    M0CP_SVPWM((int32_t)(svpwmData->Ualpha * mulValSVPWM), svpwmData->Ubeta);

    M0CP_StartOperation();

    /* Waitting operation done*/
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    svpwmData->Ta = (uint16_t)M0CP_ReadRegX();
    svpwmData->Tb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Tc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    return errSta;
}

/*!
 * @brief       M0CP SVPWM counter
 *
 * @param       svpwmData: SVPWM parameter
 *              @arg svpwmData->Ca: SVPWM Ca
 *              @arg svpwmData->Cb: SVPWM Cb
 *              @arg svpwmData->Cc: SVPWM Cc
 *              @arg svpwmData->sector: SVPWM sector
 *
 * @param       Qn: fixed point
 *
 * @param       seg: segmentation
 *
 * @retval      M0CP operation status
 *
 * @note        if SVPWM output mode is M0CP_SVPWM_OUT_CNT, you need configure M0CP and AUTORLD of TMR
 *
 */
M0CP_STA_T M0CP_IQCounterSVPWM(SVPWM_DATA_T* svpwmData, M0CP_FIXED_POINT_T Qn, M0CP_SVPWM_SEG_T seg)
{
    uint32_t timeout = 0;
    uint16_t mulValSVPWM = SVPWM_MUL_VALUE;
    M0CP_STA_T errSta = M0CP_OK;

    M0CP_ConfigSegSVPWM(seg);
    M0CP_ConfigQn(Qn);

    mulValSVPWM >>= (M0CP_FP_Q15 - Qn);

    M0CP_SVPWM((int32_t)(svpwmData->Ualpha * mulValSVPWM), svpwmData->Ubeta);

    M0CP_StartOperation();

    /* Waitting operation done */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_DONE) == RESET)
    {
        timeout++;
        if (timeout >= M0CP_TIMEOUT_VAL)
        {
            errSta = M0CP_TIMEOUT;
            return errSta;
        }
    }
    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);

    /* Read result */
    svpwmData->Ca = (uint16_t)M0CP_ReadRegX();
    svpwmData->Cb = (uint16_t)M0CP_ReadRegY();
    svpwmData->Cc = (uint16_t)M0CP_ReadRegZ();
    svpwmData->sector = (uint16_t)(M0CP_ReadRegW() & 0x0007);

    return errSta;
}
/**@} end of group M0CP_Functions */
/**@} end of group M0CP_Driver */
/**@} end of group APM32M35xx_StdPeriphDriver */

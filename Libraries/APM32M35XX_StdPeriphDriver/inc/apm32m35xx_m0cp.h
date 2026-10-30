/*!
 * @file        apm32m35xx_m0cp.h
 *
 * @brief       This file contains all the functions prototypes for the M0CP firmware library
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
#ifndef __APM32M35XX_M0CP_H
#define __APM32M35XX_M0CP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32m35xx.h"


/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup M0CP_Driver
  @{
*/

/** @defgroup M0CP_Macros Macros
  @{
*/

#define M0CP_USE_FAST_IQ                    1U

#define SVPWM_MUL_VALUE                     0xDDB3
#define M0CP_FLASH_ADDR                     0x080000BC
#define M0CP_SRAM_ADDR                      0x20002000
#define M0CP_TIMEOUT_VAL                    0x7FFFF
#define CORDIC_ROTATE_X                     0x3FFF
#define CORDIC_ROTATE_Y                     0x3FFF

#define M0CP_HardInit()                     *(volatile unsigned int*)(M0CP_BASE + 0x40) &= ~(1 << 29)
#define M0CP_DIV_UN(X,Y)                    (M0CP->X_REG = X, M0CP->Y_REG = Y)
#define M0CP_DIV_SI(X,Y)                    (M0CP->X_REG = X, M0CP->Y_REG = Y)
#define M0CP_SQUARE(X)                      (M0CP->X_REG = X)
#define M0CP_CORDIC_VECTOR(X,Y,Z)           (M0CP->X_REG = X, M0CP->Y_REG = Y ,M0CP->Z_REG = Z)
#define M0CP_CORDIC_ROTATE(X,Y,Z)           (M0CP->X_REG = X, M0CP->Y_REG = Y ,M0CP->Z_REG = Z)
#define M0CP_SVPWM(Ua,Ub)                   (M0CP->X_REG = Ub, M0CP->Y_REG = Ua)

/* Fast IQ function define */
#if M0CP_USE_FAST_IQ
#define M0CP_PARAM_ATAN2_CTRL               0x00070079
#define M0CP_PARAM_DIV_SI_CTRL              0x00060079
#define M0CP_PARAM_DIV_UN_CTRL              0x00050079
#define M0CP_PARAM_SQURE_CTRL               0x00040079
#define M0CP_PARAM_CORDIC_VECTOR_CTRL       0x00030079
#define M0CP_PARAM_CORDIC_ROTATE_CTRL       0x00020079
#define M0CP_PARAM_CORDIC_ROTATE_CTRLDIV2   0x000200F9

#define M0CP_PARAM_SVPWM7_COUNT_Q15_CTRL    0x00010279
#define M0CP_PARAM_SVPWM7_COUNT_Q14_CTRL    0x00010271
#define M0CP_PARAM_SVPWM5_COUNT_Q15_CTRL    0x00010379
#define M0CP_PARAM_SVPWM5_COUNT_Q14_CTRL    0x00010371

#define M0CP_PARAM_SVPWM7_DUTY_Q15_CTRL     0x00010079
#define M0CP_PARAM_SVPWM7_DUTY_Q14_CTRL     0x00010071
#define M0CP_PARAM_SVPWM5_DUTY_Q15_CTRL     0x00010179
#define M0CP_PARAM_SVPWM5_DUTY_Q14_CTRL     0x00010171

#define M0CP_PARAM_SVPWM_Q15_MULVALUE       0xDDB3
#define M0CP_PARAM_SVPWM_Q14_MULVALUE       0x6ED9

#define M0CP_DIV_SI_FAST(X,Y)               (*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Y, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_DIV_SI_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_DIV_UN_FAST(X,Y)               (*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Y, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_DIV_UN_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SQUARE_FAST(X)                 (*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SQURE_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_ATAN2_FAST(X,Y,Z)      		(*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Y, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x1C) = Z, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_ATAN2_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_CORDIC_VECTOR_FAST(X,Y,Z)      (*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Y, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x1C) = Z, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_CORDIC_VECTOR_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP())

#define M0CP_CORDIC_ROTATE_FAST(X,Y,Z)      (*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Y, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x1C) = Z, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_CORDIC_ROTATE_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_CORDIC_ROTATE_DIV2_FAST(X,Y,Z) (*(volatile unsigned int*)(M0CP_BASE + 0x14) = X, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Y, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x1C) = Z, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_CORDIC_ROTATE_CTRLDIV2, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM7_COUNT_Q15_FAST(Ua,Ub)  (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q15_MULVALUE), \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM7_COUNT_Q15_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(),\
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM5_COUNT_Q15_FAST(Ua,Ub)  (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q15_MULVALUE), \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM5_COUNT_Q15_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM7_COUNT_Q14_FAST(Ua,Ub)   (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q14_MULVALUE),  \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM7_COUNT_Q14_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM5_COUNT_Q14_FAST(Ua,Ub)   (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q14_MULVALUE),  \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM5_COUNT_Q14_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM7_DUTY_Q15_FAST(Ua,Ub)    (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q15_MULVALUE), \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM7_DUTY_Q15_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM5_DUTY_Q15_FAST(Ua,Ub)    (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q15_MULVALUE), \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM5_DUTY_Q15_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM7_DUTY_Q14_FAST(Ua,Ub)    (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q14_MULVALUE), \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM7_DUTY_Q14_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())

#define M0CP_SVPWM5_DUTY_Q14_FAST(Ua,Ub)    (*(volatile unsigned int*)(M0CP_BASE + 0x14) = Ub, \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x18) = Ua * (M0CP_PARAM_SVPWM_Q14_MULVALUE),  \
                                            *(volatile unsigned int*)(M0CP_BASE + 0x00) = M0CP_PARAM_SVPWM5_DUTY_Q14_CTRL, \
                                            __NOP(), __NOP(), __NOP(), __NOP(), __NOP(), __NOP())
#endif

/*!
 * @brief       M0CP start operation
 *
 * @param       None
 *
 * @retval      None
 */
#define M0CP_StartOperation()       M0CP->CTRL_REG_B.RUN = BIT_SET

/*!
 * @brief       M0CP read X register value
 *
 * @param       None
 *
 * @retval      result value
 */
#define M0CP_ReadRegX()             M0CP->X_REG

/*!
 * @brief       M0CP read Y register value
 *
 * @param       None
 *
 * @retval      result value
 */
#define M0CP_ReadRegY()             M0CP->Y_REG

/*!
 * @brief       M0CP read Z register value
 *
 * @param       None
 *
 * @retval      result value
 */
#define M0CP_ReadRegZ()             M0CP->Z_REG

/*!
 * @brief       M0CP set W register value
 *
 * @param       None
 *
 * @retval      result value
 */
#define M0CP_ReadRegW()             M0CP->W_REG

/**@} end of group M0CP_Macros */

/** @defgroup M0CP_Enumerations Enumerations
  @{
*/

/**
 * @brief   SVPWM output result struct definition
 */
typedef struct
{
    int32_t Ualpha;
    int16_t Ubeta;
    uint16_t Ta;
    uint16_t Tb;
    uint16_t Tc;
    uint16_t Ca;
    uint16_t Cb;
    uint16_t Cc;
    uint16_t sector;
} SVPWM_DATA_T;

/**
 * @brief   M0CP operation status
 */
typedef enum
{
    M0CP_OK,
    M0CP_ERR,
    M0CP_BUSY,
    M0CP_TIMEOUT,
} M0CP_STA_T;

/**
 * @brief   M0CP result register index
 */
typedef enum
{
    M0CP_X_INDEX,
    M0CP_Y_INDEX,
    M0CP_Z_INDEX,
} M0CP_REG_INDEX_T;

/**
 * @brief   M0CP bank auto conversion selection
 */
typedef enum
{
    M0CP_BANK_CONV_SOFTWARE,    /*!< Bank auto conversion by software */
    M0CP_BANK_CONV_HARDWARE,    /*!< Bank auto conversion by hardware */
} M0CP_BANK_CONV_T;

/**
 * @brief   M0CP bank register selection
 */
typedef enum
{
    M0CP_BANK_REG_GROUP_0,    /*!< Bank register group 0 */
    M0CP_BANK_REG_GROUP_1,    /*!< Bank register group 1 */
} M0CP_BANK_REG_T;

/**
 * @brief   M0CP fixed point selection
 */
typedef enum
{
    M0CP_FP_NONE,   /*!< No fixed point */
    M0CP_FP_Q1,     /*!< Q1 fixed point */
    M0CP_FP_Q2,     /*!< Q2 fixed point */
    M0CP_FP_Q3,     /*!< Q3 fixed point */
    M0CP_FP_Q4,     /*!< Q4 fixed point */
    M0CP_FP_Q5,     /*!< Q5 fixed point */
    M0CP_FP_Q6,     /*!< Q6 fixed point */
    M0CP_FP_Q7,     /*!< Q7 fixed point */
    M0CP_FP_Q8,     /*!< Q8 fixed point */
    M0CP_FP_Q9,     /*!< Q9 fixed point */
    M0CP_FP_Q10,    /*!< Q10 fixed point */
    M0CP_FP_Q11,    /*!< Q11 fixed point */
    M0CP_FP_Q12,    /*!< Q12 fixed point */
    M0CP_FP_Q13,    /*!< Q13 fixed point */
    M0CP_FP_Q14,    /*!< Q14 fixed point */
    M0CP_FP_Q15,    /*!< Q15 fixed point */
} M0CP_FIXED_POINT_T;

/**
 * @brief   M0CP CORDIC result selection
 */
typedef enum
{
    M0CP_CORDIC_XY,         /*!< CORDIC X and Y origin result */
    M0CP_CORDIC_XY_DIV2,    /*!< CORDIC X and Y result divide 2 */
} M0CP_CORDIC_RESULT_T;

/**
 * @brief   M0CP SVPWM segmentation selection
 */
typedef enum
{
    M0CP_SVPWM_SEG_7,   /*!< SVPWM 7 segmentation */
    M0CP_SVPWM_SEG_5,   /*!< SVPWM 5 segmentation */
} M0CP_SVPWM_SEG_T;

/**
 * @brief   M0CP SVPWM output selection
 */
typedef enum
{
    M0CP_SVPWM_OUT_DUTY,    /*!< SVPWM output duty */
    M0CP_SVPWM_OUT_CNT,     /*!< SVPWM output counter */
} M0CP_SVPWM_OUT_T;

/**
 * @brief   M0CP algebra mode selection
 */
typedef enum
{
    M0CP_ALG_NONE,          /*!< No select algebra mode */
    M0CP_ALG_SVPWM,         /*!< SVPWM algebra mode */
    M0CP_ALG_CORDIC_ROTATE, /*!< CORDIC rotate algebra mode */
    M0CP_ALG_CORDIC_VECTOR, /*!< CORDIC vector algebra mode */
    M0CP_ALG_SQUARE_ROOT,   /*!< Square root algebra mode */
    M0CP_ALG_DIV_UNSIGNED,  /*!< Unsigned division algebra mode */
    M0CP_ALG_DIV_SIGNED,    /*!< Signed division algebra mode */
    M0CP_ALG_ATAN2,         /*!< atan2 algebra mode */
} M0CP_ALG_MODE_T;

/**
 * @brief   M0CP event definition
 */
typedef enum
{
    M0CP_EVENT_TX   = ((uint32_t)0x01),        /*!< M0CP TX event */
} M0CP_EVENT_T;

/**
 * @brief   M0CP interrupt definition
 */
typedef enum
{
    M0CP_INT_TX     = ((uint32_t)0x01),        /*!< M0CP TX interrupt */
} M0CP_INT_T;

/**
 * @brief   M0CP interrupt flag
 */
typedef enum
{
    M0CP_INT_FLAG_DONE = ((uint32_t)0x01),     /*!< M0CP TX interrupt flag */
} M0CP_INT_FLAG_T;

/**
 * @brief   M0CP status flag
 */
typedef enum
{
    M0CP_FLAG_DONE      = ((uint32_t)0x10000),   /*!< M0CP operation finish flag */
    M0CP_FLAG_BUSY      = ((uint32_t)0x01),      /*!< M0CP operation busy flag */
    M0CP_FLAG_DIVERR    = ((uint32_t)0x02),      /*!< M0CP division error flag */
    M0CP_FLAG_OVF       = ((uint32_t)0x04),      /*!< M0CP overflow flag */
} M0CP_FLAG_T;

/**@} end of group M0CP_Enumerations */

/** @defgroup M0CP_Structures Structures
  @{
*/

/**
 * @brief   M0CP config struct definition
 */
typedef struct
{
    M0CP_ALG_MODE_T         algebraMode;    /*!< Specifies the algebra mode */
    M0CP_BANK_CONV_T        bankAutoConv;   /*!< Specifies the way of bank auto conversion */
    M0CP_BANK_REG_T         bankRegGroup;   /*!< Specifies the register group of bank */
    M0CP_FIXED_POINT_T      fixedPoint;     /*!< Specifies the format of fixed point */
    M0CP_CORDIC_RESULT_T    xyResultCORDIC; /*!< Specifies the result of X and Y from CORDIC ouput */
    M0CP_SVPWM_SEG_T        segSVPWM;       /*!< Specifies the segmentation of SVPWM */
    M0CP_SVPWM_OUT_T        outputSVPWM;    /*!< Specifies the output of SVPWM */
} M0CP_Config_T;

/**@} end of group M0CP_Structures */

/** @defgroup M0CP_Variables Variables
  @{
  */

/**@} end of group M0CP_Variables */

/** @defgroup M0CP_Functions Functions
  @{
*/

/* Algorithm */
void M0CP_Firmware_Init(void);
void M0CP_ConfigWriteBank(M0CP_BANK_REG_T bankRegGroup);
void M0CP_ConfigReadBank(M0CP_BANK_REG_T bankRegGroup);
void M0CP_ConfigOpBank(M0CP_BANK_REG_T bankRegGroup);
void M0CP_ConfigStructInit(M0CP_Config_T* m0cpConfig);
void M0CP_Config(M0CP_Config_T* m0cpConfig);
void M0CP_ConfigQn(M0CP_FIXED_POINT_T fixedPoint);
void M0CP_ConfigAlgMode(M0CP_ALG_MODE_T operation);
void M0CP_ConfigSegSVPWM(M0CP_SVPWM_SEG_T segSVPWM);
void M0CP_SetRegX(int32_t value);
void M0CP_SetRegY(int32_t value);
void M0CP_SetRegZ(int32_t value);

#if M0CP_USE_FAST_IQ
/* Fast IQ */
void M0CP_Fast_IQDivSigned(int32_t dividend, int32_t divisor,  int32_t* result);
int32_t M0CP_Fast_IQDivSignedGetQuotient(int32_t dividend, int32_t divisor);
int32_t M0CP_Fast_IQDivSignedGetRemainder(int32_t dividend, int32_t divisor);

void M0CP_Fast_IQDivUnsigned(uint32_t dividend, uint32_t divisor,  uint32_t* result);
uint32_t M0CP_Fast_IQDivUnsignedGetQuotient(uint32_t dividend, uint32_t divisor);
uint32_t M0CP_Fast_IQDivUnsignedGetRemainder(uint32_t dividend, uint32_t divisor);

uint16_t M0CP_Fast_IQSquareRoot(uint32_t input);

int16_t M0CP_Fast_IQAtan2(int32_t x, int32_t y);
int16_t M0CP_Fast_IQCos(int32_t z);
int16_t M0CP_Fast_IQCosDiv2(int32_t z);
int16_t M0CP_Fast_IQSin(int32_t z);
int16_t M0CP_Fast_IQSinDiv2(int32_t z);

void M0CP_Fast_IQCounterQ15SVPWM7(SVPWM_DATA_T* svpwmData);
void M0CP_Fast_IQCounterQ15SVPWM5(SVPWM_DATA_T* svpwmData);
void M0CP_Fast_IQCounterQ14SVPWM7(SVPWM_DATA_T* svpwmData);
void M0CP_Fast_IQCounterQ14SVPWM5(SVPWM_DATA_T* svpwmData);

void M0CP_Fast_IQDutyQ15SVPWM7(SVPWM_DATA_T* svpwmData);
void M0CP_Fast_IQDutyQ15SVPWM5(SVPWM_DATA_T* svpwmData);
void M0CP_Fast_IQDutyQ14SVPWM7(SVPWM_DATA_T* svpwmData);
void M0CP_Fast_IQDutyQ14SVPWM5(SVPWM_DATA_T* svpwmData);

void M0CP_Fast_IQRotateCORDIC(int16_t x, int16_t y, int16_t z, int16_t* result);
void M0CP_Fast_IQRotateCORDICDiv2(int32_t x, int32_t y, int32_t z, int16_t* result);

void M0CP_Fast_IQVectorCORDIC(int32_t x, int32_t y, int32_t z, int16_t* result);
#endif

/* IQ */
M0CP_STA_T M0CP_IQDivSigned(int32_t divisor, int32_t dividend, int32_t* result);
M0CP_STA_T M0CP_IQDivSignedGetQuotient(int32_t divisor, int32_t dividend, int32_t* result);
M0CP_STA_T M0CP_IQDivSignedGetRemainder(int32_t divisor, int32_t dividend, int32_t* result);

M0CP_STA_T M0CP_IQDivUnsigned(uint32_t divisor, uint32_t dividend, uint32_t* result);
M0CP_STA_T M0CP_IQDivUnsignedGetQuotient(uint32_t divisor, uint32_t dividend, uint32_t* result);
M0CP_STA_T M0CP_IQDivUnsignedGetRemainder(uint32_t divisor, uint32_t dividend, uint32_t* result);

M0CP_STA_T M0CP_IQSquareRoot(uint32_t input, uint16_t* result);
M0CP_STA_T M0CP_IQAtan2(int32_t x, int32_t y, int16_t* result);
M0CP_STA_T M0CP_IQCos(int32_t z, int16_t* result);
M0CP_STA_T M0CP_IQSin(int32_t z, int16_t* result);
M0CP_STA_T M0CP_IQVectorCORDIC(int32_t x, int32_t y, int32_t z, int16_t* result);
M0CP_STA_T M0CP_IQRotateCORDIC(int32_t x, int32_t y, int32_t z, int16_t* result);
M0CP_STA_T M0CP_IQDutySVPWM(SVPWM_DATA_T* svpwmData, M0CP_FIXED_POINT_T Qn, M0CP_SVPWM_SEG_T seg);
M0CP_STA_T M0CP_IQCounterSVPWM(SVPWM_DATA_T* svpwmData, M0CP_FIXED_POINT_T Qn, M0CP_SVPWM_SEG_T seg);

/* Reversion */
uint32_t M0CP_ReadReversion(void);

/* Event */
void M0CP_EnableTXEvent(void);
void M0CP_DisableTXEvent(void);

/* Interrupt and flag */
void M0CP_EnableInterrupt(uint32_t interrupt);
void M0CP_DisableInterrupt(uint32_t interrupt);
uint8_t M0CP_ReadStatusFlag(M0CP_FLAG_T flag);
void M0CP_ClearStatusFlag(uint32_t flag);
uint8_t M0CP_ReadIntFlag(M0CP_INT_FLAG_T flag);

/**@} end of group M0CP_Functions */
/**@} end of group M0CP_Driver */
/**@} end of group APM32M35XX_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32M35xx_M0CP_H */

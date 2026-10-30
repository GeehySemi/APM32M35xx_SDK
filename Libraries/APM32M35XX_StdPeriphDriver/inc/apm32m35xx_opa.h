/*!
 * @file        apm32m35xx_opa.h
 *
 * @brief       This file contains all the functions prototypes for the OPA firmware library
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
#ifndef __APM32M35XX_OPA_H
#define __APM32M35XX_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32m35xx.h"

/** @addtogroup APM32M35XX_StdPeriphDriver
  @{
*/

/** @addtogroup OPA_Driver
  @{
*/

/** @defgroup OPA_Macros Macros
  @{
*/

/**@} end of group OPA_Macros */

/** @defgroup OPA_Enumerations Enumerations
  @{
*/

/**
 * @brief   OPA peripheral
 */
typedef enum
{
    OPA1,     /*!< Operational amplifier 1 */
    OPA2,     /*!< Operational amplifier 2 */
    OPA3,     /*!< Operational amplifier 3 */
    OPA4,     /*!< Operational amplifier 4 */
} OPA_PERIPH_T;

/**
 * @brief   OPA gain factor
 */
typedef enum
{
    OPA_GAIN_FACTOR_0  = ((uint8_t)0x00), /*!< By the external resistance, opn reverse input, op1out is the output */
    OPA_GAIN_FACTOR_1  = ((uint8_t)0x01), /*!< By internal gain coefficient x1,opn/op1out is normal IO */
    OPA_GAIN_FACTOR_2  = ((uint8_t)0x02), /*!< By internal gain coefficient x2,opn/op1out is normal IO */
    OPA_GAIN_FACTOR_4  = ((uint8_t)0x03), /*!< By internal gain coefficient x4,opn/op1out is normal IO */
    OPA_GAIN_FACTOR_8  = ((uint8_t)0x04), /*!< By internal gain coefficient x8,opn/op1out is normal IO */
    OPA_GAIN_FACTOR_10 = ((uint8_t)0x05), /*!< By internal gain coefficient x10,opn/op1out is normal IO */
    OPA_GAIN_FACTOR_16 = ((uint8_t)0x06), /*!< By internal gain coefficient x16,opn/op1out is normal IO */
    OPA_GAIN_FACTOR_20 = ((uint8_t)0x07), /*!< By internal gain coefficient x20,opn/op1out is normal IO */
} OPA_GAIN_FACTOR_T;

/**@} end of group OPA_Enumerations*/

/** @defgroup OPA_Structures Structures
  @{
*/

/**@} end of group OPA_Structures */

/** @defgroup OPA_Variables Variables
  @{
*/

/**@} end of group OPA_Variables */

/** @defgroup OPA_Functions Functions
  @{
*/
void OPA_Enable(OPA_PERIPH_T OPAPeriph);
void OPA_Disable(OPA_PERIPH_T OPAPeriph);
void OPA_SelectGainFactor(OPA_PERIPH_T OPAPeriph, OPA_GAIN_FACTOR_T gainFactor);

/**@} end of group OPA_Functions*/
/**@} end of group OPA_Driver*/
/**@} end of group APM32M35XX_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32M35XX_OPA_H */

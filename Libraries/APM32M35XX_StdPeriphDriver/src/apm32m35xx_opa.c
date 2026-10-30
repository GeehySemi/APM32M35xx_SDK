/*!
 * @file        apm32m35xx_opa.c
 *
 * @brief       This file contains all the functions for the OPA peripheral
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
#include "apm32m35xx_opa.h"
#include "apm32m35xx_rcm.h"

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

/**@} end of group OPA_Enumerations */

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

/*!
 * @brief       Enable the OPA peripheral
 *
 * @param       OPAPeriph:   specifies the OPA peripheral
 *                           This parameter can be any combination of the following values:
 *                           @arg OPA1:  Operational amplifier 1
 *                           @arg OPA2:  Operational amplifier 2
 *                           @arg OPA3:  Operational amplifier 3
 *                           @arg OPA4:  Operational amplifier 4
 *
 * @retval      None
 */
void OPA_Enable(OPA_PERIPH_T OPAPeriph)
{
    OPA->CFG |= (uint32_t)(1 << (OPAPeriph * 8));
}

/*!
 * @brief       Disable the OPA peripheral
 *
 * @param       OPAPeriph:   specifies the OPA peripheral
 *                           This parameter can be any combination of the following values:
 *                           @arg OPA1:  Operational amplifier 1
 *                           @arg OPA2:  Operational amplifier 2
 *                           @arg OPA3:  Operational amplifier 3
 *                           @arg OPA4:  Operational amplifier 4
 *
 * @retval      None
 */
void OPA_Disable(OPA_PERIPH_T OPAPeriph)
{
    OPA->CFG &= (uint32_t)~(1 << (OPAPeriph * 8));
}


/*!
 * @brief       Enables the specified interrupts
 *
 * @param       None
 *
 * @param       OPAPeriph:   specifies the OPA peripheral
 *                           This parameter can be one of the following values:
 *                           @arg OPA1:  Operational amplifier 1
 *                           @arg OPA2:  Operational amplifier 2
 *                           @arg OPA3:  Operational amplifier 3
 *                           @arg OPA4:  Operational amplifier 4
 * @param       gainFactor:  specifies the OPA Gain Facto
 *                           The parameter can be onr of following values:
 *                           @arg OPA_GAIN_FACTOR_0: By the external resistance, opn reverse input, op1out is the output
 *                           @arg OPA_GAIN_FACTOR_1: By internal gain coefficient x1,opn/op1out is normal IO
 *                           @arg OPA_GAIN_FACTOR_2: By internal gain coefficient x2,opn/op1out is normal IO
 *                           @arg OPA_GAIN_FACTOR_4: By internal gain coefficient x4,opn/op1out is normal IO
 *                           @arg OPA_GAIN_FACTOR_8: By internal gain coefficient x8,opn/op1out is normal IO
 *                           @arg OPA_GAIN_FACTOR_10: By internal gain coefficient x10,opn/op1out is normal IO
 *                           @arg OPA_GAIN_FACTOR_16: By internal gain coefficient x16,opn/op1out is normal IO
 *                           @arg OPA_GAIN_FACTOR_20: By internal gain coefficient x20,opn/op1out is normal IO
 *
 * @retval      None
 */
void OPA_SelectGainFactor(OPA_PERIPH_T OPAPeriph, OPA_GAIN_FACTOR_T gainFactor)
{
    OPA->CFG |= (uint32_t)(gainFactor << (OPAPeriph * 8 + 2));
}

/**@} end of group OPA_Functions*/
/**@} end of group OPA_Driver*/
/**@} end of group APM32M35XX_StdPeriphDriver*/

/*!
 * @file        board.c
 *
 * @brief       This file contains firmware functions to manage Leds and push-buttons
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
#include "board.h"

#ifdef BOARD_APM32M35XX_MINI
    #include "Board_APM32M35XX/src/board_apm32m35xx.c"
#endif

/** @addtogroup Boards
  @{
*/

/** @addtogroup Board_APM32M35XX
  @{
*/

/**@} end of group Board_APM32M35XX */
/**@} end of group Boards */

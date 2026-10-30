/*!
 * @file        bsp_usart.h
 *
 * @brief       Header for bsp_usart.c module
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
#ifndef __BSP_I2C_H
#define __BSP_I2C_H

/* Includes */
#include "board.h"
#include "apm32m35xx.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_i2c.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_I2C
  @{
  */

/** @defgroup IAP_BootLoader_I2C_Macros Macros
  @{
  */

/**@} end of group IAP_BootLoader_I2C_Macros*/

/** @defgroup IAP_BootLoader_I2C_Functions Functions
  @{
  */

void I2C_Init(void);
uint32_t I2C_Write(uint8_t* dat);
uint32_t I2C_WriteBuf(uint8_t* dat, uint16_t length);
uint32_t I2C_Read(uint8_t* dat, uint16_t num);
/**@} end of group IAP_BootLoader_I2C_Functions */
/**@} end of group IAP_BootLoader_I2C */
/**@} end of group Examples */

#endif

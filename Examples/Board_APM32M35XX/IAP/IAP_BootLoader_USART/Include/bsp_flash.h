/*!
 * @file        bsp_flash.h
 *
 * @brief       Header for bsp_flash.c module
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
#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

/* Includes */
#include "main.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_USART
  @{
  */

/** @defgroup IAP_BootLoader_USART_Macros Macros
  @{
  */

#define FLASH_BASE                  (uint32_t)0x08000000

/* 1 Kbytes */
#define FLASH_PAGE_SIZE             (uint32_t)0x400

#define USER_APP1_ADDRESS           (uint32_t)0x08004000
/* 8 KBytes */
#define USER_APP1_END_ADDRESS       (uint32_t)0x08006000
#define USER_APP1_FLASH_SIZE        (USER_APP1_END_ADDRESS - USER_APP1_ADDRESS)

#define USER_APP2_ADDRESS           (uint32_t)0x08006000
/* 8 KBytes */
#define USER_APP2_END_ADDRESS       (uint32_t)0x08008000
#define USER_APP2_FLASH_SIZE        (USER_APP2_END_ADDRESS - USER_APP2_ADDRESS)

#define USER_FLASH_SIZE             (USER_APP2_END_ADDRESS - USER_APP1_ADDRESS)

/**@} end of group IAP_BootLoader_USART_Macros*/

/** @defgroup IAP_BootLoader_USART_Enumerations Enumerations
  @{
  */

/*!
 * @brief    APP type define
 */
typedef enum
{
    APP1 = 0,   /*!< Application1 */
    APP2 = 1    /*!< Application2 */
} APP_TypeDef;

/**@} end of group IAP_BootLoader_USART_Enumerations*/

/** @defgroup IAP_BootLoader_USART_Functions Functions
  @{
  */

void FLASH_IAP_Init(void);
uint32_t FLASH_IAP_Erase(APP_TypeDef Application);
uint32_t FLASH_IAP_Write(__IO uint32_t* address, uint32_t* data, uint16_t length, APP_TypeDef Application);

/**@} end of group IAP_BootLoader_USART_Functions */
/**@} end of group IAP_BootLoader_USART */
/**@} end of group Examples */

#endif

/*!
 * @file        menu.c
 *
 * @brief       Display a usart menu to user and include IAP download and upload and area jump operation
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
#include "common.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_SPI
  @{
  */

/** @defgroup IAP_BootLoader_SPI_Variables Variables
  @{
  */

uint8_t filek[1024] = {0};
uint8_t FileN[FILE_NAME_MAX];

uint32_t FlashProtection = 0;

/**@} end of group IAP_BootLoader_SPI_Variables */

/** @defgroup IAP_BootLoader_SPI_Functions Functions
  @{
  */

/*!
 * @brief       Download a file via serial port
 *
 * @param       Application : APP1 or APP2
 *
 * @retval      None
 *
 * @note
 */
void Download(APP_TypeDef Application)
{
    uint32_t timeout = 0xFFFF;
    int32_t Size = 0;

    Size = recceiveFile(&filek[0], Application);
    while (timeout-- > 0);

    switch (Size)
    {
        case -3:
            break;

        case -2:
            break;

        case -1:
            break;

        default:


            break;
    }
}

/*!
 * @brief       Upload a file via serial port.
 *
 * @param       Application : APP1 or APP2
 *
 * @retval      None
 *
 * @note
 */
void Upload(APP_TypeDef Application)
{
    if (ReadKey() == FRAME_CRC16)
    {

        if (Application == APP1)
        {
            /* Transmit the flash image through ymodem protocol */
            transmitFile((uint8_t*)USER_APP1_ADDRESS, \
                                  (const uint8_t*)"Up_APM32M35XX_App1_FlashImage.bin", USER_APP1_FLASH_SIZE);
        }
        else
        {
            /* Transmit the flash image through ymodem protocol */
            transmitFile((uint8_t*)USER_APP2_ADDRESS, \
                                  (const uint8_t*)"Up_APM32M35XX_App2_FlashImage.bin", USER_APP2_FLASH_SIZE);
        }
    }
}

/*!
 * @brief       Display the Main Menu on HyperTerminal
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void Select_Menu(void)
{
    uint8_t key = 0;

    /* Checks whether the FLASH Write Protection Status is set or not */
    if (FMC_ReadOptionByteWriteProtection() != 0xFFFFFFFF)
    {
        Jump_to_App(APP1);
    }

    while (1)
    {

        /* Receive key */
        key = ReadKey();

        switch (key)
        {
            case 0x31:/* Download user application in the Flash */
                Download(APP1);
                break;

            case 0x32:/* Upload user application from the Flash */
                Upload(APP1);
                break;

            case 0x33:/* execute the new program */
            /* execute the new program */
                Jump_to_App(APP1);
                break;

            case 0x34:/* execute the new program */
                Download(APP2);
                break;

            case 0x35:/* execute the new program */
                Upload(APP2);
                break;

            case 0x36:/* execute the new program */
                Jump_to_App(APP2);
                break;

            default:
                break;
        }
    }
}

/**@} end of group IAP_BootLoader_SPI_Functions */
/**@} end of group IAP_BootLoader_SPI */
/**@} end of group Examples */

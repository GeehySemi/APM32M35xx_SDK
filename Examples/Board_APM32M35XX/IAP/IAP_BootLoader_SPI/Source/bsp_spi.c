/*!
 * @file        bsp_usart.c
 *
 * @brief       Usart board support package body
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
#include "bsp_spi.h"
#include <stdio.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_SPI
  @{
  */

/** @defgroup IAP_BootLoader_SPI_Functions Functions
  @{
  */


/*!
 * @brief       SPI Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_Init(void)
{
    GPIO_Config_T gpioConfig;
    SPI_Config_T spiConfig;

    /* Enable related clock*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* Config alter function*/
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_5, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_PIN0);

    /* config PIN_6  MISO*/
    gpioConfig.pin =  GPIO_PIN_6 ;
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioConfig);

    /* config PIN_5->SCK , PIN_7->MOSI*/
    gpioConfig.pin = GPIO_PIN_5 | GPIO_PIN_7;
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.pupd = GPIO_PUPD_PU;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioConfig);

    /* config PIN_4->NSS*/
    gpioConfig.pin = GPIO_PIN_4;
    gpioConfig.mode = GPIO_MODE_IN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioConfig);

    /* SPI RESET*/
    SPI_Reset();
    SPI_ConfigStructInit(&spiConfig);

    /* SPI configuration*/
    /* Set Clock polarity is Low, but Slave is High*/
    spiConfig.polarity = SPI_CLKPOL_LOW;
    /* select master mode*/
    spiConfig.mode = SPI_MODE_SLAVE;
    /* SPI Clock Phase is 1EDGE, but Slave is 1EDGE*/
    spiConfig.phase = SPI_CLKPHA_1EDGE;
    /* Enable Software slave control */
    spiConfig.slaveSelect = SPI_SSC_ENABLE;
    /* Set SPI BaudRate divider*/
    spiConfig.baudrateDiv = SPI_BAUDRATE_DIV_256;
    /* SPI data length*/
    spiConfig.length = SPI_DATA_LENGTH_8B;
    spiConfig.firstBit = SPI_FIRST_BIT_LSB;
    SPI_Config(&spiConfig);

    /* Set internal slave*/
    SPI_DisableInternalSlave();

    SPI_ConfigFIFOThreshold(SPI_RXFIFO_QUARTER);
    SPI_Enable();
}


/**@} end of group IAP_BootLoader_SPI_Functions */
/**@} end of group IAP_BootLoader_SPI */
/**@} end of group Examples */

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
#include "bsp_i2c.h"
#include <stdio.h>
#include <string.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_I2C
  @{
  */

/** @defgroup IAP_BootLoader_I2C_Macros Macros
  @{
  */

#define I2CT_FLAG_TIMEOUT           ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT           ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/**@} end of group IAP_BootLoader_I2C_Macros */

/** @defgroup IAP_BootLoader_I2C_Variables Variables
  @{
  */

static volatile uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

/**@} end of group IAP_BootLoader_I2C_Variables */


/** @defgroup IAP_BootLoader_I2C_Functions Functions
  @{
  */

/*!
 * @brief       I2C Init
 *
 * @param       baudRate
 *
 * @retval      None
 *
 * @note
 */
void I2C_Init(void)
{
    GPIO_Config_T gpioConfigStruct;
    I2C_Config_T i2cConfigStruct;
    /* Enable I2C related Clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_I2C);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* Free I2C_SCL and I2C_SDA */
    gpioConfigStruct.mode = GPIO_MODE_OUT;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;
    gpioConfigStruct.outtype = GPIO_OUT_TYPE_PP;
    gpioConfigStruct.pupd = GPIO_PUPD_NO;
    gpioConfigStruct.pin = GPIO_PIN_8;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    gpioConfigStruct.pin = GPIO_PIN_9;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    GPIO_SetBit(GPIOB, GPIO_PIN_8);
    GPIO_SetBit(GPIOB, GPIO_PIN_9);

    /* Connect I2C to SCL */
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_8, GPIO_AF_PIN1);
    /* Connect I2C to SDA */
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_9, GPIO_AF_PIN1);
    /*  Config I2C GPIO */
    gpioConfigStruct.mode = GPIO_MODE_AF;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;
    gpioConfigStruct.outtype = GPIO_OUT_TYPE_OD;
    gpioConfigStruct.pupd = GPIO_PUPD_NO;
    gpioConfigStruct.pin = GPIO_PIN_8;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    gpioConfigStruct.pin = GPIO_PIN_9;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    /*  Config I2C */
    I2C_Reset();
    RCM_ConfigI2CCLK(RCM_I2CCLK_SYSCLK);
    i2cConfigStruct.ack = I2C_ACK_ENABLE;
    i2cConfigStruct.ackaddress = I2C_ACK_ADDRESS_7BIT;
    i2cConfigStruct.address1 = 0xA0;
    i2cConfigStruct.analogfilter = I2C_ANALOG_FILTER_ENABLE;
    i2cConfigStruct.digitalfilter = I2C_DIGITAL_FILTER_0;
    i2cConfigStruct.mode = I2C_MODE_I2C;
    i2cConfigStruct.timing = 0xB0420F13;
    I2C_Config(&i2cConfigStruct);

    /* Enable the I2C Interrupt */
    I2C_EnableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);

    /* slave configuration*/
    I2C_EnableSlaveByteControl();
    I2C_EnableReload();
    I2C_EnableStretchClock();

    /* Enable I2C */
    I2C_Enable();
}

uint32_t I2C_Write(uint8_t* dat)
{
    I2CTimeout = I2CT_LONG_TIMEOUT;

    /* Wait until I2C is idle */
    while (I2C_ReadStatusFlag(I2C_FLAG_BUSY) == SET)
    {
        I2C_Init();
        if ((I2CTimeout--) == 0)
        {
            return 1;
        }
    }
    /* Disable I2C interrupt  */
    I2C_DisableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);
    I2C_DisableReload();
    /* I2C Send Configuration*/
    I2C_HandlingTransfer(0xB0, strlen((char*)dat), I2C_RELOAD_MODE_AUTOEND, I2C_GENERATE_START_WRITE);

    /* I2C Send Data */
    while (*dat)
    {
        I2C_TxData(*dat++);

        I2CTimeout = I2CT_LONG_TIMEOUT;

        while (I2C_ReadStatusFlag(I2C_FLAG_TXBE) == RESET)
        {
            if ((I2CTimeout--) == 0)
            {
                return 2;
            }
        }
    }

    /* I2C Generate Stop signal */
    I2C_EnableGenerateStop();

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_ReadStatusFlag(I2C_FLAG_STOP) == RESET)
    {
        if ((I2CTimeout--) == 0)
        {
            return 3;
        }
    }

    /* I2C Clear Stop Flag */
    I2C_ClearIntFlag(I2C_INT_FLAG_STOP);
    /* I2C Config Number of Bytes to send or to write */
    I2C_EnableReload();
    I2C_ConfigNumberOfBytes(1);
    /* I2C Enable Interrupt */
    I2C_EnableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);

    return 0;
}


uint32_t I2C_WriteBuf(uint8_t* dat, uint16_t length)
{
    I2CTimeout = I2CT_LONG_TIMEOUT;

    /* Wait until I2C is idle */
    while (I2C_ReadStatusFlag(I2C_FLAG_BUSY) == SET)
    {
        I2C_Init();
        if ((I2CTimeout--) == 0)
        {
            return 1;
        }
    }
    /* Disable I2C interrupt  */
    I2C_DisableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);
    I2C_DisableReload();
    /* I2C Send Configuration*/
    I2C_HandlingTransfer(0xB0, length, I2C_RELOAD_MODE_AUTOEND, I2C_GENERATE_START_WRITE);

    /* I2C Send Data */
    while (length--)
    {
        I2C_TxData(*dat++);

        I2CTimeout = I2CT_LONG_TIMEOUT;

        while (I2C_ReadStatusFlag(I2C_FLAG_TXBE) == RESET)
        {
            if ((I2CTimeout--) == 0)
            {
                return 2;
            }
        }
    }

    /* I2C Generate Stop signal */
    I2C_EnableGenerateStop();

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_ReadStatusFlag(I2C_FLAG_STOP) == RESET)
    {
        if ((I2CTimeout--) == 0)
        {
            return 3;
        }
    }

    /* I2C Clear Stop Flag */
    I2C_ClearIntFlag(I2C_INT_FLAG_STOP);
    /* I2C Config Number of Bytes to send or to write */
    I2C_EnableReload();
    I2C_ConfigNumberOfBytes(1);
    /* I2C Enable Interrupt */
    I2C_EnableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);

    return 0;
}


uint32_t I2C_Read(uint8_t* dat, uint16_t num)
{
    I2CTimeout = I2CT_LONG_TIMEOUT;

    /* Wait until I2C is idle */
    while (I2C_ReadStatusFlag(I2C_FLAG_BUSY) == SET)
    {
        I2C_Init();
        if ((I2CTimeout--) == 0)
        {
            return 1;
        }
    }
    /* Disable I2C interrupt  */
    I2C_DisableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);
    I2C_DisableReload();
    /* I2C Send Configuration*/
    I2C_HandlingTransfer(0xB0, num, I2C_RELOAD_MODE_AUTOEND, I2C_GENERATE_START_READ);

    /* I2C Send Data */
    while (num--)
    {
        I2CTimeout = I2CT_LONG_TIMEOUT;

        while (I2C_ReadStatusFlag(I2C_FLAG_RXBNE) == RESET)
        {
            if ((I2CTimeout--) == 0)
            {
                return 2;
            }
        }

        *dat++ = I2C_RxData();
    }

    /* I2C Generate Stop signal */
    I2C_EnableGenerateStop();

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_ReadStatusFlag(I2C_FLAG_STOP) == RESET)
    {
        if ((I2CTimeout--) == 0)
        {
            return 3;
        }

    }

    /* I2C Clear Stop Flag */
    I2C_ClearIntFlag(I2C_INT_FLAG_STOP);
    /* I2C Config Number of Bytes to send or to write */
    I2C_EnableReload();
    I2C_ConfigNumberOfBytes(1);
    /* I2C Enable Interrupt */
    I2C_EnableInterrupt(I2C_INT_RXIE | I2C_INT_ADDRIE | I2C_INT_STOPIE);

    return 0;
}
/**@} end of group IAP_BootLoader_I2C_Functions */
/**@} end of group IAP_BootLoader_I2C */
/**@} end of group Examples */

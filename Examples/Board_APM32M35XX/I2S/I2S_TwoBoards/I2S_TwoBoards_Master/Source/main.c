/*!
 * @file        main.c
 *
 * @brief       Main program body
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
#include "main.h"
#include "bsp_delay.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_gpio.h"
#include "apm32m35xx_misc.h"
#include "apm32m35xx_spi.h"
#include "apm32m35xx_eint.h"
#include <stdio.h>
#include <string.h>

/** @addtogroup Examples
  * @brief I2S two boards master examples
  @{
  */

/** @addtogroup I2S_TwoBoards_Master
  @{
  */

/** @defgroup I2S_TwoBoards_Master_Macros Macros
  @{
*/

/* printf using USART1 */
#define DEBUG_USART                 USART1

/* Buffsize */
#define BuffSize                    32
/**@} end of group I2S_TwoBoards_Master_Macros*/

/** @defgroup I2S_TwoBoards_Master_Variables Variables
  @{
  */

/* KeyState */
uint8_t KeyState = RESET;

/* index of TxData */
volatile uint8_t TxIdx = 0;

/* I2S TX Buffer */
uint16_t I2S_Buffer_TX[BuffSize] =
{
    0x0102, 0x0304, 0x0506, 0x0707,
    0x1112, 0x1314, 0x1516, 0x1717,
    0x2122, 0x2324, 0x2526, 0x2727,
    0x3132, 0x3334, 0x3536, 0x3737,
    0x4142, 0x4344, 0x4546, 0x4747,
    0x5152, 0x5354, 0x5556, 0x5757,
    0x6162, 0x6364, 0x6566, 0x6767,
    0x7172, 0x7374, 0x7576, 0x7777,
};

/**@} end of group I2S_TwoBoards_Master_Variables*/

/** @defgroup I2S_TwoBoards_Master_Functions Functions
  @{
  */

void APM_MINI_Init(void);
/* I2S Master Init */
void I2S_Master_Init(void);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    APM_MINI_Init();

    I2S_Master_Init();

    printf("This is an example of I2S two boards master \r\n");

    printf("Press the KEY1,master will send data to");
    printf("slave along with information that showed in serial port\r\n");

    while (1)
    {
        if (APM_MINI_PBGetState(BUTTON_KEY1) == 0)
        {
            printf("I2S Master Transmitter Buffer:\r\n");

            while (TxIdx < BuffSize)
            {
                while (SPI_ReadStatusFlag(SPI_FLAG_TXBE) == RESET);

                printf("0x%04X,", I2S_Buffer_TX[TxIdx]);
                SPI_I2S_TxData16(I2S_Buffer_TX[TxIdx++]);

                if (TxIdx % 8 == 0)
                {
                    printf("\r\n");
                }
            }
            printf("\r\n");
            TxIdx = 0;

            while (APM_MINI_PBGetState(BUTTON_KEY1) == 0);
        }

        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(500);
    }
}

/*!
 * @brief       Init MINI board
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_Init(void)
{
    /* Init delay function */
    APM_DelayInit();
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    APM_MINI_COMInit(COM1);
}

/*!
 * @brief       I2S Master Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void I2S_Master_Init(void)
{
    GPIO_Config_T gpioConfig;
    I2S_Config_T i2sConfig;

    /* Enable related clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* config PIN_4->WS, PIN_5->CK, PIN_7->SD */
    gpioConfig.pin =  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_NO;
    GPIO_Config(GPIOA, &gpioConfig);

    /* Config alter function */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_4, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_5, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_PIN0);

    /* I2S configuration */
    i2sConfig.mode       =  I2S_MODE_MASTER_TX;
    i2sConfig.standard   =  I2S_STANDARD_PHILIPS;
    i2sConfig.length     =  I2S_DATA_LENGTH_16B;
    i2sConfig.MCLKOutput =  I2S_MCLK_OUTPUT_DISABLE;
    i2sConfig.audioDiv   =  I2S_AUDIO_DIV_8K;
    i2sConfig.polarity   =  I2S_CLKPOL_LOW;

    SPI_Reset();
    I2S_Config(&i2sConfig);
    I2S_Enable();
}

#if defined (__CC_ARM) || defined (__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @param       *f:  pointer to a FILE that can recording all information
*              needed to control a stream
*
* @retval      The characters that need to be send.
*
* @note
*/
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

#elif defined (__GNUC__)

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @retval      The characters that need to be send.
*
* @note
*/
int __io_putchar(int ch)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return ch;
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       file:  Meaningless in this function.
*
* @param       *ptr:  Buffer pointer for data to be sent.
*
* @param       len:  Length of data to be sent.
*
* @retval      The characters that need to be send.
*
* @note
*/
int _write(int file, char* ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

#else
#warning Not supported compiler type
#endif

/**@} end of group I2S_TwoBoards_Master_Functions */
/**@} end of group I2S_TwoBoards_Master */
/**@} end of group Examples */

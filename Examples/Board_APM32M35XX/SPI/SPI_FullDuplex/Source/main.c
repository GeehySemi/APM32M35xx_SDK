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

/** @addtogroup Examples
  * @brief SPI_FullDuplex examples
  @{
  */

/** @addtogroup SPI_FullDuplex
  @{
  */

/** @defgroup SPI_FullDuplex_Macros Macros
  @{
*/
/** printf function configs to USART1*/
#define DEBUG_USART         USART1

/** Buffer Size*/
#define DATA_BUF_SIZE       (30)

/**@} end of group SPI_FullDuplex_Macros*/

/** @defgroup SPI_FullDuplex_Functions Functions
  @{
  */

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
int main(void)
{
    /* Buffer Compare state */
    BOOL state = FALSE;
    /* SPI receive Buf*/
    uint8_t rxDataBufSPI[DATA_BUF_SIZE]   = {0x00};
    /* USART receive Buf*/
    uint8_t rxDataBufUSART[DATA_BUF_SIZE] = {0x00};

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM1);
    APM_DelayInit();

    SPI_FullDuplex_Init();
    USART_FullDuplex_Init();

    for (int i = 0; i < DATA_BUF_SIZE; i++)
    {
        /* SPI send data*/
        SPI_WriteByte(i);

        /* Tx send data*/
        USART_TxData(USART2, i);

        /* Wait data is received by SPI */
        while (SPI_ReadStatusFlag(SPI_FLAG_RXBNE) == RESET) ;

        rxDataBufSPI[i] = SPI_I2S_RxData16();

        /* Wait data is received by UART1 */
        while (USART_ReadStatusFlag(USART2, USART_FLAG_RXBNE) == RESET);

        rxDataBufUSART[i] = USART_RxData(USART2);

    }

    /* Compare receive Buffer*/
    state = BufferCompare(rxDataBufUSART, rxDataBufSPI, DATA_BUF_SIZE);

    /* Data is ok then turn on LED2 */
    if (state == TRUE)
    {
        APM_MINI_LEDOn(LED2);
        printf("Data is ok, LED2 On \r\n");
    }
    else
    {
        APM_MINI_LEDOff(LED2);
        printf("Data is error, LED2 Off \r\n");
    }

    while (1)
    {
        APM_MINI_LEDToggle(LED3);
        APM_DelayMs(200);
    }
}

/*!
 * @brief       SPI Write uint8_t data
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_WriteByte(uint8_t dat)
{
    while (SPI_ReadStatusFlag(SPI_FLAG_TXBE) == RESET);
    SPI_TxData8(dat);
}

/*!
 * @brief       SPI Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SPI_FullDuplex_Init()
{
    GPIO_Config_T gpioConfig;
    SPI_Config_T spiConfig;

    /* Enable related Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

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

    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_5, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_PIN0);

    SPI_ConfigStructInit(&spiConfig);

    spiConfig.length = SPI_DATA_LENGTH_8B;

    spiConfig.baudrateDiv = SPI_BAUDRATE_DIV_32;
    /*  2 line full duplex  */
    spiConfig.direction = SPI_DIRECTION_2LINES_FULLDUPLEX;
    /*  LSB first  */
    spiConfig.firstBit = SPI_FIRST_BIT_LSB;
    /*  Slave mode  */
    spiConfig.mode = SPI_MODE_SLAVE;
    /*  Polarity is high  */
    spiConfig.polarity = SPI_CLKPOL_HIGH;
    /*  Software select slave enable  */
    spiConfig.slaveSelect = SPI_SSC_ENABLE;
    /*  Phase is 2 edge  */
    spiConfig.phase = SPI_CLKPHA_2EDGE;
    /*  SPI config  */
    SPI_Config(&spiConfig);

    SPI_ConfigFIFOThreshold(SPI_RXFIFO_QUARTER);

    SPI_Enable();
}

/*!
 * @brief       USART Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void USART_FullDuplex_Init()
{
    GPIO_Config_T gpioConfig;
    USART_Config_T usartConfig;
    USART_SyncClockConfig_T usartSyncClockConfig;

    /* Enable GPIO clock */
    RCM_EnableAHBPeriphClock(MINI_COM2_TX_GPIO_CLK);

    /* Enable COM2 clock */
    RCM_EnableAPB1PeriphClock(MINI_COM2_CLK);

    /* Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(MINI_COM2_TX_GPIO_PORT, MINI_COM2_TX_SOURCE, MINI_COM2_TX_AF);
    /* Connect PXx to USARTx_Rx */
    GPIO_ConfigPinAF(MINI_COM2_RX_GPIO_PORT, MINI_COM2_RX_SOURCE, MINI_COM2_RX_AF);
    /* Connect PXx to USARTx_Clk */
    GPIO_ConfigPinAF(MINI_COM2_TX_GPIO_PORT, GPIO_PIN_SOURCE_4, GPIO_AF_PIN1);

    /* Configure USART Tx as alternate function push-pull */
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.pin = MINI_COM2_TX_PIN;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(MINI_COM2_TX_GPIO_PORT, &gpioConfig);

    /* Configure USART Rx as input floating */
    gpioConfig.pin  = MINI_COM2_RX_PIN;
    GPIO_Config(MINI_COM2_RX_GPIO_PORT, &gpioConfig);

    /* Configure USART CLK  */
    gpioConfig.pin  = GPIO_PIN_4;
    GPIO_Config(GPIOA, &gpioConfig);

    /* Enable USART Clock  */
    usartSyncClockConfig.enable = USART_CLKEN_ENABLE;
    /* Enable last bit clock  */
    usartSyncClockConfig.lastBitClock = USART_LBCP_ENABLE;
    /* Clock phase is 1 edge */
    usartSyncClockConfig.phase = USART_CLKPHA_1EDGE;
    /* Clock polarity is Low */
    usartSyncClockConfig.polarity = USART_CLKPOL_LOW;
    /* Synchronous communication clock configuration */
    USART_ConfigSyncClock(USART2, &usartSyncClockConfig);

    /* BaudRate is 115200 */
    usartConfig.baudRate = 115200;
    /* Enable RX and TX */
    usartConfig.mode = USART_MODE_TX_RX;
    /* Parity disable */
    usartConfig.parity = USART_PARITY_NONE;
    /* One stop bit */
    usartConfig.stopBits = USART_STOP_BIT_1;
    /* Word length is 8bit */
    usartConfig.wordLength = USART_WORD_LEN_8B;

    /* USART2 configuration */
    USART_Config(USART2, &usartConfig);

    /* Enable USART2 */
    USART_Enable(USART2);
}

/*!
 * @brief       Compares two buffers
 *
 * @param       buf1:    First buffer to be compared
 *
 * @param       buf1:    Second buffer to be compared
 *
 * @param       size:    Buffer size
 *
 * @retval      Return TRUE if buf1 = buf2. If not then return FALSE
 *
 * @note
 */
BOOL BufferCompare(uint8_t* buf1, uint8_t* buf2, uint8_t size)
{
    uint8_t i;

    for (i = 0; i < size; i++)
    {
        if (buf1[i] != buf2[i])
        {
            return FALSE;
        }
    }

    return TRUE;
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

/**@} end of group SPI_FullDuplex_Functions */
/**@} end of group SPI_FullDuplex */
/**@} end of group Examples */

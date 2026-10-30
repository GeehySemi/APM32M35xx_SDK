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
#include "apm32m35xx_m0cp.h"
#include "apm32m35xx_rcm.h"
#include "apm32m35xx_tmr.h"
#include <stdio.h>
#include <string.h>

/** @addtogroup Examples
  * @brief M0CP SVPWM counter examples
  @{
  */

/** @addtogroup M0CP_CounterSVPWM
  @{
  */

/** @defgroup M0CP_CounterSVPWM_Macros Macros
  @{
*/

/* printf using USART1 */
#define DEBUG_USART             USART1
#define PWM_Period              1000
#define sqrt2                   707     /*!< (sqrt(2) / 2) * 1000 */

/**@} end of group M0CP_CounterSVPWM_Macros*/

/** @defgroup M0CP_CounterSVPWM_Functions Functions
  @{
  */

void APM_MINI_Init(void);
void M0CP_Init(void);
void TMR_M0CP_Init(void);
void APM_MINI_TMR1_PWMOutPut_Init(void);

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
    uint8_t model = 1;
    uint8_t i;
    int16_t seq_X[] = {sqrt2, -sqrt2, sqrt2, -sqrt2}; /*!< sin(45°), sin(135°), sin(-45°), sin(-135°) */
    int16_t seq_Y[] = {sqrt2, sqrt2, -sqrt2, -sqrt2}; /*!< cos(45°), cos(135°), cos(-45°), cos(-135°) */

    SVPWM_DATA_T svpwmInfo;

    APM_MINI_Init();

    APM_MINI_TMR1_PWMOutPut_Init();

    M0CP_Init();

    printf("This is an example of M0CP SVPWM output duty operation \r\n");

    printf("Press KEY1 to start test.\r\n");

    while (1)
    {
        if (APM_MINI_PBGetState(BUTTON_KEY1) == 0)
        {
            for (i = 0; i < 4; i++)
            {
                svpwmInfo.Ualpha = (model * seq_X[i]);
                svpwmInfo.Ubeta = (model * seq_Y[i]);
#if M0CP_USE_FAST_IQ
                /* SVPWM counter segmentation 7 and Q15 algorithm */
                M0CP_Fast_IQCounterQ15SVPWM7(&svpwmInfo);

                printf(">> SVPWM(%d,%d), Seg = 7, Qn = 15\r\n", svpwmInfo.Ualpha, svpwmInfo.Ubeta);
                printf("<< Ca = %d%%, Cb = %d%%, Cc = %d%%, sector = %d\r\n"
                       , (svpwmInfo.Ca * 100 / PWM_Period)
                       , (svpwmInfo.Cb * 100 / PWM_Period)
                       , (svpwmInfo.Cc * 100 / PWM_Period)
                       , svpwmInfo.sector);
#else
                /* SVPWM counter segmentation 7 and Q15 algorithm */
                if (M0CP_IQCounterSVPWM(&svpwmInfo, M0CP_FP_Q15, M0CP_SVPWM_SEG_7) != M0CP_OK)
                {
                    printf("M0CP SVPWM 7 Q15 segmentation timeout\r\n");
                }
                else
                {
                    printf(">> SVPWM(%d,%d), Seg = 7, Qn = 15\r\n", svpwmInfo.Ualpha, svpwmInfo.Ubeta);
                    printf("<< Ca = %d%%, Cb = %d%%, Cc = %d%%, sector = %d\r\n"
                           , (svpwmInfo.Ca * 100 / PWM_Period)
                           , (svpwmInfo.Cb * 100 / PWM_Period)
                           , (svpwmInfo.Cc * 100 / PWM_Period)
                           , svpwmInfo.sector);
                }
#endif
            }
            model++;
        }

        APM_MINI_LEDToggle(LED2);
        APM_DelayMs(200);
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
 * @brief       M0CP initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void M0CP_Init(void)
{
    M0CP_Config_T m0cpConfigStruct;

    /* Load firmware from Flash to SRAM */
    M0CP_Firmware_Init();

    /* Reset M0CP */
    RCM_EnableAHBPeriphReset(RCM_AHB_PERIPH_M0CP);
    RCM_DisableAHBPeriphReset(RCM_AHB_PERIPH_M0CP);

    /* Enable M0CP clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_M0CP);

    /* Init M0CP hardware */
    M0CP_HardInit();

    M0CP_ClearStatusFlag(M0CP_FLAG_DONE);
    /* Disable M0CP TX interrupt */
    M0CP_DisableInterrupt(M0CP_INT_TX);

    /* Wait for M0CP to be ready */
    while (M0CP_ReadStatusFlag(M0CP_FLAG_BUSY) == SET)
    {

    }

    M0CP_ConfigStructInit(&m0cpConfigStruct);

    /* Configure M0CP */
    m0cpConfigStruct.algebraMode        = M0CP_ALG_SVPWM;
    m0cpConfigStruct.bankAutoConv       = M0CP_BANK_CONV_SOFTWARE;
    m0cpConfigStruct.bankRegGroup       = M0CP_BANK_REG_GROUP_0;
    m0cpConfigStruct.fixedPoint         = M0CP_FP_Q15;
    m0cpConfigStruct.outputSVPWM        = M0CP_SVPWM_OUT_CNT;
    m0cpConfigStruct.segSVPWM           = M0CP_SVPWM_SEG_7;
    M0CP_Config(&m0cpConfigStruct);
}

/*!
 * @brief       TMR M0CP initialization
 *
 * @param       None
 *
 * @retval      None
 *
 */
void TMR_M0CP_Init(void)
{
    TMR_SelectM0CPBuffMode(TMR1, TMR_M0CP_BUFFER_NEXT); /*!< M0CP update to CCx will be in next update event */
    TMR_SelectM0CPPWMCycleMode(TMR1, TMR_M0CP_CYCLE_AUTORLD); /*!< The PWM period takes the value of AUTORLD */
    TMR_SelectM0CPPDCONMode(TMR1, TMR_M0CP_PDCON_RESET);
    TMR_SelectM0CPUpdateMode(TMR1, TMR_M0CP_UPDATE_SET);

    TMR_ChannelxDataSelect(TMR1, TMR_CHANNEL_1, TMR_CHANNEL_DATA_32_47); /*!< X_REG -> TMR1_CC1 */
    TMR_ChannelxDataSelect(TMR1, TMR_CHANNEL_2, TMR_CHANNEL_DATA_16_31); /*!< Y_REG -> TMR1_CC2 */
    TMR_ChannelxDataSelect(TMR1, TMR_CHANNEL_3, TMR_CHANNEL_DATA_0_15);  /*!< Z_REG -> TMR1_CC3 */
}

/*!
 * @brief       TMR1 PWM Output Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR1_PWMOutPut_Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_OCConfig_T  occonfig;
    GPIO_Config_T   gpioconfig;

    /* Enable Clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);

    /* Connect TMR1 to CH1 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_PIN2);
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_8;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioconfig);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision = TMR_CKD_DIV1;
    /* Up-counter */
    timeBaseConfig.counterMode = TMR_COUNTER_MODE_UP;
    /* Set divider = 47 .So TMR1 clock freq ~= 48/(47+1) = 1MHZ */
    timeBaseConfig.div = SystemCoreClock / 1000000 - 1;
    /* Set counter = 1000 */
    timeBaseConfig.period = 1000;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;
    TMR_ConfigTimeBase(TMR1, &timeBaseConfig);

    /* PWM1 mode */
    occonfig.OC_Mode = TMR_OC_MODE_PWM1;
    /* Idle State is reset */
    occonfig.OC_Idlestate = TMR_OCIDLESTATE_RESET;
    /* NIdle State is reset */
    occonfig.OC_NIdlestate = TMR_OCNIDLESTATE_RESET;
    /* Enable CH1N ouput */
    occonfig.OC_OutputNState = TMR_OUTPUT_NSTATE_DISABLE;
    /* Enable CH1 ouput */
    occonfig.OC_OutputState = TMR_OUTPUT_STATE_ENABLE;
    /* CH1  polarity is high */
    occonfig.OC_Polarity = TMR_OC_POLARITY_HIGH;
    /* CH1N polarity is high */
    occonfig.OC_NPolarity = TMR_OC_NPOLARITY_HIGH;
    /* Set compare value */
    occonfig.Pulse = 500;
    TMR_OC1Config(TMR1, &occonfig);

    /* Enable PWM output */
    TMR_EnablePWMOutputs(TMR1);

    /* Config TMR1 M0CP */
    TMR_M0CP_Init();

    /* Enable TMR1  */
    TMR_Enable(TMR1);
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

/**@} end of group M0CP_CounterSVPWM_Functions */
/**@} end of group M0CP_CounterSVPWM */
/**@} end of group Examples */

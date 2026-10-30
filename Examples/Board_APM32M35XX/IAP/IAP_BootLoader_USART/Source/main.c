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
#include <stdio.h>

uint32_t JumpAddress;
pFunction Jump_To_Application;

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader_USART
  @{
  */

/** @defgroup IAP_BootLoader_USART_Functions Functions
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
    SCB->VTOR = VECT_TAB_OFFSET;

    /* Initialize LED */
    Led_Init();

    /* Initialize UART mounted */
    USART_Init(DEBUG_USART_BAUDRATE);

    /* Configure the Flash to re-program the Flash */
    FLASH_IAP_Init();

    /* Display Select menu */
    Select_Menu();

    /* Jump to user application 1 */
    SendString(">> Jump to user application 1\r\n");
    Jump_to_App(APP1);

    /* Infinite loop */
    while (1)
    {

    }
}

/*!
 * @brief       Delay
 *
 * @param       count:  delay count
 *
 * @retval      None
 *
 * @note
 */
void Delay(uint32_t count)
{
    volatile uint32_t delay = count;

    while (delay--);
}

/*!
 * @brief       Led Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void Led_Init(void)
{
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);

    APM_MINI_LEDOn(LED2);
    APM_MINI_LEDOn(LED3);
}

/*!
 * @brief       Jump to user application
 *
 * @param       Application : APP1 or APP2
 *
 * @retval      None
 *
 * @note
 */
void Jump_to_App(uint8_t Application)
{
    uint32_t address;

    /* Lock the Program memory */
    FMC_Lock();

    /* Reset RCM */
    /* Set HSIEN bit */
    RCM->CTRL1_B.HSIEN = BIT_SET;
    /* Reset SCLKSEL, AHBPSC, APB1PSC, APB2PSC, ADCPSC and COC bits */
    RCM->CFG1 &= (uint32_t)0x08FFB80CU;
    /* Reset HSEEN, CSSEN and PLLEN bits */
    RCM->CTRL1 &= (uint32_t)0xFEF6FFFFU;
    /* Reset HSEBCFG bit */
    RCM->CTRL1_B.HSEBCFG = BIT_RESET;
    /* Reset PLLSRCSEL, PLLHSEPSC, PLLMULCFG bits */
    RCM->CFG1 &= (uint32_t)0xFFC0FFFFU;
    /* Reset PREDIV[3:0] bits */
    RCM->CFG1 &= (uint32_t)0xFFFFFFF0U;
    /* Reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits */
    RCM->CFG3 &= (uint32_t)0xFFFFFEAC;
    /* Reset  HSI14 bit */
    RCM->CTRL2_B.HSI14EN = BIT_RESET;
    /* Disable all interrupts */
    RCM->INT = 0x00000000U;

    /* Disable aLL peripheral clock  */
    RCM->AHBRST  = 0xFFFFFFFFU;
    RCM->APBRST1 = 0xFFFFFFFFU;
    RCM->APBRST2 = 0xFFFFFFFFU;

    RCM->AHBRST  = 0x00000000U;
    RCM->APBRST1 = 0x00000000U;
    RCM->APBRST2 = 0x00000000U;

    RCM->AHBCLKEN = 0x00000000U;
    RCM->APBCLKEN1 = 0x00000000U;
    RCM->APBCLKEN2 = 0x00000000U;

    if (Application == APP1)
    {
        address = USER_APP1_ADDRESS;
    }
    else
    {
        address = USER_APP2_ADDRESS;
    }

    /* Jump to user application */
    JumpAddress = *(__IO uint32_t*)(address + 4);
    Jump_To_Application = (pFunction) JumpAddress;

    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) address);

    /* Jump to application */
    Jump_To_Application();
}

/**@} end of group IAP_BootLoader_USART_Functions */
/**@} end of group IAP_BootLoader_USART */
/**@} end of group Examples */

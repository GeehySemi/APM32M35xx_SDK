;/*!
; * @file       startup_apm32m35xx.s
; *
; * @brief      APM32M35XX devices vector table for EWARM toolchain.
; *
; * @version    V1.0.0
; *
; * @date       2024-05-30
; *
; * @attention
; *
; *  Copyright (C) 2024 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be useful and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */

        MODULE  ?cstartup

        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                   ; Reset Handler

        DCD     NMI_Handler                     ; NMI Handler
        DCD     HardFault_Handler               ; Hard Fault Handler
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     SVC_Handler                     ; SVCall Handler
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     PendSV_Handler                  ; PendSV Handler
        DCD     SysTick_Handler                 ; SysTick Handler

        ; External Interrupts
        DCD     WWDT_IRQHandler                 ; Window Watchdog
        DCD     PVD_IRQHandler                  ; PVD through EINT Line detect
        DCD     RTC_IRQHandler                  ; RTC through EINT Line
        DCD     FLASH_IRQHandler                ; FLASH
        DCD     RCM_IRQHandler                  ; RCM
        DCD     EINT0_1_IRQHandler              ; EINT Line 0 and 1
        DCD     EINT2_3_IRQHandler              ; EINT Line 2 and 3
        DCD     EINT4_15_IRQHandler             ; EINT Line 4 to 15
        DCD     M0CP_IRQHandler                 ; M0CP
        DCD     DMA_CH1_IRQHandler              ; DMA Channel 1
        DCD     DMA_CH2_3_IRQHandler            ; DMA Channel 2 and 3
        DCD     DMA_CH4_7_IRQHandler            ; DMA Channel 4 to 7
        DCD     ADC_COMP_IRQHandler             ; ADC, COMP1 and COMP2
        DCD     TMR1_BRK_UP_TRG_COM_IRQHandler  ; TMR1 Break, Update, Trigger and Commutation
        DCD     TMR1_CC_IRQHandler              ; TMR1 Capture Compare
        DCD     TMR2_IRQHandler                 ; TMR2
        DCD     TMR3_IRQHandler                 ; TMR3
        DCD     TMR6_IRQHandler                 ; TMR6
        DCD     0                               ; Reserved
        DCD     TMR4_IRQHandler                 ; TMR4
        DCD     TMR7_IRQHandler                 ; TMR7
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     I2C_IRQHandler                  ; I2C
        DCD     0                               ; Reserved
        DCD     SPI_IRQHandler                  ; SPI
        DCD     0                               ; Reserved
        DCD     USART1_IRQHandler               ; USART1
        DCD     USART2_IRQHandler               ; USART2
        DCD     0                               ; Reserved
        DCD     CAN_IRQHandler                  ; CAN

        DCD     0x010001b7                      ; @000000
        DCD     0x00008437                      ; @000001
        DCD     0xfff40413                      ; @000002
        DCD     0x00400073                      ; @000003
        DCD     0x0000185b                      ; @000040
        DCD     0x0000205b                      ; @000041
        DCD     0x0000285b                      ; @000042
        DCD     0x80005c5b                      ; @000043
        DCD     0x8000645b                      ; @000044
        DCD     0x80006c5b                      ; @000045
        DCD     0x0000405b                      ; @000046
        DCD     0x0000485b                      ; @000047
        DCD     0x0000505b                      ; @000048
        DCD     0x00400073                      ; @000049
        DCD     0x0000105b                      ; @000080
        DCD     0x9000005b                      ; @000081
        DCD     0x897200db                      ; @000082
        DCD     0x84fd815b                      ; @000083
        DCD     0x828881db                      ; @000084
        DCD     0x8145825b                      ; @000085
        DCD     0x80a302db                      ; @000086
        DCD     0x8051835b                      ; @000087
        DCD     0x802883db                      ; @000088
        DCD     0x8014845b                      ; @000089
        DCD     0x800a04db                      ; @00008a
        DCD     0x8005055b                      ; @00008b
        DCD     0x800285db                      ; @00008c
        DCD     0x8001865b                      ; @00008d
        DCD     0x800086db                      ; @00008e
        DCD     0x8000875b                      ; @00008f
        DCD     0x8000585b                      ; @000090
        DCD     0x8000605b                      ; @000091
        DCD     0x0000405b                      ; @000092
        DCD     0x0000485b                      ; @000093
        DCD     0x00400073                      ; @000094
        DCD     0x04050763                      ; @0000c0
        DCD     0x04060263                      ; @0000c1
        DCD     0x9000085b                      ; @0000c2
        DCD     0x897208db                      ; @0000c3
        DCD     0x84fd895b                      ; @0000c4
        DCD     0x828889db                      ; @0000c5
        DCD     0x81458a5b                      ; @0000c6
        DCD     0x80a30adb                      ; @0000c7
        DCD     0x80518b5b                      ; @0000c8
        DCD     0x80288bdb                      ; @0000c9
        DCD     0x80148c5b                      ; @0000ca
        DCD     0x800a0cdb                      ; @0000cb
        DCD     0x80050d5b                      ; @0000cc
        DCD     0x80028ddb                      ; @0000cd
        DCD     0x80018e5b                      ; @0000ce
        DCD     0x80008edb                      ; @0000cf
        DCD     0x80008f5b                      ; @0000d0
        DCD     0x00400073                      ; @0000d1
        DCD     0x00014681                      ; @0000d2
        DCD     0x0001a801                      ; @0000d3
        DCD     0x00064463                      ; @0000d4
        DCD     0xa0196691                      ; @0000d5
        DCD     0xffffc6b7                      ; @0000d6
        DCD     0x00010001                      ; @0000d7
        DCD     0x00010001                      ; @0000d8
        DCD     0x00010001                      ; @0000d9
        DCD     0x00010001                      ; @0000da
        DCD     0x00730001                      ; @0000db
        DCD     0x00000040                      ; @0000dc
        DCD     0x0000705b                      ; @000100
        DCD     0x00010001                      ; @000101
        DCD     0x00010001                      ; @000102
        DCD     0x00010001                      ; @000103
        DCD     0x00010001                      ; @000104
        DCD     0x00400073                      ; @000105
        DCD     0x0000305b                      ; @000140
        DCD     0x00010001                      ; @000141
        DCD     0x00010001                      ; @000142
        DCD     0x00010001                      ; @000143
        DCD     0x00400073                      ; @000144
        DCD     0x0000385b                      ; @000180
        DCD     0x00010001                      ; @000181
        DCD     0x00010001                      ; @000182
        DCD     0x00010001                      ; @000183
        DCD     0x00400073                      ; @000184
        DCD     0x08055d63                      ; @0001c0
        DCD     0x0001a073                      ; @0001c1
        DCD     0x04065563                      ; @0001c2
        DCD     0x9000085b                      ; @0001c3
        DCD     0x897208db                      ; @0001c4
        DCD     0x84fd895b                      ; @0001c5
        DCD     0x828889db                      ; @0001c6
        DCD     0x81458a5b                      ; @0001c7
        DCD     0x80a30adb                      ; @0001c8
        DCD     0x80518b5b                      ; @0001c9
        DCD     0x80288bdb                      ; @0001ca
        DCD     0x80148c5b                      ; @0001cb
        DCD     0x800a0cdb                      ; @0001cc
        DCD     0x80050d5b                      ; @0001cd
        DCD     0x80028ddb                      ; @0001ce
        DCD     0x80018e5b                      ; @0001cf
        DCD     0x80008edb                      ; @0001d0
        DCD     0x80008f5b                      ; @0001d1
        DCD     0x10738e81                      ; @0001d2
        DCD     0x00730000                      ; @0001d3
        DCD     0xce510040                      ; @0001d4
        DCD     0x9000085b                      ; @0001d5
        DCD     0x897208db                      ; @0001d6
        DCD     0x84fd895b                      ; @0001d7
        DCD     0x828889db                      ; @0001d8
        DCD     0x81458a5b                      ; @0001d9
        DCD     0x80a30adb                      ; @0001da
        DCD     0x80518b5b                      ; @0001db
        DCD     0x80288bdb                      ; @0001dc
        DCD     0x80148c5b                      ; @0001dd
        DCD     0x800a0cdb                      ; @0001de
        DCD     0x80050d5b                      ; @0001df
        DCD     0x80028ddb                      ; @0001e0
        DCD     0x80018e5b                      ; @0001e1
        DCD     0x80008edb                      ; @0001e2
        DCD     0x80008f5b                      ; @0001e3
        DCD     0x107396a2                      ; @0001e4
        DCD     0x00730000                      ; @0001e5
        DCD     0xce310040                      ; @0001e6
        DCD     0x085bc129                      ; @0001e7
        DCD     0x08db9000                      ; @0001e8
        DCD     0x895b8972                      ; @0001e9
        DCD     0x89db84fd                      ; @0001ea
        DCD     0x8a5b8288                      ; @0001eb
        DCD     0x0adb8145                      ; @0001ec
        DCD     0x8b5b80a3                      ; @0001ed
        DCD     0x8bdb8051                      ; @0001ee
        DCD     0x8c5b8028                      ; @0001ef
        DCD     0x0cdb8014                      ; @0001f0
        DCD     0x0d5b800a                      ; @0001f1
        DCD     0x8ddb8005                      ; @0001f2
        DCD     0x8e5b8002                      ; @0001f3
        DCD     0x8edb8001                      ; @0001f4
        DCD     0x8f5b8000                      ; @0001f5
        DCD     0x00738000                      ; @0001f6
        DCD     0x66910040                      ; @0001f7
        DCD     0x00064463                      ; @0001f8
        DCD     0x40d006b3                      ; @0001f9
        DCD     0x40d006b3                      ; @0001fa
        DCD     0x86a2a031                      ; @0001fb
        DCD     0x00001073                      ; @0001fc
        DCD     0x8e95a011                      ; @0001fd
        DCD     0x00400073                      ; @0001fe

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

        LDR     R0, =sfe(CSTACK)          ; set stack pointer
        MSR     MSP, R0

        LDR R0,=0x00000004
        LDR R1, [R0]
        LSRS R1, R1, #24
        LDR R2,=0x1F
        CMP R1, R2

        BNE ApplicationStart

        LDR R0,=0x40021018
        LDR R1,=0x00000001
        STR R1, [R0]

        LDR R0,=0x40010000
        LDR R1,=0x00000000
        STR R1, [R0]
ApplicationStart
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCM_IRQHandler
        B RCM_IRQHandler

        PUBWEAK EINT0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINT0_1_IRQHandler
        B EINT0_1_IRQHandler

        PUBWEAK EINT2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINT2_3_IRQHandler
        B EINT2_3_IRQHandler

        PUBWEAK EINT4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINT4_15_IRQHandler
        B EINT4_15_IRQHandler

        PUBWEAK M0CP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
M0CP_IRQHandler
        B M0CP_IRQHandler

        PUBWEAK DMA_CH1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_CH1_IRQHandler
        B DMA_CH1_IRQHandler

        PUBWEAK DMA_CH2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_CH2_3_IRQHandler
        B DMA_CH2_3_IRQHandler

        PUBWEAK DMA_CH4_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_CH4_7_IRQHandler
        B DMA_CH4_7_IRQHandler

        PUBWEAK ADC_COMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_COMP_IRQHandler
        B ADC_COMP_IRQHandler

        PUBWEAK TMR1_BRK_UP_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1_BRK_UP_TRG_COM_IRQHandler
        B TMR1_BRK_UP_TRG_COM_IRQHandler

        PUBWEAK TMR1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1_CC_IRQHandler
        B TMR1_CC_IRQHandler

        PUBWEAK TMR2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_IRQHandler
        B TMR2_IRQHandler

        PUBWEAK TMR3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR3_IRQHandler
        B TMR3_IRQHandler

        PUBWEAK TMR6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_IRQHandler
        B TMR6_IRQHandler

        PUBWEAK TMR4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR4_IRQHandler
        B TMR4_IRQHandler

        PUBWEAK TMR7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR7_IRQHandler
        B TMR7_IRQHandler

        PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C_IRQHandler
        B I2C_IRQHandler

        PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI_IRQHandler
        B SPI_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK CAN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_IRQHandler
        B CAN_IRQHandler

        END

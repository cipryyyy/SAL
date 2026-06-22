.syntax unified
.cpu cortex-m4
.thumb

.section .isr_vector, "a"

.global isr_functions
.global Default_Handler

isr_functions:
    @StartUp Informations
    .word _endOfRAM                     @ End of RAM, start of stack
    .word _reset                        @ Reset

    @Internal handler
    .word NMI_Handler                   @ Not Maskable Interrupt
    .word HardFault_Handler             @ Hard Fault
    .word MemManage_Handler             @ Memory management fault
    .word BusFault_Handler              @ Bus Fault
    .word UsageFault_Handler            @ Usage Fault
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word SVC_Handler                   @ SuperVisor Call Handler
    .word DebugMon_Handler              @ Debug Monitor
    .word 0                             @ Reserved
    .word PendSV_Handler                @ Pending Super Visor
    .word SysTick_Handler               @ SysTick interrupt

    @Interrupt Request
    .word WWDG_IRQ                      @ Window Watchdog IRQ
    .word PVD_IRQ                       @ PVD IRQ
    .word TAMP_IRQ                      @ TAMP IRQ
    .word RTC_WK_IRQ                    @ RTC IRQ
    .word FLASH_IRQ                     @ FLASH IRQ
    .word RCC_IRQ                       @ RCC IRQ
    .word EXTI0_IRQ                     @ EXTI Line 0 IRQ
    .word EXTI1_IRQ                     @ EXTI Line 1 IRQ
    .word EXTI2_IRQ                     @ EXTI Line 2 IRQ
    .word EXTI3_IRQ                     @ EXTI Line 3 IRQ
    .word EXTI4_IRQ                     @ EXTI Line 4 IRQ
    .word DMA1Stream0_IRQ               @ DMA1 Stream 0 IRQ
    .word DMA1Stream1_IRQ               @ DMA1 Stream 1 IRQ
    .word DMA1Stream2_IRQ               @ DMA1 Stream 2 IRQ
    .word DMA1Stream3_IRQ               @ DMA1 Stream 3 IRQ
    .word DMA1Stream4_IRQ               @ DMA1 Stream 4 IRQ
    .word DMA1Stream5_IRQ               @ DMA1 Stream 5 IRQ
    .word DMA1Stream6_IRQ               @ DMA1 Stream 6 IRQ
    .word ADC_IRQ                       @ ADC IRQ
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word EXTI9_5_IRQ                   @ EXTI Line 5-9 IRQ
    .word TIM1_BRK_TIM9_IRQ             @ TIM1 Break, TIM9 Global
    .word TIM1_UP_TIM10_IRQ             @ TIM1 Update, TIM10 Global
    .word TIM1_TRG_COM_TIM11_IRQ        @ TIM1 TRGO, TIM11 Global
    .word TIM1_CC_IRQ                   @ TIM1 Capture Compare
    .word TIM2_IRQ                      @ TIM2 Global
    .word TIM3_IRQ                      @ TIM3 Global
    .word TIM4_IRQ                      @ TIM4 Global
    .word I2C1_EV_IRQ                   @ I2C1 Event
    .word I2C1_ER_IRQ                   @ I2C1 Error
    .word I2C2_EV_IRQ                   @ I2C2 Event
    .word I2C2_ER_IRQ                   @ I2C2 Error
    .word SPI1_IRQ                      @ SPI1 Global
    .word SPI3_IRQ                      @ SPI3 Global
    .word USART1_IRQ                    @ USART1 Global
    .word USART2_IRQ                    @ USART2 Global
    .word 0                             @ Reserved
    .word EXTI15_10_IRQ                 @ EXTI Line 10-15 IRQ
    .word EXTI17_RTC_Alarm_IRQ          @ EXTI Line 17 / RTC Alarm IRQ
    .word EXTI18_OTG_FS_IRQ             @ EXTI Line 18 / OTG FS IRQ
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word DMA1Stream7_IRQ               @ DMA1 Stream 7 IRQ
    .word 0                             @ Reserved
    .word SDIO_IRQ                      @ SDIO IRQ
    .word TIM5_IRQ                      @ TIM5 IRQ
    .word SPI3_IRQ                      @ SPI3 IRQ
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word DMA2Stream0_IRQ               @ DMA2 Stream 0 IRQ
    .word DMA2Stream1_IRQ               @ DMA2 Stream 1 IRQ
    .word DMA2Stream2_IRQ               @ DMA2 Stream 2 IRQ
    .word DMA2Stream3_IRQ               @ DMA2 Stream 3 IRQ
    .word DMA2Stream4_IRQ               @ DMA2 Stream 4 IRQ
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word DMA2Stream5_IRQ               @ DMA2 Stream 5 IRQ
    .word DMA2Stream6_IRQ               @ DMA2 Stream 6 IRQ
    .word DMA2Stream7_IRQ               @ DMA2 Stream 7 IRQ
    .word USART6_IRQ                    @ USART6 Global
    .word I2C3_EV_IRQ                   @ I2C3 Event
    .word I2C3_ER_IRQ                   @ I2C3 Error
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word FPU_IRQ                       @ FPU Error
    .word 0                             @ Reserved
    .word 0                             @ Reserved
    .word SPI4_IRQ                      @ SPI4 IRQ
    .word SPI5_IRQ                      @ SPI5 IRQ

.section .text
    .thumb_func
    .global _reset
    _reset:
        ldr r0, =_sdata
        ldr r1, =_edata
        ldr r2, =_sidata
        movs r3, #0
        b LoopCopyDataInit

    CopyDataInit:
        ldr r4, [r2, r3]
        str r4, [r0, r3]
        adds r3, r3, #4

    LoopCopyDataInit:
        adds r4, r0, r3
        cmp r4, r1
        bcc CopyDataInit

        ldr r2, =_sbss
        ldr r4, =_ebss
        movs r3, #0
        b LoopFillZerobss

    FillZerobss:
        str  r3, [r2]
        adds r2, r2, #4

    LoopFillZerobss:
        cmp r2, r4
        bcc FillZerobss
        
        bl main
        b .

    .thumb_func
    __safetyLoop:
        b __safetyLoop

    .weak NMI_Handler
    .thumb_set NMI_Handler, __safetyLoop

    .weak HardFault_Handler
    .thumb_set HardFault_Handler, __safetyLoop

    .weak MemManage_Handler
    .thumb_set MemManage_Handler, __safetyLoop

    .weak BusFault_Handler
    .thumb_set BusFault_Handler, __safetyLoop

    .weak UsageFault_Handler
    .thumb_set UsageFault_Handler, __safetyLoop

    .weak SVC_Handler
    .thumb_set SVC_Handler, __safetyLoop

    .weak DebugMon_Handler
    .thumb_set DebugMon_Handler, __safetyLoop

    .weak PendSV_Handler
    .thumb_set PendSV_Handler, __safetyLoop

    .weak SysTick_Handler
    .thumb_set SysTick_Handler, __safetyLoop

    .weak WWDG_IRQ
    .thumb_set WWDG_IRQ, __safetyLoop

    .weak PVD_IRQ
    .thumb_set PVD_IRQ, __safetyLoop

    .weak TAMP_IRQ
    .thumb_set TAMP_IRQ, __safetyLoop

    .weak RTC_WK_IRQ
    .thumb_set RTC_WK_IRQ, __safetyLoop

    .weak FLASH_IRQ
    .thumb_set FLASH_IRQ, __safetyLoop

    .weak RCC_IRQ
    .thumb_set RCC_IRQ, __safetyLoop

    .weak EXTI0_IRQ
    .thumb_set EXTI0_IRQ, __safetyLoop

    .weak EXTI1_IRQ
    .thumb_set EXTI1_IRQ, __safetyLoop

    .weak EXTI2_IRQ
    .thumb_set EXTI2_IRQ, __safetyLoop

    .weak EXTI3_IRQ
    .thumb_set EXTI3_IRQ, __safetyLoop

    .weak EXTI4_IRQ
    .thumb_set EXTI4_IRQ, __safetyLoop

    .weak DMA1Stream0_IRQ
    .thumb_set DMA1Stream0_IRQ, __safetyLoop

    .weak DMA1Stream1_IRQ
    .thumb_set DMA1Stream1_IRQ, __safetyLoop

    .weak DMA1Stream2_IRQ
    .thumb_set DMA1Stream2_IRQ, __safetyLoop

    .weak DMA1Stream3_IRQ
    .thumb_set DMA1Stream3_IRQ, __safetyLoop

    .weak DMA1Stream4_IRQ
    .thumb_set DMA1Stream4_IRQ, __safetyLoop

    .weak DMA1Stream5_IRQ
    .thumb_set DMA1Stream5_IRQ, __safetyLoop

    .weak DMA1Stream6_IRQ
    .thumb_set DMA1Stream6_IRQ, __safetyLoop

    .weak ADC_IRQ
    .thumb_set ADC_IRQ, __safetyLoop

    .weak EXTI9_5_IRQ
    .thumb_set EXTI9_5_IRQ, __safetyLoop

    .weak TIM1_BRK_TIM9_IRQ
    .thumb_set TIM1_BRK_TIM9_IRQ, __safetyLoop

    .weak TIM1_UP_TIM10_IRQ
    .thumb_set TIM1_UP_TIM10_IRQ, __safetyLoop

    .weak TIM1_TRG_COM_TIM11_IRQ
    .thumb_set TIM1_TRG_COM_TIM11_IRQ, __safetyLoop

    .weak TIM1_CC_IRQ
    .thumb_set TIM1_CC_IRQ, __safetyLoop

    .weak TIM2_IRQ
    .thumb_set TIM2_IRQ, __safetyLoop

    .weak TIM3_IRQ
    .thumb_set TIM3_IRQ, __safetyLoop

    .weak TIM4_IRQ
    .thumb_set TIM4_IRQ, __safetyLoop

    .weak I2C1_EV_IRQ
    .thumb_set I2C1_EV_IRQ, __safetyLoop

    .weak I2C1_ER_IRQ
    .thumb_set I2C1_ER_IRQ, __safetyLoop

    .weak I2C2_EV_IRQ
    .thumb_set I2C2_EV_IRQ, __safetyLoop

    .weak I2C2_ER_IRQ
    .thumb_set I2C2_ER_IRQ, __safetyLoop

    .weak SPI1_IRQ
    .thumb_set SPI1_IRQ, __safetyLoop

    .weak SPI3_IRQ
    .thumb_set SPI3_IRQ, __safetyLoop

    .weak USART1_IRQ
    .thumb_set USART1_IRQ, __safetyLoop

    .weak USART2_IRQ
    .thumb_set USART2_IRQ, __safetyLoop

    .weak EXTI15_10_IRQ
    .thumb_set EXTI15_10_IRQ, __safetyLoop

    .weak EXTI17_RTC_Alarm_IRQ
    .thumb_set EXTI17_RTC_Alarm_IRQ, __safetyLoop

    .weak EXTI18_OTG_FS_IRQ
    .thumb_set EXTI18_OTG_FS_IRQ, __safetyLoop

    .weak DMA1Stream7_IRQ
    .thumb_set DMA1Stream7_IRQ, __safetyLoop

    .weak SDIO_IRQ
    .thumb_set SDIO_IRQ, __safetyLoop

    .weak TIM5_IRQ
    .thumb_set TIM5_IRQ, __safetyLoop

    .weak SPI3_IRQ
    .thumb_set SPI3_IRQ, __safetyLoop

    .weak DMA2Stream0_IRQ
    .thumb_set DMA2Stream0_IRQ, __safetyLoop

    .weak DMA2Stream1_IRQ
    .thumb_set DMA2Stream1_IRQ, __safetyLoop

    .weak DMA2Stream2_IRQ
    .thumb_set DMA2Stream2_IRQ, __safetyLoop

    .weak DMA2Stream3_IRQ
    .thumb_set DMA2Stream3_IRQ, __safetyLoop

    .weak DMA2Stream4_IRQ
    .thumb_set DMA2Stream4_IRQ, __safetyLoop

    .weak DMA2Stream5_IRQ
    .thumb_set DMA2Stream5_IRQ, __safetyLoop

    .weak DMA2Stream6_IRQ
    .thumb_set DMA2Stream6_IRQ, __safetyLoop

    .weak DMA2Stream7_IRQ
    .thumb_set DMA2Stream7_IRQ, __safetyLoop

    .weak USART6_IRQ
    .thumb_set USART6_IRQ, __safetyLoop

    .weak I2C3_EV_IRQ
    .thumb_set I2C3_EV_IRQ, __safetyLoop

    .weak I2C3_ER_IRQ
    .thumb_set I2C3_ER_IRQ, __safetyLoop

    .weak FPU_IRQ
    .thumb_set FPU_IRQ, __safetyLoop

    .weak SPI4_IRQ
    .thumb_set SPI4_IRQ, __safetyLoop

    .weak SPI5_IRQ
    .thumb_set SPI5_IRQ, __safetyLoop

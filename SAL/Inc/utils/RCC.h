/**
 * @file RCC.h
*/

#ifndef RCC_H
#define RCC_H

#include <stdint.h>
#include "utils/container.h"

// Input Data
#define CRYSTAL_INPUT_FREQUENCY 8000000 //Hz

// Config and control
#define FLASH_ACR               *(volatile uint32_t *)(FLASH_BASE + 0x00)   //Flash configuration
#define RCC_CR                  *(volatile uint32_t *)(RCC_BASE + 0x00)     //Oscillator controller
#define RCC_PLLCFGR             *(volatile uint32_t *)(RCC_BASE + 0x04)     //PLL config
#define RCC_CFGR                *(volatile uint32_t *)(RCC_BASE + 0x08)     //RCC config

// RCC clock registers
#define RCC_AHB1ENR             *(volatile uint32_t *)(RCC_BASE + 0x30)
#define RCC_APB1ENR             *(volatile uint32_t *)(RCC_BASE + 0x40)
#define RCC_APB2ENR             *(volatile uint32_t *)(RCC_BASE + 0x44)

// AHB1 enables
#define AHB1_GPIOA_EN           (1UL << 0)
#define AHB1_GPIOB_EN           (1UL << 1)
#define AHB1_GPIOC_EN           (1UL << 2)
#define AHB1_GPIOD_EN           (1UL << 3)

// APB1 enables
#define APB1_USART2_EN          (1UL << 17)

// APB2 enables
#define APB2_USART1_EN          (1UL << 4)
#define APB2_USART6_EN          (1UL << 5)

// ARM SYST registers
#define SYST_CSR                *(volatile uint32_t *)(0xE000E010) // Control and Status
#define SYST_RVR                *(volatile uint32_t *)(0xE000E014) // Reload Value
#define SYST_CVR                *(volatile uint32_t *)(0xE000E018) // Current Value
#define SYST_COUNT              16

// PLL Controls
#define PLLM_SHIFT              0
#define PLLN_SHIFT              6
#define PLLP_SHIFT              16
#define PLLM_MASK               0b111111UL 
#define PLLN_MASK               0b111111111UL
#define PLLP_MASK               0b11UL
#define PLLSRC_SHIFT            22

#define PLLP_DIVIDER_2          0b00UL
#define PLLP_DIVIDER_4          0b01UL
#define PLLP_DIVIDER_6          0b10UL
#define PLLP_DIVIDER_8          0b11UL
#define PLLM_DIVIDER(x)         x
#define PLLN_MULTIPLIER(x)      x

#define PLL_ON                  (1 << 24)   // Activate PL
#define PLL_RDY                 (1 << 25)   // PLL status

// HSE
#define HSE_BYP                 (1 << 18)   // Bypass, only for squared signals
#define HSE_ON                  (1 << 16)   // Activate HSE
#define HSE_RDY                 (1 << 17)   // HSE status

//* AHBx/APBx enable/disable
#define AHB1_Enable(control_bit)  (RCC_AHB1ENR |=  control_bit)
#define AHB1_Disable(control_bit) (RCC_AHB1ENR &= ~control_bit)
#define APB1_Enable(control_bit)  (RCC_APB1ENR |=  control_bit)
#define APB1_Disable(control_bit) (RCC_APB1ENR &= ~control_bit)
#define APB2_Enable(control_bit)  (RCC_APB2ENR |=  control_bit)
#define APB2_Disable(control_bit) (RCC_APB2ENR &= ~control_bit)

/**
    @fn SysCLK_Init
    @brief Set the Phase Locked Loop for frequency setup
    @param PLLM divider    [2, 15]
    @param PLLN multiplier [50, 432]
    @param PLLP divider    (2, 4, 6 or 8)
    @note //Frequency =  (oscillator * N) / (M * P)
    @return None
*/
void SysCLK_Init(uint8_t PLLM, uint16_t PLLN, uint8_t PLLP);

/**
    @fn delay
    @brief suspend operations
    @param ms milliseconds to wait
    @return None
*/
void delay(uint32_t ms);

/**
    @fn delay_microsecond
    @brief suspend operations
    @param us microseconds to wait
    @return None
*/
void delay_microsecond(uint32_t us);

#endif //RCC_H
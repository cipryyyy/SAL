/**
 * @file RCC.h
*/

#ifndef RCC_H
#define RCC_H

#include <stdint.h>
#include "utils/container.h"

#define CRYSTAL_INPUT_FREQUENCY 8000000 //Hz

#define FLASH_ACR       *(volatile uint32_t *)(FLASH_BASE + 0x00)   //Flash configuration

#define RCC_CR          *(volatile uint32_t *)(RCC_BASE + 0x00)     //Oscillator controller
#define RCC_PLLCFGR     *(volatile uint32_t *)(RCC_BASE + 0x04)     //PLL config
#define RCC_CFGR        *(volatile uint32_t *)(RCC_BASE + 0x08)     //RCC config

#define SYST_CSR        *(volatile uint32_t *)(0xE000E010) // Control and Status
#define SYST_RVR        *(volatile uint32_t *)(0xE000E014) // Reload Value
#define SYST_CVR        *(volatile uint32_t *)(0xE000E018) // Current Value
#define SYST_COUNT      16

#define PLLM_SHIFT      0
#define PLLN_SHIFT      6
#define PLLP_SHIFT      16
#define PLLM_MASK       0b111111UL 
#define PLLN_MASK       0b111111111UL
#define PLLP_MASK       0b11UL
#define PLLSRC_SHIFT    22

#define PLLP_DIVIDER_2 0b00UL
#define PLLP_DIVIDER_4 0b01UL
#define PLLP_DIVIDER_6 0b10UL
#define PLLP_DIVIDER_8 0b11UL
#define PLLM_DIVIDER(x) x
#define PLLN_MULTIPLIER(x) x

#define HSE_BYP         (1 << 18)   // Bypass, only for squared signals
#define HSE_ON          (1 << 16)   // Activate HSE
#define HSE_RDY         (1 << 17)   // HSE status

#define PLL_ON          (1 << 24)   // Activate PL
#define PLL_RDY         (1 << 25)   // PLL status

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

//TODO
void AHB_prescaler();

//TODO1
void APB1_prescaler();

//TODO
void APB2_prescaler();

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
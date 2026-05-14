//Flash
#ifndef INC_CLOCK_H
#define INC_CLOCK_H

#include <stdint.h>

#define RCC_BASE        0x40023800
#define FLASH_BASE      0x40023C00
#define FLASH_ACR       *(volatile uint32_t *)(FLASH_BASE + 0x00)   //Flash configuration

// Clock
#define RCC_AHB1ENR     *(volatile uint32_t *)(RCC_BASE + 0x30)
#define RCC_CR          *(volatile uint32_t *)(RCC_BASE + 0x00)     //Oscillator controller
#define RCC_PLLCFGR     *(volatile uint32_t *)(RCC_BASE + 0x04)     //PLL config
#define RCC_CFGR        *(volatile uint32_t *)(RCC_BASE + 0x08)     //RCC config

//* BITS
//f_VCO = f_PLLinput * (PLLN / PLLM)
//f_clock = f_VCO / PLLP
#define PLLM_SHIFT      0
#define PLLN_SHIFT      6
#define PLLP_SHIFT      16
#define PLLM_MASK       0b111111UL 
#define PLLN_MASK       0b111111111UL
#define PLLP_MASK       0b11UL
#define PLLSRC_SHIFT    22

#define HSE_BYP         (1 << 18)   // Bypass, only for squared signals
#define HSE_ON          (1 << 16)   // Activate HSE
#define HSE_RDY         (1 << 17)   // HSE status

#define PLL_ON          (1 << 24)   // Activate PL
#define PLL_RDY         (1 << 25)   // PLL status

void delay(uint32_t ms);

/*
@fn setClock
@brief setup the PLL
@note based on fixed 8MHz Nucleo crystal
@param PLLM divider (2,4,6 or 8)
@param PLLN multiplier
@param PLLP divider
@return 0 if OK, 1 if failed
*/
uint8_t setClock(uint8_t PLLM, uint8_t PLLN, uint8_t PLLP);

#endif //INC_CLOCK_H
/**
 * @file RCC.c
*/

#include "utils/RCC.h"

uint32_t frequency = 0;

void SysCLK_Init(uint8_t PLLM, uint16_t PLLN, uint8_t PLLP) {
    uint8_t flash_latency;

    if (PLLM < 2 || PLLM > 63) return;
    if (PLLN < 50 || PLLN > 432) return;
    if (PLLP > 3) return;

    frequency = (CRYSTAL_INPUT_FREQUENCY * PLLN) / (PLLM * (PLLP + 1) * 2);

    if (frequency > 100000000) return;

    if (frequency <= 30000000) {
        flash_latency = 0b00;
    } else if (frequency <= 64000000) {
        flash_latency = 0b01;
    } else if (frequency <= 90000000) {
        flash_latency = 0b10;
    } else {
        flash_latency = 0b11;
    }

    RCC_CR |= HSE_BYP;
    RCC_CR |= HSE_ON;

    while (!(RCC_CR & HSE_RDY));

    FLASH_ACR &= ~(0b11111UL);
    FLASH_ACR |= flash_latency;

    RCC_PLLCFGR &= ~((PLLM_MASK << PLLM_SHIFT) | (PLLN_MASK << PLLN_SHIFT) | (PLLP_MASK << PLLP_SHIFT));
    RCC_PLLCFGR |= (((PLLM & PLLM_MASK) << PLLM_SHIFT) | ((PLLN & PLLN_MASK) << PLLN_SHIFT) | ((PLLP & PLLP_MASK) << PLLP_SHIFT));

    RCC_PLLCFGR |= 1 << PLLSRC_SHIFT;

    RCC_CR |= PLL_ON;
    while (!(RCC_CR & PLL_RDY));

    RCC_CFGR &= ~(0b11);
    RCC_CFGR |= 0b10;

    while (((RCC_CFGR >> 2) & 0x03) != 0b10);
}

void delay(uint32_t ms) {
    if (frequency == 0) return;

    SYST_RVR = frequency/1000 - 1;
    SYST_CVR = 0;
    SYST_CSR = 0x05;

    for (uint32_t i = 0; i < ms; i++) {
        while (!(SYST_CSR & (1 << SYST_COUNT)));
    }

    SYST_CSR = 0;
}

void delay_microsecond(uint32_t us) {
    if (frequency == 0) return;

    SYST_RVR = frequency/1000000 - 1;
    SYST_CVR = 0;
    SYST_CSR = 0x05;

    for (uint32_t i = 0; i < us; i++) {
        while (!(SYST_CSR & (1 << SYST_COUNT)));
    }

    SYST_CSR = 0;
}
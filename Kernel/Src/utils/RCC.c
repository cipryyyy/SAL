/**
 * @file RCC.c
*/

#include "utils/RCC.h"

uint32_t ticks = 0;
uint32_t sysCLK = 0;
uint32_t AHB1_prescaler = 1;
uint32_t APB1_prescaler = 1;
uint32_t APB2_prescaler = 1;

void SysCLK_Init(uint8_t PLLM, uint16_t PLLN, uint8_t PLLP) {
    uint8_t flash_latency;

    if (PLLM < 2 || PLLM > 63) return;
    if (PLLN < 50 || PLLN > 432) return;
    if (PLLP > 3) return;

    sysCLK = (CRYSTAL_INPUT_FREQUENCY * PLLN) / (PLLM * (PLLP + 1) * 2);

    if (sysCLK > 100000000) return;

    if (sysCLK <= 30000000) {
        flash_latency = 0b00;
    } else if (sysCLK <= 64000000) {
        flash_latency = 0b01;
    } else if (sysCLK <= 90000000) {
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

    if (sysCLK > 50000000) {
        APB1_SetPrescaler(APB_PRESCALER_2);
    } else {
        APB1_SetPrescaler(APB_PRESCALER_1);
    }

    SYST_CTRL = 0;
    SYST_LOAD = (sysCLK/1000) - 1;
    SYST_VAL = 0;
    SYST_CTRL = SYSTICK_CTRL_CLKSOURCE | SYSTICK_CTRL_TICKINT   | SYSTICK_CTRL_ENABLE;
}

void APB1_SetPrescaler(uint32_t prescaler) {
    if (prescaler > APB_PRESCALER_16) return;

    RCC_CFGR &= ~(0b111UL << APB1_PRESCALER_SHIFT);
    RCC_CFGR |= prescaler << APB1_PRESCALER_SHIFT;

    if (prescaler < APB_PRESCALER_2) {
        APB1_prescaler = 1;
    } else {
        APB1_prescaler = 1 << ((prescaler & 0b11) + 1);
    }
}

void APB2_SetPrescaler(uint32_t prescaler)  {
    if (prescaler > APB_PRESCALER_16) return;

    RCC_CFGR &= ~(0b111UL << APB2_PRESCALER_SHIFT);
    RCC_CFGR |= prescaler << APB2_PRESCALER_SHIFT;

    if (prescaler < APB_PRESCALER_2) {
        APB2_prescaler = 1;
    } else {
        APB2_prescaler = 1 << ((prescaler & 0b11) + 1);
    }
}

void AHB1_SetPrescaler(uint32_t prescaler) {
    if (prescaler > AHB_PRESCALER_512) return;

    RCC_CFGR &= ~(0b1111UL << AHB1_PRESCALER_SHIFT);
    RCC_CFGR |= prescaler << AHB1_PRESCALER_SHIFT;

    switch(prescaler) {
        case AHB_PRESCALER_2:   AHB1_prescaler = 2; break;
        case AHB_PRESCALER_4:   AHB1_prescaler = 4; break;
        case AHB_PRESCALER_8:   AHB1_prescaler = 8; break;
        case AHB_PRESCALER_16:  AHB1_prescaler = 16; break;
        case AHB_PRESCALER_64:  AHB1_prescaler = 64; break;
        case AHB_PRESCALER_128: AHB1_prescaler = 128; break;
        case AHB_PRESCALER_256: AHB1_prescaler = 256; break;
        case AHB_PRESCALER_512: AHB1_prescaler = 512; break;
        default:                AHB1_prescaler = 1; break;
    }
}

void delay(uint32_t ms) {
    if (sysCLK == 0) return;

    int32_t initialTick = getTick();
    while (getTick() - initialTick < ms) {}
}

uint32_t get_sysCLK() {
    return sysCLK;
}

uint32_t get_AHB1_prescaler() {
    return AHB1_prescaler;
}

uint32_t get_APB1_prescaler() {
    return APB1_prescaler;
}

uint32_t get_APB2_prescaler() {
    return APB2_prescaler;
}

void SysTick_Handler(void) {
    ticks++;
}

int getTick() {
    return ticks;
}

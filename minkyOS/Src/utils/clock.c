#include "utils/clock.h"

uint8_t setPLL(uint8_t PLLM, uint16_t PLLN, uint8_t PLLP) {
    uint8_t  PLLM_value;
    uint16_t PLLN_value;
    uint8_t  PLLP_value;

    uint8_t VCO = ((8/PLLM)*PLLN)/PLLP;
    if (VCO > 100) return 1;   //F411 limit = 100MHz

    //validity check
    if (PLLP % 2 != 0 || PLLP < 2 || PLLP > 8) return 1;
    PLLP_value = (PLLP/2) - 1;

    if (PLLN < 50 || PLLN > 432) return 1;
    PLLN_value = PLLN;

    if (PLLM < 2 || PLLM > 63) return 1;
    PLLM_value = PLLM;

    RCC_CR |= HSE_BYP;      //Set bypass
    RCC_CR |= HSE_ON;       //Set as on

    while (!(RCC_CR & HSE_RDY)); //Wait for the clock to be ready

    RCC_PLLCFGR &= ~((PLLM_MASK << PLLM_SHIFT) | (PLLN_MASK << PLLN_SHIFT) | (PLLP_MASK << PLLP_SHIFT));
    RCC_PLLCFGR |= (((PLLM_value & PLLM_MASK) << PLLM_SHIFT) | ((PLLN_value & PLLN_MASK) << PLLN_SHIFT) | ((PLLP_value & PLLP_MASK) << PLLP_SHIFT));

    //(table 5) Vcc = 3.3V
    uint8_t FLASH_WS;
    if (VCO <= 30)      FLASH_WS = 0x0;
    else if (VCO <= 64) FLASH_WS = 0x1;
    else if (VCO <= 90) FLASH_WS = 0x2;
    else                FLASH_WS = 0x3;

    FLASH_ACR &= ~(0b111UL);
    FLASH_ACR |= FLASH_WS;

    //Set HSE as src
    RCC_PLLCFGR |= 1 << PLLSRC_SHIFT;

    //Turn on PLL
    RCC_CR |= PLL_ON;
    while (!(RCC_CR & PLL_RDY));    // Wait for it to be ready

    //Set PLL as system clock
    RCC_CFGR &= ~(0b11);    //Clear
    RCC_CFGR |= 0b10;

    //Wait for the switch (SWS)
    while (((RCC_CFGR >> 2) & 0x03) != 0b10);

    return SYS_OK;
}

void delay(uint32_t ms) {
    return;
}
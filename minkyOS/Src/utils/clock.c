#include "utils/clock.h"

//TODO set PLLM, PLLN, PPLP
//TODO set FLASH_ACR based on table 5

uint8_t setClock(uint8_t PLLM, uint16_t PLLN, uint8_t PLLP) {
    uint8_t  PLLM_value;
    uint16_t PPLN_value;
    uint8_t  PPLM_value;

    if (((8/PLLM)*PLLN)/PLLP > 100) return 1;   //F411 limit = 100MHz

    //validity check
    switch (PLLM) {
        case 2:
            PLLM_value = 0x00;
        case 4:
            PLLM_value = 0x00;
        case 6:
            PLLM_value = 0x00;
        case 8:
            PLLM_value = 0x00;
    }

    RCC_CR |= HSE_BYP;      //Set bypass
    RCC_CR |= HSE_ON;       //Set as on

    while (!(RCC_CR & HSE_RDY)); //Wait for the clock to be ready

    //Clock setup 8MHz / 8 (M) = 1MHz * 200 (N) = 200MHz / 2 (P) = 100MHz
    RCC_PLLCFGR &= ~((PLLM_MASK << PLLM_SHIFT) + (PLLN_MASK << PLLN_SHIFT) + (PLLP_MASK << PLLP_SHIFT));
    RCC_PLLCFGR |= (((8 & PLLM_MASK) << PLLM_SHIFT) | ((200 & PLLN_MASK) << PLLN_SHIFT) | ((0 & PLLP_MASK) << PLLP_SHIFT));

    //(table 5) Vcc =3.3V
    FLASH_ACR &= ~(0b11111UL);
    FLASH_ACR |= 0x03;

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
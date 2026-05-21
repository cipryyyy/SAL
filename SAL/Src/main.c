/**
 * @file main.c
 * @note default program, sweep internal LED
*/

#include "main.h"

void main(void) {
    //Setup
    GPIO_Init(GPIOA);
    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);
    SysCLK_Init(PLLM_DIVIDER(8), PLLN_MULTIPLIER(200), PLLP_DIVIDER_2);

    uint8_t mode = 0;
    uint8_t delay = 0;
    uint16_t counter = 0;
    //Main Loop
    while(1) {
        SetPinHIGH(GPIOA, GPIO_PIN_5);
        delay_microsecond(delay);
        SetPinLOW(GPIOA, GPIO_PIN_5);
        delay_microsecond(100 - delay);

        counter++;
        if (counter != 100) continue;

        if (mode == 0){
            delay++;
            if (delay == 100) mode = 1;
        } else {
            delay--;
            if (delay == 0) mode = 0;
        }
        counter = 0;
    }
}
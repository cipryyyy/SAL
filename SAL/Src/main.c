/**
 * @file main.c
*/

#include "main.h"

void main(void) {
    //Setup
    GPIO_Init(GPIOA);
    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);
    SysCLK_Init(PLLM_DIVIDER(8), PLLN_MULTIPLIER(200), PLLP_DIVIDER_2);

    //Main Loop
    while(1) {
        for (int i = 0; i < 3; i++) {
            SetPinHIGH(GPIOA, GPIO_PIN_5);
            delay(1000);
            SetPinLOW(GPIOA, GPIO_PIN_5);
            delay(1000);
        }
    }
}
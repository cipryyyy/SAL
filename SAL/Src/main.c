/**
 * @file main.c
 * @note default program, sweep internal LED if blue button is pressed
*/

#include "main.h"

void main(void) {
    //Setup
    GPIO_Init(GPIOA);
    GPIO_Init(GPIOC);
    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);       //Internal LED
    GPIO_SetPinMode(GPIOC, GPIO_PIN_13, GPIO_MODE_INPUT);       // Blue button
    UART2_Init();
    SysCLK_Init(PLLM_DIVIDER(8), PLLN_MULTIPLIER(200), PLLP_DIVIDER_2);

    uint8_t pinValue;
    uint8_t mode = 0;
    uint8_t delay = 0;
    uint16_t counter = 0;

    //Main Loop
    while(1) {
        pinValue = readPin(GPIOC, GPIO_PIN_13);
        if (!pinValue) {
            counter = 0;
            mode = 0;
            delay = 0;
            continue;
        }

        //Press blue button
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
            UART2_WriteChar('a');
        }
        counter = 0;
    }
}
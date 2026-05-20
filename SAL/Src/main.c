/**
 * @file main.c
*/

#include "main.h"

void main(void) {
    GPIO_Init(GPIOA);
    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);

    while(1) {
        SetPinHIGH(GPIOA, GPIO_PIN_5);    //Set pin HIGH
        for (int i = 0; i < 100000; i++) {
            //wait
        }
        SetPinLOW(GPIOA, GPIO_PIN_5);    //Set pin LOW
        for (int i = 0; i < 100000; i++) {
            //wait
        }
    }
}
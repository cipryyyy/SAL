/**
 * @file GPIO.c
*/

#include "utils/GPIO.h"

void GPIO_Init(uint32_t GPIOx) {
    switch (GPIOx) {
        case GPIOA:
            RCC_AHB1ENR |= RCC_GPIOAEN;
            break;
        case GPIOB:
            RCC_AHB1ENR |= RCC_GPIOBEN;
            break;
        case GPIOC:
            RCC_AHB1ENR |= RCC_GPIOCEN;
            break;
        case GPIOD:
            RCC_AHB1ENR |= RCC_GPIODEN;
            break;
    }
}

void GPIO_SetPinMode(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t MODE) {
    GPIOx_MODER(GPIOx) &= ~(0b11UL << (GPIO_PIN * 2));    //Clear bits
    GPIOx_MODER(GPIOx) |= (MODE << (5 * 2));     //Set as output
    return;
}

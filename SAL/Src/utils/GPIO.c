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

void GPIO_SetPinMode(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t mode, uint32_t pupd) {
    GPIOx_MODER(GPIOx) &= ~(0b11UL << (GPIO_PIN << 1));
    GPIOx_MODER(GPIOx) |= (mode << (GPIO_PIN << 1));

    GPIOx_PUPDR(GPIOx) &= ~(0b11UL << (GPIO_PIN << 1));
    GPIOx_PUPDR(GPIOx) &= ~(pupd << (GPIO_PIN << 1));

    return;
}
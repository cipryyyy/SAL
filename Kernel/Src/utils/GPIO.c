/**
 * @file GPIO.c
*/

#include "utils/GPIO.h"

void GPIO_Init()
{
    AHB1_Enable(AHB1_GPIOA_EN);
    AHB1_Enable(AHB1_GPIOB_EN);
    AHB1_Enable(AHB1_GPIOC_EN);
    AHB1_Enable(AHB1_GPIOD_EN);
}

void GPIO_SetPinMode(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t mode)
{
    GPIOx_MODER(GPIOx) &= ~(0b11UL << (GPIO_PIN << 1));
    GPIOx_MODER(GPIOx) |= (mode << (GPIO_PIN << 1));
}

void GPIO_SetPinType(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t type)
{
    GPIOx_OTYPER(GPIOx) &= ~(0b11UL << (GPIO_PIN << 1));
    GPIOx_OTYPER(GPIOx) |= (type << (GPIO_PIN << 1));
}

void GPIO_SetPinSpeed(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t speed)
{
    GPIOx_OSPEEDR(GPIOx) &= ~(0b11UL << (GPIO_PIN << 1));
    GPIOx_OSPEEDR(GPIOx) |= (speed << (GPIO_PIN << 1));
}

void GPIO_SetPUPD(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t pupd)
{
    GPIOx_PUPDR(GPIOx) &= ~(0b11UL << (GPIO_PIN << 1));
    GPIOx_PUPDR(GPIOx) |= (pupd << (GPIO_PIN << 1));
}

void GPIO_SetAF(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t AlternateFunction)
{
    GPIO_SetPinMode(GPIOx, GPIO_PIN, GPIO_MODE_ALTERNATE);
    if (GPIO_PIN < 8) {
        GPIOx_AFRL(GPIOx) &= ~(0b1111UL << (GPIO_PIN << 2));
        GPIOx_AFRL(GPIOx) |= (AlternateFunction << (GPIO_PIN << 2));
    } else {
        GPIOx_AFRH(GPIOx) &= ~(0b1111UL << ((GPIO_PIN - 8) << 2));
        GPIOx_AFRH(GPIOx) |= (AlternateFunction << ((GPIO_PIN - 8) << 2));
    }
}
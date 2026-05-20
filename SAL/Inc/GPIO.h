/**
 * @file GPIO.h
*/

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "container.h"

#define RCC_BASE        0x40023800
#define GPIOA           (GPIO_BASE + 0x0)
#define GPIOB           (GPIO_BASE + 0x400)
#define GPIOC           (GPIO_BASE + 0x800)
#define GPIOD           (GPIO_BASE + 0xC00)  

#define RCC_AHB1ENR     *(volatile uint32_t *)(RCC_BASE + 0x30)

#define RCC_GPIOAEN     (1 << 0)
#define RCC_GPIOBEN     (1 << 1)
#define RCC_GPIOCEN     (1 << 2)
#define RCC_GPIODEN     (1 << 3)

#define GPIO_MODE_INPUT      0x0
#define GPIO_MODE_OUTPUT     0x1
#define GPIO_MODE_ALTERNATE  0x2
#define GPIO_MODE_ANALOG     0x3

//MACRO
#define GPIOx_MODER(GPIOx)     *(volatile uint32_t *)(GPIOx + 0x00)
#define GPIOx_ODR(GPIOx)       *(volatile uint32_t *)(GPIOx + 0x14)

#define SetPinHIGH(GPIOx, GPIO_PIN) (GPIOx_ODR(GPIOx) |= (1 << GPIO_PIN))
#define SetPinLOW(GPIOx, GPIO_PIN)  (GPIOx_ODR(GPIOx) &= ~(1 << GPIO_PIN))

void GPIO_Init(uint32_t GPIOx);
void GPIO_SetPinMode(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t MODE);

#endif //GPIO_H
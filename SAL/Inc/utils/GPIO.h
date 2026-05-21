/**
 * @file GPIO.h
*/

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "utils/container.h"

// Registers
#define GPIOA               (GPIO_BASE + 0x0)
#define GPIOB               (GPIO_BASE + 0x400)
#define GPIOC               (GPIO_BASE + 0x800)
#define GPIOD               (GPIO_BASE + 0xC00) 

#define RCC_GPIOAEN         (1 << 0)
#define RCC_GPIOBEN         (1 << 1)
#define RCC_GPIOCEN         (1 << 2)
#define RCC_GPIODEN         (1 << 3) 

// RCC GPIO clock enable
#define RCC_AHB1ENR         *(volatile uint32_t *)(RCC_BASE + 0x30)

// GPIO MODES 
#define GPIO_MODE_INPUT     0x0
#define GPIO_MODE_OUTPUT    0x1
#define GPIO_MODE_ALTERNATE 0x2
#define GPIO_MODE_ANALOG    0x3

//GPIO Registers
#define GPIOx_MODER(GPIOx)  *(volatile uint32_t *)(GPIOx + 0x00)
#define GPIOx_ODR(GPIOx)    *(volatile uint32_t *)(GPIOx + 0x14)

//Inline methods
#define SetPinHIGH(GPIOx, GPIO_PIN) (GPIOx_ODR(GPIOx) |= (1 << GPIO_PIN))
#define SetPinLOW(GPIOx, GPIO_PIN)  (GPIOx_ODR(GPIOx) &= ~(1 << GPIO_PIN))
#define TogglePin(GPIOx, GPIO_PIN)  (GPIOx_ODR(GPIOx) ^= (1 << GPIO_PIN))

/**
    @fn GPIO_Init
    @brief Initialize GPIOx interface
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @return None
*/
void GPIO_Init(uint32_t GPIOx);

/**
    @fn GPIO_SetPinMode
    @brief Set Pin Mode
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @param GPIO_PIN Pin number in register (e.g. GPIOA, GPIOB...)
    @param mode Pin Mode
    @return None
*/
void GPIO_SetPinMode(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t mode);

#endif //GPIO_H
/**
 * @file GPIO.h
*/

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "utils/RCC.h"
#include "utils/container.h"

// GPIO Registers
#define GPIOA               (GPIO_BASE + 0x0)
#define GPIOB               (GPIO_BASE + 0x400)
#define GPIOC               (GPIO_BASE + 0x800)
#define GPIOD               (GPIO_BASE + 0xC00) 

// GPIOx PINS
#define GPIO_PIN_0          0x0
#define GPIO_PIN_1          0x1
#define GPIO_PIN_2          0x2
#define GPIO_PIN_3          0x3
#define GPIO_PIN_4          0x4
#define GPIO_PIN_5          0x5
#define GPIO_PIN_6          0x6
#define GPIO_PIN_7          0x7
#define GPIO_PIN_8          0x8
#define GPIO_PIN_9          0x9
#define GPIO_PIN_10         0xA
#define GPIO_PIN_11         0xB
#define GPIO_PIN_12         0xC
#define GPIO_PIN_13         0xD
#define GPIO_PIN_14         0xE
#define GPIO_PIN_15         0xF

// GPIO Registers
#define GPIOx_MODER(GPIOx)   (*(volatile uint32_t *)(GPIOx + 0x00))
#define GPIOx_OTYPER(GPIOx)  (*(volatile uint32_t *)(GPIOx + 0x04))
#define GPIOx_OSPEEDR(GPIOx) (*(volatile uint32_t *)(GPIOx + 0x08))
#define GPIOx_PUPDR(GPIOx)   (*(volatile uint32_t *)(GPIOx + 0x0C))
#define GPIOx_IDR(GPIOx)     (*(volatile uint32_t *)(GPIOx + 0x10))
#define GPIOx_ODR(GPIOx)     (*(volatile uint32_t *)(GPIOx + 0x14))
#define GPIOx_BSSR(GPIOx)    (*(volatile uint32_t *)(GPIOx + 0x18))
#define GPIOx_LCKR(GPIOx)    (*(volatile uint32_t *)(GPIOx + 0x1C))
#define GPIOx_AFRL(GPIOx)    (*(volatile uint32_t *)(GPIOx + 0x20))
#define GPIOx_AFRH(GPIOx)    (*(volatile uint32_t *)(GPIOx + 0x24))

// GPIO MODES 
#define GPIO_MODE_INPUT     0x0UL
#define GPIO_MODE_OUTPUT    0x1UL
#define GPIO_MODE_ALTERNATE 0x2UL
#define GPIO_MODE_ANALOG    0x3UL

// GPIO TYPE
#define GPIO_PUSH_PULL      0x0UL
#define GPIO_OPEN_DRAIN     0x1UL

// GPIO SPEED
#define GPIO_SPEED_LOW      0x0UL
#define GPIO_SPEED_MEDIUM   0x1UL
#define GPIO_SPEED_FAST     0x2UL
#define GPIO_SPEED_HIGH     0x3UL

// GPIO PullUp and PullDown
#define GPIO_NOPULL         0x0UL
#define GPIO_PULLUP         0x1UL
#define GPIO_PULLDOWN       0x2UL

// Inline methods
#define GPIO_SetPinHIGH(GPIOx, GPIO_PIN) (GPIOx_BSSR(GPIOx) |= (1 << GPIO_PIN))
#define GPIO_SetPinLOW(GPIOx, GPIO_PIN)  (GPIOx_BSSR(GPIOx) |= (1 << (GPIO_PIN + 16)))
#define GPIO_TogglePin(GPIOx, GPIO_PIN)  (GPIOx_ODR(GPIOx) ^= (1 << GPIO_PIN))
#define GPIO_LockPin(GPIOx, GPIO_PIN)    (GPIOx_LCKR(GPIOx) |= (1 << GPIO_PIN))
#define GPIO_ReadPin(GPIOx, GPIO_PIN)    ((uint8_t)(~((GPIOx_IDR(GPIOx)) >> (GPIO_PIN)) & 1U))

#ifdef __cplusplus
extern "C" {
#endif

/**
    @fn GPIO_Init
    @brief Initialize GPIOx interface
    @return None
*/
void GPIO_Init();

/**
    @fn GPIO_SetPinMode
    @brief Set Pin Mode
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @param GPIO_PIN Pin number in register (e.g. GPIOA, GPIOB...)
    @param mode Pin mode
    @return None
*/
void GPIO_SetPinMode(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t mode);

/**
    @fn GPIO_SetPinType
    @brief Set Pin Type
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @param GPIO_PIN Pin number in register (e.g. GPIOA, GPIOB...)
    @param type Pin type
    @return None
*/
void GPIO_SetPinType(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t type);

/**
    @fn GPIO_SetPinSpeed
    @brief Set Pin Speed
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @param GPIO_PIN Pin number in register (e.g. GPIOA, GPIOB...)
    @param speed Pin speed
    @return None
*/
void GPIO_SetPinSpeed(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t speed);

/**
    @fn GPIO_SetPUPD
    @brief Set pull-up or pull-down
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @param GPIO_PIN Pin number in register (e.g. GPIOA, GPIOB...)
    @param pupd Pull-up or pull-down
    @return None
*/
void GPIO_SetPUPD(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t pupd);

/**
    @fn GPIO_SetAF
    @brief Set alternative function for pins
    @param GPIOx GPIO register (e.g. GPIOA, GPIOB...)
    @param GPIO_PIN Pin number in register (e.g. GPIOA, GPIOB...)
    @param AlternateFunction Pull-up or pull-down
    @return None
*/
void GPIO_SetAF(uint32_t GPIOx, uint8_t GPIO_PIN, uint32_t AlternateFunction);

#ifdef __cplusplus
}
#endif

#endif //GPIO_H
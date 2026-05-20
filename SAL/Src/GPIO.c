#include "GPIO.h"

#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000

// Clock enable
#define RCC_AHB1ENR     *(volatile uint32_t *)(RCC_BASE + 0x30)

//GPIOA config
#define GPIOA_MODER     *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR       *(volatile uint32_t *)(GPIOA_BASE + 0x14)

#define RCC_GPIOAEN     (1 << 0)
#define GPIOA5          (1 << 5)

void GPIOA_Init() {
    RCC_AHB1ENR |= RCC_GPIOAEN;     //Enable GPIOA clock

    //Set pin PA7 as output (0x01) in MODER register
    GPIOA_MODER &= ~(0b11UL << (5 * 2));    //Clear bits
    GPIOA_MODER |= (0b01UL << (5 * 2));     //Set as output
}

void On() {
    GPIOA_ODR |= GPIOA5;
    return;
}

void Off() {
    GPIOA_ODR &= ~GPIOA5;
    return;
}
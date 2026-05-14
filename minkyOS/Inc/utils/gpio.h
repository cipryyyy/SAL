#ifndef INC_GPIO_H
#define INC_GPIO_H

#define GPIO_BASE       0x40020000

#ifdef GPIOA
#define GPIOA_MODER     *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR       *(volatile uint32_t *)(GPIOA_BASE + 0x14)

//#define RCC_GPIOAEN     (1 << 0)
//#define GPIOA5          (1 << 5)
#endif //GPIOA

#endif //INC_GPIO_H
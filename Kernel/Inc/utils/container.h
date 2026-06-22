/**
 * @file container.h
 * @note General definitions
*/

#ifndef CONTAINER_H
#define CONTAINER_H

//Base addresses
#define RCC_BASE        0x40023800
#define GPIO_BASE       0x40020000
#define FLASH_BASE      0x40023C00
#define USART1_BASE     0x40011000
#define USART2_BASE     0x40004400
#define USART6_BASE     0x40011400

// IPC
#define OPERATION_OK    0

//Pins alternate functions
#define PIN_AF_SYS      0
#define PIN_AF_TIM1     1
#define PIN_AF_TIM2     1
#define PIN_AF_TIM3     2
#define PIN_AF_TIM4     2
#define PIN_AF_TIM5     2
#define PIN_AF_TIM9     3
#define PIN_AF_TIM10    3
#define PIN_AF_TIM11    3
#define PIN_AF_I2C1     4
#define PIN_AF_I2C2     4
#define PIN_AF_I2C3     4

//TODO find a better way to handle it, SPI and I2S occupies multiple numbers

#define PIN_AF_USART1   7
#define PIN_AF_USART2   7
#define PIN_AF_USART6   8
#define PIN_AF_I2C2     9
#define PIN_AF_I2C3     9
#define PIN_AF_OTG1     10
#define PIN_AF_SDIO     12

#endif //CONTAINER_H
/**
 * @file UART.h
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "utils/GPIO.h"
#include "utils/RCC.h"
#include "utils/container.h"

#define USARTx_SR(USARTx)  *(volatile uint32_t *)(USARTx + 0x00)    // Status
#define USARTx_DR(USARTx)  *(volatile uint32_t *)(USARTx + 0x04)    // Data
#define USARTx_BRR(USARTx) *(volatile uint32_t *)(USARTx + 0x08)    // Baudrate
#define USARTx_CR1(USARTx) *(volatile uint32_t *)(USARTx + 0x0C)    // Control 1
#define USARTx_CR2(USARTx) *(volatile uint32_t *)(USARTx + 0x10)    // Control 2

#define BRR_MANTISSA_SHIFT 4
#define BRR_FRACTION_SHIFT 0
#define CR1_TX_EN_SHIFT    3
#define CR1_PARITY_SHIFT   10
#define CR1_UART_EN_SHIFT  13
#define CR1_WORD_SHIFT     12

#define CR2_STOP_BIT_SHIFT 12

#define WORD_8BIT 0b0
#define WORD_9BIT 0b1

#define PCE_DISABLE 0b0
#define PCE_ENABLE 0b1

//BAUDRATE
#define BAUDRATE 115200

#ifdef __cplusplus
extern "C" {
#endif

/**
    @fn UART2_Init
    @brief Initalize UART2
    @return None
*/
void UART2_Init();

/**
    @fn UART_Transmit
    @brief Initalize UART2
    @param UART_address address, in container.h
    @param data Pointer to the data
    @param data_length Amount of data to transmit
    @return None
*/
void UART_Transmit(uint32_t UART_address, uint8_t* data, uint16_t data_length);

#ifdef __cplusplus
}
#endif

#endif //UART_H
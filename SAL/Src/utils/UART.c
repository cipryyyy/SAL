/**
 * @file UART.c
*/

#include "utils/UART.h"

void UART2_Init() {
    GPIO_SetPinMode(GPIOA, GPIO_PIN_2, GPIO_MODE_ALTERNATE);
    GPIO_SetAF(GPIOA, GPIO_PIN_2, 0x7);
    GPIO_SetPinMode(GPIOA, GPIO_PIN_3, GPIO_MODE_ALTERNATE);
    GPIO_SetAF(GPIOA, GPIO_PIN_3, 0x7);

    APB1_Enable(APB1_USART2_EN);

    //! Work in progress
    //FIXED

    //USARTDIV = 50'000'000/16*baudrate
    //target = 115200 -> 54,25347 -> integer = 54, frac = 0,25347 * 16 ~= 4

    uint16_t DIV_Mantissa = 54;
    uint8_t  DIV_Fraction = 4;
    uint16_t DIV_Value = (DIV_Mantissa << BRR_MANTISSA_SHIFT | DIV_Fraction << BRR_FRACTION_SHIFT);

    USARTx_BRR(USART2_BASE) &= ~(0xFFFFUL);
    USARTx_BRR(USART2_BASE) |= DIV_Value;

    USARTx_CR1(USART2_BASE) |= (WORD_8BIT << CR1_WORD_SHIFT) | (PCE_DISABLE << CR1_PARITY_SHIFT);
    USARTx_CR2(USART2_BASE) &= ~(0b11 << CR2_STOP_BIT_SHIFT);

    USARTx_CR1(USART2_BASE) |= (0b1 << CR1_TX_EN_SHIFT) | (0b1 << CR1_UART_EN_SHIFT);

    //TODO improve
}

void UART2_WriteChar(char c) {
    while ( !(USARTx_SR(USART2_BASE) & (1 << 7)) ) {
    }
    USARTx_DR(USART2_BASE) = c;
}
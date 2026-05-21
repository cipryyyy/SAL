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

    uint32_t APB1_frequency = get_sysCLK()/(get_AHB1_prescaler() * get_APB1_prescaler());
    uint16_t DIV_Mantissa = (uint16_t)(APB1_frequency/(16 * BAUDRATE));
    uint8_t  DIV_Fraction = (uint8_t)(((APB1_frequency/(16 * BAUDRATE)) - DIV_Mantissa) * 16);

    uint16_t DIV_Value = (DIV_Mantissa << BRR_MANTISSA_SHIFT | DIV_Fraction << BRR_FRACTION_SHIFT);

    USARTx_BRR(USART2_BASE) &= ~(0xFFFFUL);
    USARTx_BRR(USART2_BASE) |= DIV_Value;

    USARTx_CR1(USART2_BASE) |= (WORD_8BIT << CR1_WORD_SHIFT) | (PCE_DISABLE << CR1_PARITY_SHIFT);
    USARTx_CR2(USART2_BASE) &= ~(0b11 << CR2_STOP_BIT_SHIFT);

    USARTx_CR1(USART2_BASE) |= (0b1 << CR1_TX_EN_SHIFT) | (0b1 << CR1_UART_EN_SHIFT);
}

void UART2_WriteChar(char c) {
    while ( !(USARTx_SR(USART2_BASE) & (1 << 7)) ) {
    }
    USARTx_DR(USART2_BASE) = c;
}
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

    uint32_t usartdiv = (APB1_frequency + (BAUDRATE / 2)) / BAUDRATE; 

    USARTx_BRR(USART2_BASE) &= ~(0xFFFFUL);
    USARTx_BRR(USART2_BASE) |= usartdiv;

    USARTx_CR1(USART2_BASE) |= (WORD_8BIT << CR1_WORD_SHIFT) | (PCE_DISABLE << CR1_PARITY_SHIFT);
    USARTx_CR2(USART2_BASE) &= ~(0b11 << CR2_STOP_BIT_SHIFT);

    USARTx_CR1(USART2_BASE) |= (0b1 << CR1_TX_EN_SHIFT) | (0b1 << CR1_UART_EN_SHIFT);
}

void UART_Transmit(uint32_t UART_address, uint8_t* data, uint16_t data_length) {
    for (int i = 0; i < data_length; i++) {
        while ( !(USARTx_SR(UART_address) & (1 << 7))) {}
        USARTx_DR(UART_address) = data[i];
    }
    while (!(USARTx_SR(UART_address) & (1 << 6))); 
}
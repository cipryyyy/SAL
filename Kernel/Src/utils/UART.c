/**
 * @file UART.c
*/

#include "utils/UART.h"

//DIV = f_CLK/(8* (2 - OVER8) * baudrate)

//TODO Add general Init given UARTx
//TODO Make it support all configs (just 8N1 now)
void UART2_Init(uint32_t baudrate) {
    APB1_Enable(APB1_USART2_EN);
    
    //Setup pins
    GPIO_SetAF(GPIOA, GPIO_PIN_2, PA2_USART2_TX);
    GPIO_SetAF(GPIOA, GPIO_PIN_3, PA3_USART2_RX);

    //TODO Improve calculation
    uint32_t APB1_frequency = get_sysCLK()/(get_AHB1_prescaler() * get_APB1_prescaler());
    uint16_t DIV_Mantissa = (uint16_t)(APB1_frequency/(16 * baudrate));
    uint8_t  DIV_Fraction = (uint8_t)(((APB1_frequency/(16 * baudrate)) - DIV_Mantissa) * 16);

    uint16_t DIV_Value = (DIV_Mantissa << BRR_MANTISSA_SHIFT | DIV_Fraction << BRR_FRACTION_SHIFT);

    USARTx_BRR(USART2_BASE) &= ~(0xFFFFUL);
    USARTx_BRR(USART2_BASE) |= DIV_Value;

    //Setup baudrate, parity, wordlength and stop bits
    USARTx_CR1_RESET(USART2_BASE, USARTx_CR1_M);     //8
    USARTx_CR1_RESET(USART2_BASE, USARTx_CR1_PCE);   //N
    USARTx_CR2(USART2_BASE) &= ~(0b11 << USARTx_CR2_STOP_SHIFT);
    USARTx_CR2(USART2_BASE) |= USARTx_1STOP_BITS;   //1
    
    USARTx_CR1_SET(USART2_BASE, USARTx_CR1_TX_EN);  //Enable TX
    USARTx_CR1_SET(USART2_BASE, USARTx_CR1_RX_EN);  //Enable RX

    //Enable UART
    USARTx_CR1_SET(USART2_BASE, USARTx_CR1_UE);
}

//TODO Add error flags check
int UART_Transmit(uint32_t USARTaddress, uint8_t* data, uint16_t data_length, uint32_t timeout) {
    uint32_t initialTick = getTick();

    for (int i = 0; i < data_length; i++) {
        while (!USARTx_SR_TXE(USARTaddress)) {
            if (getTick() - initialTick > timeout) return 1;
        }
        USARTx_DR(USARTaddress) = data[i];
    }
    while (!(USARTx_SR(USARTaddress) & (1 << 6))) {
        if (getTick() - initialTick > timeout) return 1;
    }

    return OPERATION_OK;
}

//TODO Add error flags check
int UART_Receive(uint32_t USARTaddress, uint8_t* data, uint16_t data_length, int32_t timeout) {
    uint32_t initialTick = getTick();

    for(int i = 0; i < data_length; i++) {
        while (!USARTx_SR_RXNE(USARTaddress)) {
            if (getTick() - initialTick > timeout) return 1;
        }
        data[i] = USARTx_DR_READ(USARTaddress);
    }

    return OPERATION_OK;
}

//TODO Add Interrupt TX and RX
//TODO Add Receive interrupt

/**
 * @file UART.h
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "utils/GPIO.h"
#include "utils/RCC.h"
#include "utils/container.h"

// Register
#define USARTx_SR(USARTx)   *(volatile uint32_t *)(USARTx + 0x00)    // Status
#define USARTx_DR(USARTx)   *(volatile uint32_t *)(USARTx + 0x04)    // Data
#define USARTx_BRR(USARTx)  *(volatile uint32_t *)(USARTx + 0x08)    // Baudrate
#define USARTx_CR1(USARTx)  *(volatile uint32_t *)(USARTx + 0x0C)    // Control 1
#define USARTx_CR2(USARTx)  *(volatile uint32_t *)(USARTx + 0x10)    // Control 2
#define USARTx_CR3(USARTx)  *(volatile uint32_t *)(USARTx + 0x14)    // Control 3
#define USARTx_GTPR(USARTx) *(volatile uint32_t *)(USARTx + 0x18)    // Guard Time and Prescaler

// SR Register (read-only)
#define USARTx_SR_PE(USARTx)   ((uint8_t)((USARTx_SR(USARTx) >> 0)) & 0x1)   // Parity error
#define USARTx_SR_FE(USARTx)   ((uint8_t)((USARTx_SR(USARTx) >> 1)) & 0x1)   // Framing error
#define USARTx_SR_NF(USARTx)   ((uint8_t)((USARTx_SR(USARTx) >> 2)) & 0x1)   // Noise error
#define USARTx_SR_ORE(USARTx)  ((uint8_t)((USARTx_SR(USARTx) >> 3)) & 0x1)   // OverRun Error
#define USARTx_SR_IDLE(USARTx) ((uint8_t)((USARTx_SR(USARTx) >> 4)) & 0x1)   // Idle detecion
#define USARTx_SR_RXNE(USARTx) ((uint8_t)((USARTx_SR(USARTx) >> 5)) & 0x1)   // Receive Register Not Empty
#define USARTx_SR_TC(USARTx)   ((uint8_t)((USARTx_SR(USARTx) >> 6)) & 0x1)   // Transmission Complete
#define USARTx_SR_TXE(USARTx)  ((uint8_t)((USARTx_SR(USARTx) >> 7)) & 0x1)   // Transmission Register Empty
#define USARTx_SR_LBD(USARTx)  ((uint8_t)((USARTx_SR(USARTx) >> 8)) & 0x1)   // Break detection for LIN mode
#define USARTx_SR_CTS(USARTx)  ((uint8_t)((USARTx_SR(USARTx) >> 9)) & 0x1)   // Clear To Send

// DR Register
//! Only for 8N1
#define USARTx_DR_READ(USARTx) ((uint16_t)((USARTx_DR(USARTx) & 0xFF)))

// CR1 Register
#define USARTx_CR1_SET(USARTx, bit) (USARTx_CR1(USARTx) |= (1 << bit))
#define USARTx_CR1_RESET(USARTx, bit) (USARTx_CR1(USARTx) &= ~(1 << bit))
#define USARTx_CR1_SBK         0
#define USARTx_CR1_RWU         1
#define USARTx_CR1_RX_EN       2
#define USARTx_CR1_TX_EN       3
#define USARTx_CR1_IDLEIE      4
#define USARTx_CR1_RXNEIE      5
#define USARTx_CR1_TCIE        6
#define USARTx_CR1_TXEIE       7
#define USARTx_CR1_PEIE        8
#define USARTx_CR1_PS          9
#define USARTx_CR1_PCE         10
#define USARTx_CR1_WAKE        11
#define USARTx_CR1_M           12
#define USARTx_CR1_UE          13
#define USARTx_CR1_OVER8       15

// CR2 Register
#define USARTx_CR2_SET(USARTx, bit)   (USARTx_CR2(USARTx) |= (1 << bit))
#define USARTx_CR2_RESET(USARTx, bit) (USARTx_CR2(USARTx) &= ~(1 << bit))

#define USARTx_CR2_ADDR_SHIFT  0
#define USARTx_CR2_LBDL        5
#define USARTx_CR2_LBDIE       6
#define USARTx_CR2_LBCL        8
#define USARTx_CR2_CPHA        9
#define USARTx_CR2_CPOL        10
#define USARTx_CR2_CLKEN       11
#define USARTx_CR2_STOP_SHIFT  12
#define USARTx_CR2_LINEN       14

// CR3 Register
#define USARTx_CR3_SET(USARTx, bit)   (USARTx_CR3(USARTx) |= (1 << bit))
#define USARTx_CR3_RESET(USARTx, bit) (USARTx_CR3(USARTx) &= ~(1 << bit))

#define USARTx_CR3_EIE         0
#define USARTx_CR3_IREN        1
#define USARTx_CR3_IRLP        2
#define USARTx_CR3_HDSEL       3
#define USARTx_CR3_NACK        4
#define USARTx_CR3_SCEN        5
#define USARTx_CR3_DMAR        6
#define USARTx_CR3_DMAT        7
#define USARTx_CR3_RTSE        8
#define USARTx_CR3_CTSE        9
#define USARTx_CR3_CTSIE       10
#define USARTx_CR3_ONEBIT      11

// GTPR Register
#define BRR_MANTISSA_SHIFT 4
#define BRR_FRACTION_SHIFT 0

// UART configs
#define USARTx_WORD_8BIT        0b0
#define USARTx_WORD_9BIT        0b1
#define USARTx_PCE_DISABLE      0b0
#define USARTx_PCE_ENABLE       0b1
#define USARTx_05STOP_BITS      (0b01 << USARTx_CR2_STOP_SHIFT)
#define USARTx_1STOP_BITS       (0b00 << USARTx_CR2_STOP_SHIFT)
#define USARTx_15STOP_BITS      (0b11 << USARTx_CR2_STOP_SHIFT)
#define USARTx_2STOP_BITS       (0b10 << USARTx_CR2_STOP_SHIFT)

#ifdef __cplusplus
extern "C" {
#endif

/**
    @fn UART2_Init
    @brief Initalize UART2
    @param baudrate 
    @return None
*/
void UART2_Init(uint32_t baudrate);

/**
    @fn UART_Transmit
    @brief Transmit a string over UART
    @param UART_address address, in container.h
    @param data Pointer to the data
    @param data_length Amount of data to transmit
    @param timeout milliseconds before declaring failure
    @return Operation code
*/
int UART_Transmit(uint32_t UART_address, uint8_t* data, uint16_t data_length, uint32_t timeout);

/**
    @fn UART_Receive
    @brief Receive a string via UART
    @param UART_address address, in container.h
    @param data Pointer to the data
    @param timeout milliseconds before declaring failure
    @return Operation code
*/
int UART_Receive(uint32_t UART_address, uint8_t* data, uint16_t data_length, int32_t timeout);

void USARTx_set_node_address(uint32_t USARTx, uint8_t address);      //TODO

#ifdef __cplusplus
}
#endif

#endif //UART_H
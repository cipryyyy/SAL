#include "main.h"

int main(void) {
    SysCLK_Init(PLLM_DIVIDER(8), PLLN_MULTIPLIER(200), PLLP_DIVIDER_2);
    GPIO_Init();
    UART2_Init(9600);

    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);

    uint8_t RX;
    while (1) {
        if (UART_Receive(USART2_BASE, &RX, 1, 1000) == OPERATION_OK) {
            GPIO_SetPinHIGH(GPIOA, GPIO_PIN_5);
            if (UART_Transmit(USART2_BASE, &RX, 1, 10) == OPERATION_OK) GPIO_SetPinLOW(GPIOA, GPIO_PIN_5);
        }
    }
    return 0;
}
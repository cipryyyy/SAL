#include "main.h"

int main(void) {
    //INIT
    SysCLK_Init(PLLM_DIVIDER(8), PLLN_MULTIPLIER(200), PLLP_DIVIDER_2);
    GPIO_Init();
    UART2_Init();

    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);

    uint8_t string[] = "Hello world\n";

    while (1)
    {
        // Blink
        for (int i = 0; i < 3; i++) {
            SetPinHIGH(GPIOA, GPIO_PIN_5);
            delay(50);
            SetPinLOW(GPIOA, GPIO_PIN_5);
            delay(50);
        }
        delay(700);

        //Print "Hello world" with the UART
        UART_Transmit(USART2_BASE, string, sizeof(string));
    }
    return 0;
}
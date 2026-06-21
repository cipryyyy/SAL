#include "main.h"

int main(void) {
    GPIO_Init();
    GPIO_SetPinMode(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT);
    SysCLK_Init(PLLM_DIVIDER(8), PLLN_MULTIPLIER(200), PLLP_DIVIDER_2);

    while (1)
    {
        SetPinLOW(GPIOA, GPIO_PIN_5);
        delay(100);
        SetPinHIGH(GPIOA, GPIO_PIN_5);
        delay(100);
    }

    return 0;
}
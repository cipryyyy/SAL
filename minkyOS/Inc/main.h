#ifndef INC_MAIN_H
#define INC_MAIN_H

//#define DEBUG

#ifdef DEBUG
    #define SYST_CSR    *(volatile uint32_t *)(0xE000E010) // Control and Status
    #define SYST_RVR    *(volatile uint32_t *)(0xE000E014) // Reload Value
    #define SYST_CVR    *(volatile uint32_t *)(0xE000E018) // Current Value
    #define SYST_COUNT  16
#endif //DEBUG

#include "utils/clock.h"
#include "utils/gpio.h"

int main(void);
void error(void);

#endif //INC_MAIN_H
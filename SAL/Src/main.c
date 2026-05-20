#include "GPIO.h"

void main(void) {
    GPIOA_Init();

    while(1) {
        On();    //Set pin HIGH
        for (int i = 0; i < 500000; i++) {
            //wait
        }
        Off();    //Set pin LOW
        for (int i = 0; i < 500000; i++) {
            //wait
        }
    }
}
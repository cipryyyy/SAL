#include "main.h"

int main(void) {
    if (setPLL(8, 200, 2) != SYS_OK) error();
    
    while(1) {
        
    }
}

void error() {
    while (1) {

    }
}
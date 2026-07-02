/**
 * @file memory.c
*/

#include "utils/memory.h"

void *_sbrk(ptrdiff_t incr) {
    const uint8_t* max_heap = (uint8_t*)&_ssafety;

    static uint8_t *_sbrk_heap_end = &_sheap;
    uint8_t *prev_heap_end;

    if (_sbrk_heap_end + incr > max_heap) return (void *)-1;

    prev_heap_end = _sbrk_heap_end;
    _sbrk_heap_end += incr;

    return (void *)prev_heap_end;
}

void MPU_limit_stack(void) {
    MPU_CTRL = 0;
    MPU_RNR = 0;
    MPU_RBAR = (uint32_t)&_ssafety;
    MPU_RASR = (0b000 << 24) | (1 << 28) | (4 << 1) | 1;

    SCB_SHCSR |= (1 << 16);

    MPU_CTRL = 0x5;

    __asm volatile ("dsb" ::: "memory");
    __asm volatile ("isb" ::: "memory");
}

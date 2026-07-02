/**
 * @file memory.h
*/

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define MPU_CTRL   (*(volatile uint32_t*)0xE000ED94)
#define MPU_RNR    (*(volatile uint32_t*)0xE000ED98)
#define MPU_RBAR   (*(volatile uint32_t*)0xE000ED9C)
#define MPU_RASR   (*(volatile uint32_t*)0xE000EDA0)
#define SCB_SHCSR  (*(volatile uint32_t*)0xE000ED24)

extern uint8_t _sheap;
extern uint8_t _endOfRAM;
extern uint8_t _min_stack_size;

extern uint32_t _ssafety;

#ifdef __cplusplus
extern "C" {
#endif

void *_sbrk(ptrdiff_t incr);
void MPU_limit_stack(void);

void MemManage_Handler(void);

#ifdef __cplusplus
}
#endif

#endif //MEMORY_H
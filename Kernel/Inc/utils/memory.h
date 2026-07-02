/**
 * @file memory.h
*/

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

extern uint8_t _sheap;                                     //Where heap starts
extern uint8_t _endOfRAM;                                  //Where SRAM ends and stack stats
extern uint8_t _min_stack_size;

void *_sbrk(int incr);

#endif //MEMORY_H
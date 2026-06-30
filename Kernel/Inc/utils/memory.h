/**
 * @file memory.h
*/

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

extern uint32_t _sheap;
extern uint32_t _endOfRAM;

int _sbrk(int incr);

#endif //MEMORY_H
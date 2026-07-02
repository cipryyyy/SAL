/**
 * @file memory.c
*/

#include "utils/memory.h"

void *_sbrk(ptrdiff_t incr) {
    const uint32_t limitStack = (uint32_t)&_endOfRAM - (uint32_t)&_min_stack_size;  //Stack limit, where it starts minus its minimal length
    const uint8_t* max_heap = (uint8_t*)limitStack;             //Heap limit, wher it meets the stack

    static uint8_t *_sbrk_heap_end = NULL;                     //Pointer to current heap end
    uint8_t *prev_heap_end;

    if (_sbrk_heap_end == NULL) _sbrk_heap_end = &_sheap;       //Initialize where current heap ends (at heap starting point)

    if (_sbrk_heap_end + incr > max_heap) return (void *)-1;    //Check if I'm overflowing the heap

    prev_heap_end = _sbrk_heap_end;                             //Store previous value (used by the calling function to point data)
    _sbrk_heap_end += incr;                                     //Increment current heap size

    return (void *)prev_heap_end;                               //Return the pointer
}
/* Specify entry point */
ENTRY(_reset)

/* Minimum heap and stack size */
_min_heap_size = 0x400;
_stack_size = 0x800;

/* F411 physical memory data */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Where SRAM ends */
_endOfRAM = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  /* IRQ section */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  /* text section */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

  _sidata = LOADADDR(.data);

  /* defined data section */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT > FLASH

  /* undefined data section */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .; 
  } > RAM

  /* heap, I reserve AT LEAST _min_heap_size to it */
  .heap :
  {
    . = ALIGN(4);
    _sheap = .;
    . = . + _min_heap_size;
    _eheap = .;
    . = ALIGN(4);
  } > RAM

  /* safety region, this is where heap and stack meets, neither can cross it */
  .safety :
  {
    . = ALIGN(32);
    _ssafety = .;
    . = . + 32;
    _esafety = .;
  } > RAM

  .stack :
  {
    . = ALIGN(4);
    _sstack = .;
    . = . + (_stack_size - 32);
    _estack = .;
  } > RAM

}
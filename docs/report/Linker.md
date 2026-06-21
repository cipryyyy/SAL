# Linker

*See also [C Run-Time](/docs/report/CRT.md)*

*Documentation of [linker.ld](/Kernel/Startup/linker.ld), used to compile the code and specify where all the section must be written*

## ENTRY

The first thing the we must define is the entry point, this is necessary to avoid incorrect code optimization (e.g. remove unused function).

```
ENTRY(_reset)
```

## MEMORY

Here we will define the physical memory infos, such as RAM origin (starting point), length, access mode (read, write and/or execute) and the FLASH origin length and access mode.

```
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
}
```

After it, we can also define the end of the RAM, given by the sum of its origin and its length.

```
_endOfRAM = ORIGIN(RAM) + LENGTH(RAM);
```

## SECTIONS

```

SECTIONS
{
    ...
}
```

Here we will define all the memory sections, so the **ISR**, the **TEXT**, **DATA** and **BSS** sections

### ISR

```
.isr_vector :
{
. = ALIGN(4);
KEEP(*(.isr_vector))
. = ALIGN(4);
} > FLASH
```

All the section must be aligned to the word (32 bit/4 byte long data), for this reason we must call the `.align 4` command at the beginning and the end of each section.

The section is forced to be kept in the final `.elf` file, to avoid garbage collections errors in compile-time. The final `> FLASH` specify that the block must be stored in the flash memory.

### TEXT

```
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH
```

Store the code (`.text` and `.text*` subsections) and the read-only data (`.rodata` and `.rodata*`) after the ISR.

### DATA

Those are the values that we must store in the RAM. At the startup we must copy all the global and static values from the FLASH to the RAM (otherwise we will read garbage due to startup electrical noise in the RAM).

To do so, we must first define the starting point of the `DATA` section.

```
  _sidata = LOADADDR(.data);
```

The structure is similar to the `ISR` and `TEXT` sections, but we must store the first (`_sdata`) and the last (`_edata`) addresses.

```
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT > FLASH
```

With the `> RAM AT > FLASH` we will tell the compiler that data will be in the RAM, but they must be stored also in the FLASH, so we can load them when the device is powered on.

### BSS
Those are the non defined values, so we just need to store data position in the RAM (during the startup we will fill them with zeros).

```
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
```
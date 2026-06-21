# C Run-Time (CRT)

*See also [Linker](/docs/report/Linker.md)*

 Documentation of [`crt.s`](/Kernel/Startup/crt.s), which contains all the vital operation that the microprocessor must execute before and during its usage. It contains:

 * Where is the entry point of the `main()` function
 * Where the SRAM ends
 * Interrupt function calls
 * Initial copy from the FLASH to RAM for global and static data

## Compiling information

In the first lines of the program we will define what type of CPU we are using (`cortex-m4` in our case). Additionally we must specify that we are going to use `thumb` instruction, which are the only one supported by the `cortex M` series.

We cannot use the old `thumb` ISA (which is over 30 years old), we'll use the *Thumb2*, which contains more instruction, with the `.syntax unified` command.

```ARM
.syntax unified
.cpu cortex-m4
.thumb
```

## .isr_vector section

Here we must define a vector containing all the interrupt functions, the correct order is defined in the [Reference Manual](/docs/sources/STM_referenceManual.pdf), section 10.2. We will add the `"a"` flag to specify that it must be allocated (with the linker we define that it must be stored in the FLASH).

```ARM
.section .isr_vector, "a"

.global isr_functions
.global Default_Handler

isr_functions:
    .word _endOfRAM           @ SRAM end
    .word _reset              @ After-reset entry point
    .word NMI_Handler         @ Non Maskable Interrupt 
    .word HardFault_Handler   @ Hard Fault Handler
    .word MemManage_Handler   @ Memory Management Fault Handler
    .word BusFault_Handler    @ Bus Fault Handler
    .word UsageFault_Handler  @ Usage Fault Handler
    .word 0                   @ Reserved
    .word 0                   @ Reserved
    .word 0                   @ Reserved
    .word 0                   @ Reserved
    .word SVC_Handler         @ SVC Handler 
    .word DebugMon_Handler    @ Debug Monitor
    .word 0                   @ Reserved
    .word PendSV_Handler      @ PendSV Handler
    .word SysTick_Handler     @ SysTick Handler
```

There are other interrupts available such as DMA, ADC, external interrupts, timers etc. We can add them all in the file, of course we must use the defined order.

In case an interrupt happens (e.g. Hard Fault error), the processor will automatically call the `HardFault_Handler()` function. For this reason we will define some template function in the following sections, these function can be overwritten in the `C/C++` code later.

### Safety system

Here we will define some functions with the `.weak` instruction, it basically means that if there's no override of the function (e.g. we will not define the handler ourselves) it will be used this one.

```ARM
    .weak NMI_Handler
    .thumb_set NMI_Handler, __safetyLoop
```

In case this fuction is used, it will jump to `__safetyLoop`, which is a simple **trap**, this function will keep jumping into itself, freezing register values.

```ARM
    .thumb_func
    __safetyLoop:
        b __safetyLoop
```

## .text section

This is the heart of the program. The first that we must define is the `_reset` instruction, so what happens when the microprocessor is powered up.

As we previously stated, we must use thumb instruction, so we have to define all the functions as `thumb_func` to avoid misalignment.

```ARM
.section .text

.thumb_func
```

In the `_reset` part, the first thing that we must do is to copy the global and static values from the FLASH to the RAM, to do so we will exploit the `_sdata` and `_edata` addresses that we defined in the [linker.ld](/Kernel/Startup/linker.ld) file.

```ARM
.global _reset
    _reset:
        ldr r0, =_sdata
        ldr r1, =_edata
        ldr r2, =_sidata
        movs r3, #0
        b LoopCopyDataInit

    CopyDataInit:
        ldr r4, [r2, r3]
        str r4, [r0, r3]
        adds r3, r3, #4

    LoopCopyDataInit:
        adds r4, r0, r3
        cmp r4, r1
        bcc CopyDataInit
```

After that, we will clean the `.bss` section contained between the `_sbss` and `_ebss` addresses.

```ARM
        ldr r2, =_sbss
        ldr r4, =_ebss
        movs r3, #0
        b LoopFillZerobss

    FillZerobss:
        str  r3, [r2]
        adds r2, r2, #4

    LoopFillZerobss:
        cmp r2, r4
        bcc FillZerobss
```

Done so, the system is ready to be launched, we can call the `main()` function.

```ARM
        bl main
        b .
```

The final `b .` is a ***trap***, if we exit the main function (which should never happen) we will freeze all registers, in order to preserve the CPU status for a debugger analysis.

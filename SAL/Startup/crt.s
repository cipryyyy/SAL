.cpu cortex-m4
.thumb

.text
    .word 0x20020000        //end of SRAM
    .word _reset            //reset vector
    .thumb_func
    _reset:
        bl main
        b .

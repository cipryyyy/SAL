#!/bin/bash

echo "--- Compiling ---"
make

if [ $? -eq 0 ]; then
    echo "--- Flashing ---"
    STM32_Programmer_CLI -c port=swd -d build/app.elf -v -hardRst -rst -s
else
    echo "Build failed, skipping flash."
fi

cd ..
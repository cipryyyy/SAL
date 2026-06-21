cmake_minimum_required(VERSION 3.10)

project(SAL C CXX ASM)

# Source files
set(SOURCE_FILES
    SAL/Startup/crt.s
    SAL/Src/main.cpp
    SAL/Src/utils/GPIO.c
    SAL/Src/utils/UART.c
    SAL/Src/utils/RCC.c
)

add_executable(main ${SOURCE_FILES})

# Header folders
target_include_directories(main PRIVATE
    SAL/Inc
    SAL/Inc/utils
)

target_compile_options(main PRIVATE
    "-mcpu=cortex-m4"
    "-mthumb"
    "$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>" 
    "$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>" 
)

# Flags
target_link_options(main PRIVATE
    "-T${CMAKE_CURRENT_SOURCE_DIR}/SAL/Startup/linker.ld"
    "-nostartfiles"
    "-mcpu=cortex-m4"
    "-mthumb"
    "--specs=nosys.specs"
    "-fno-exceptions"  
    "-fno-rtti"
)

add_custom_command(TARGET main POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex main main.hex
)
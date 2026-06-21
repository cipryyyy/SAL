cmake_minimum_required(VERSION 3.10)

# Project name and languages
project(SAL C ASM)

# Source files
set(SOURCE_FILES
    SAL/Src/main.c
    SAL/Src/utils/GPIO.c
    SAL/Src/utils/UART.c
    SAL/Src/utils/RCC.c
)

# Headers
include_directories(
    SAL/Inc
    SAL/Inc/utils
)

add_executable(main ${SOURCE_FILES})
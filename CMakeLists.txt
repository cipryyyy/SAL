cmake_minimum_required(VERSION 3.10)

project(SAL C CXX ASM)

# Set debug mode as default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Source files
set(SOURCE_FILES
    Kernel/Startup/crt.s
    Kernel/Src/main.cpp
    Kernel/Src/utils/GPIO.c
    Kernel/Src/utils/UART.c
    Kernel/Src/utils/RCC.c
)
add_executable(main ${SOURCE_FILES})
set_target_properties(main PROPERTIES SUFFIX ".elf")       #Add .elf to the end of the file

# Headers
target_include_directories(main PRIVATE
    Kernel/Inc
    Kernel/Inc/utils
)

# Compilation options
target_compile_options(main PRIVATE
    "-mcpu=cortex-m4"                                       # Architecture
    "-mthumb"                                               # Thumb instruction
    "$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>"            # If c++, disable exceptions
    "$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>"                  # If c++, disable Run-Time Type Information
)

# Linking option
target_link_options(main PRIVATE
    "-T${CMAKE_CURRENT_SOURCE_DIR}/Kernel/Startup/linker.ld"   # Linker path
    "-nostartfiles"                                         # Do not use C library startups
    "-mcpu=cortex-m4"                                       # Ensure architecture
    "-mthumb"                                               # Ensure thumb instructions
    "--specs=nosys.specs"                                   # No OS in use
    "-fno-exceptions"                                       # Ensure no exceptions
    "-fno-rtti"                                             # Ensure no RTTI
    "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/main.map"         # Generate .map file
)

add_custom_command(TARGET main POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex main.elf main.hex #Generate .hex file
)
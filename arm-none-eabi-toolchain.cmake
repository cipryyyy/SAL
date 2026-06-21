set(CMAKE_SYSTEM_NAME Generic)                                                      # Generic system (No windows, Linux, Mac...)
set(CMAKE_SYSTEM_PROCESSOR arm)                                                     # Set processor architecture
set(CMAKE_C_COMPILER arm-none-eabi-gcc)                                             # Set C Compiler
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)                                           # Set assembly Compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)                                   # Compiler test
set(OBJECT_GEN_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft")                    # Generation flags (ARM-M4, thumb and no FPU)
set(CMAKE_C_FLAGS "${OBJECT_GEN_FLAGS}" CACHE INTERNAL "C compiler flags")          # Assign C flags
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS}" CACHE INTERNAL "ASM compiler flags")      # Assign ASM flags
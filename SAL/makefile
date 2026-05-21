CC  = arm-none-eabi-gcc
AS  = arm-none-eabi-as
LD  = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy
STL = st-flash

# Il percorso di inclusione diventa relativo a SAL/
CFLAGS = -mthumb -mcpu=cortex-m4 -IInc

# La cartella build si trova ora un livello sopra rispetto al makefile
BUILD_DIR = ../build

OBJS = $(BUILD_DIR)/crt.o \
       $(BUILD_DIR)/main.o \
       $(BUILD_DIR)/RCC.o \
       $(BUILD_DIR)/UART.o \
       $(BUILD_DIR)/GPIO.o

all: $(BUILD_DIR)/app.bin

$(BUILD_DIR)/crt.o: Startup/crt.s
	@mkdir -p $(BUILD_DIR)
	$(AS) -o $(BUILD_DIR)/crt.o Startup/crt.s

$(BUILD_DIR)/main.o: Src/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/main.o Src/main.c

$(BUILD_DIR)/GPIO.o: Src/utils/GPIO.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/GPIO.o Src/utils/GPIO.c

$(BUILD_DIR)/UART.o: Src/utils/UART.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/UART.o Src/utils/UART.c

$(BUILD_DIR)/RCC.o: Src/utils/RCC.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/RCC.o Src/utils/RCC.c

$(BUILD_DIR)/app.elf: Startup/linker.ld $(OBJS)
	$(LD) -T Startup/linker.ld -o $(BUILD_DIR)/app.elf $(OBJS)

$(BUILD_DIR)/app.bin: $(BUILD_DIR)/app.elf
	$(BIN) -O binary $(BUILD_DIR)/app.elf $(BUILD_DIR)/app.bin

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
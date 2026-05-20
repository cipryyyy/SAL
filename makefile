CC  = arm-none-eabi-gcc
AS  = arm-none-eabi-as
LD  = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy
STL = st-flash

# Aggiunto -ISAL/Inc per dire al compilatore dove trovare i file .h
CFLAGS = -mthumb -mcpu=cortex-m4 -ISAL/Inc

# Cartella di output per i file generati
BUILD_DIR = build

# Lista dei file oggetto che vogliamo creare dentro la cartella build
OBJS = $(BUILD_DIR)/crt.o \
       $(BUILD_DIR)/main.o \
       $(BUILD_DIR)/GPIO.o

all: $(BUILD_DIR)/app.bin

# Regola per l'assembly (Startup)
$(BUILD_DIR)/crt.o: crt.s
	@mkdir -p $(BUILD_DIR)
	$(AS) -o $(BUILD_DIR)/crt.o crt.s

# Regola per main.c
$(BUILD_DIR)/main.o: SAL/Src/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/main.o SAL/Src/main.c

# Regola per GPIO.c (Nuovo)
$(BUILD_DIR)/GPIO.o: SAL/Src/GPIO.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/GPIO.o SAL/Src/GPIO.c

# Linker - unisce tutti gli oggetti in un file .elf
$(BUILD_DIR)/app.elf: linker.ld $(OBJS)
	$(LD) -T linker.ld -o $(BUILD_DIR)/app.elf $(OBJS)

# Generazione del file binario finale per il flash
$(BUILD_DIR)/app.bin: $(BUILD_DIR)/app.elf
	$(BIN) -O binary $(BUILD_DIR)/app.elf $(BUILD_DIR)/app.bin

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
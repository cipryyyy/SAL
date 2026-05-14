CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy

CFLAGS = -mthumb -mcpu=cortex-m4 -IInc -O0 -g

BUILD_DIR = build

SRCS = $(shell find Src -name "*.c")
ASMS = $(shell find Src -name "*.s")

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o) $(ASMS:%.s=$(BUILD_DIR)/%.o)

LDSCRIPT = Src/linker.ld

TARGET_ELF = $(BUILD_DIR)/app.elf
TARGET_BIN = $(BUILD_DIR)/app.bin

all: $(TARGET_BIN)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) -o $@ $<

$(TARGET_ELF): $(OBJS) $(LDSCRIPT)
	@mkdir -p $(BUILD_DIR)
	$(LD) -T $(LDSCRIPT) -o $@ $(OBJS)

$(TARGET_BIN): $(TARGET_ELF)
	$(BIN) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
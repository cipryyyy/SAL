# SAL

Designed for STM32NUCLEO-F411

## Structure

```
├── README.md
├── SAL
│   ├── Inc
│   │   ├── Main files headers
│   │   └── utils
│   │       ├── Utilities reserved headers
│   ├── Src
│   │   ├── Main files
│   │   └── utils
│   │       ├── Utilities source code
│   ├── crt.s          <- Startuo file
│   └── linker.ld      <- Linker file
├── build
│   ├── objects and binaries produced
├── flash.sh           <- Script to flash the firmware
└── makefile
```

## Usage

### ADD a file
    1. Create the header file in `SAL/Inc`
    2. Create the source code in `SAL/Src`
    3. In `makefile`, update:
```makefile

$(BUILD_DIR)/FILE.o: SAL/Src/path/to/file.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/FILE.o SAL/Src/path/to/file.c
```
    4. In `makefile`, update:
```makefile
OBJS = $(BUILD_DIR)/crt.o \
       $(BUILD_DIR)/main.o \
       $(BUILD_DIR)/RCC.o \
       $(BUILD_DIR)/GPIO.o\
       # New file here
       $(BUILD_DIR)/FILE.o\
```

### FLASH the firmware

Just run `flash.sh` or use `STM32CubeProgramer` with the `.elf` file in `/build`.

## TODO list
- [x] GPIO
- [ ] RCC
- [ ] UART
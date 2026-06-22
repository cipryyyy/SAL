# General Purpose Input/Output (GPIO)

*See also: [Reset and Clock Control](/docs/report/RCC.md)*

Documentation for [`GPIO.h`](/Kernel/Inc/utils/GPIO.h) and [`GPIO.c`](/Kernel/Src/utils/GPIO.c).

The GPIO library manages pin behavior and state across all available GPIO ports.

---

## Initialization

To begin operating with the GPIO interface, call `GPIO_Init()`. This function enables all four ports (`GPIOA`, `GPIOB`, `GPIOC`, and `GPIOD`) on the **AHB1** bus.

If fine-grained power control is required, individual ports can be enabled using `AHB1_Enable()`, as described in the [Reset and Clock Control](/docs/report/RCC.md) guide. This is only recommended when targeting extremely low power consumption.

To disable the GPIO interface, call `GPIO_DeInit()`.

---

## Pin Modes

> Reference: [Section 8.4.1](/docs/sources/STM_referenceManual.pdf)

Each pin can be configured in one of four operating modes:

| Constant | Mode |
|---|---|
| `GPIO_MODE_INPUT` | Input |
| `GPIO_MODE_OUTPUT` | Output |
| `GPIO_MODE_ALTERNATE` | Alternate function |
| `GPIO_MODE_ANALOG` | Analog |

The mode is encoded as a 2-bit value and written to the `MODER` register via `GPIO_SetPinMode()`.

### Input Mode

> Reference: [Section 8.4.5](/docs/sources/STM_referenceManual.pdf)

In input mode, the pin's logic level is captured in the port's `IDR` register. Use `GPIO_ReadPin()` to read the current value.

### Output Mode

> Reference: [Section 8.4.6](/docs/sources/STM_referenceManual.pdf)

In output mode, the pin's logic level can be controlled via three functions:

| Function | Description |
|---|---|
| `GPIO_SetPinHIGH(GPIOx, GPIO_PIN)` | Drives the pin to logic 1 |
| `GPIO_SetPinLOW(GPIOx, GPIO_PIN)` | Drives the pin to logic 0 |
| `GPIO_TogglePin(GPIOx, GPIO_PIN)` | Inverts the current pin state |

`GPIO_SetPinHIGH` and `GPIO_SetPinLOW` operate on the `BSSR` register, which supports atomic set/reset operations without read-modify-write cycles.

`GPIO_TogglePin` uses the `ODR` register directly. The `ODR` register should be used when the current pin state is relevant (e.g., toggling) or when multiple pins need to be updated simultaneously.

### Alternate Function Mode

To use a pin with a peripheral (e.g., UART TX, timer output, SDIO), configure it in alternate function mode. Each pin supports multiple alternate functions, so the desired one must be selected explicitly.

`GPIO_SetAF()` internally configures the pin as `GPIO_MODE_ALTERNATE` and selects the specified alternate function, so no separate call to `GPIO_SetPinMode()` is needed.

### Analog Mode

In analog mode, the pin is connected to the ADC or DAC peripheral. Note that DAC is not supported on the STM32F411.

---

## Pin Type

Pin type controls the electrical behavior of the output driver. Two types are available:

| Constant | Type | Behavior |
|---|---|---|
| `GPIO_PUSH_PULL` | Push-Pull | Actively drives the line to 3.3 V when HIGH, and to 0 V when LOW (e.g., UART TX) |
| `GPIO_OPEN_DRAIN` | Open-Drain | Pulls the line to 0 V when LOW; leaves it floating when HIGH (e.g., I²C lines) |

Pin type is written to the `GPIOx_OTYPER` register via `GPIO_SetPinType()`.

---

## Pin Speed

> Reference: [Section 8.4.3](/docs/sources/STM_referenceManual.pdf)

Pin speed controls how quickly the output transitions between logic levels. Four speed grades are available:

| Constant | Speed |
|---|---|
| `GPIO_SPEED_LOW` | Low |
| `GPIO_SPEED_MEDIUM` | Medium |
| `GPIO_SPEED_FAST` | Fast |
| `GPIO_SPEED_HIGH` | High |

Pin speed is written to the `GPIOx_OSPEEDR` register via `GPIO_SetPinSpeed()`.

> **Note:** Higher slew rates increase overshoot during rise times and generate more electromagnetic interference (EMI). Choose the lowest speed that satisfies the timing requirements.

---

## Pull-Up and Pull-Down

> Reference: [Section 8.4.4](/docs/sources/STM_referenceManual.pdf)

Floating pins can cause undefined behavior. The STM32F411 provides internal pull-up and pull-down resistors to keep undriven pins at a defined logic level.

The pull resistor configuration is written to the `PUPDR` register via `GPIO_SetPUPD()`. Three settings are available:

| Constant | Description |
|---|---|
| `GPIO_NOPULL` | No pull resistor (default for most pins) |
| `GPIO_PULLUP` | Internal pull-up resistor |
| `GPIO_PULLDOWN` | Internal pull-down resistor |

> **Default state:** Most pins reset to `GPIO_NOPULL`. Exceptions are `PA13`, `PA15`, and `PB4`, which default to `GPIO_PULLUP`, and `PA14`, which defaults to `GPIO_PULLDOWN`.

---

## Alternate Function Selection

> Reference: [Sections 8.4.9–8.4.10](/docs/sources/STM_referenceManual.pdf)

To enable an alternate function on a pin, the correct function index must be selected. The full mapping of pins to alternate functions is available in [Table 9](/docs/sources/STM_datasheet.pdf) of the datasheet.

Call `GPIO_SetAF(GPIOx, GPIO_PIN, AlternateFunction)` with the index from that table. The function handles mode configuration internally.

Because a single 32-bit register cannot hold the 4-bit AF selector for all 16 pins of a port (16 × 4 = 64 bits), two registers are used:

| Register | Pins |
|---|---|
| `AFRL` | Pins 0–7 |
| `AFRH` | Pins 8–15 |

`GPIO_SetAF()` selects the correct register automatically based on the pin number.

---

## Pin Lock

> Reference: [Section 8.4.8](/docs/sources/STM_referenceManual.pdf)

`GPIO_LockPin(GPIOx, GPIO_PIN)` locks a pin's configuration at the hardware level, preventing any further changes to its mode, type, speed, or pull settings until the next reset.

> **Warning:** Once a pin is locked, its configuration cannot be modified without a full device reset.
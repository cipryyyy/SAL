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
│   ├── crt.s          <- Startup file
│   └── linker.ld      <- Linker file
├── build
│   ├── objects and binaries produced
└── CMakeLists.txt
```

## Usage

### Compile
1. Run this:
    ```bash
    cmake . #Just the first time
    make
    ```

### Flash the firmware

From VSCode on macOS:
1. Install `CMake Tools` extension
2. Open the `CMAKE` extension from the sidebar
3. In `Pinned Commands -> Run Tasks` run `CubeProg: Flash project (SWD)`

From cubeProgrammer:
1. Select the following settings:
   * Next to the `connect` button select `SWD`
   * `Port`: `SWD`
   * `Frequency`: `4000`
   * `Mode`: `Normal`
   * `Reset Mode`: `Hardware Reset`
   * `Speed`: `Reliable`
2. Press `Connect`
3. In the left sidebar, select `Erasing & programming`
4. In `file path`, insert `build/main`
5. Check `Run after programming` and `Verify programming`
6. Press `Start programming`
7. Once the programming is done, press `Disconnect`

### ADD a file

1. Create the header in `SAL/Inc/`
2. Create the source in `SAL/Src/`
3. Add the path to the source in the `CMakeLists.txt` file, in `SOURCE_FILES`

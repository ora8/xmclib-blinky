cmake_minimum_required(VERSION 3.15)
project(xmclib-blinky C CXX ASM)

# Name des Ziel-Betriebssystems (Bare-Metal)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compiler-Pfade erzwingen (ggf. Pfad anpassen, falls nicht im System-PATH)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Suche nach Bibliotheken/Programmen auf dem Host-PC für das Target verhindern
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Verhindert, dass CMake Linux-spezifische Bibliotheken in die Bare-Metal-Toolchain einschleust
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")

# 1. Compiler & Linker Flags für Cortex-M4 (Thumb-Mode & Hard-FPU) definieren
set(ARM_FLAGS 
    -mcpu=cortex-m4 
    -mthumb 
    -mfloat-abi=hard 
    -mfpu=fpv4-sp-d16
)

# 2. Ihr Executable/Target (Name an Ihr Projekt anpassen)
add_executable(xmclib-blinky.elf
    src/main.cpp
    src/startup_XMC4700.S  # Startup-Datei hinzufügen
    src/system_XMC4700.c
    src/gpio.cpp
    src/led.cpp
    src/boards/xmc47_relax_kit.cpp
)

# 2. Das C-Makro dem Target hinzufügen
target_compile_definitions(xmclib-blinky.elf PRIVATE XMC4700_F144x2048)


include_directories(xmclib-blinky.elf
    include
    include/CMSIS
    include/infineon)

# Setze den OUTPUT_NAME explizit auf "xmclib-blinky.elf"
set_target_properties(xmclib-blinky.elf PROPERTIES
    OUTPUT_NAME "xmclib-blinky"
    SUFFIX ".elf"
)

# Compiler-Flags setzen
target_compile_options(xmclib-blinky.elf PRIVATE
    ${ARM_FLAGS}
    -ffreestanding
    -nostdlib
    -ffunction-sections
    -fdata-sections
    -Wno-psabi
)

# Linker-Flags setzen
target_link_options(xmclib-blinky.elf PRIVATE
    ${ARM_FLAGS}
    -nostartfiles  # Deaktiviert die Standard-Startup-Datei (crt0.o)
    #-nostdlib       # Deaktiviert die Standardbibliothek
    #-nodefaultlibs  # Verhindert das Einbinden von Standardbibliotheken
    -lc       # Bindet die Standard-C-Bibliothek (für memcpy, __libc_init_array) ein
    -lgcc   
     -specs=nano.specs
    -specs=nosys.specs
    -Wl,--gc-sections
    -static
    -Wl,-Map=xmclib-blinky.map
    -Wl,-T../xmc4700.ld
    -e Reset_Handler  # Setzt den Eintragspunkt auf Reset_Handler
)

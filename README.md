# TM4C123GH6PM Drivers
## Drivers for the Texas Instruments Tiva C TM4C123GH6PM microcontroller.

Drivers for the Texas Instruments Tiva C TM4C123GH6PM 
microcontroller. It is designed to be easy to use, similar to an arduino,
however knowledge of pointers and memory management is reccommended.

[ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) is required to build this project. [OpenOCD](http://openocd.org/) is required to 
download main.elf to the board. Both are freely available to download and install

To compile the project use navigate to the project directory in a terminal and
use the command `make`.

Next use the command `openocd -f board/ek-tm4c123gxl.cfg -c "program main.elf"`
to download the code to the board. Hit the reset switch to reset the processor to
see the code in action.

The command `arm-none-eabi-gdb main.elf` can be used to access the debugger. 
* Use the command `target extended-remote:3333` to connect to the board
* Use the command `monitor reset halt` to halt the processor (required to load code)
* Use the command `load` to load new code onto the board
* Use the command `monitor reset init` to restart the processor
* The rest of the GDB commands are the same

## Functional Peripherals
* NVIC Interrupts
* PLL system clock for different clock speeds
* GPIO, GPIO interrupt on both edges
* 16/32-bit and 32/64-bit General Purpose Timer in oneshot and periodic mode
* PWM can be initilized for single and double ended complementary mode.

## In Progress
* ADC: Planning implementation

## Planned in no specific order
* µDMA
* GPIO: Poll raw interrupt status
* GPIO: interrupt on a single edge
* USB
* UART
* SPI
* I2C
* Systick
* MPU
* FPU
* SBC
* Analog Comparator
* Memory
    * EEPROM
    * Flash
* Hibernate
* Watchdog

# Test program

Main contains a very simple example program of how to use the drivers.

# TM4C123GH6PM Drivers
Drivers for the Texas Instruments Tiva C ARM 4F TM4C123GH6PM microcontroller. 
It is designed to be easy to use, similar to an arduino, however knowledge of 
pointers and memory management is reccommended. This project is written in C++.

# How to use
[ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) is required to build this project. [OpenOCD](http://openocd.org/) is required to 
download main.elf to the board. Both are freely available to download and install.

You will probably have to add both openOCD and the ARM GNU Toolchain bin folder to your path

To build the example main, navigate to the project directory in a terminal and
use the command `make`.

Use the command `openocd -f board/ek-tm4c123gxl.cfg -c "program main.elf"`
to download the code to the board. Hit the reset switch to reset the processor to
see the example code in action.

The command `arm-none-eabi-gdb main.elf` can be used to access the debugger. 
* Use the command `target extended-remote:3333` to connect to the board
* Use the command `monitor reset halt` to halt the processor (required to load code)
* Use the command `load` to load new code onto the board
* Use the command `monitor reset init` to restart the processor
* The rest of the GDB commands are the same

# Progress

## Disclaimer
This project is a work in progress. Class names, function names, enum names, etc..
may change, with out notice, at any time. 

## Functional Peripherals
* NVIC Interrupts
* PLL system clock for different clock speeds
* GPIO, GPIO interrupt on both edges
* 16/32-bit and 32/64-bit General Purpose Timer in oneshot and periodic mode
* PWM can be initilized for single and double ended complementary mode.
* ADC polling

## In Progress, To Do's
* Further test the ADC polling function
* Test the ADC interrupt function
* Implement the `void initializeDigitalComparator(void);` functionality

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
* Examples folder

# Test program
Main contains a very simple example program of how to use the drivers.

# License
All code is under the the GPl v3 License. Please the read the associated LICENSE
file for an in depth licensing agreement

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see https://www.gnu.org/licenses/.

# Copyright
Copyright Matthew Hardenburgh 2020. All rights reserved.

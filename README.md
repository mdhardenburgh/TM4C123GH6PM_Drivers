# RTOS
## A very simple RTOS for the Tiva TM4C123GH6PM microcontroller.

Drivers for the Texas Instruments Tiva C TM4C123GH6PM 
microcontroller. It is designed to be easy to use, similar to an arduino,
however knowledge of pointers and memory management is reccommended.

ARM GNU Toolchain is required to build this project. OpenOCD is required to 
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
* The reset of the GDB commands are the same

GPIO is currently only fuctional and functional for simple inputs and outputs.

Main contains a very simple example program of how to use the GPIO.

More to come soon!


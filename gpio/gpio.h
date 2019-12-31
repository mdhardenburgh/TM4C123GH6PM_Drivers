/**
 * @file gpio.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/24/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019 Matthew Hardenburgh
 * mdhardenburgh@gmail.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 * 
 * @section DESCRIPTION
 * 
 * Class header of the GPIO for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM.
 * 
 * The standard Tiva C devboard has the following pins connect to the switches
 * and LEDs
 * _____________________________________________
 * | GPIO Pin | Pin Function |     Device      |
 * |----------|--------------|-----------------|
 * |   PF4    |     GPIO     |       SW1       |
 * |----------|--------------|-----------------|
 * |   PF0    |     GPIO     |       SW2       |
 * |----------|--------------|-----------------|
 * |   PF1    |     GPIO     |  RGB LED (Red)  |
 * |----------|--------------|-----------------|
 * |   PF2    |     GPIO     |  RGB LED (Blue) |
 * |----------|--------------|-----------------|
 * |   PF3    |     GPIO     | RGB LED (Green) |
 * |----------|--------------|-----------------|
 * 
 * The table below shows special consideration GPIO pins. Most GPIO pins are 
 * configured as GPIOs and tri-stated by default (GPIOAFSEL=0, GPIODEN=0, 
 * GPIOPDR=0, GPIOPUR=0, and GPIOPCTL=0). Special consideration pins may be 
 * programed to a non-GPIO function or may have special commit controls out of 
 * reset. In addition, a Power-On-Reset (POR) or asserting RST returns these 
 * GPIO to their original special consideration state.
 * 
 * ____________________________
 * | GPIO Pin | Default Reset |
 * |          |     State     |
 * |----------|---------------|
 * |  PA[1:0] |     UART0     |
 * |----------|---------------|
 * |  PA[5:2] |     SSI0      |
 * |----------|---------------|
 * |  PB[3:2] |     I2C0      |
 * |----------|---------------|
 * |  PC[3:0] |    JTAG/SWD   |
 * |----------|---------------|
 * |   PD[7]  |     GPIO      |
 * |----------|---------------|
 * |   PF[0]  |     GPIO      |
 * |----------|---------------|
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include "gpioControl.h"

enum direction
{
    input, output
};

class Gpio : GpioControl
{
    public:
        Gpio();
        Gpio(GPIO_Port_Pins gpio, direction dir);
        ~Gpio();

        void gpioWrite(setORClear value);
        uint32_t gpioRead(void);

    private:

        GPIO_Port_Pins gpio = PA0;
        uint32_t gpioBaseAddress;
        uint32_t gpioPin;

        uint32_t gpioKey = 0x4C4F434B;

        const uint32_t GPIODATA = 0x3FC;
        const uint32_t GPIODIR = 0x400;

        Register GPIO_Port_GPIODIR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODIR)}; // 0x400 GPIODIR RW 0x0000.0000 GPIO Direction 663
        Register GPIO_Port_GPIODATA{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODATA)}; // 0x000 GPIODATA RW 0x0000.0000 GPIO Data 662

        bitField GPIODATA_DATA{0, 1, RW}; //GPIO Data. 

        bitField GPIODIR_DIR{0, 1, RW}; //GPIO Data Direction. 

};

#endif //GPIO_H
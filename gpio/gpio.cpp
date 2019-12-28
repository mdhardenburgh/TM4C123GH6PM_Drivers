/**
 * @file gpio.cpp
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
 * Class implemnetation of the GPIO for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM.
 */
#include "gpio.h"

Gpio::Gpio()
{

}

Gpio::Gpio(GPIO_Port_Pins gpio, direction dir)
{   


    (*this).gpio = gpio;
    uint32_t gpioPort = (*this).gpio/8;
    uint32_t gpioPin = (((*this).gpio % 8));

    GPIODIR_DIR.bit = gpioPin;
    GPIOCR_CR.bit = gpioPin;
    GPIOAFSEL_AFSEL.bit = gpioPin;
    GPIODEN_DEN.bit = gpioPin;
    GPIOAMSEL_GPIOAMSEL.bit = gpioPin;


    RCGCGPIO.setRegisterBitFieldStatus(RCGCGPIO_REG[gpioPort], set);
    while(PRGPIO.getRegisterBitFieldStatus(PRGPIO_REG[gpioPort]) == 0)
    {
        //Ready?
    }

    //Unlock NMI for use.
    if(gpio == PF0)
    {
        GPIOLOCK[gpioPort].setRegisterBitFieldStatus(GPIOLOCK_LOCK, gpioKey);
        GPIOCR[gpioPort].setRegisterBitFieldStatus(GPIOCR_CR, set);
    }

    GPIODIR[gpioPort].setRegisterBitFieldStatus(GPIODIR_DIR, dir);
    GPIOAFSEl[gpioPort].setRegisterBitFieldStatus(GPIOAFSEL_AFSEL, clear);
    GPIODEN[gpioPort].setRegisterBitFieldStatus(GPIODEN_DEN, set);
    GPIOAMSEL[gpioPort].setRegisterBitFieldStatus(GPIOAMSEL_GPIOAMSEL, clear);
    

}

Gpio::~Gpio()
{

}

void Gpio::gpioWrite(setORClear value)
{
    if((value == 0x0) || (value == 0x1))
    {
        GPIODATA_DATA.bit = (gpio % 8);
        GPIODATA[gpio/8].setRegisterBitFieldStatus(GPIODATA_DATA, value);
    }
}

uint32_t Gpio::gpioRead(void)
{
    return 0;
}
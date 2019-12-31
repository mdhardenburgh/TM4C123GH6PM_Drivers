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
    (*this).gpioBaseAddress = GPIO_PORT_AHB[((*this).gpio)/8];
    (*this).gpioPin = (((*this).gpio % 8));

    GPIO_Port_GPIOAFSEL.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIOAFSEl));
    GPIO_Port_GPIOPUR.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIOPUR));
    GPIO_Port_GPIODEN.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIODEN));
    GPIO_Port_GPIOLOCK.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIOLOCK));
    GPIO_Port_GPIOCR.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIOCR));
    GPIO_Port_GPIOAMSEL.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIOAMSEL));
    GPIO_Port_GPIOPCTL.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIOPCTL));
    GPIO_Port_GPIODIR.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIODIR));
    GPIO_Port_GPIODATA.setRegisterAddress((volatile uint32_t*)(gpioBaseAddress + GPIODATA));


    GPIOPUR_PUE.bit = gpioPin;
    GPIODATA_DATA.bit = gpioPin;
    GPIODIR_DIR.bit = gpioPin;
    
    GPIOCR_CR.bit = gpioPin;
    GPIOAFSEL_AFSEL.bit = gpioPin;
    GPIODEN_DEN.bit = gpioPin;
    GPIOAMSEL_GPIOAMSEL.bit = gpioPin;


    RCGCGPIO.setRegisterBitFieldStatus(RCGCGPIO_REG[((*this).gpio)/8], set);
    while(PRGPIO.getRegisterBitFieldStatus(PRGPIO_REG[((*this).gpio)/8]) == 0)
    {
        //Ready?
    }

    //Unlock NMI for use.
    if(gpio == PF0)
    {
        GPIO_Port_GPIOLOCK.setRegisterBitFieldStatus(GPIOLOCK_LOCK, gpioKey);
        GPIO_Port_GPIOCR.setRegisterBitFieldStatus(GPIOCR_CR, set);
    }

    GPIO_Port_GPIODIR.setRegisterBitFieldStatus(GPIODIR_DIR, dir);
    if(dir == input)
    {
        GPIO_Port_GPIOPUR.setRegisterBitFieldStatus(GPIOPUR_PUE, set);
    }

    GPIO_Port_GPIOAFSEL.setRegisterBitFieldStatus(GPIOAFSEL_AFSEL, clear);
    GPIO_Port_GPIODEN.setRegisterBitFieldStatus(GPIODEN_DEN, set);
    GPIO_Port_GPIOAMSEL.setRegisterBitFieldStatus(GPIOAMSEL_GPIOAMSEL, clear);
    

}

Gpio::~Gpio()
{

}

void Gpio::gpioWrite(setORClear value)
{
    if((value == 0x0) || (value == 0x1))
    {
        GPIO_Port_GPIODATA.setRegisterBitFieldStatus(GPIODATA_DATA, value);
    }
}

uint32_t Gpio::gpioRead(void)
{
    return(GPIO_Port_GPIODATA.getRegisterBitFieldStatus(GPIODATA_DATA));
}
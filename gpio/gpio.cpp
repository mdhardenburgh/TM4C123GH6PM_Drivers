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
    (*this).gpioBaseAddress = GPIO_Port_AHB_BASE + (((*this).gpio)/8) * 0x1000;
    (*this).gpioPin = (((*this).gpio % 8));

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCGPIO_OFFSET)), set, (uint32_t)((*this).gpio)/8, 1, RW);
    while(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + PRGPIO_OFFSET)), (uint32_t)((*this).gpio)/8, 1, RO) == 0)
    {
        //Ready?
    }

    //Unlock NMI for use.
    if(gpio == PF0)
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOLOCK_OFFSET)), gpioKey, 0, 32, RW);
        *(((volatile uint32_t*)(gpioBaseAddress + GPIOCR_OFFSET))) |= (0x1 << gpioPin);
    }

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIODIR_OFFSET)), dir, gpioPin, 1, RW);
    
    if(dir == input)
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOPUR_OFFSET)), set, gpioPin, 1, RW);
    }

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOAFSEl_OFFSET)), clear, gpioPin, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIODEN_OFFSET)), set, gpioPin, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOAMSEL_OFFSET)), clear, gpioPin, 1, RW);

}


Gpio::Gpio(GPIO_Port_Pins gpio, direction dir, uint32_t interruptPriority) : Gpio(gpio, dir)
{


    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOIM_OFFSET)), clear, gpioPin, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOIS_OFFSET)), clear, gpioPin, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOIBE_OFFSET)), set, gpioPin, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOICR_OFFSET)), set, gpioPin, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOIM_OFFSET)), set, gpioPin, 1, RW);


    /**
     * If gpio is == to Port F (Port number 5) use interrupt number 30 
     * (according to interrupt table), else use interrupt number 0 -> 4 
     * (corresponding to interrupt Port A through Port E)
     */
    Nvic::activateInterrupt((interrupt)((((((*this).gpio)/8) == 5) ? 30 : (((*this).gpio)/8))), interruptPriority);

}

Gpio::~Gpio()
{   

}

void Gpio::interruptClear(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIOICR_OFFSET)), set, gpioPin, 1, RW);
}

void Gpio::gpioWrite(setORClear value)
{
    if((value == 0x0) || (value == 0x1))
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIODATA_OFFSET)), value, gpioPin, 1, RW);
    }
}

uint32_t Gpio::gpioRead(void)
{
    return((Register::getRegisterBitFieldStatus(((volatile uint32_t*)(gpioBaseAddress + GPIODATA_OFFSET)), gpioPin, 1, RW)));
}
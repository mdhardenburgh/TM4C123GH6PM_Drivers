/**
 * @file gpio.cpp
 * @brief TM4C123GH6PM GPIO Driver Definition
 * @author Matthew Hardenburgh
 * @version 0.1
 * @date 3/21/2020
 * @copyright Matthew Hardenburgh 2020
 * 
 * @section license LICENSE
 * 
 * TM4C123GH6PM Drivers
 * Copyright (C) 2020  Matthew Hardenburgh
 * mdhardenburgh@protonmail.com
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
 */
#include "gpio.h"

/**
 * @brief empty constructor placeholder
 */
Gpio::Gpio()
{

}

/**
 * @brief empty deconstructor placeholder
 */
Gpio::~Gpio()
{   

}

/**
 * @brief Simple gpio initializer constructor.
 * @param gpio pin to be initialized.
 * @param dir of the gpio, to be an output or input.
 */
void Gpio::initialize(uint32_t gpio, direction dir)
{  
    alternateFunction = gpio%100; //get encoding for alternate function
    gpio = gpio/100; //get rid of gpio encoding

    gpioPort = (gpio/8);
    (*this).gpio = (gpio%8);
    (*this).dir = dir;
    baseAddress = GPIO_Port_AHB_BASE + (gpioPort) * 0x1000;

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCGPIO_OFFSET)), set, (uint32_t)(gpioPort), 1, RW);
    while(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + PRGPIO_OFFSET)), (uint32_t)(gpioPort), 1, RO) == 0)
    {
        //Ready?
    }

    //Unlock NMI for use.
    if(gpio == (uint32_t)PF0::GPIO)
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOLOCK_OFFSET)), gpioKey, 0, 32, RW);
        *(((volatile uint32_t*)(baseAddress + GPIOCR_OFFSET))) |= (0x1 << (*this).gpio);
    }

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIODIR_OFFSET)), (*this).dir, (*this).gpio, 1, RW);
    
    //If no alternate function encoding
    if(alternateFunction == 0)
    {
        if((*this).dir == input)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOPUR_OFFSET)), set, (*this).gpio, 1, RW);
        }


        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOAFSEl_OFFSET)), clear, (*this).gpio, 1, RW);
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIODEN_OFFSET)), set, (*this).gpio, 1, RW);
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOAMSEL_OFFSET)), clear, (*this).gpio, 1, RW);

    }

    //I have a note to fix this, is it fixed?
    //If alternate function is encoded
    else
    {
        alternateFunction = alternateFunction - 1; //Get rid of encoding offset

        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOAFSEl_OFFSET)), set, gpio, 1, RW); //Enable alternate function for GPIO pin

        //Analog alternate function
        if(alternateFunction == 0)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIODEN_OFFSET)), clear, gpio, 1, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOAMSEL_OFFSET)), set, gpio, 1, RW);
        }

        //Digital alternate Function
        else
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOPCTL_OFFSET)), alternateFunction, gpio * 4, 4, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIODEN_OFFSET)), set, gpio, 1, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOAMSEL_OFFSET)), clear, gpio, 1, RW);
        }


    }
}

/**
 * @brief Gpio interrupt constructor. Interrupts on both edges only.
 * @param gpio pin to be initialized.
 * @param dir of the gpio, to be an output or input.
 * @param interruptPriority of the gpio, 0 being the highest priority and 7
 *        being the lowest.
 */
void Gpio::initialize(uint32_t gpio, direction dir, uint32_t interruptPriority)
{
    (*this).interruptPriority = interruptPriority;
    
    initialize(gpio, dir);
    
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOIM_OFFSET)), clear, (*this).gpio, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOIS_OFFSET)), clear, (*this).gpio, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOIBE_OFFSET)), set, (*this).gpio, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOICR_OFFSET)), set, (*this).gpio, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOIM_OFFSET)), set, (*this).gpio, 1, RW);


    /*
    * If gpio is == to Port F (Port number 5) use interrupt number 30 
    * (according to interrupt table), else use interrupt number 0 -> 4 
    * (corresponding to interrupt Port A through Port E)
    */
    Nvic::activateInterrupt((interrupt)((((gpioPort) == 5) ? 30 : (gpioPort))), (*this).interruptPriority);
}

/**
 * @brief Clears the interrupt. Generally used in an ISR.
 */
void Gpio::interruptClear()
{

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIOICR_OFFSET)), set, gpio, 1, RW);
}

/**
 * @brief Writes to the gpio pin.
 * @param value to write to pin. Accepted values are 1 or 0.
 */
void Gpio::write(setORClear value)
{
    if((value == 0x0) || (value == 0x1))
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIODATA_OFFSET)), value, gpio, 1, RW);
    }
}

/**
 * @brief Reads from a gpio pin.
 * @return Value of the gpio pin, either a 1 or 0.
 */
uint32_t Gpio::read()
{
    return((Register::getRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPIODATA_OFFSET)), gpio, 1, RW)));
}
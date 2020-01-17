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

    RCGCGPIO = new Register((volatile uint32_t*)(systemControlBase + RCGCGPIO_OFFSET)); 
    PRGPIO = new Register((volatile uint32_t*)(systemControlBase + PRGPIO_OFFSET)); 

    GPIOAFSEL = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOAFSEl_OFFSET));
    GPIOPUR = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOPUR_OFFSET));
    GPIODEN = new Register((volatile uint32_t*)(gpioBaseAddress + GPIODEN_OFFSET));
    GPIOLOCK = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOLOCK_OFFSET));
    GPIOCR = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOCR_OFFSET));
    GPIOAMSEL = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOAMSEL_OFFSET));
    GPIOPCTL = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOPCTL_OFFSET));
    GPIODIR = new Register((volatile uint32_t*)(gpioBaseAddress + GPIODIR_OFFSET));

    GPIOICR = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOICR_OFFSET));
    GPIO_Port_GPIODATA = new Register((volatile uint32_t*)(gpioBaseAddress + GPIODATA_OFFSET));

    // GPIODATA_DATA = new bitField(0, 1, RW);

    RCGCGPIO_Rn.bit = ((*this).gpio)/8;
    PRGPIO_Rn.bit = ((*this).gpio)/8;

    GPIOPUR_PUE.bit = gpioPin;
    GPIODATA_DATA.bit = gpioPin;
    GPIODIR_DIR.bit = gpioPin;
    
    //GPIOCR_CR.bit = gpioPin;
    GPIOAFSEL_AFSEL.bit = gpioPin;
    GPIODEN_DEN.bit = gpioPin;
    GPIOAMSEL_GPIOAMSEL.bit = gpioPin;


    (*RCGCGPIO).setRegisterBitFieldStatus(RCGCGPIO_Rn, set);
    while((*PRGPIO).getRegisterBitFieldStatus(PRGPIO_Rn) == 0)
    {
        //Ready?
    }

    //Unlock NMI for use.
    if(gpio == PF0)
    {
        (*GPIOLOCK).setRegisterBitFieldStatus(GPIOLOCK_LOCK, gpioKey);
        *((*GPIOCR).getRegisterAddress()) |= (0x1 << gpioPin);
    }

    (*GPIODIR).setRegisterBitFieldStatus(GPIODIR_DIR, dir);
    if(dir == input)
    {
        (*GPIOPUR).setRegisterBitFieldStatus(GPIOPUR_PUE, set);
    }

    (*GPIOAFSEL).setRegisterBitFieldStatus(GPIOAFSEL_AFSEL, clear);
    (*GPIODEN).setRegisterBitFieldStatus(GPIODEN_DEN, set);
    (*GPIOAMSEL).setRegisterBitFieldStatus(GPIOAMSEL_GPIOAMSEL, clear);
    
    delete RCGCGPIO;
    delete PRGPIO;
    delete GPIOAFSEL;
    delete GPIOPUR;
    delete GPIODEN;
    delete GPIOLOCK;
    delete GPIOCR;
    delete GPIOAMSEL;
    delete GPIOPCTL;
    delete GPIODIR;

}


Gpio::Gpio(GPIO_Port_Pins gpio, direction dir, uint32_t interruptPriority) : Gpio(gpio, dir)
{

    // GPIO_PORTF_IM_R &= ~0x11;
    // GPIO_PORTF_IS_R &= ~0x11; //Clear the sense reg. 0 is edge triggered.
    // GPIO_PORTF_IBE_R |= 0x11; //Set the pins to sense on both edges.
    // GPIO_PORTF_ICR_R |= 0x11;
    // GPIO_PORTF_IM_R |= 0x11; //Set the interupts to be enabled.

    myNvic = new Nvic();
    // (*myNvic).disableInterrupts();

    GPIOIM = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOIM_OFFSET)); 
    GPIOIS = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOIS_OFFSET)); 
    GPIOIBE = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOIBE_OFFSET)); 
    GPIOIEV = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOIEV_OFFSET)); 
    GPIORIS = new Register((volatile uint32_t*)(gpioBaseAddress + GPIORIS_OFFSET));

    GPIOIM_IME.bit = gpioPin;
    GPIOIS_IS.bit = gpioPin;
    GPIOIBE_IBE.bit = gpioPin;
    GPIOICR_IC.bit = gpioPin;
    GPIOIM_IME.bit = gpioPin;

    (*GPIOIM).setRegisterBitFieldStatus(GPIOIM_IME, clear);
    (*GPIOIS).setRegisterBitFieldStatus(GPIOIS_IS, clear);
    (*GPIOIBE).setRegisterBitFieldStatus(GPIOIBE_IBE, set);
    (*GPIOICR).setRegisterBitFieldStatus(GPIOICR_IC, set);
    (*GPIOIM).setRegisterBitFieldStatus(GPIOIM_IME, set);


    /**
     * If gpio is == to Port F (Port number 5) use interrupt number 30 
     * (according to interrupt table), else use interrupt number 0 -> 4 
     * (corresponding to interrupt Port A through Port E)
     */
    (*myNvic).activateInterrupt((interrupt)((((((*this).gpio)/8) == 5) ? 30 : (((*this).gpio)/8))), interruptPriority);
    // (*myNvic).enableInterrupts();

    delete GPIOIM;
    delete GPIOIS;
    delete GPIOIBE;
    delete GPIOIEV;
    delete myNvic;
}

Gpio::~Gpio()
{
    delete GPIOICR;
    delete GPIO_Port_GPIODATA;
    delete GPIORIS;
}

void Gpio::interruptClear(void)
{
    (*GPIOICR).setRegisterBitFieldStatus(GPIOICR_IC, set);
}

void Gpio::gpioWrite(setORClear value)
{
    if((value == 0x0) || (value == 0x1))
    {
        (*GPIO_Port_GPIODATA).setRegisterBitFieldStatus(GPIODATA_DATA, value);
    }
}

uint32_t Gpio::gpioRead(void)
{
    return((*GPIO_Port_GPIODATA).getRegisterBitFieldStatus(GPIODATA_DATA));
}
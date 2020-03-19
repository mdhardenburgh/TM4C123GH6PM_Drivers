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

    Register RCGCGPIO((volatile uint32_t*)(systemControlBase + RCGCGPIO_OFFSET));
    Register PRGPIO((volatile uint32_t*)(systemControlBase + PRGPIO_OFFSET)); 

    Register GPIOAFSEL((volatile uint32_t*)(gpioBaseAddress + GPIOAFSEl_OFFSET));
    Register GPIOPUR((volatile uint32_t*)(gpioBaseAddress + GPIOPUR_OFFSET));
    Register GPIODEN((volatile uint32_t*)(gpioBaseAddress + GPIODEN_OFFSET));
    Register GPIOLOCK((volatile uint32_t*)(gpioBaseAddress + GPIOLOCK_OFFSET));
    Register GPIOCR((volatile uint32_t*)(gpioBaseAddress + GPIOCR_OFFSET));
    Register GPIOAMSEL((volatile uint32_t*)(gpioBaseAddress + GPIOAMSEL_OFFSET));
    Register GPIOPCTL((volatile uint32_t*)(gpioBaseAddress + GPIOPCTL_OFFSET));
    Register GPIODIR((volatile uint32_t*)(gpioBaseAddress + GPIODIR_OFFSET));

    // GPIOICR = new Register((volatile uint32_t*)(gpioBaseAddress + GPIOICR_OFFSET));
    // GPIO_Port_GPIODATA = new Register((volatile uint32_t*)(gpioBaseAddress + GPIODATA_OFFSET));

    bitField RCGCGPIO_Rn((uint32_t)((*this).gpio)/8, 1, RW);
    bitField PRGPIO_Rn((uint32_t)((*this).gpio)/8, 1, RO);

    bitField GPIODATA_DATA(gpioPin, 1, RW);

    bitField GPIOPUR_PUE(gpioPin, 1, RW);
    bitField GPIODIR_DIR(gpioPin, 1, RW);
    bitField GPIOAFSEL_AFSEL(gpioPin, 1, RW);
    bitField GPIODEN_DEN(gpioPin, 1, RW);
    bitField GPIOAMSEL_GPIOAMSEL(gpioPin, 1, RW);
    bitField GPIOLOCK_LOCK(0, 32, RW);
    
    //GPIOCR_CR.bit = gpioPin;
 


    (RCGCGPIO).setRegisterBitFieldStatus(RCGCGPIO_Rn, set);
    while((PRGPIO).getRegisterBitFieldStatus(PRGPIO_Rn) == 0)
    {
        //Ready?
    }

    //Unlock NMI for use.
    if(gpio == PF0)
    {
        (GPIOLOCK).setRegisterBitFieldStatus(GPIOLOCK_LOCK, gpioKey);
        *((GPIOCR).getRegisterAddress()) |= (0x1 << gpioPin);
    }

    (GPIODIR).setRegisterBitFieldStatus(GPIODIR_DIR, dir);
    if(dir == input)
    {
        (GPIOPUR).setRegisterBitFieldStatus(GPIOPUR_PUE, set);
    }

    (GPIOAFSEL).setRegisterBitFieldStatus(GPIOAFSEL_AFSEL, clear);
    (GPIODEN).setRegisterBitFieldStatus(GPIODEN_DEN, set);
    (GPIOAMSEL).setRegisterBitFieldStatus(GPIOAMSEL_GPIOAMSEL, clear);
    


}


Gpio::Gpio(GPIO_Port_Pins gpio, direction dir, uint32_t interruptPriority) : Gpio(gpio, dir)
{

    // GPIO_PORTF_IM_R &= ~0x11;
    // GPIO_PORTF_IS_R &= ~0x11; //Clear the sense reg. 0 is edge triggered.
    // GPIO_PORTF_IBE_R |= 0x11; //Set the pins to sense on both edges.
    // GPIO_PORTF_ICR_R |= 0x11;
    // GPIO_PORTF_IM_R |= 0x11; //Set the interupts to be enabled.

    Nvic myNvic;
    // (*myNvic).disableInterrupts();

    Register GPIOIM((volatile uint32_t*)(gpioBaseAddress + GPIOIM_OFFSET)); 
    Register GPIOIS((volatile uint32_t*)(gpioBaseAddress + GPIOIS_OFFSET)); 
    Register GPIOIBE((volatile uint32_t*)(gpioBaseAddress + GPIOIBE_OFFSET)); 
    Register GPIOIEV((volatile uint32_t*)(gpioBaseAddress + GPIOIEV_OFFSET)); 
    Register GPIORIS((volatile uint32_t*)(gpioBaseAddress + GPIORIS_OFFSET));
    Register GPIOICR((volatile uint32_t*)(gpioBaseAddress + GPIOICR_OFFSET));

    bitField GPIOIM_IME(gpioPin, 1, RW);
    bitField GPIOIS_IS(gpioPin, 1, RW);
    bitField GPIOIBE_IBE(gpioPin, 1, RW);
    bitField GPIOICR_IC(gpioPin, 1, RW);
    // GPIOICR_IC = new bitField(gpioPin, 1, RW);

    (GPIOIM).setRegisterBitFieldStatus(GPIOIM_IME, clear);
    (GPIOIS).setRegisterBitFieldStatus(GPIOIS_IS, clear);
    (GPIOIBE).setRegisterBitFieldStatus(GPIOIBE_IBE, set);
    (GPIOICR).setRegisterBitFieldStatus(GPIOICR_IC, set);
    (GPIOIM).setRegisterBitFieldStatus(GPIOIM_IME, set);


    /**
     * If gpio is == to Port F (Port number 5) use interrupt number 30 
     * (according to interrupt table), else use interrupt number 0 -> 4 
     * (corresponding to interrupt Port A through Port E)
     */
    myNvic.activateInterrupt((interrupt)((((((*this).gpio)/8) == 5) ? 30 : (((*this).gpio)/8))), interruptPriority);
    // (*myNvic).enableInterrupts();

}

Gpio::~Gpio()
{   
    // delete GPIO_Port_GPIODATA;
    // delete GPIOICR;
}

void Gpio::interruptClear(void)
{
    bitField GPIOICR_IC(gpioPin, 1, RW);
    Register GPIOICR((volatile uint32_t*)(gpioBaseAddress + GPIOICR_OFFSET));
    (GPIOICR).setRegisterBitFieldStatus(GPIOICR_IC, set);
}

void Gpio::gpioWrite(setORClear value)
{
    if((value == 0x0) || (value == 0x1))
    {
        bitField GPIODATA_DATA(gpioPin, 1, RW);
        Register GPIO_Port_GPIODATA((volatile uint32_t*)(gpioBaseAddress + GPIODATA_OFFSET));

        (GPIO_Port_GPIODATA).setRegisterBitFieldStatus(GPIODATA_DATA, value);
    }
}

uint32_t Gpio::gpioRead(void)
{
    bitField GPIODATA_DATA(gpioPin, 1, RW);
    Register GPIO_Port_GPIODATA((volatile uint32_t*)(gpioBaseAddress + GPIODATA_OFFSET));

    return((GPIO_Port_GPIODATA).getRegisterBitFieldStatus(GPIODATA_DATA));
}
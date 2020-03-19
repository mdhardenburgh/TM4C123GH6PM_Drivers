/*

RTOS
Copyright (C) 2019  Matthew Hardenburgh
mdhardenburgh@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/.

*/

/**
 * @file main.c
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @license GPL v3
 * @date 11/04/2019
 */

#include "main.h"

SystemControl* mySystemControl = NULL;



Gpio* greenLed = NULL;
Gpio* blueLed = NULL;
Gpio* redLed = NULL;
Gpio* swtich1 = NULL;
Gpio* swtich2 = NULL;
GeneralPurposeTimer* testTimer = NULL;

/**
 * These functions further help eliminate unwanted exceptions
 */

extern "C" void __cxa_pure_virtual() 
{ 
    while(1); 
}

void __gnu_cxx::__verbose_terminate_handler()
{
    while(1);
}

extern "C" void GPIO_Port_F_Handler(void)
{
    
    if((*swtich1).gpioRead() == 1)
    {
        (*redLed).gpioWrite(clear);
        (*swtich1).interruptClear();
    }

    if((*swtich1).gpioRead() == 0)
    {
        (*redLed).gpioWrite(set);
        (*swtich1).interruptClear();
    }

    if((*swtich2).gpioRead() == 1)
    {
        (*blueLed).gpioWrite(clear);
        (*swtich2).interruptClear();
    }

    if((*swtich2).gpioRead() == 0)
    {
        (*blueLed).gpioWrite(set);
        (*swtich2).interruptClear();
    }

}

extern "C" void _16_32_Bit_Timer_0A_Handler(void)
{
    if((*greenLed).gpioRead() == set)
    {
        (*greenLed).gpioWrite(clear);
        (*testTimer).interruptClear();
    }
    else if((*greenLed).gpioRead() == clear)
    {
        (*greenLed).gpioWrite(set);
        (*testTimer).interruptClear();
    }
    
}

void blink(void)
{    
    if((*greenLed).gpioRead() == set)
    {
        (*greenLed).gpioWrite(clear);
        (*testTimer).interruptClear();
    }
    else if((*greenLed).gpioRead() == clear)
    {
        (*greenLed).gpioWrite(set);
        (*testTimer).interruptClear();
    }
}

extern "C" void SystemInit(void)
{
    mySystemControl = new SystemControl(_80MHz);

    greenLed = new Gpio(PF3, output);
    blueLed = new Gpio(PF2, output);
    redLed = new Gpio(PF1, output);


}

int main(void)
{

    Nvic::disableInterrupts();
    swtich1 = new Gpio(PF4, input, 3);
    swtich2 = new Gpio(PF0, input, 3);
    testTimer = new GeneralPurposeTimer(periodic, shortTimer0, 80000000, down, concatenated, 3);
    (*testTimer).enableTimer();
    Nvic::enableInterrupts();

    // testTimer = new GeneralPurposeTimer(periodic, shortTimer0, 80000000, down, concatenated);
    // (*testTimer).enableTimer();
    
    // (*greenLed).gpioWrite(set);
    (*blueLed).gpioWrite(set);
    (*redLed).gpioWrite(set);
    
    

    while(1)
    {
        // (*testTimer).pollStatus(blink);
        Nvic::wfi();
    }

    delete mySystemControl;
    delete blueLed;
    delete redLed;
    delete swtich1;
    delete swtich2;
}

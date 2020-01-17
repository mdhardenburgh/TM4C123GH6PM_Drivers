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

Nvic* myNvic;
Sbc* mySbc;
SystemControl* systemController;

Gpio* blueLed;
Gpio* redLed;
Gpio* swtich1;
Gpio* swtich2;

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

extern "C" void SystemInit(void)
{
    myNvic = new Nvic();
    mySbc = new Sbc();
    systemController = new SystemControl(_80MHz);

    blueLed = new Gpio(PF2, output);
    redLed = new Gpio(PF1, output);
}

int main(void)
{
    (*myNvic).disableInterrupts();
    swtich1 = new Gpio(PF4, input, 3);
    swtich2 = new Gpio(PF0, input, 3);
    (*myNvic).enableInterrupts();

    (*blueLed).gpioWrite(set);
    (*redLed).gpioWrite(set);
    
    

    while(1)
    {
        (*myNvic).wfi(); // the -Os flag was causing issues
    }

    delete myNvic;
    delete mySbc;
    delete systemController;
    delete blueLed;
    delete redLed;
    delete swtich1;
    delete swtich2;
}

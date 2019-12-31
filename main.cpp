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

#include "register.h"
#include "corePeripherals/systick/systick.h"
#include "corePeripherals/nvic/nvic.h"
#include "corePeripherals/sbc/sbc.h"
#include "systemControl/systemControl.h"
#include "systemControl/systemClock.h"
#include "gpio/gpioControl.h"
#include "gpio/gpio.h"
#include "timer/generalPurposeTimer.h"
#include "timer/shortTimer.h"


int main(void)
{
    Systick mySistick();
    Nvic myNvic();
    Sbc mySbc();
    SystemClock myClock();
    Gpio blueLed(PF2, output);
    Gpio redLed(PF1, output);
    Gpio swtich2(PF0, input);
    Gpio swtich1(PF4, input);

    blueLed.gpioWrite(set);
    redLed.gpioWrite(set);

    while(1)
    {
        
        if(swtich1.gpioRead() == 1)
        {
            redLed.gpioWrite(clear);
        }

        if(swtich1.gpioRead() == 0)
        {
            redLed.gpioWrite(set);
        }

        if(swtich2.gpioRead() == 1)
        {
            blueLed.gpioWrite(set);
        }

        if(swtich2.gpioRead() == 0)
        {
            blueLed.gpioWrite(clear);
        }
    }
}

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

int readme = -1;
float voltageValue = -1;

uint32_t adcResolution;

Gpio greenLed;
Gpio blueLed;
Gpio redLed;

Gpio swtich1;
Gpio swtich2;

Gpio adcPin;

Pwm greenPwm;

uint32_t sequencerPriority = (uint32_t)ssPriority0::third|(uint32_t)ssPriority1::second|(uint32_t)ssPriority2::first|(uint32_t)ssPriority3::zeroth;
Adc testAdc;

// GeneralPurposeTimer myTimer;

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
    
    if(swtich1.read() == 1)
    {
        redLed.write((uint32_t)setORClear::clear);
        swtich1.interruptClear();
    }

    if(swtich1.read() == 0)
    {
        redLed.write((uint32_t)setORClear::set);
        swtich1.interruptClear();
    }

    if(swtich2.read() == 1)
    {
        blueLed.write((uint32_t)setORClear::clear);
        swtich2.interruptClear();
    }

    if(swtich2.read() == 0)
    {
        blueLed.write((uint32_t)setORClear::set);
        swtich2.interruptClear();
    }

}

// extern "C" void _16_32_Bit_Timer_0A_Handler(void)
// {
//     if(greenLed.read() == set)
//     {
//         greenLed.write(clear);
//         myTimer.clearInterrupt();
//     }

//     else if(greenLed.read() == clear)
//     {
//         greenLed.write(set);
//         myTimer.clearInterrupt();
//     } 
// }

void pollTest(void)
{

    (void)testAdc.getAdcSample(); 
    readme = testAdc.getAdcSample();
    testAdc.clearInterrupt();
}

extern "C" void SystemInit(void)
{
    SystemControl::initializeGPIOHB();
    SystemControl::initializeClock(_80MHz);

    greenLed.initialize((uint32_t)PF3::M1PWM7, output);
    blueLed.initialize((uint32_t)PF2::GPIO, output); 
    redLed.initialize((uint32_t)PF1::GPIO, output);
    adcPin.initialize((uint32_t)PE3::AIN0, input);

    greenPwm.initializeSingle(7, module1, 0xFFFF, 0xFFFF/2, 0x1, countDirectionPwm::down, (uint32_t)ACTZERO::invertPwm, true, (uint32_t)pwmUnitClockDivisor::_64);

    testAdc.initializeModule((uint32_t)adcModule::module0, sequencerPriority, false, false);

    adcResolution = Adc::getAdcResolution();
}
 
int main(void)
{
    
    Nvic::disableInterrupts();

    swtich1.initialize((uint32_t)PF4::GPIO, input, 3);
    swtich2.initialize((uint32_t)PF0::GPIO, input, 3);

    // myTimer.initializeForInterupt(periodic, shortTimer0, 80000000, down, concatenated, 3);
    // myTimer.enableTimer();

    Nvic::enableInterrupts();

    testAdc.initializeForPolling((uint32_t)sampleSequencer::SS3, (uint32_t)ssTriggerSource::processor, (uint32_t)ssInputSrc0::AIN0, (uint32_t)ssControl0::END0|(uint32_t)ssControl0::IE0, pollTest);
    testAdc.enableSampleSequencer();
    testAdc.initiateSampling();

    blueLed.write((uint32_t)setORClear::set);
    redLed.write((uint32_t)setORClear::set);
        
    while(1)
    {
        // Nvic::wfi();
        testAdc.pollStatus();
        voltageValue = (3.3/(1<<adcResolution))*readme;
        voltageValue = voltageValue;
    }

}

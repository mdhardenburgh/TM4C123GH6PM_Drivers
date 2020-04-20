/**
 * @file pwm.cpp
 * @brief TM4C123GH6PM PWM Driver Definition
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

#include "pwm.h"

/**
 * @brief empty constructor placeholder
 */
Pwm::Pwm()
{

}

/**
 * @brief empty deconstructor placeholder
 */
Pwm::~Pwm()
{

}

void Pwm::initializeSingle(pwmGenerator myPwmGen, pwmModule module, uint32_t period, uint32_t dutyCycle, countDirectionPwm countDir, uint32_t genOptions, pwmOutput output, bool enablePwmDiv, uint32_t divisor)
{
    initialize(myPwmGen, module, period, countDir, enablePwmDiv, divisor);
    
    //2. Configure the PWM generator for countdown mode with immediate updates to the parameters.
    
    //2b. Write the PWMnGENA register.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0GENA_OFFSET + (0x40 * myPwmGen) + (uint32_t)output)), genOptions, 0, 11+1, RW);

    //4. Set pulse width for pwmA
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CMPA_OFFSET + (0x40 * myPwmGen) + (uint32_t)output)), dutyCycle, 0, 15+1, RW);

    //6. Enable PWM
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + SRPWM_OFFSET), set, module, 1, RW);
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), 0x00001, 0, 18+1, RW);

    //7. Enable PWM output.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWMENABLE_OFFSET + (0x40 * myPwmGen))), 0x1, 0 + ((myPwmGen*2)+(((uint32_t)output)/4)), 1, RW); //(uint32_t)output >> 2
}


//Fix this

/**
 * @brief Initialize PWM with a specified period and duty cycle
 * @param clockCycles period in clock ticks/cycles
 * @param dutyCycle duty cycle of the PWM in clock ticks. Must be less than the
 *                  period
 */

void Pwm::initializePair(pwmGenerator myPwmGen, pwmModule module, uint32_t period, uint32_t dutyCycleA, uint32_t dutyCycleB, countDirectionPwm countDir, uint32_t genAOptions, uint32_t genBOptions, bool enablePwmDiv, uint32_t divisor)
{

    initialize(myPwmGen, module, period, countDir, enablePwmDiv, divisor);
    
    //2. Configure the PWM generator for countdown mode with immediate updates to the parameters.
    
    //2b. Write the PWMnGENA register.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0GENA_OFFSET + (0x40 * myPwmGen))), genAOptions, 0, 11+1, RW);

    //2c. Write the PWMnGENB register.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0GENB_OFFSET + (0x40 * myPwmGen))), genBOptions, 0, 11+1, RW);

    //4. Set pulse width for pwmA
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CMPA_OFFSET + (0x40 * myPwmGen))), dutyCycleA, 0, 15+1, RW);

    //5. Set pulse width for pwmB
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CMPB_OFFSET + (0x40 * myPwmGen))), dutyCycleB, 0, 15+1, RW);

    //6. Enable PWM
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + SRPWM_OFFSET), set, module, 1, RW);
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), 0x00001, 0, 18+1, RW);

    //7. Enable PWM output.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWMENABLE_OFFSET + (0x40 * myPwmGen))), 0x3, 0 + (2*myPwmGen), 2, RW); 
}

void Pwm::initialize(pwmGenerator myPwmGen, pwmModule module, uint32_t period, countDirectionPwm countDir, bool enablePwmDiv, uint32_t divisor)
{
    countDir = countDir;
    
    baseAddress = pwm0BaseAddress + (module * 0x1000);
    
    //0. Enable the clock for PWM
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCPWM_OFFSET)), set, module, 1, RW);
    while(Register::getRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + PRPWM_OFFSET), module, 1, RO) == 0)
    {
        //Ready??
    }

    if(enablePwmDiv == true)
    {
        //1a. Configure the Run-Mode Clock Configuration (RCC) register in the System Control module to use the PWM divide (USEPWMDIV).
        Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + RCC_OFFSET), set, 20, 1, RW);
        //1b. Set the divider (PWMDIV).
        Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + RCC_OFFSET), divisor, 17, (19-17)+1, RW);
    }

    if(enablePwmDiv == true)
    {
        //1a. Configure the Run-Mode Clock Configuration (RCC) register in the System Control module to use the PWM divide (USEPWMDIV).
        Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + RCC_OFFSET), set, 20, 1, RW);
        //1b. Set the divider (PWMDIV).
        Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + RCC_OFFSET), divisor, 17, (19-17)+1, RW);
    }

    //2. Configure the PWM generator for countdown mode with immediate updates to the parameters.

    //2a. Write the PWMnCTL register with a value of 0x0000.0000 to clear it.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), 0x00000, 0, 18+1, RW);

    //3. Set the period
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0LOAD_OFFSET + (0x40 * myPwmGen))), period, 0, 15+1, RW);
}

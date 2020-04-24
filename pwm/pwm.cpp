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

/**
 * If a zero or load event coincides with a compare A or compare B event, the 
 * zero or load action is taken and the compare A or compare B action is 
 * ignored. If a compare A event coincides with a compare B event, the compare 
 * B action is taken and the compare A action is ignored.
 */

//Clean up, add gen options using ORs of 12 bit numbers. Add documentation


/**
 * @brief Init single ended PWM with a specified duty cycle
 * 
 * @details MnPWMn Indicated on the signals description page indicates the
 *          module and PWM generator associated with the GPIO pin. For example
 *          M1PWM7 indicates module1 pwmPin 7.
 * 
 * @param pwmPin Output pin of the PWM module.
 * @param module that controlls the pin.
 * @param period of the PWM in clock ticks.
 * @param compA Number that in clock ticks that is compared against the 
 *              counter. When the counter matches what is in the comparator,
 *              It can trigger an action based on genOptions.
 * @param compB Same function. When the counter matches this number it can 
 *              trigger an action based upon genOptions
 * @param countDir Direction to count, either down (load from \c load value and
 *                 then count down to 0 to load again from the \c load value)
 *                 or count up then down.
 * @param genOptions Pwm generator control options. Can make the output go 
 *                   high or low based upon the options chosen using the ACTCMP
 *                   enums defined in the pwm.h file.
 * @param enablePwmDiv Enable the PWM peripheral clock pre-divider to 
 *                     pre-divide the system clock before it reaches the PWM
 *                     peripheral
 * @param divisor Binary divisor used to pre-divide the system clock. Must be
 *                enabled with the \c enablePwmDiv first
 */
void Pwm::initializeSingle(uint32_t pwmPin, pwmModule module, uint32_t period, uint32_t compA, uint32_t compB, countDirectionPwm countDir, uint32_t genOptions, bool enablePwmDiv, uint32_t divisor)
{
    initialize(pwmPin, module, period, countDir, enablePwmDiv, divisor);
    
    //2. Configure the PWM generator for countdown mode with immediate updates to the parameters.
    
    //2b. Write the PWMnGENn register. 
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0GENA_OFFSET + (0x40 * myPwmGen) + ((pwmPin%2) * 4))), genOptions, 0, 11+1, RW);

    //4. Set timer comparators
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CMPA_OFFSET + (0x40 * myPwmGen))), compA, 0, 15+1, RW);
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CMPB_OFFSET + (0x40 * myPwmGen))), compB, 0, 15+1, RW);

    //6. Enable PWM
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), set, 0, 1, RW);

    //7. Enable PWM output.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + PWMENABLE_OFFSET), set, 0 + ((myPwmGen*2)+(((pwmPin%2) * 4)/4)), 1, RW); //(uint32_t)output >> 2
}


//Fix this using init single. fix the documentation

/**
 * @brief Initialize PWM with a specified period and duty cycle
 * @param clockCycles period in clock ticks/cycles
 * @param dutyCycle duty cycle of the PWM in clock ticks. Must be less than the
 *                  period
 */

void Pwm::initializePair(uint32_t pwmPin, pwmModule module, uint32_t period, uint32_t dutyCycleA, uint32_t dutyCycleB, countDirectionPwm countDir, uint32_t genAOptions, uint32_t genBOptions, bool enablePwmDiv, uint32_t divisor)
{

    initialize(pwmPin, module, period, countDir, enablePwmDiv, divisor);
    
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
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), 0x00001, 0, 1, RW);

    //7. Enable PWM output.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWMENABLE_OFFSET + (0x40 * myPwmGen))), 0x3, 0 + (2*myPwmGen), 2, RW); 
}

//clean up, add count direction option

void Pwm::initialize(uint32_t pwmPin, pwmModule module, uint32_t period, countDirectionPwm countDir, bool enablePwmDiv, uint32_t divisor)
{    
    baseAddress = pwm0BaseAddress + (module * 0x1000);
    myPwmGen = pwmPin/2;
    
    //0. Enable the clock for PWM
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCPWM_OFFSET)), set, module, 1, RW);
    while(Register::getRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + PRPWM_OFFSET), module, 1, RO) == 0)
    {
        //Ready??
    }

    // Clear count register by reseting PWM

    Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + SRPWM_OFFSET), set, module, 1, RW);

    for(uint32_t i = 0; i < 100; i++)
    {
        //wait
    }

    Register::setRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + SRPWM_OFFSET), clear, module, 1, RW);

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

    //2. Configure the PWM generator for countdown mode with immediate updates to the parameters.

    //2a. Write the PWMnCTL register with a value of 0x0000.0000 to clear it.
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), clear, 0, 1, RW);
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), set, 2, 1, RW);

    //Set count direction
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0CTL_OFFSET + (0x40 * myPwmGen))), (uint32_t)countDir, 3, 1, RW);

    //3. Set the period
    Register::setRegisterBitFieldStatus((volatile uint32_t*)(baseAddress + (PWM0LOAD_OFFSET + (0x40 * myPwmGen))), period, 0, 15+1, RW);
}

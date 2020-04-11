/**
 * @file systemControl.cpp
 * @brief TM4C123GH6PM System Control Driver Definition
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

#include "systemControl.h"

/**
 * @brief empty constructor placeholder
 */
SystemControl::SystemControl()
{
    
}

/**
 * @brief empty deconstructor placeholder
 */
SystemControl::~SystemControl()
{
	
}

/**
 * @brief Initializes the system to use GPIO AHB for use instead of the APB
 */
void SystemControl::initializeGPIOHB(void)
{

	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET)), set, 0, 1, RW);
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET)), set, 1, 1, RW);
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET)), set, 2, 1, RW);
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET)), set, 3, 1, RW);
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET)), set, 4, 1, RW);
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET)), set, 5, 1, RW);
}

/**
 * @brief Initializes the PLL for system clock use
 *
 * @param frequency of the new system clock.
 */ 
void SystemControl::initializeClock(SYSDIV2 frequency)
{
	
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), set, 31, 1, RW); //0. Use RCC2.
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), set, 11, 1, RW); //1. Bypass PLL while initiializing
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC_OFFSET)), _16MHz_XTAL, 6, 5, RW); // 2. Select the crystal value and the oscillator source, configure for 16MHz crystal.
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), MOSC, 4, 3, RW);  //Confgure for main oscillator source.
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), clear, 13, 1, RW); // 3. Activate PLL by clearing PWRDN.
	
	/*
	 * 4.Set the desired system divider.
	 */

	/*
	 * Append the SYSDIV2LSB bit to the SYSDIV2 field to create a 7 bit divisor 
	 * using the 400 MHz PLL output.
	 */
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), set, 30, 1, RW);
	
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), ((frequency - 1) & 0x01), 22, 1, RW);
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), ((frequency - 1) >> 1), 23, 6, RW);

	while((Register::getRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RIS_OFFSET)), 6, 1, RO)) == 0)  // 5. Wait for the PLL to lock by polling PLLRIS.
	{

	}
	
	Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)), clear, 11, 1, RW); // 6. Enable use of the PLL by clearing BYPASS.
}


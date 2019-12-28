/**
 * @file systemClock.cpp
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/21/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019  Matthew Hardenburgh
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
 * Class implementation for the system clock unit for the Texas Instruments Tiva 
 * C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 */
#include "systemClock.h"

/**
 * Default PLL init frequency of 80MHz
 */
SystemClock::SystemClock()
{
	activatePll(_80MHz);
}

SystemClock::SystemClock(uint32_t frequency)
{
	activatePll(frequency);
}

SystemClock::~SystemClock()
{

}

void SystemClock::activatePll(uint32_t frequency)
{
	RCC2.setRegisterBitFieldStatus(RCC2_USERCC2, set); //0. Use RCC2.
	RCC2.setRegisterBitFieldStatus(RCC2_BYPASS2, set); //1. Bypass PLL while initiializing
	RCC.setRegisterBitFieldStatus(RCC_XTAL, _16MHz_XTAL); // 2. Select the crystal value and the oscillator source, configure for 16MHz crystal.
	RCC2.setRegisterBitFieldStatus(RCC2_OSCSRC2, MOSC);  //Confgure for main oscillator source.
	RCC2.setRegisterBitFieldStatus(RCC2_PWRDN2, clear); // 3. Activate PLL by clearing PWRDN.
	
	/**
	 * 4.Set the desired system divider.
	 */

	/**
	 * Append the SYSDIV2LSB bit to the SYSDIV2 field to create a 7 bit divisor 
	 * using the 400 MHz PLL output.
	 */
	RCC2.setRegisterBitFieldStatus(RCC2_DIV400, set);
	
	RCC2.setRegisterBitFieldStatus(RCC2_SYSDIV2LSB, ((frequency - 1) & 0x01));
	RCC2.setRegisterBitFieldStatus(RCC2_SYSDIV2, ((frequency - 1) >> 1));

	while(RIS.getRegisterBitFieldStatus(RIS_PLLLRIS) == 0)  // 5. Wait for the PLL to lock by polling PLLRIS.
	{

	}
	
	RCC2.setRegisterBitFieldStatus(RCC2_BYPASS2, clear); // 6. Enable use of the PLL by clearing BYPASS.
}
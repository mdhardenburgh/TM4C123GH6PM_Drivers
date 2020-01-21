/**
 * @file systemControl.cpp
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/15/2019
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
 * Class implementation for the system control unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Registers provided for legacy software support only are listed 
 * in “System Control Legacy Register Descriptions” on page 424.
 */

#include "systemControl.h"



SystemControl::SystemControl()
{
    
    Register GPIOHBCTL((volatile uint32_t*)(systemControlBase + GPIOHBCTL_OFFSET));
    bitField GPIOHBCTL_PORTn(0, 1, RW); //Port n Advanced High-Performance Bus


    for(int i = 0; i < 6; i++)
    {
        GPIOHBCTL_PORTn.bit = i;
        GPIOHBCTL.setRegisterBitFieldStatus(GPIOHBCTL_PORTn, set);
    }
    
}

SystemControl::SystemControl(SYSDIV2 frequency) : SystemControl()
{   
    Register RCC((volatile uint32_t*)(systemControlBase + RCC_OFFSET));
    Register RCC2((volatile uint32_t*)(systemControlBase + RCC2_OFFSET)); 
    Register RIS((volatile uint32_t*)(systemControlBase + RIS_OFFSET));

	bitField RCC2_USERCC2(31, 1, RW); //Use RCC2
	bitField RCC2_BYPASS2(11, 1, RW); //PLL Bypass 2
	bitField RCC_XTAL(6, 5, RW); //Crystal Value
	bitField RCC2_OSCSRC2(4, 3, RW); //Oscillator Source 2
	bitField RCC2_PWRDN2(13, 1, RW); //Power-Down PLL 2
	bitField RCC2_DIV400(30, 1, RW); //Divide PLL as 400 MHz versus 200 MHz
	bitField RCC2_SYSDIV2LSB(22, 1, RW); //Additional LSB for SYSDIV2
	bitField RCC2_SYSDIV2(23, 6, RW); //System Clock Divisor 2
	bitField RIS_PLLLRIS(6, 1, RO); //PLL Lock Raw Interrupt Status


	
    (RCC2).setRegisterBitFieldStatus(RCC2_USERCC2, set); //0. Use RCC2.
	(RCC2).setRegisterBitFieldStatus(RCC2_BYPASS2, set); //1. Bypass PLL while initiializing
	(RCC).setRegisterBitFieldStatus(RCC_XTAL, _16MHz_XTAL); // 2. Select the crystal value and the oscillator source, configure for 16MHz crystal.
	(RCC2).setRegisterBitFieldStatus(RCC2_OSCSRC2, MOSC);  //Confgure for main oscillator source.
	(RCC2).setRegisterBitFieldStatus(RCC2_PWRDN2, clear); // 3. Activate PLL by clearing PWRDN.
	
	/**
	 * 4.Set the desired system divider.
	 */

	/**
	 * Append the SYSDIV2LSB bit to the SYSDIV2 field to create a 7 bit divisor 
	 * using the 400 MHz PLL output.
	 */
	(RCC2).setRegisterBitFieldStatus(RCC2_DIV400, set);
	
	(RCC2).setRegisterBitFieldStatus(RCC2_SYSDIV2LSB, ((frequency - 1) & 0x01));
	(RCC2).setRegisterBitFieldStatus(RCC2_SYSDIV2, ((frequency - 1) >> 1));

	while((RIS).getRegisterBitFieldStatus(RIS_PLLLRIS) == 0)  // 5. Wait for the PLL to lock by polling PLLRIS.
	{

	}
	
	(RCC2).setRegisterBitFieldStatus(RCC2_BYPASS2, clear); // 6. Enable use of the PLL by clearing BYPASS.
}

SystemControl::~SystemControl()
{
	
}




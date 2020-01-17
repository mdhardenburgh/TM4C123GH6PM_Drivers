/**
 * @file nvic.c
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 11/13/2019
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
 * Class implementation for the nested vector interrupt controller for the 
 * Texas Instruments Tiva C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * This section lists and describes the NVIC registers, in numerical order by address offset.
 * 
 * The NVIC registers can only be fully accessed from privileged mode, but 
 * interrupts can be pended while in unprivileged mode by enabling the 
 * Configuration and Control (CFGCTRL) register. Any other unprivileged mode 
 * access causes a bus fault.
 * 
 * Ensure software uses correctly aligned register accesses. The processor does 
 * not support unaligned accesses to NVIC registers.
 * 
 * An interrupt can enter the pending state even if it is disabled.
 * 
 * Before programming the VTABLE register to relocate the vector table, ensure 
 * the vector table entries of the new vector table are set up for fault 
 * handlers, NMI, and all enabled exceptions such as interrupts. For more 
 * information, see page 163.
 * 
 */

#include "nvic.h"

Nvic::Nvic()
{
    //Init NVIC here
}

Nvic::~Nvic()
{

}

void Nvic::activateInterrupt(interrupt myInterrupt, uint32_t priority)
{
    if((myInterrupt < 139) && (priority < 8))
    {
        PRIORITY_INT.bit = ((myInterrupt % nvicRegisterOffset) * 8) + 5;
        INT.bit = myInterrupt % 32;

        PRI = new Register((volatile uint32_t*)(corePeripheralBase + PRI_OFFSET + (nvicRegisterOffset * (myInterrupt / nvicRegisterOffset))));
        EN = new Register((volatile uint32_t*)(corePeripheralBase + EN_OFFSET + (nvicRegisterOffset * (myInterrupt / 32))));

        (*PRI).setRegisterBitFieldStatus(PRIORITY_INT, priority);
        (*EN).setRegisterBitFieldStatus(INT, (uint32_t)set);

        delete PRI;
        delete EN;
    }
    
    else
    {
        return;
    }
}

#pragma GCC push_options
#pragma GCC optimize("O0")
uint32_t Nvic::disableInterrupts(void)
{
    volatile uint32_t ui32Ret;
    asm volatile(

        "mrs     r0, PRIMASK\n"
        "cpsid   i\n"
        "bx      lr\n"
        : "=r" (ui32Ret)
    );

    return(ui32Ret);
}
#pragma GCC pop_options


#pragma GCC push_options
#pragma GCC optimize("O0")
uint32_t Nvic::enableInterrupts(void)
{
    volatile uint32_t ui32Ret;
    asm volatile(

        "mrs     r0, PRIMASK\n"
        "cpsie   i\n"
        "bx      lr\n"
        : "=r" (ui32Ret)
    );

    return(ui32Ret);
}
#pragma GCC pop_options


#pragma GCC push_options
#pragma GCC optimize("O0")
void Nvic::wfi(void)
{
    //
    // Wait for the next interrupt.
    //
    asm volatile(

        "wfi     \n"
        "bx    lr\n"
    );
    
}
#pragma GCC pop_options
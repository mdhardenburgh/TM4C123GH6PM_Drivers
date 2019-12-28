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

uint32_t Nvic::getInterruptRegisterSettingStatus(interrupt myInterrupt, registerGroup group)
{
    //return(registerTable[(myInterrupt / 32) + group].getRegisterBitFieldStatus((myInterrupt % 32), INT.bitWidth, INT.permission));
    INT.bit = myInterrupt % 32;
    return(registerTable[(myInterrupt / 32) + group].getRegisterBitFieldStatus(INT));

}


void Nvic::setInterruptRegisterSetting(interrupt myInterrupt, registerGroup group)
{
    if(group != ACTIVE)
    {
        INT.bit = myInterrupt % 32;
        registerTable[(myInterrupt / 32) + group].setRegisterBitFieldStatus(INT, set);
    }

    else
    {
        return;
    }
    
}


uint32_t Nvic::getInterruptPriorityStatus(interrupt interruptNumber)
{
    if((interruptNumber < 139))
    {
        INT.bit = (((interruptNumber % 4) * 8) + 5);
        return(priorityRegisters[interruptNumber/4].getRegisterBitFieldStatus(INT));
    }


    else
    {
        return(INT32_MAX);
    }
}

void Nvic::setInterruptPriority(interrupt interruptNumber, uint32_t priority)
{
    if((interruptNumber < 139) && (priority < 8))
    {
        INT.bit = ((interruptNumber % 4) * 8) + 5;
        priorityRegisters[interruptNumber/4].setRegisterBitFieldStatus(INT, priority);
    }

    else
    {
        return;
    }
    
}

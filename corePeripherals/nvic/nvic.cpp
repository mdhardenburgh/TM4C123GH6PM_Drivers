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

const uint32_t Nvic::ENn_OFFSET[5] = {EN0_OFFSET, EN1_OFFSET, EN2_OFFSET, EN3_OFFSET, EN4_OFFSET};
const uint32_t Nvic::DISn_OFFSET[5] = {DIS0_OFFSET, DIS1_OFFSET, DIS2_OFFSET, DIS3_OFFSET, DIS4_OFFSET};
const uint32_t Nvic::PENDn_OFFSET[5] = {PEND0_OFFSET, PEND1_OFFSET, PEND2_OFFSET, PEND3_OFFSET, PEND4_OFFSET};
const uint32_t Nvic::UNPENDn_OFFSET[5] = {UNPEND0_OFFSET, UNPEND1_OFFSET, UNPEND2_OFFSET, UNPEND3_OFFSET, UNPEND4_OFFSET};
const uint32_t Nvic::ACTIVEn_OFFSET[5] = {ACTIVE0_OFFSET, ACTIVE1_OFFSET, ACTIVE2_OFFSET, ACTIVE3_OFFSET, ACTIVE4_OFFSET};
const uint32_t Nvic::PRIn_OFFSET[35] = {PRI0_OFFSET, PRI1_OFFSET, PRI2_OFFSET, PRI3_OFFSET, PRI4_OFFSET, PRI5_OFFSET,
                                        PRI6_OFFSET, PRI7_OFFSET, PRI8_OFFSET, PRI9_OFFSET, PRI10_OFFSET, PRI11_OFFSET,
                                        PRI12_OFFSET, PRI13_OFFSET, PRI14_OFFSET, PRI15_OFFSET, PRI16_OFFSET, PRI17_OFFSET,
                                        PRI18_OFFSET, PRI19_OFFSET, PRI20_OFFSET, PRI21_OFFSET, PRI22_OFFSET, PRI23_OFFSET,
                                        PRI24_OFFSET, PRI25_OFFSET, PRI26_OFFSET, PRI27_OFFSET, PRI28_OFFSET, PRI29_OFFSET,
                                        PRI30_OFFSET, PRI31_OFFSET, PRI32_OFFSET, PRI33_OFFSET, PRI34_OFFSET};

Nvic::Nvic()
{

}

Nvic::~Nvic()
{

}

/**
 * @param myInterrupt 
 */
void Nvic::activateInterrupt(interrupt myInterrupt, uint32_t priority)
{
    if((myInterrupt < 139) && (priority < 8))
    {
        bitField PRIORITY_INT(((myInterrupt % nvicRegisterOffset) * 8) + 5, 3, RW);
        bitField INT((uint32_t)(myInterrupt % 32), 1, RW);

        Register PRI((volatile uint32_t*)(corePeripheralBase + PRIn_OFFSET[myInterrupt/4]));
        Register EN((volatile uint32_t*)(corePeripheralBase + ENn_OFFSET[myInterrupt/32]));

        (PRI).setRegisterBitFieldStatus(PRIORITY_INT, priority);
        (EN).setRegisterBitFieldStatus(INT, (uint32_t)set);

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
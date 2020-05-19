/**
 * @file nvic.cpp
 * @brief TM4C123GH6PM NVIC Driver Definition
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


/**
 * @brief empty constructor placeholder
 */
Nvic::Nvic()
{

}

/**
 * @brief empty deconstructor placeholder
 */
Nvic::~Nvic()
{

}

/**
 * @brief Activates an interrupt
 * @param myInterrupt coresponds to the interrupt number of the interrupt that 
 *        you want to activate.
 * @param priority of the interrput that you want to activate
 */
void Nvic::activateInterrupt(interrupt myInterrupt, uint32_t priority)
{
    
    if((myInterrupt < 139) && (priority < 8))
    {   
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(corePeripheralBase + PRIn_OFFSET[myInterrupt/4])), priority, ((myInterrupt % nvicRegisterOffset) * 8) + 5, 3, RW);
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(corePeripheralBase + ENn_OFFSET[myInterrupt/32])), (uint32_t)setORClear::set, (uint32_t)(myInterrupt % 32), 1, RW);

    }
    
    else
    {
        return;
    }
}

/**
 * @brief Disables interrupt globally
 * @details Used when configuring interrupts at initial bootup
 * @return A dummy value needed to get code to work, generally cast the return 
 *         value to void.
 */
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

/**
 * @brief Enables interrupt globally
 * @details Used when configuring interrupts at initial bootup
 * @return A dummy value needed to get code to work, generally cast the return 
 *         value to void.
 */
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

/**
 * @brief Puts processer into sleep mode as configured by the system control 
 *        module and waits for another interrupt.
 */
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
/**
 * @file generalPurposeTimer.cpp
 * @brief TM4C123GH6PM General Purpose Timer Driver Definition
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

#include "generalPurposeTimer.h"

const uint32_t GeneralPurposeTimer::timerBaseAddresses[12] = {_16_32_bit_Timer_0_base, _16_32_bit_Timer_1_base, _16_32_bit_Timer_2_base, _16_32_bit_Timer_3_base, _16_32_bit_Timer_4_base, _16_32_bit_Timer_5_base,
    _32_64_bit_Wide_Timer_0_base, _32_64_bit_Wide_Timer_1_base, _32_64_bit_Wide_Timer_2_base, _32_64_bit_Wide_Timer_3_base, _32_64_bit_Wide_Timer_4_base, _32_64_bit_Wide_Timer_5_base};

const uint32_t GeneralPurposeTimer::PPnTIMER_OFFSET[2] = {PPTIMER_OFFSET, PPWTIMER_OFFSET};
const uint32_t GeneralPurposeTimer::SRnTIMER_OFFSET[2] = {SRTIMER_OFFSET, SRWTIMER_OFFSET};
const uint32_t GeneralPurposeTimer::RCGCnTIMER_OFFSET[2] = {RCGCTIMER_OFFSET, RCGCWTIMER_OFFSET};
const uint32_t GeneralPurposeTimer::SCGCnTIMER_OFFSET[2] = {SCGCTIMER_OFFSET, SCGCWTIMER_OFFSET};
const uint32_t GeneralPurposeTimer::DCGCnTIMER_OFFSET[2] = {DCGCTIMER_OFFSET, DCGCWTIMER_OFFSET};
const uint32_t GeneralPurposeTimer::PRnTIMER_OFFSET[2] = {PRTIMER_OFFSET, PRWTIMER_OFFSET}; 

const uint32_t GeneralPurposeTimer::GPTMTnMR_OFFSET[2] = {GPTMTAMR_OFFSET, GPTMTBMR_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnILR_OFFSET[2] = {GPTMTAILR_OFFSET, GPTMTBILR_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnMATCHR_OFFSET[2] = {GPTMTAMATCHR_OFFSET, GPTMTBMATCHR_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnPR_OFFSET[2] = {GPTMTAPR_OFFSET, GPTMTBPR_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnPMR_OFFSET[2] = {GPTMTAPMR_OFFSET, GPTMTBPMR_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnR_OFFSET[2] = {GPTMTAR_OFFSET, GPTMTBR_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnV_OFFSET[2] = {GPTMTAV_OFFSET, GPTMTBV_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnPS_OFFSET[2] = {GPTMTAPS_OFFSET, GPTMTBPS_OFFSET};
const uint32_t GeneralPurposeTimer::GPTMTnPV_OFFSET[2] = {GPTMTAPV_OFFSET, GPTMTBPV_OFFSET};

/**
 * @brief empty constructor placeholder
 */
GeneralPurposeTimer::GeneralPurposeTimer()
{
  
}

/**
 * @brief Initializes a timer in which the status of the timer is polled,
 *        rather than an NVIC interrupt being generated.
 * 
 * @param mode of the timer. Can be one-shot, periodic, RTC, input edge count,
 *        time capture, or PWM
 * @param block of the timer used. There are six A&B short timers and six A&B
 *        wide timers.
 * @param period of the timer in clock ticks
 * @param direction of the timer count
 * @param use of timer. Timer A, Timer B, or concatonated
 *  
 */
GeneralPurposeTimer::GeneralPurposeTimer(timerMode mode, timerBlock block, uint32_t period, countDirection dir, timerUse use)
{
    (*this).use = use;
    (*this).mode = mode;
    period = period - 1;
    baseAddress = timerBaseAddresses[block];


    //0. Enable the clock for the timer
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCnTIMER_OFFSET[block/6])), set, (block%6), 1, RW);
    while(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + PRnTIMER_OFFSET[block/6])), (block%6), 1, RO) == 0)
    {
        //Ready?
    }

    //1. Disbale the timer before making any changes
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMCTL_OFFSET)), clear, (use%2)*8, 1, RW); //disable the timer
    if((mode == oneShot) || (mode == periodic))
    {
        interruptBit = ((use == timerB) ? 8 : 0);
        
        //2. Configure for single or concatenated mode 
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMCFG_OFFSET)), ((use == concatenated) ? 0x0 : 0x4), 0, 3, RW);

        //3. Configure for One-Shot or Periodic mode
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTnMR_OFFSET[(use%2)])), mode + 1, 0, 2, RW);

        //4. Optional configuration. Configure for count direction
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTnMR_OFFSET[(use%2)])), dir, 4, 1, RW);
        
        //5. Interval load
        if(use == timerA)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTAILR_OFFSET)), period, 0, 16, RW);
        }

        else if(use == timerB)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTBILR_OFFSET)), period, 0, 16, RW);
        }

        else if(use == concatenated)
        {
            //concatenated short timer
            if((block/6) == 0)
            {
                // GPTMTAILR.setRegisterBitFieldStatus(GPTMTAILR_TAILR, period);
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTAILR_OFFSET)), period, 0, 32, RW); //This is where the problems begin with reg B
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTAPR_OFFSET)), clear, 0, 8, RW);

            }

            //concatenated wide timer
            else
            {
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTBILR_OFFSET)), ((period & 0xFFFFFFFF00000000) >> 32), 0, 32, RW);
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMTAILR_OFFSET)), (period & 0x00000000FFFFFFFF), 0, 32, RW);
            }
        }

    }

    else if(mode == realTimeClock)
    {
        interruptBit = 3;
    }

    else if(mode == edgeCount)
    {
        interruptBit = ((use == timerB) ? 9 : 1);
    }

    else if(mode == edgeTime)
    {
        interruptBit = ((use == timerB) ? 10 : 2);
    }

    else if(mode == PWM)
    {
        interruptBit = ((use == timerB) ? 10 : 2);
    }

    interruptClear();

}

/**
 * @brief Initializes a timer in which an NVIC interrupt is generated and 
 *        the status does not have to be constantly polled.
 * 
 * @param mode of the timer. Can be one-shot, periodic, RTC, input edge count,
 *        time capture, or PWM
 * @param block of the timer used. There are six A&B short timers and six A&B
 *        wide timers.
 * @param period of the timer in clock ticks
 * @param direction of the timer count
 * @param use of timer. Timer A, Timer B, or concatonated
 * @param interuptPriority of the interrupt. Lower numbers have higher priority.
 *  
 */
GeneralPurposeTimer::GeneralPurposeTimer(timerMode mode, timerBlock block, uint32_t period, countDirection dir, timerUse use, uint32_t interuptPriority) : GeneralPurposeTimer(mode, block, period, dir, use)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMIMR_OFFSET)), set, interruptBit, 1, RW);

    switch (block)
    {
        case shortTimer0:
            Nvic::activateInterrupt((use == timerB) ? _16_32_Bit_Timer_0B_Interrupt : _16_32_Bit_Timer_0A_Interrupt, interuptPriority);
            break;

        case shortTimer1:
            Nvic::activateInterrupt((use == timerB) ? _16_32_Bit_Timer_1B_Interrupt : _16_32_Bit_Timer_1A_Interrupt, interuptPriority);
            break;
        
        case shortTimer2:
            Nvic::activateInterrupt((use == timerB) ? _16_32_Bit_Timer_2B_Interrupt : _16_32_Bit_Timer_2A_Interrupt, interuptPriority);
            break;

        case shortTimer3:
            Nvic::activateInterrupt((use == timerB) ? _16_32_Bit_Timer_3B_Interrupt : _16_32_Bit_Timer_3A_Interrupt, interuptPriority);
            break;

        case shortTimer4:
            Nvic::activateInterrupt((use == timerB) ? _16_32_Bit_Timer_4B_Interrupt : _16_32_Bit_Timer_4A_Interrupt, interuptPriority);
            break;

        case shortTimer5:
            Nvic::activateInterrupt((use == timerB) ? _16_32_Bit_Timer_5B_Interrupt : _16_32_Bit_Timer_5A_Interrupt, interuptPriority);
            break;

        case wideTimer0:
            Nvic::activateInterrupt((use == timerB) ? _32_64_Bit_Timer_0B_Interrupt : _32_64_Bit_Timer_0A_Interrupt, interuptPriority);
            break;

        case wideTimer1:
            Nvic::activateInterrupt((use == timerB) ? _32_64_Bit_Timer_1B_Interrupt : _32_64_Bit_Timer_1A_Interrupt, interuptPriority);
            break;

        case wideTimer2:
            Nvic::activateInterrupt((use == timerB) ? _32_64_Bit_Timer_2B_Interrupt : _32_64_Bit_Timer_2A_Interrupt, interuptPriority);
            break;

        case wideTimer3:
            Nvic::activateInterrupt((use == timerB) ? _32_64_Bit_Timer_3B_Interrupt : _32_64_Bit_Timer_3A_Interrupt, interuptPriority);
            break;

        case wideTimer4:
            Nvic::activateInterrupt((use == timerB) ? _32_64_Bit_Timer_4B_Interrupt : _32_64_Bit_Timer_4A_Interrupt, interuptPriority);
            break;

        case wideTimer5:
            Nvic::activateInterrupt((use == timerB) ? _32_64_Bit_Timer_5B_Interrupt : _32_64_Bit_Timer_5A_Interrupt, interuptPriority);
            break;
        
        default:
            Nvic::activateInterrupt(_16_32_Bit_Timer_0A_Interrupt, interuptPriority);
            break;
    }
    
}

/**
 * @brief empty deconstructor placeholder
 */
GeneralPurposeTimer::~GeneralPurposeTimer()
{

}

/**
 * @brief To be used in a poll loop. Checks the Raw Interrupt Status of the timer.
 * 
 * @param action to be taken if the RIS is set.
 */
void GeneralPurposeTimer::pollStatus(void(*action)(void))
{
    
    if(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMRIS_OFFSET)), interruptBit, 1, RO) == set)
    {
        action();
    }

}

/**
 * @brief clears the interrupt status
 */
void GeneralPurposeTimer::interruptClear(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMICR_OFFSET)), set, interruptBit, 1, RW1C);
}

/**
 * @brief timers are disabled by default during intialization. This function
 *        Enables the timers.
 */
void GeneralPurposeTimer::enableTimer(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + GPTMCTL_OFFSET)), set, (use%2)*8, 1, RW);
}
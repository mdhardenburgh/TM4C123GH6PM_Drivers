/**
 * @file systick.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 11/10/2019
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
 * Driver header for the Texas Instruments Tiva C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * This section lists and describes the System Timer registers, in numerical 
 * order by address offset.
 * 
 */

#ifndef SYSTICK_H
#define SYSTICK_H

#include "../../register/register.h"

const uint32_t STCTRL_OFFSET = 0x010;
const uint32_t STRELOAD_OFFSET = 0x014;
const uint32_t STCURRENT_OFFSET = 0x018;

class Systick
{
    public:
        Systick();
        //Systick(uint32_t frequency);
        ~Systick();

    private:


        /**
         * Description: Count Flag
         * 
         * Value Description
         * 0_____The SysTick timer has not counted to 0 since the last time
         * ______this bit was read.
         * 
         * 1_____The SysTick timer has counted to 0 since the last time this bit 
         * ______was read.
         * 
         * This bit is cleared by a read of the register or if the 
         * STCURRENT register is written with any value.
         * 
         * If read by the debugger using the DAP, this bit is cleared only if 
         * the MasterType bit in the AHB-AP Control Register is clear. Otherwise,
         * the COUNT bit is not changed by the debugger read. See the ARM®
         * Debug Interface V5 Architecture Specification for more information on
         * MasterType.
         */
        // bitField STCTRL_COUNT{16, 1, RO};

        /**
         * Description: Clock Source
         * 
         * Value Description
         * 0_____Precision internal oscillator (PIOSC) divided by 4
         * 
         * 1_____System clock
         */
        // bitField STCTRL_CLK_SRC{2, 1, RW};

        /**
         * Description: Interrupt Enable
         * 
         * Value Description
         * 0_____Interrupt generation is disabled. Software can use the COUNT 
         * ______bit to determine if the counter has ever reached 0.
         * 
         * 1_____An interrupt is generated to the NVIC when SysTick counts to 0.
         */
        // bitField STCTRL_INTEN{1, 1, RW};

        /**
         * Description: Enable
         * 
         * Value Description
         * 0_____The counter is disabled.
         * 
         * 1______Enables SysTick to operate in a multi-shot way. That is, the
         * _______counter loads the RELOAD value and begins counting down. On 
         * _______reaching 0, the COUNT bit is set and an interrupt is generated 
         * _______if enabled by INTEN. The counter then loads the RELOAD value 
         * _______again and begins counting.
         */
        // bitField STCTRL_ENABLE{0, 1, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Reload Value
         * 
         * Value to load into the SysTick Current Value (STCURRENT) register 
         * when the counter reaches 0.
         */
        // bitField STRELOAD_RELOAD{0, 24, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Current Value
         * 
         * This field contains the current value at the time the register is 
         * accessed. No read-modify-write protection is provided, so change with care.
         * 
         * This register is write-clear. Writing to it with any value clears the 
         * register. Clearing this register also clears the COUNT bit of the 
         * STCTRL register.
         */
        // bitField STCURRENT_CURRENT{0, 24, RW};

};

#endif //SYSTICK_H

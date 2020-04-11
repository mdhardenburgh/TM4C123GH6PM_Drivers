/**
 * @file systick.h
 * @brief TM4C123GH6PM Systick Driver Declaration
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
 */

/**
 * @class Systick
 * @brief TM4C123GH6PM Systick Driver
 * 
 * @section systickDescription Systick Description
 * 
 * Systick is a system timer used for thread switching. Systick is genrally not
 * used for general purpose timing. The Systick timer is a 24-bit clear-on-write, 
 * decrementing, wrap-on-zero counter.
 * 
 * For more detailed information on Systick please see page 123 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection systickRegisterDescription Systick Register Description
 * 
 * The Systick class contains a list of Systick registers listed as an offset relative
 * to the hexadecimal base address of Core Peripherals 0xE000E000.
 * 
 */



#ifndef SYSTICK_H
#define SYSTICK_H

#include "../../register/register.h"

class Systick
{
    public:
        Systick();
        //Systick(uint32_t frequency);
        ~Systick();

    private:

        static const uint32_t STCTRL_OFFSET = 0x010; // 0x010 STCTRL RW 0x0000.0004 SysTick Control and Status Register 138
        static const uint32_t STRELOAD_OFFSET = 0x014; // 0x014 STRELOAD RW - SysTick Reload Value Register 140
        static const uint32_t STCURRENT_OFFSET = 0x018; // 0x018 STCURRENT RWC - SysTick Current Value Register 141
};
#endif //SYSTICK_H

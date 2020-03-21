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

        static const uint32_t STCTRL_OFFSET = 0x010;
        static const uint32_t STRELOAD_OFFSET = 0x014;
        static const uint32_t STCURRENT_OFFSET = 0x018;
};
#endif //SYSTICK_H

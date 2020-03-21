/**
 * @file fpu.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 11/11/2019
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
 * Class header for the floating point unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * Floating-Point Unit (FPU) Register Descriptions
 * 
 * This section lists and describes the Floating-Point Unit (FPU) registers,
 * in numerical order by address offset.
 */

#ifndef FPU_H
#define FPU_H

#include "../../register/register.h"



class Fpu
{
    public:
        Fpu();
        ~Fpu();
    
    private:

        static const uint32_t CPAC_OFFSET = 0xD88;
        static const uint32_t FPCC_OFFSET = 0xF34;
        static const uint32_t FPCA_OFFSET = 0xF38;
        static const uint32_t FPDSC_OFFSET = 0xF3C;
    
};
#endif //FPU
/**
 * @file mpu.h
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
 * Driver header for the memory protection unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * This section lists and describes the Memory Protection Unit (MPU) registers, 
 * in numerical order by address offset.
 * 
 * The MPU registers can only be accessed from privileged mode.
 */

#ifndef MPU_H
#define MPU_H

#include <stdint-gcc.h>
#include <stddef.h>
#include <math.h>
#include "../../register/register.h"


class Mpu
{
    public:
        Mpu();
        ~Mpu();

    private:
    
        static const uint32_t MPUTYPE_OFFSET = 0xD90;
        static const uint32_t MPUCTRL_OFFSET = 0xD94;
        static const uint32_t MPUNUMBER_OFFSET = 0xD98;
        static const uint32_t MPUBASE_OFFSET = 0xD9C;
        static const uint32_t MPUBASE1_OFFSET = 0xDA4;
        static const uint32_t MPUBASE2_OFFSET = 0xDAC;
        static const uint32_t MPUBASE3_OFFSET = 0xDB4;
        static const uint32_t MPUATTR_OFFSET = 0xDA0;  
        static const uint32_t MPUATTR1_OFFSET = 0xDA8;
        static const uint32_t MPUATTR2_OFFSET = 0xDB0;
        static const uint32_t MPUATTR3_OFFSET = 0xDB8;
};
#endif //MPU
/**
 * @file sbc.h
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
 * Driver header for the system block controller for the Texas Instruments Tiva
 * C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Block (SCB) Register Descriptions
 * 
 * This section lists and describes the System Control Block (SCB) registers, 
 * in numerical order by address offset. The SCB registers can only be accessed 
 * from privileged mode.
 * 
 * All registers must be accessed with aligned word accesses except for the 
 * FAULTSTAT and SYSPRI1-SYSPRI3 registers, which can be accessed with byte or 
 * aligned halfword or word accesses. The processor does not support unaligned 
 * accesses to system control block registers.
 */

#ifndef SBC_H
#define SBC_H

#include <stdint-gcc.h>
#include <stddef.h>
#include "../../register/register.h"


class Sbc
{
    public:
        Sbc();
        ~Sbc();
        

    private:

        static const uint32_t ACTLR_OFFSET = 0x008;
        static const uint32_t CPUID_OFFSET = 0xD00; 
        static const uint32_t INTCTRL_OFFSET = 0xD04;
        static const uint32_t VTABLE_OFFSET = 0xD08;
        static const uint32_t APINT_OFFSET = 0xD0C;
        static const uint32_t SYSCTRL_OFFSET = 0xD10;
        static const uint32_t CFGCTRL_OFFSET = 0xD14;
        static const uint32_t SYSPRI1_OFFSET = 0xD18;
        static const uint32_t SYSPRI2_OFFSET = 0xD1C;
        static const uint32_t SYSPRI3_OFFSET = 0xD20;
        static const uint32_t SYSHNDCTRL_OFFSET = 0xD24;
        static const uint32_t FAULTSTAT_OFFSET = 0xD28;
        static const uint32_t HFAULTSTAT_OFFSET = 0xD2C;       
        static const uint32_t MMADDR_OFFSET = 0xD34;
        static const uint32_t FAULTADDR_OFFSET = 0xD38;
};
#endif //SBC
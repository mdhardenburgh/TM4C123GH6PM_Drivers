/**
 * @file sbc.h
 * @brief TM4C123GH6PM SBC Driver Declaration
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
 * @class Sbc
 * @brief TM4C123GH6PM SBC Driver
 * 
 * @section sbcDescription SBC Description
 * 
 * The SBC Provides system implementation information and system control, 
 * including configuration, control, and reporting of system exceptions.
 * 
 * For more detailed information on the SBC please see page 125 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection sbcRegisterDescription SBC Register Description
 * 
 * The SBC class contains a list of SBC registers listed as an offset relative
 * to the hexadecimal base address of Core Peripherals 0xE000E000.
 * 
 * This Class lists and describes the System Control Block (SCB) registers, 
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

        static const uint32_t ACTLR_OFFSET = 0x008; // 0x008 ACTLR RW 0x0000.0000 Auxiliary Control 157
        static const uint32_t CPUID_OFFSET = 0xD00; // 0xD00 CPUID RO 0x410F.C241 CPU ID Base 159
        static const uint32_t INTCTRL_OFFSET = 0xD04; // 0xD04 INTCTRL RW 0x0000.0000 Interrupt Control and State 160
        static const uint32_t VTABLE_OFFSET = 0xD08; // 0xD08 VTABLE RW 0x0000.0000 Vector Table Offset 163
        static const uint32_t APINT_OFFSET = 0xD0C; // 0xD0C APINT RW 0xFA05.0000 Application Interrupt and Reset Control 164
        static const uint32_t SYSCTRL_OFFSET = 0xD10; // 0xD10 SYSCTRL RW 0x0000.0000 System Control 166
        static const uint32_t CFGCTRL_OFFSET = 0xD14; // 0xD14 CFGCTRL RW 0x0000.0200 Configuration and Control 168
        static const uint32_t SYSPRI1_OFFSET = 0xD18; // 0xD18 SYSPRI1 RW 0x0000.0000 System Handler Priority 1 170
        static const uint32_t SYSPRI2_OFFSET = 0xD1C; // 0xD1C SYSPRI2 RW 0x0000.0000 System Handler Priority 2 171
        static const uint32_t SYSPRI3_OFFSET = 0xD20; // 0xD20 SYSPRI3 RW 0x0000.0000 System Handler Priority 3 172
        static const uint32_t SYSHNDCTRL_OFFSET = 0xD24; // 0xD24 SYSHNDCTRL RW 0x0000.0000 System Handler Control and State 173
        static const uint32_t FAULTSTAT_OFFSET = 0xD28; // 0xD28 FAULTSTAT RW1C 0x0000.0000 Configurable Fault Status 177
        static const uint32_t HFAULTSTAT_OFFSET = 0xD2C; // 0xD2C HFAULTSTAT RW1C 0x0000.0000 Hard Fault Status 183      
        static const uint32_t MMADDR_OFFSET = 0xD34; // 0xD34 MMADDR RW - Memory Management Fault Address 184
        static const uint32_t FAULTADDR_OFFSET = 0xD38; // 0xD38 FAULTADDR RW - Bus Fault Address 185
};
#endif //SBC
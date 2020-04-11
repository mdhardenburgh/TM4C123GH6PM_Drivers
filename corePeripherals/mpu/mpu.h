/**
 * @file mpu.h
 * @brief TM4C123GH6PM MPU Driver Declaration
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
 * @class Mpu
 * @brief TM4C123GH6PM MPU Driver
 * 
 * @section mpuDescription MPU Description
 * 
 * The TM4C123GH6PM microcontroller supports the standard ARMv7 Protected
 * Memory System Architecture model. The MPU provides full support for 
 * protection regions, overlapping protection regions, access permissions, and 
 * exporting memory attributes to the system.
 * 
 * The MPU divides the memory map into a number of regions and defines the 
 * location, size, access permissions, and memory attributes of each region. 
 * The MPU supports independent attribute settings for each region, overlapping 
 * regions, and export of memory attributes to the system.
 * 
 * For more detailed information on the MPU please see page 125 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection mpuRegisterDescription MPU Register Description
 * 
 * The MPU class contains a list of MPU registers listed as an offset relative
 * to the hexadecimal base address of Core Peripherals 0xE000E000.
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
    
        static const uint32_t MPUTYPE_OFFSET = 0xD90; // 0xD90 MPUTYPE RO 0x0000.0800 MPU Type 186
        static const uint32_t MPUCTRL_OFFSET = 0xD94; // 0xD94 MPUCTRL RW 0x0000.0000 MPU Control 187
        static const uint32_t MPUNUMBER_OFFSET = 0xD98; // 0xD98 MPUNUMBER RW 0x0000.0000 MPU Region Number 189
        static const uint32_t MPUBASE_OFFSET = 0xD9C; // 0xD9C MPUBASE RW 0x0000.0000 MPU Region Base Address 190
        static const uint32_t MPUBASE1_OFFSET = 0xDA4; // 0xDA0 MPUATTR RW 0x0000.0000 MPU Region Attribute and Size 192
        static const uint32_t MPUBASE2_OFFSET = 0xDAC; // 0xDA4 MPUBASE1 RW 0x0000.0000 MPU Region Base Address Alias 1 190
        static const uint32_t MPUBASE3_OFFSET = 0xDB4; // 0xDA8 MPUATTR1 RW 0x0000.0000 MPU Region Attribute and Size Alias 1 192
        static const uint32_t MPUATTR_OFFSET = 0xDA0; // 0xDAC MPUBASE2 RW 0x0000.0000 MPU Region Base Address Alias 2 190
        static const uint32_t MPUATTR1_OFFSET = 0xDA8; // 0xDB0 MPUATTR2 RW 0x0000.0000 MPU Region Attribute and Size Alias 2 192
        static const uint32_t MPUATTR2_OFFSET = 0xDB0; // 0xDB4 MPUBASE3 RW 0x0000.0000 MPU Region Base Address Alias 3 190
        static const uint32_t MPUATTR3_OFFSET = 0xDB8; // 0xDB8 MPUATTR3 RW 0x0000.0000 MPU Region Attribute and Size Alias 3 192
};
#endif //MPU
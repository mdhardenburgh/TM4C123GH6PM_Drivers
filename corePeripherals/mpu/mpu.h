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

const uint32_t MPUTYPE_OFFSET = 0xD90;
const uint32_t MPUCTRL_OFFSET = 0xD94;
const uint32_t MPUNUMBER_OFFSET = 0xD98;
const uint32_t MPUBASE_OFFSET = 0xD9C;
const uint32_t MPUBASE1_OFFSET = 0xDA4;
const uint32_t MPUBASE2_OFFSET = 0xDAC;
const uint32_t MPUBASE3_OFFSET = 0xDB4;
const uint32_t MPUATTR_OFFSET = 0xDA0;  
const uint32_t MPUATTR1_OFFSET = 0xDA8;
const uint32_t MPUATTR2_OFFSET = 0xDB0;
const uint32_t MPUATTR3_OFFSET = 0xDB8;

class Mpu
{
    public:
        Mpu();
        ~Mpu();

    private:
    


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /**
         * Description: Number of I Regions
         * 
         * This field indicates the number of supported MPU instruction regions.
         * This field always contains 0x00. The MPU memory map is unified and
         * is described by the DREGION field.
         */
        // bitField MPUTYPE_IREGION{16, 8, RO};

        /**
         * Description: Number of D Regions
         * 
         * Value Description
         * 0x08__Indicates there are eight supported MPU data regions.
         */
        // bitField MPUTYPE_DREGION{8, 8, RO};

        /**
         * Description: Separate or Unified MPU
         * 
         * Value Description
         * 0_____Indicates the MPU is unified.
         */
        // bitField MPUTYPE_SEPARATE{0, 1, RO};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: MPU Default Region
         * 
         * This bit enables privileged software access to the default memory map.
         * 
         * Value Description
         * 0_____If the MPU is enabled, this bit disables use of the default
         * ______memory map. Any memory access to a location not covered by any
         * ______enabled region causes a fault.
         * 
         * 1_____If the MPU is enabled, this bit enables use of the default 
         * ______memory map as a background region for privileged software 
         * ______accesses.
         * 
         * When this bit is set, the background region acts as if it is region 
         * number -1. Any region that is defined and enabled has priority over 
         * this default map.
         * 
         * If the MPU is disabled, the processor ignores this bit.
         */
        // bitField MPUCTRL_PRIVDEFEN{2, 1, RW};

        /**
         * Description: MPU Enabled During Faults
         * 
         * This bit controls the operation of the MPU during hard fault, NMI, 
         * and FAULTMASK handlers.
         * 
         * Value Description
         * 0_____The MPU is disabled during hard fault, NMI, and FAULTMASK
         * ______handlers, regardless of the value of the ENABLE bit.
         * 
         * 1_____The MPU is enabled during hard fault, NMI, and FAULTMASK
         * ______handlers.
         * 
         * When the MPU is disabled and this bit is set, the resulting behavior 
         * is unpredictable.
         */
        // bitField MPUCTRL_HFNMIENA{1, 1, RW};

        /**
         * Description: MPU Enable
         * 
         * Value Description
         * 0_____The MPU is disabled.
         * 
         * 1_____The MPU is enabled.
         * 
         * When the MPU is disabled and the HFNMIENA bit is set, the resulting
         * behavior is unpredictable.
         */
        // bitField MPUCTRL_ENABLE{0, 1, RW};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: MPU Region to Access
         * 
         * This field indicates the MPU region referenced by the MPUBASE and
         * MPUATTR registers. The MPU supports eight memory regions.
         */
        // bitField MPUNUMBER_NUMBER{0, 3, RW};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Base Address Mask
         * 
         * Bits 31:N in this field contain the region base address. 
         * The value of N depends on the region size, as shown above. The 
         * remaining bits (N-1):5 are reserved.
         * 
         * Software should not rely on the value of a reserved bit. To provide
         * compatibility with future products, the value of a reserved bit 
         * should be preserved across a read-modify-write operation.
         */
        // bitField MPUBASE_ADDR{5, 27, RW};

        /**
         * Description: Region Number Valid
         * 
         * Value Description
         * 0_____The MPUNUMBER register is not changed and the processor updates 
         * ______the base address for the region specified in the MPUNUMBER 
         * ______register and ignores the value of the REGION field.
         * 
         * 1_____The MPUNUMBER register is updated with the value of the REGION 
         * ______field and the base address is updated for the region specified 
         * ______in the REGION field.
         * 
         * This bit is always read as 0.
         */
        // bitField MPUBASE_VALID{4, 1, WO};

        /**
         * Description: Region Number
         * 
         * On a write, contains the value to be written to the MPUNUMBER register.
         * On a read, returns the current region number in the MPUNUMBER register.
         */
        // bitField MPUBASE_REGION{0, 3, RW};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Instruction Access Disable
         * 
         * Value Description
         * 0_____Instruction fetches are enabled.
         * 
         * 1_____Instruction fetches are disabled.
         */
        // bitField MPUATTR_XN{28, 1, RW};

        /**
         * Description: Access Privilege
         * 
         * For information on using this bit field, see Table 3-5 on page 129.
         */
        // bitField MPUATTR_AP{24, 3, RW};

        /**
         * Description: Type Extension Mask
         * 
         * For information on using this bit field, see Table 3-3 on page 128.
         */
        // bitField MPUATTR_TEX{19, 3, RW};

        /**
         * Description: Shareable
         * 
         * For information on using this bit, see Table 3-3 on page 128.
         */
        // bitField MPUATTR_S{18, 1, RW};

        /**
         * Description: Cacheable
         * 
         * For information on using this bit, see Table 3-3 on page 128.
         */
        // bitField MPUATTR_C{17, 1, RW};

        /**
         * Description: Bufferable
         * 
         * For information on using this bit, see Table 3-3 on page 128.
         */
        // bitField MPUATTR_B{16, 1, RW};

        /**
         * Description: Subregion Disable Bits
         * 
         * Value Description
         * 0_____The corresponding subregion is enabled.
         * 
         * 1_____The corresponding subregion is disabled.
         * 
         * Region sizes of 128 bytes and less do not support subregions. When
         * writing the attributes for such a region, configure the SRD field as 
         * 0x00. See the section called “Subregions” on page 128 for more 
         * information.
         */
        // bitField MPUATTR_SRD{8, 8, RW};

        /**
         * Description: Region Size Mask
         * 
         * The SIZE field defines the size of the MPU memory region specified by
         * the MPUNUMBER register. Refer to Table 3-10 on page 192 for more
         * information.
         */
        // bitField MPUATTR_SIZE{1, 5, RW};

        /**
         * Description: Region Enable
         * 
         * Value Description
         * 0_____The region is disabled.
         * 
         * 1_____The region is enabled.
         */
        // bitField MPUATTR_ENABLE{0, 1, RW};

};


#endif //MPU
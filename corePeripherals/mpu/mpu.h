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
#include "../../register.h"

class Mpu
{
    public:
        Mpu();
        ~Mpu();

    private:
        /**
         * Cortex-M4 Peripheral SysTick, NVIC, MPU, FPU and SCB registers.
         * These register definitions begin on page 134 of the TM4C123GH6PM Datasheet.
         */
        const uint32_t corePeripheralBase = 0xE000E000;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         * Register 80: MPU Type (MPUTYPE), offset 0xD90
         * 
         * Note: This register can only be accessed from privileged mode.
         * 
         * The MPUTYPE register indicates whether the MPU is present, and if so, how
         * many regions it supports.
         */
        Register* MPUTYPE;

        /**
         * Register 81: MPU Control (MPUCTRL), offset 0xD94
         * 
         * Note: This register can only be accessed from privileged mode. 
         * 
         * The MPUCTRL register enables the MPU, enables the default memory map 
         * background region, and enables use of the MPU when in the hard fault, 
         * Non-maskable Interrupt (NMI), and Fault Mask Register (FAULTMASK) 
         * escalated handlers.
         * 
         * When the ENABLE and PRIVDEFEN bits are both set:
         * 
         *     ■ For privileged accesses, the default memory map is as described 
         *       in “Memory Model” on page 92. Any access by privileged software 
         *       that does not address an enabled memory region behaves as 
         *       defined by the default memory map.
         *     
         *     ■ Any access by unprivileged software that does not address an 
         *       enabled memory region causes a memory management fault.
         * 
         * Execute Never (XN) and Strongly Ordered rules always apply to the 
         * System Control Space regardless of the value of the ENABLE bit.
         * 
         * When the ENABLE bit is set, at least one region of the memory map 
         * must be enabled for the system to function unless the PRIVDEFEN bit 
         * is set. If the PRIVDEFEN bit is set and no regions are enabled, then 
         * only privileged software can operate.
         * 
         * When the ENABLE bit is clear, the system uses the default memory map, 
         * which has the same memory attributes as if the MPU is not implemented 
         * (see Table 2-5 on page 95 for more information). The default memory 
         * map applies to accesses from both privileged and unprivileged software.
         * 
         * When the MPU is enabled, accesses to the System Control Space and 
         * vector table are always permitted. Other areas are accessible based 
         * on regions and whether PRIVDEFEN is set.
         * 
         * Unless HFNMIENA is set, the MPU is not enabled when the processor is 
         * executing the handler for an exception with priority –1 or –2. These 
         * priorities are only possible when handling a hard fault or NMI 
         * exception or when FAULTMASK is enabled. Setting the HFNMIENA bit 
         * enables the MPU when operating with these two priorities.
         */
        Register* MPUCTRL;

        /**
         * Register 82: MPU Region Number (MPUNUMBER), offset 0xD98
         * 
         * Note: This register can only be accessed from privileged mode.
         * 
         * The MPUNUMBER register selects which memory region is referenced by 
         * the MPU Region Base Address (MPUBASE) and MPU Region Attribute and 
         * Size (MPUATTR) registers. Normally, the required region number 
         * should be written to this register before accessing the MPUBASE or 
         * the MPUATTR register. However, the region number can be changed by 
         * writing to the MPUBASE register with the VALID bit set (see page 190). 
         * This write updates the value of the REGION field.
         */
        Register* MPUNUMBER;

        /**
         * Register 83: MPU Region Base Address (MPUBASE), offset 0xD9C
         * Register 84: MPU Region Base Address Alias 1 (MPUBASE1), offset 0xDA4
         * Register 85: MPU Region Base Address Alias 2 (MPUBASE2), offset 0xDAC
         * Register 86: MPU Region Base Address Alias 3 (MPUBASE3), offset 0xDB4
         * 
         * Note: This register can only be accessed from privileged mode. 
         * 
         * The MPUBASE register defines the base address of the MPU region selected by 
         * the MPU Region Number (MPUNUMBER) register and can update the value of the 
         * MPUNUMBER register. To change the current region number and update the 
         * MPUNUMBER register, write the MPUBASE register with the VALID bit set.
         * 
         * The ADDR field is bits 31:N of the MPUBASE register. Bits (N-1):5 are 
         * reserved. The region size, as specified by the SIZE field in the MPU Region 
         * Attribute and Size (MPUATTR) register, defines the value of N where:
         * 
         * N = Log 2 (Region size in bytes)
         * 
         * If the region size is configured to 4 GB in the MPUATTR register, there is no 
         * valid ADDR field. In this case, the region occupies the complete memory map, 
         * and the base address is 0x0000.0000.
         * 
         * The base address is aligned to the size of the region. For example, a 64-KB 
         * region must be aligned on a multiple of 64 KB, for example, at 0x0001.0000 or 
         * 0x0002.0000.
         */
        Register* MPUBASE;
        Register* MPUBASE1;
        Register* MPUBASE2;
        Register* MPUBASE3;

        /**
         * Register 87: MPU Region Attribute and Size (MPUATTR), offset 0xDA0
         * Register 88: MPU Region Attribute and Size Alias 1 (MPUATTR1), offset 0xDA8
         * Register 89: MPU Region Attribute and Size Alias 2 (MPUATTR2), offset 0xDB0
         * Register 90: MPU Region Attribute and Size Alias 3 (MPUATTR3), offset 0xDB8
         * 
         * Note: This register can only be accessed from privileged mode. 
         * 
         * The MPUATTR register defines the region size and memory attributes of the MPU 
         * region specified by the MPU Region Number (MPUNUMBER) register and enables 
         * that region and any subregions.
         * 
         * The MPUATTR register is accessible using word or halfword accesses with the 
         * most-significant halfword holding the region attributes and the 
         * least-significant halfword holds the region size and the region and subregion 
         * enable bits.
         * 
         * The MPU access permission attribute bits, XN, AP, TEX, S, C, and B, control 
         * access to the corresponding memory region. If an access is made to an area of 
         * memory without the required permissions, then the MPU generates a permission 
         * fault.
         * 
         * The SIZE field defines the size of the MPU memory region specified by the 
         * MPUNUMBER register as follows:
         * 
         * (Region size in bytes) = 2^(SIZE+1)
         * 
         * The smallest permitted region size is 32 bytes, corresponding to a SIZE value 
         * of 4. Table 3-10 on page 192 gives example SIZE values with the corresponding 
         * region size and value of N in the MPU Region Base Address (MPUBASE) register.
         * 
         * Table 3-10. Example SIZE Field Values
         * ________________________________________________________________________________
         * | SIZE Encoding  | Region Size | Value of N (a)        | Note                  |
         * |----------------|-------------|-----------------------|-----------------------|
         * | 00100b (0x4)   | 32 B        | 5                     | Minimum permitted size|
         * |----------------|-------------|-----------------------|-----------------------|
         * | 01001b (0x9)   | 1 KB        | 10                    |                       |
         * |----------------|-------------|-----------------------|-----------------------|
         * | 10011b (0x13)  | 1 MB        | 20                    |                       |
         * |----------------|-------------|-----------------------|-----------------------|
         * | 11101b (0x1D)  | 1 GB        | 30                    |                       |
         * |----------------|-------------|-----------------------|-----------------------|
         * | 11111b (0x1F)  | 4 GB        | No valid ADDR field   | Maximum possible size |
         * |                |             | in MPUBASE; the region|                       |
         * |                |             | occupies the complete |                       |
         * |                |             | memory map.           |                       |
         * |________________|_____________|_______________________|_______________________|
         * a. Refers to the N parameter in the MPUBASE register (see page 190).
         * 
         */
        Register* MPUATTR;
        Register* MPUATTR1;
        Register* MPUATTR2;
        Register* MPUATTR3;













        /**
         * Description: Number of I Regions
         * 
         * This field indicates the number of supported MPU instruction regions.
         * This field always contains 0x00. The MPU memory map is unified and
         * is described by the DREGION field.
         */
        bitField MPUTYPE_IREGION{16, 8, RO};

        /**
         * Description: Number of D Regions
         * 
         * Value Description
         * 0x08__Indicates there are eight supported MPU data regions.
         */
        bitField MPUTYPE_DREGION{8, 8, RO};

        /**
         * Description: Separate or Unified MPU
         * 
         * Value Description
         * 0_____Indicates the MPU is unified.
         */
        bitField MPUTYPE_SEPARATE{0, 1, RO};

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
        bitField MPUCTRL_PRIVDEFEN{2, 1, RW};

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
        bitField MPUCTRL_HFNMIENA{1, 1, RW};

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
        bitField MPUCTRL_ENABLE{0, 1, RW};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: MPU Region to Access
         * 
         * This field indicates the MPU region referenced by the MPUBASE and
         * MPUATTR registers. The MPU supports eight memory regions.
         */
        bitField MPUNUMBER_NUMBER{0, 3, RW};

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
        bitField MPUBASE_ADDR{5, 27, RW};

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
        bitField MPUBASE_VALID{4, 1, WO};

        /**
         * Description: Region Number
         * 
         * On a write, contains the value to be written to the MPUNUMBER register.
         * On a read, returns the current region number in the MPUNUMBER register.
         */
        bitField MPUBASE_REGION{0, 3, RW};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Instruction Access Disable
         * 
         * Value Description
         * 0_____Instruction fetches are enabled.
         * 
         * 1_____Instruction fetches are disabled.
         */
        bitField MPUATTR_XN{28, 1, RW};

        /**
         * Description: Access Privilege
         * 
         * For information on using this bit field, see Table 3-5 on page 129.
         */
        bitField MPUATTR_AP{24, 3, RW};

        /**
         * Description: Type Extension Mask
         * 
         * For information on using this bit field, see Table 3-3 on page 128.
         */
        bitField MPUATTR_TEX{19, 3, RW};

        /**
         * Description: Shareable
         * 
         * For information on using this bit, see Table 3-3 on page 128.
         */
        bitField MPUATTR_S{18, 1, RW};

        /**
         * Description: Cacheable
         * 
         * For information on using this bit, see Table 3-3 on page 128.
         */
        bitField MPUATTR_C{17, 1, RW};

        /**
         * Description: Bufferable
         * 
         * For information on using this bit, see Table 3-3 on page 128.
         */
        bitField MPUATTR_B{16, 1, RW};

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
        bitField MPUATTR_SRD{8, 8, RW};

        /**
         * Description: Region Size Mask
         * 
         * The SIZE field defines the size of the MPU memory region specified by
         * the MPUNUMBER register. Refer to Table 3-10 on page 192 for more
         * information.
         */
        bitField MPUATTR_SIZE{1, 5, RW};

        /**
         * Description: Region Enable
         * 
         * Value Description
         * 0_____The region is disabled.
         * 
         * 1_____The region is enabled.
         */
        bitField MPUATTR_ENABLE{0, 1, RW};

};


#endif //MPU
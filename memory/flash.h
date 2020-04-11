/**
 * @file flash.h
 * @brief TM4C123GH6PM Flash Driver Declaration
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
 * @class Flash
 * @brief TM4C123GH6PM Flash Driver
 * 
 * @section flashDescription Flash Description
 * 
 * The TM4C123GH6PM microcontroller has 256KB of on chip Flash. The Flash 
 * controller has a user-friendly interface for memory programming. Flash is 
 * organized in 1KB eraseable blocks with memory protection on a 2KB block 
 * basis.
 * 
 * For more detailed information on the PWM please see page 524 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 */

#ifndef FLASH_H
#define FLASH_H

#include "../systemControl/systemControl.h"

class Flash
{
    public:
        Flash();
        ~Flash();
    
    private:

        static const uint32_t flashBase = 0x400FD000;

        static const uint32_t flashWriteOffset = 0x4;

        static const uint32_t FMA_OFFSET = 0x000; // 0x000 FMA RW 0x0000.0000 Flash Memory Address 542
        static const uint32_t FMD_OFFSET = 0x004; // 0x004 FMD RW 0x0000.0000 Flash Memory Data 543
        static const uint32_t FMC_OFFSET = 0x008; // 0x008 FMC RW 0x0000.0000 Flash Memory Control 544
        static const uint32_t FCRIS_OFFSET = 0x00C; // 0x00C FCRIS RO 0x0000.0000 Flash Controller Raw Interrupt Status 546
        static const uint32_t FCIM_OFFSET = 0x010; // 0x010 FCIM RW 0x0000.0000 Flash Controller Interrupt Mask 549
        static const uint32_t FCMISC_OFFSET = 0x014; // 0x014 FCMISC RW1C 0x0000.0000 Flash Controller Masked Interrupt Status and Clear 551
        static const uint32_t FMC2_OFFSET = 0x020; // 0x020 FMC2 RW 0x0000.0000 Flash Memory Control 2 554
        static const uint32_t FWBVAL_OFFSET = 0x030; // 0x030 FWBVAL RW 0x0000.0000 Flash Write Buffer Valid 555
        
        /*
         * Register 9: Flash Write Buffer n (FWBn), offset 0x100 - 0x17C
         * 
         * These 32 registers hold the contents of the data to be written into 
         * the Flash memory on a buffered Flash memory write operation. The 
         * offset selects one of the 32-bit registers. Only FWBn registers that 
         * have been updated since the preceding buffered Flash memory write 
         * operation are written into the Flash memory, so it is not necessary 
         * to write the entire bank of registers in order to write 1 or 2 words. 
         * The FWBn registers are written into the Flash memory with the FWB0 
         * register corresponding to the address contained in FMA. FWB1 is 
         * written to the address FMA+0x4 etc. Note that only data bits that are 
         * 0 result in the Flash memory being modified. A data bit that is 1 
         * leaves the content of the Flash memory bit at its previous value
         */
        static const uint32_t FWBn_OFFSET = 0x100; // FWBn RW 0x0000.0000 Flash Write Buffer n 556 0x100 - 0x17C
        static const uint32_t FSIZE_OFFSET = 0xFC0; // 0xFC0 FSIZE RO 0x0000.007F Flash Size 557
        static const uint32_t SSIZE_OFFSET = 0xFC4; // 0xFC4 SSIZE RO 0x0000.007F SRAM Size 558
        static const uint32_t ROMSWMAP_OFFSET = 0xFCC; // 0xFCC ROMSWMAP RO 0x0000.0000 ROM Software Map 559

        /*
         * Memory Register Descriptions (System Control Offset)
         * 
         * The remainder of this section lists and describes the registers that 
         * reside in the System Control address space, in numerical order by 
         * address offset. Registers in this section are relative to the System 
         * Control base address of 0x400F.E000.
         */


        static const uint32_t RMCTL_OFFSET = 0x0F0; // 0x0F0 RMCTL RW1C - ROM Control 577
        static const uint32_t FMPRE0_OFFSET = 0x130; // 0x130 FMPRE0 RW 0xFFFF.FFFF Flash Memory Protection Read Enable 0 578
        static const uint32_t FMPRE0_ALIAS_OFFSET = 0x200; // 0x200 FMPRE0 RW 0xFFFF.FFFF Flash Memory Protection Read Enable 0 578
        static const uint32_t FMPPE0_OFFSET = 0x134; // 0x134 FMPPE0 RW 0xFFFF.FFFF Flash Memory Protection Program Enable 0 579
        static const uint32_t FMPPE0_ALIAS_OFFSET = 0x400; // 0x400 FMPPE0 RW 0xFFFF.FFFF Flash Memory Protection Program Enable 0 579
        static const uint32_t BOOTCFG_OFFSET = 0x1D0; // 0x1D0 BOOTCFG RO 0xFFFF.FFFE Boot Configuration 581
        static const uint32_t USER_REG0_OFFSET = 0x1E0; // 0x1E0 USER_REG0 RW 0xFFFF.FFFF User Register 0 584
        static const uint32_t USER_REG1_OFFSET = 0x1E4; // 0x1E4 USER_REG1 RW 0xFFFF.FFFF User Register 1 584
        static const uint32_t USER_REG2_OFFSET = 0x1E8; // 0x1E8 USER_REG2 RW 0xFFFF.FFFF User Register 2 584
        static const uint32_t USER_REG3_OFFSET = 0x1EC; // 0x1EC USER_REG3 RW 0xFFFF.FFFF User Register 3 584
        static const uint32_t FMPRE1_OFFSET = 0x204; // 0x204 FMPRE1 RW 0xFFFF.FFFF Flash Memory Protection Read Enable 1 578
        static const uint32_t FMPRE2_OFFSET = 0x208; // 0x208 FMPRE2 RW 0xFFFF.FFFF Flash Memory Protection Read Enable 2 578
        static const uint32_t FMPRE3_OFFSET = 0x20C; // 0x20C FMPRE3 RW 0xFFFF.FFFF Flash Memory Protection Read Enable 3 578
        static const uint32_t FMPPE1_OFFSET = 0x404; // 0x404 FMPPE1 RW 0xFFFF.FFFF Flash Memory Protection Program Enable 1 579
        static const uint32_t FMPPE2_OFFSET = 0x408; // 0x408 FMPPE2 RW 0xFFFF.FFFF Flash Memory Protection Program Enable 2 579
        static const uint32_t FMPPE3_OFFSET = 0x40C; // 0x40C FMPPE3 RW 0xFFFF.FFFF Flash Memory Protection Program Enable 3 579

};

#endif//FLASH_H
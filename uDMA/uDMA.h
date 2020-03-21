/**
 * @file uDMA.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/17/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019 Matthew Hardenburgh
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
 * Class header for the system control unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Registers provided for legacy software support only are listed 
 * in “System Control Legacy Register Descriptions” on page 424.
 * 
 * μDMA Register Descriptions
 * 
 * The register addresses given are relative to the μDMA base address of 0x400F.F000.
 * 
 */

#ifndef uDMA_H
#define uDMA_H

#include "../systemControl/systemControl.h"

class uDMA
{
    public:
        uDMA();
        ~uDMA();

    private:

        static const uint32_t uDMA_Base = 0x400FF000;

        static const uint32_t PPDMA_OFFSET = 0x30C; //0x30C PPDMA RO 0x0000.0001 Micro Direct Memory Access Peripheral Present 293
        static const uint32_t SRDMA_OFFSET = 0x50C; //0x50C SRDMA RW 0x0000.0000 Micro Direct Memory Access Software Reset 316
        static const uint32_t RCGCDMA_OFFSET = 0x60C; //0x60C RCGCDMA RW 0x0000.0000 Micro Direct Memory Access Run Mode Clock Gating Control 342
        static const uint32_t SCGCDMA_OFFSET = 0x70C; //0x70C SCGCDMA RW 0x0000.0000 Micro Direct Memory Access Sleep Mode Clock Gating Control 364
        static const uint32_t DCGCDMA_OFFSET = 0x80C; //0x80C DCGCDMA RW 0x0000.0000 Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control 386
        static const uint32_t PRDMA_OFFSET = 0xA0C; //0xA0C PRDMA RO 0x0000.0000 Micro Direct Memory Access Peripheral Ready 408

};


#endif //uDMA_H
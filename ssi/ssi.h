/**
 * @file ssi.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/18/2019
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
 * Class header for the system control unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Registers provided for legacy software support only are listed 
 * in “System Control Legacy Register Descriptions” on page 424.
 * 
 * Synchronous Serial Interface (SSI) Register Descriptions
 * 
 * The remainder of this section lists and describes the SSI registers, in 
 * numerical order by address offset.
 */

#ifndef SSI_H
#define SSI_H

#include "../systemControl/systemControl.h"

class Ssi : SystemControl
{
    public:
        Ssi();
        ~Ssi();

    private:
        const uint32_t ssi0BaseAddress = 0x40008000;
        const uint32_t ssi1BaseAddress = 0x40009000;
        const uint32_t ssi2BaseAddress = 0x4000A000;
        const uint32_t ssi3BaseAddress = 0x4000B000;

        const uint32_t PPSSI_OFFSET = 0x31C;
        const uint32_t SRSSI_OFFSET = 0x51C;
        const uint32_t RCGCSSI_OFFSET = 0x61C;
        const uint32_t SCGCSSI_OFFSET = 0x71C;
        const uint32_t DCGCSSI_OFFSET = 0x81C;
        const uint32_t PRSSI_OFFSET = 0xA1C;

/**********************System Control Register Descriptions********************/

        Register* PPSSI; //0x31C PPSSI RO 0x0000.000F Synchronous Serial Interface Peripheral Present 297
        Register* SRSSI; //0x51C SRSSI RW 0x0000.0000 Synchronous Serial Interface Software Reset 320
        Register* RCGCSSI; //0x61C RCGCSSI RW 0x0000.0000 Synchronous Serial Interface Run Mode Clock Gating Control 346
        Register* SCGCSSI; //0x71C SCGCSSI RW 0x0000.0000 Synchronous Serial Interface Sleep Mode Clock Gating Control 368
        Register* DCGCSSI; //0x81C DCGCSSI RW 0x0000.0000 Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control 390
        Register* PRSSI; //0xA1C PRSSI RO 0x0000.0000 Synchronous Serial Interface Peripheral Ready 412

/**************************System Control BitFields****************************/

        bitField PPSSI_P3{3, 1, RO}; //SSI Module 3 Present
        bitField PPSSI_P2{2, 1, RO}; //SSI Module 2 Present
        bitField PPSSI_P1{1, 1, RO}; //SSI Module 1 Present
        bitField PPSSI_P0{0, 1, RO}; //SSI Module 0 Present

        bitField SRSSI_R3{3, 1, RW}; //SSI Module 3 Software Reset
        bitField SRSSI_R2{2, 1, RW}; //SSI Module 2 Software Reset
        bitField SRSSI_R1{1, 1, RW}; //SSI Module 1 Software Reset
        bitField SRSSI_R0{0, 1, RW}; //SSI Module 0 Software Reset

        bitField RCGCSSI_R3{3, 1, RW}; //SSI Module 3 Run Mode Clock Gating Control
        bitField RCGCSSI_R2{2, 1, RW}; //SSI Module 2 Run Mode Clock Gating Control
        bitField RCGCSSI_R1{1, 1, RW}; //SSI Module 1 Run Mode Clock Gating Control
        bitField RCGCSSI_R0{0, 1, RW}; //SSI Module 0 Run Mode Clock Gating Control

        bitField SCGCSSI_S3{3, 1, RW}; //SSI Module 3 Sleep Mode Clock Gating Control
        bitField SCGCSSI_S2{2, 1, RW}; //SSI Module 2 Sleep Mode Clock Gating Control
        bitField SCGCSSI_S1{1, 1, RW}; //SSI Module 1 Sleep Mode Clock Gating Control
        bitField SCGCSSI_S0{0, 1, RW}; //SSI Module 0 Sleep Mode Clock Gating Control

        bitField DCGCSSI_D3{3, 1, RW}; //SSI Module 3 Deep-Sleep Mode Clock Gating Control
        bitField DCGCSSI_D2{2, 1, RW}; //SSI Module 2 Deep-Sleep Mode Clock Gating Control
        bitField DCGCSSI_D1{1, 1, RW}; //SSI Module 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCSSI_D0{0, 1, RW}; //SSI Module 0 Deep-Sleep Mode Clock Gating Control

        bitField PRSSI_R3{3, 1, RO}; //SSI Module 3 Peripheral Ready
        bitField PRSSI_R2{2, 1, RO}; //SSI Module 2 Peripheral Ready
        bitField PRSSI_R1{1, 1, RO}; //SSI Module 1 Peripheral Ready
        bitField PRSSI_R0{0, 1, RO}; //SSI Module 0 Peripheral Ready

};

#endif // SSI_H
/**
 * @file i2c.h
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
 * Inter-Integrated Circuit (I2C) Interface Register Descriptions
 * 
 */

#ifndef I2C_H
#define I2C_H

#include "../systemControl/systemControl.h"

class I2c : SystemControl
{
    public:
        I2c();
        ~I2c();

    private:
        const uint32_t i2c0BaseAddress = 0x40020000;
        const uint32_t i2c1BaseAddress = 0x40021000;
        const uint32_t i2c2BaseAddress = 0x40022000;
        const uint32_t i2c3BaseAddress = 0x40023000;

/**********************System Control Register Descriptions********************/

        Register PPI2C{(volatile uint32_t*)(systemControlBase + 0x320)}; //0x320 PPI2C RO 0x0000.000F Inter-Integrated Circuit Peripheral Present 299
        Register SRI2C{(volatile uint32_t*)(systemControlBase + 0x520)}; //0x520 SRI2C RW 0x0000.0000 Inter-Integrated Circuit Software Reset 322
        Register RCGCI2C{(volatile uint32_t*)(systemControlBase + 0x620)}; //0x620 RCGCI2C RW 0x0000.0000 Inter-Integrated Circuit Run Mode Clock Gating Control 348
        Register SCGCI2C{(volatile uint32_t*)(systemControlBase + 0x720)}; //0x720 SCGCI2C RW 0x0000.0000 Inter-Integrated Circuit Sleep Mode Clock Gating Control 370
        Register DCGCI2C{(volatile uint32_t*)(systemControlBase + 0x820)}; //0x820 DCGCI2C RW 0x0000.0000 Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control 392
        Register PRI2C{(volatile uint32_t*)(systemControlBase + 0xA20)}; //0xA20 PRI2C RO 0x0000.0000 Inter-Integrated Circuit Peripheral Ready 414

/**************************System Control BitFields****************************/

        bitField PPI2C_P5{5, 1, RO}; //I2C Module 5 Present
        bitField PPI2C_P4{4, 1, RO}; //I2C Module 4 Present
        bitField PPI2C_P3{3, 1, RO}; //I2C Module 3 Present
        bitField PPI2C_P2{2, 1, RO}; //I2C Module 2 Present
        bitField PPI2C_P1{1, 1, RO}; //I2C Module 1 Present
        bitField PPI2C_P0{0, 1, RO}; //I2C Module 0 Present

        bitField SRI2C_R3{3, 1, RW}; //I2C Module 3 Software Reset
        bitField SRI2C_R2{2, 1, RW}; //I2C Module 2 Software Reset
        bitField SRI2C_R1{1, 1, RW}; //I2C Module 1 Software Reset
        bitField SRI2C_R0{0, 1, RW}; //I2C Module 0 Software Reset

        bitField RCGCI2C_R3{3, 1, RW}; //I2C Module 3 Run Mode Clock Gating Control
        bitField RCGCI2C_R2{2, 1, RW}; //I2C Module 2 Run Mode Clock Gating Control
        bitField RCGCI2C_R1{1, 1, RW}; //I2C Module 1 Run Mode Clock Gating Control
        bitField RCGCI2C_R0{0, 1, RW}; //I2C Module 0 Run Mode Clock Gating Control

        bitField SCGCI2C_S3{3, 1, RW}; //I2C Module 3 Sleep Mode Clock Gating Control
        bitField SCGCI2C_S2{2, 1, RW}; //I2C Module 2 Sleep Mode Clock Gating Control
        bitField SCGCI2C_S1{1, 1, RW}; //I2C Module 1 Sleep Mode Clock Gating Control
        bitField SCGCI2C_S0{0, 1, RW}; //I2C Module 0 Sleep Mode Clock Gating Control

        bitField DCGCI2C_D3{3, 1, RW}; //I2C Module 3 Deep-Sleep Mode Clock Gating Control
        bitField DCGCI2C_D2{2, 1, RW}; //I2C Module 2 Deep-Sleep Mode Clock Gating Control
        bitField DCGCI2C_D1{1, 1, RW}; //I2C Module 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCI2C_D0{0, 1, RW}; //I2C Module 0 Deep-Sleep Mode Clock Gating Control

        bitField PRI2C_R3{3, 1, RO}; //I2C Module 3 Peripheral Ready
        bitField PRI2C_R2{2, 1, RO}; //I2C Module 2 Peripheral Ready
        bitField PRI2C_R1{1, 1, RO}; //I2C Module 1 Peripheral Ready
        bitField PRI2C_R0{0, 1, RO}; //I2C Module 0 Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC2_I2C1HS{15, 1, RO}; //I2C Module 1 Speed. When set, indicates that I2C module 1 can operate in high-speed mode.
        bitField DC2_I2C1{14, 1, RO}; //I2C Module 1 Present. When set, indicates that I2C module 1 is present.
        bitField DC2_I2C0HS{13, 1, RO}; //I2C Module 0 Speed. When set, indicates that I2C module 0 can operate in high-speed mode.
        bitField DC2_I2C0{12, 1, RO}; //I2C Module 0 Present. When set, indicates that I2C module 0 is present.

        bitField SRCR1_I2C1{14, 1, RO}; //I2C1 Reset Control
        bitField SRCR1_I2C0{12, 1, RO}; //I2C0 Reset Control

        bitField RCGC1_I2C1{14, 1, RO}; //I2C1 Clock Gating Control
        bitField RCGC1_I2C0{12, 1, RO}; //I2C0 Clock Gating Control

        bitField SCGC1_I2C1{14, 1, RO}; //I2C1 Clock Gating Control
        bitField SCGC1_I2C0{12, 1, RO}; //I2C0 Clock Gating Control

        bitField DCGC1_I2C1{14, 1, RO}; //I2C1 Clock Gating Control
        bitField DCGC1_I2C0{12, 1, RO}; //I2C0 Clock Gating Control

};

#endif //I2C_H
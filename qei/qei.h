/**
 * @file qei.h
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
 * Quadrature Encoder Interface (QEI) Register Descriptions
 * 
 * The remainder of this section lists and describes the QEI registers, in 
 * numerical order by address offset.
 */

#ifndef QEI_H
#define QEI_H

#include "../systemControl/systemControl.h"

class Qei : SystemControl
{
    public:
        Qei();
        ~Qei();

    private:
        const uint32_t qei0BaseAddress = 0x4002C000;
        const uint32_t qei1BaseAddress = 0x4002D000;

/**********************System Control Register Descriptions********************/

        Register PPQEI{(volatile uint32_t*)(systemControlBase + 0x344)}; //0x344 PPQEI RO 0x0000.0003 Quadrature Encoder Interface Peripheral Present 306
        Register SRQEI{(volatile uint32_t*)(systemControlBase + 0x544)}; //0x544 SRQEI RW 0x0000.0000 Quadrature Encoder Interface Software Reset 332
        Register RCGCQEI{(volatile uint32_t*)(systemControlBase + 0x644)}; //0x644 RCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Run Mode Clock Gating Control 355
        Register SCGCQEI{(volatile uint32_t*)(systemControlBase + 0x744)}; //0x744 SCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Sleep Mode Clock Gating Control 377
        Register DCGCQEI{(volatile uint32_t*)(systemControlBase + 0x844)}; //0x844 DCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control 399
        Register PRQEI{(volatile uint32_t*)(systemControlBase + 0xA44)}; //0xA44 PRQEI RO 0x0000.0000 Quadrature Encoder Interface Peripheral Ready 421

/**************************System Control BitFields****************************/

        bitField PPQEI_P1{1, 1, RO}; //QEI Module 1 Present
        bitField PPQEI_P0{0, 1, RO}; //QEI Module 0 Present

        bitField SRQEI_R1{1, 1, RW}; //QEI Module 1 Software Reset
        bitField SRQEI_R0{0, 1, RW}; //QEI Module 0 Software Reset

        bitField RCGCQEI_R1{1, 1, RW}; //QEI Module 1 Run Mode Clock Gating Control
        bitField RCGCQEI_R0{0, 1, RW}; //QEI Module 0 Run Mode Clock Gating Control

        bitField SCGCQEI_S1{1, 1, RW}; //QEI Module 1 Sleep Mode Clock Gating Control
        bitField SCGCQEI_S0{0, 1, RW}; //QEI Module 0 Sleep Mode Clock Gating Control

        bitField DCGCQEI_D1{1, 1, RW}; //QEI Module 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCQEI_D0{0, 1, RW}; //QEI Module 0 Deep-Sleep Mode Clock Gating Control

        bitField PRQEI_R1{1, 1, RO}; //QEI Module 1 Peripheral Ready
        bitField PRQEI_R0{0, 1, RO}; //QEI Module 0 Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC2_QEI1{9, 1, RO}; //QEI Module 1 Present. When set, indicates that QEI module 1 is present.
        bitField DC2_QEI0{8, 1, RO}; //QEI Module 0 Present. When set, indicates that QEI module 0 is present.

        bitField SRCR1_QEI1{9, 1, RO}; //QEI1 Reset Control
        bitField SRCR1_QEI0{8, 1, RO}; //QEI0 Reset Control

        bitField RCGC1_QEI1{9, 1, RO}; //QEI1 Clock Gating Control
        bitField RCGC1_QEI0{8, 1, RO}; //QEI0 Clock Gating Control

        bitField SCGC1_QEI1{9, 1, RO}; //QEI1 Clock Gating Control
        bitField SCGC1_QEI0{8, 1, RO}; //QEI0 Clock Gating Control

        bitField DCGC1_QEI1{9, 1, RO}; //QEI1 Clock Gating Control
        bitField DCGC1_QEI0{8, 1, RO}; //QEI0 Clock Gating Control
        
};

#endif //P_H
/**
 * @file comparator.h
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
 * Analog Comparators Register Descriptions
 * 
 * The remainder of this section lists and describes the Analog Comparator 
 * registers, in numerical order by address offset.
 */

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "../systemControl/systemControl.h"

class Comparator : SystemControl
{
    public:
        Comparator();
        ~Comparator();

    private:
        const uint32_t analogComparatorBaseAddress = 0x4003C000;

/**********************System Control Register Descriptions********************/

        Register PPACMP{(volatile uint32_t*)(systemControlBase + 0x33C)}; //0x33C PPACMP RO 0x0000.0001 Analog Comparator Peripheral Present 304
        Register SRACMP{(volatile uint32_t*)(systemControlBase + 0x53C)}; //0x53C SRACMP RW 0x0000.0000 Analog Comparator Software Reset 329
        Register RCGCACMP{(volatile uint32_t*)(systemControlBase + 0x63C)}; //0x63C RCGCACMP RW 0x0000.0000 Analog Comparator Run Mode Clock Gating Control 353
        Register SCGCACMP{(volatile uint32_t*)(systemControlBase + 0x73C)}; //0x73C SCGCACMP RW 0x0000.0000 Analog Comparator Sleep Mode Clock Gating Control 375
        Register DCGCACMP{(volatile uint32_t*)(systemControlBase + 0x83C)}; //0x83C DCGCACMP RW 0x0000.0000 Analog Comparator Deep-Sleep Mode Clock Gating Control 397
        Register PRACMP{(volatile uint32_t*)(systemControlBase + 0xA3C)}; //0xA3C PRACMP RO 0x0000.0000 Analog Comparator Peripheral Ready 419

/**************************System Control BitFields****************************/

        bitField PPACMP_P0{0, 1, RO}; //Analog Comparator Module Present
        bitField SRACMP_R0{0, 1, RW}; //Analog Comparator Module 0 Software Reset
        bitField RCGCACMP_R0{0, 1, RW}; //Analog Comparator Module 0 Run Mode Clock Gating Control
        bitField SCGCACMP_S0{0, 1, RW}; //Analog Comparator Module 0 Sleep Mode Clock Gating Control
        bitField DCGCACMP_D0{0, 1, RW}; //Analog Comparator Module 0 Deep-Sleep Mode Clock Gating Control
        bitField PRACMP_R0{0, 1, RO}; //Analog Comparator Module 0 Peripheral Ready
        

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC2_COMP2{26, 1, RO}; //Analog Comparator 2 Present. When set, indicates that analog comparator 2 is present.
        bitField DC2_COMP1{25, 1, RO}; //Analog Comparator 1 Present. When set, indicates that analog comparator 1 is present.
        bitField DC2_COMP0{24, 1, RO}; //Analog Comparator 0 Present. When set, indicates that analog comparator 0 is present.

        bitField DC3_C2O{14, 1, RO}; //C2o Pin Present. When set, indicates that the analog comparator 2 output pin is present.
        bitField DC3_C2PLUS{13, 1, RO}; //C2+ Pin Present. When set, indicates that the analog comparator 2 (+) input pin is present.
        bitField DC3_C2MINUS{12, 1, RO}; //C2- Pin Present. When set, indicates that the analog comparator 2 (-) input pin is present.
        bitField DC3_C1O{11, 1, RO}; //C1o Pin Present. When set, indicates that the analog comparator 1 output pin is present.
        bitField DC3_C1PLUS{10, 1, RO}; //C1+ Pin Present. When set, indicates that the analog comparator 1 (+) input pin is present.
        bitField DC3_C1MINUS{9, 1, RO}; //C1- Pin Present. When set, indicates that the analog comparator 1 (-) input pin is present.
        bitField DC3_C0O{8, 1, RO}; //C0o Pin Present. When set, indicates that the analog comparator 0 output pin is present.
        bitField DC3_C0PLUS{7, 1, RO}; //C0+ Pin Present. When set, indicates that the analog comparator 0 (+) input pin is present.
        bitField DC3_C0MINUS{6, 1, RO}; //C0- Pin Present. When set, indicates that the analog comparator 0 (-) input pin is present.

        bitField SRCR1_COMP1{25, 1, RO}; //Analog Comp 1 Reset Control
        bitField SRCR1_COMP0{24, 1, RO}; //Analog Comp 0 Reset Control

        bitField RCGC1_COMP1{25, 1, RO}; //Analog Comp 1 Clock Gating Control
        bitField RCGC1_COMP0{24, 1, RO}; //Analog Comp 0 Clock Gating Control

        bitField SCGC1_COMP1{25, 1, RO}; //Analog Comp 1 Clock Gating Control
        bitField SCGC1_COMP0{24, 1, RO}; //Analog Comp 0 Clock Gating Control

        bitField DCGC1_COMP1{25, 1, RO}; //Analog Comp 1 Clock Gating
        bitField DCGC1_COMP0{24, 1, RO}; //Analog Comp 0 Clock Gating

};

#endif //COMPARATOR_H
/**
 * @file shortTimer.h
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
 * General-Purpose Timers Register Descriptions
 * 
 * The remainder of this section lists and describes the GPTM registers, 
 * in numerical order by address offset.
 * 
 */

#ifndef SHORT_TIMER_H
#define SHORT_TIMER_H

#include "../systemControl/systemControl.h"
#include "generalPurposeTimer.h"

class ShortTimer : SystemControl, GeneralPurposeTimer
{
    public:
        ShortTimer();
        ~ShortTimer();

    private:
        const uint32_t _16_32_bit_Timer_0_base = 0x40030000;
        const uint32_t _16_32_bit_Timer_1_base = 0x40031000;
        const uint32_t _16_32_bit_Timer_2_base = 0x40032000;
        const uint32_t _16_32_bit_Timer_3_base = 0x40033000;
        const uint32_t _16_32_bit_Timer_4_base = 0x40034000;
        const uint32_t _16_32_bit_Timer_5_base = 0x40035000;

/**********************System Control Register Descriptions********************/

        Register PPTIMER{(volatile uint32_t*)(systemControlBase + 0x304)}; //0x304 PPTIMER RO 0x0000.003F 16/32-Bit General-Purpose Timer Peripheral Present 288
        Register SRTIMER{(volatile uint32_t*)(systemControlBase + 0x504)}; //0x504 SRTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Software Reset 312
        Register RCGCTIMER{(volatile uint32_t*)(systemControlBase + 0x604)}; //0x604 RCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control 338
        Register SCGCTIMER{(volatile uint32_t*)(systemControlBase + 0x704)}; //0x704 SCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control 360
        Register DCGCTIMER{(volatile uint32_t*)(systemControlBase + 0x804)}; //0x804 DCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control 382
        Register PRTIMER{(volatile uint32_t*)(systemControlBase + 0xA04)}; //0xA04 PRTIMER RO 0x0000.0000 16/32-Bit General-Purpose Timer Peripheral Ready 404

/**************************System Control BitFields****************************/

        bitField PPTIMER_P5{5, 1, RO}; //16/32-Bit General-Purpose Timer 5 Present
        bitField PPTIMER_P4{4, 1, RO}; //16/32-Bit General-Purpose Timer 4 Present
        bitField PPTIMER_P3{3, 1, RO}; //16/32-Bit General-Purpose Timer 3 Present
        bitField PPTIMER_P2{2, 1, RO}; //16/32-Bit General-Purpose Timer 2 Present
        bitField PPTIMER_P1{1, 1, RO}; //16/32-Bit General-Purpose Timer 1 Present
        bitField PPTIMER_P0{0, 1, RO}; //16/32-Bit General-Purpose Timer 0 Present

        bitField SRTIMER_R5{5, 1, RW}; //16/32-Bit General-Purpose Timer 5 Software Reset
        bitField SRTIMER_R4{4, 1, RW}; //16/32-Bit General-Purpose Timer 4 Software Reset
        bitField SRTIMER_R3{3, 1, RW}; //16/32-Bit General-Purpose Timer 3 Software Reset
        bitField SRTIMER_R2{2, 1, RW}; //16/32-Bit General-Purpose Timer 2 Software Reset
        bitField SRTIMER_R1{1, 1, RW}; //16/32-Bit General-Purpose Timer 1 Software Reset
        bitField SRTIMER_R0{0, 1, RW}; //16/32-Bit General-Purpose Timer 0 Software Reset

        bitField RCGCTIMER_5{5, 1, RW}; //16/32-Bit General-Purpose Timer 5 Run Mode Clock Gating Control
        bitField RCGCTIMER_4{4, 1, RW}; //16/32-Bit General-Purpose Timer 4 Run Mode Clock Gating Control
        bitField RCGCTIMER_3{3, 1, RW}; //16/32-Bit General-Purpose Timer 3 Run Mode Clock Gating Control
        bitField RCGCTIMER_2{2, 1, RW}; //16/32-Bit General-Purpose Timer 2 Run Mode Clock Gating Control
        bitField RCGCTIMER_1{1, 1, RW}; //16/32-Bit General-Purpose Timer 1 Run Mode Clock Gating Control
        bitField RCGCTIMER_0{0, 1, RW}; //16/32-Bit General-Purpose Timer 0 Run Mode Clock Gating Control

        bitField SCGCTIMER_S5{5, 1, RW}; //16/32-Bit General-Purpose Timer 5 Sleep Mode Clock Gating Control
        bitField SCGCTIMER_S4{4, 1, RW}; //16/32-Bit General-Purpose Timer 4 Sleep Mode Clock Gating Control
        bitField SCGCTIMER_S3{3, 1, RW}; //16/32-Bit General-Purpose Timer 3 Sleep Mode Clock Gating Control
        bitField SCGCTIMER_S2{2, 1, RW}; //16/32-Bit General-Purpose Timer 2 Sleep Mode Clock Gating Control
        bitField SCGCTIMER_S1{1, 1, RW}; //16/32-Bit General-Purpose Timer 1 Sleep Mode Clock Gating Control
        bitField SCGCTIMER_S0{0, 1, RW}; //16/32-Bit General-Purpose Timer 0 Sleep Mode Clock Gating Control

        bitField DCGCTIMER_D5{5, 1, RW}; //16/32-Bit General-Purpose Timer 5 Deep-Sleep Mode Clock Gating Control
        bitField DCGCTIMER_D4{4, 1, RW}; //16/32-Bit General-Purpose Timer 4 Deep-Sleep Mode Clock Gating Control
        bitField DCGCTIMER_D3{3, 1, RW}; //16/32-Bit General-Purpose Timer 3 Deep-Sleep Mode Clock Gating Control
        bitField DCGCTIMER_D2{2, 1, RW}; //16/32-Bit General-Purpose Timer 2 Deep-Sleep Mode Clock Gating Control
        bitField DCGCTIMER_D1{1, 1, RW}; //16/32-Bit General-Purpose Timer 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCTIMER_D0{0, 1, RW}; //16/32-Bit General-Purpose Timer 0 Deep-Sleep Mode Clock Gating Control

        bitField PRTIMER_R5{5, 1, RO}; //16/32-Bit General-Purpose Timer 5 Peripheral Ready
        bitField PRTIMER_R4{4, 1, RO}; //16/32-Bit General-Purpose Timer 4 Peripheral Ready
        bitField PRTIMER_R3{3, 1, RO}; //16/32-Bit General-Purpose Timer 3 Peripheral Ready
        bitField PRTIMER_R2{2, 1, RO}; //16/32-Bit General-Purpose Timer 2 Peripheral Ready
        bitField PRTIMER_R1{1, 1, RO}; //16/32-Bit General-Purpose Timer 1 Peripheral Ready
        bitField PRTIMER_R0{0, 1, RO}; //16/32-Bit General-Purpose Timer 0 Peripheral Ready

};

#endif //SHORT_TIMER_H
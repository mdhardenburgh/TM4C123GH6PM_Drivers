/**
 * @file wideTimer.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/18/2019
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

#ifndef WIDE_TIMER_H
#define WIDE_TIMER_H

#include "../systemControl/systemControl.h"
#include "generalPurposeTimer.h"

class WideTimer : SystemControl, GeneralPurposeTimer
{
    public:
        WideTimer();
        ~WideTimer();

    private:
        const uint32_t _32_64_bit_Wide_Timer_0 = 0x40036000;
        const uint32_t _32_64_bit_Wide_Timer_1 = 0x40037000;
        const uint32_t _32_64_bit_Wide_Timer_2 = 0x4004C000;
        const uint32_t _32_64_bit_Wide_Timer_3 = 0x4004D000;
        const uint32_t _32_64_bit_Wide_Timer_4 = 0x4004E000;
        const uint32_t _32_64_bit_Wide_Timer_5 = 0x4004F000;

/**********************System Control Register Descriptions********************/

        Register PPWTIMER{(volatile uint32_t*)(systemControlBase + 0x35C)}; //0x35C PPWTIMER RO 0x0000.003F 32/64-Bit Wide General-Purpose Timer Peripheral Present 308
        Register SRWTIMER{(volatile uint32_t*)(systemControlBase + 0x55C)}; //0x55C SRWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Software Reset 335
        Register RCGCWTIMER{(volatile uint32_t*)(systemControlBase + 0x65C)}; //0x65C RCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control 357
        Register SCGCWTIMER{(volatile uint32_t*)(systemControlBase + 0x75C)}; //0x75C SCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control 379
        Register DCGCWTIMER{(volatile uint32_t*)(systemControlBase + 0x85C)}; //0x85C DCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control 401
        Register PRWTIMER{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0xA5C PRWTIMER RO 0x0000.0000 32/64-Bit Wide General-Purpose Timer Peripheral Ready 423

/**************************System Control BitFields****************************/

        bitField PPWTIMER_P5{5, 1, RO}; //32/64-Bit Wide General-Purpose Timer 5 Present
        bitField PPWTIMER_P4{4, 1, RO}; //32/64-Bit Wide General-Purpose Timer 4 Present
        bitField PPWTIMER_P3{3, 1, RO}; //32/64-Bit Wide General-Purpose Timer 3 Present
        bitField PPWTIMER_P2{2, 1, RO}; //32/64-Bit Wide General-Purpose Timer 2 Present
        bitField PPWTIMER_P1{1, 1, RO}; //32/64-Bit Wide General-Purpose Timer 1 Present
        bitField PPWTIMER_P0{0, 1, RO}; //32/64-Bit Wide General-Purpose Timer 0 Present

        bitField SRWTIMER_R5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Software Reset
        bitField SRWTIMER_R4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Software Reset
        bitField SRWTIMER_R3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Software Reset
        bitField SRWTIMER_R2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Software Reset
        bitField SRWTIMER_R1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Software Reset
        bitField SRWTIMER_R5{0, 0, RW}; //32/64-Bit Wide General-Purpose Timer 0 Software Reset

        bitField RCGCWTIMER_R5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Run Mode Clock Gating Control
        bitField RCGCWTIMER_R4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Run Mode Clock Gating Control
        bitField RCGCWTIMER_R3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Run Mode Clock Gating Control
        bitField RCGCWTIMER_R2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Run Mode Clock Gating Control
        bitField RCGCWTIMER_R1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Run Mode Clock Gating Control
        bitField RCGCWTIMER_R0{0, 1, RW}; //32/64-Bit Wide General-Purpose Timer 0 Run Mode Clock Gating Control

        bitField SCGCWTIMER_S5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Sleep Mode Clock Gating Control
        bitField SCGCWTIMER_S4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Sleep Mode Clock Gating Control
        bitField SCGCWTIMER_S3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Sleep Mode Clock Gating Control
        bitField SCGCWTIMER_S2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Sleep Mode Clock Gating Control
        bitField SCGCWTIMER_S1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Sleep Mode Clock Gating Control
        bitField SCGCWTIMER_S0{0, 1, RW}; //32/64-Bit Wide General-Purpose Timer 0 Sleep Mode Clock Gating Control

        bitField DCGCWTIMER_D5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Deep-Sleep Mode Clock Gating Control
        bitField DCGCWTIMER_D4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Deep-Sleep Mode Clock Gating Control
        bitField DCGCWTIMER_D3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Deep-Sleep Mode Clock Gating Control
        bitField DCGCWTIMER_D2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Deep-Sleep Mode Clock Gating Control
        bitField DCGCWTIMER_D1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCWTIMER_D0{0, 1, RW}; //32/64-Bit Wide General-Purpose Timer 0 Deep-Sleep Mode Clock Gating Control

        bitField PRWTIMER_R5{5, 1, RO}; //32/64-Bit Wide General-Purpose Timer 5 Peripheral Ready
        bitField PRWTIMER_R4{4, 1, RO}; //32/64-Bit Wide General-Purpose Timer 4 Peripheral Ready
        bitField PRWTIMER_R3{3, 1, RO}; //32/64-Bit Wide General-Purpose Timer 3 Peripheral Ready
        bitField PRWTIMER_R2{2, 1, RO}; //32/64-Bit Wide General-Purpose Timer 2 Peripheral Ready
        bitField PRWTIMER_R1{1, 1, RO}; //32/64-Bit Wide General-Purpose Timer 1 Peripheral Ready
        bitField PRWTIMER_R0{0, 1, RO}; //32/64-Bit Wide General-Purpose Timer 0 Peripheral Ready
};

#endif
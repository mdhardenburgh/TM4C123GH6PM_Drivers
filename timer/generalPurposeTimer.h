/**
 * @file generalPurposeTimer.h
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

#ifndef GENERAL_PURPOSE_TIMER_H
#define GENERAL_PURPOSE_TIMER_H

#include "../register/register.h"
#include "generalPurposeTimer.h"

enum timerMode
{
    oneShot, periodic, realTimeClock, inputEdgeCount, inputEdgeTime, PWM
};

enum timerSize
{
    shortTimer, WideTimer
};

class GeneralPurposeTimer
{
    public:
        GeneralPurposeTimer();
        ~GeneralPurposeTimer();

    private:

        const uint32_t _16_32_bit_Timer_0_base = 0x40030000;
        const uint32_t _16_32_bit_Timer_1_base = 0x40031000;
        const uint32_t _16_32_bit_Timer_2_base = 0x40032000;
        const uint32_t _16_32_bit_Timer_3_base = 0x40033000;
        const uint32_t _16_32_bit_Timer_4_base = 0x40034000;
        const uint32_t _16_32_bit_Timer_5_base = 0x40035000;

        const uint32_t _32_64_bit_Wide_Timer_0 = 0x40036000;
        const uint32_t _32_64_bit_Wide_Timer_1 = 0x40037000;
        const uint32_t _32_64_bit_Wide_Timer_2 = 0x4004C000;
        const uint32_t _32_64_bit_Wide_Timer_3 = 0x4004D000;
        const uint32_t _32_64_bit_Wide_Timer_4 = 0x4004E000;
        const uint32_t _32_64_bit_Wide_Timer_5 = 0x4004F000;

        const uint32_t PPTIMER_OFFSET = 0x304; //0x304 PPTIMER RO 0x0000.003F 16/32-Bit General-Purpose Timer Peripheral Present 288
        const uint32_t SRTIMER_OFFSET = 0x504; //0x504 SRTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Software Reset 312
        const uint32_t RCGCTIMER_OFFSET = 0x604; //0x604 RCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control 338
        const uint32_t SCGCTIMER_OFFSET = 0x704; //0x704 SCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control 360
        const uint32_t DCGCTIMER_OFFSET = 0x804; //0x804 DCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control 382
        const uint32_t PRTIMER_OFFSET = 0xA04; //0xA04 PRTIMER RO 0x0000.0000 16/32-Bit General-Purpose Timer Peripheral Ready 404

        const uint32_t PPWTIMER_OFFSET = 0x304; //0x35C PPWTIMER RO 0x0000.003F 32/64-Bit Wide General-Purpose Timer Peripheral Present 308
        const uint32_t SRWTIMER_OFFSET = 0x55C; //0x55C SRWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Software Reset 335
        const uint32_t RCGCWTIMER_OFFSET = 0x65C; //0x65C RCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control 357
        const uint32_t SCGCWTIMER_OFFSET = 0x75C; //0x75C SCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control 379
        const uint32_t DCGCWTIMER_OFFSET = 0x85C; //0x85C DCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control 401
        const uint32_t PRWTIMER_OFFSET = 0xA5C; //0xA5C PRWTIMER RO 0x0000.0000 32/64-Bit Wide General-Purpose Timer Peripheral Ready 423


        const uint32_t GPTMCFG_OFFSET = 0x000; // 0x000 GPTMCFG RW 0x0000.0000 GPTM Configuration 727
        const uint32_t GPTMTAMR_OFFSET = 0x004; // 0x004 GPTMTAMR RW 0x0000.0000 GPTM Timer A Mode 729
        const uint32_t GPTMTBMR_OFFSET = 0x008; // 0x008 GPTMTBMR RW 0x0000.0000 GPTM Timer B Mode 733
        const uint32_t GPTMCTL_OFFSET = 0x00C; // 0x00C GPTMCTL RW 0x0000.0000 GPTM Control 737
        const uint32_t GPTMSYNC_OFFSET = 0x010; // 0x010 GPTMSYNC RW 0x0000.0000 GPTM Synchronize 741
        const uint32_t GPTMIMR_OFFSET = 0x018; // 0x018 GPTMIMR RW 0x0000.0000 GPTM Interrupt Mask 745
        const uint32_t GPTMRIS_OFFSET = 0x01C; // 0x01C GPTMRIS RO 0x0000.0000 GPTM Raw Interrupt Status 748
        const uint32_t GPTMMIS_OFFSET = 0x020; // 0x020 GPTMMIS RO 0x0000.0000 GPTM Masked Interrupt Status 751
        const uint32_t GPTMICR_OFFSET = 0x024; // 0x024 GPTMICR W1C 0x0000.0000 GPTM Interrupt Clear 754
        const uint32_t GPTMTAILR_OFFSET = 0x028; // 0x028 GPTMTAILR RW 0xFFFF.FFFF GPTM Timer A Interval Load 756
        const uint32_t GPTMTBILR_OFFSET = 0x02C; // 0x02C GPTMTBILR RW - GPTM Timer B Interval Load 757
        const uint32_t GPTMTAMATCHR_OFFSET = 0x030; // 0x030 GPTMTAMATCHR RW 0xFFFF.FFFF GPTM Timer A Match 758
        const uint32_t GPTMTBMATCHR_OFFSET = 0x034; // 0x034 GPTMTBMATCHR RW - GPTM Timer B Match 759
        const uint32_t GPTMTAPR_OFFSET = 0x038; // 0x038 GPTMTAPR RW 0x0000.0000 GPTM Timer A Prescale 760
        const uint32_t GPTMTBPR_OFFSET = 0x03C; // 0x03C GPTMTBPR RW 0x0000.0000 GPTM Timer B Prescale 761
        const uint32_t GPTMTAPMR_OFFSET = 0x040; // 0x040 GPTMTAPMR RW 0x0000.0000 GPTM TimerA Prescale Match 762
        const uint32_t GPTMTBPMR_OFFSET = 0x044; // 0x044 GPTMTBPMR RW 0x0000.0000 GPTM TimerB Prescale Match 763
        const uint32_t GPTMTAR_OFFSET = 0x048; // 0x048 GPTMTAR RO 0xFFFF.FFFF GPTM Timer A 764
        const uint32_t GPTMTBR_OFFSET = 0x04C; // 0x04C GPTMTBR RO - GPTM Timer B 765
        const uint32_t GPTMTAV_OFFSET = 0x050; // 0x050 GPTMTAV RW 0xFFFF.FFFF GPTM Timer A Value 766
        const uint32_t GPTMTBV_OFFSET = 0x054; // 0x054 GPTMTBV RW - GPTM Timer B Value 767
        const uint32_t GPTMRTCPD_OFFSET = 0x058; // 0x058 GPTMRTCPD RO 0x0000.7FFF GPTM RTC Predivide 768
        const uint32_t GPTMTAPS_OFFSET = 0x05C; // 0x05C GPTMTAPS RO 0x0000.0000 GPTM Timer A Prescale Snapshot 769
        const uint32_t GPTMTBPS_OFFSET = 0x060; // 0x060 GPTMTBPS RO 0x0000.0000 GPTM Timer B Prescale Snapshot 770
        const uint32_t GPTMTAPV_OFFSET = 0x064; // 0x064 GPTMTAPV RO 0x0000.0000 GPTM Timer A Prescale Value 771
        const uint32_t GPTMTBPV_OFFSET = 0x068; // 0x068 GPTMTBPV RO 0x0000.0000 GPTM Timer B Prescale Value 772
        const uint32_t GPTMPP_OFFSET = 0xFC0; // 0xFC0 GPTMPP RO 0x0000.0000 GPTM Peripheral Properties 773



/**************************System Control BitFields****************************/

        // bitField PPTIMER_P5{5, 1, RO}; //16/32-Bit Short General-Purpose Timer 5 Present
        // bitField PPTIMER_P4{4, 1, RO}; //16/32-Bit Short General-Purpose Timer 4 Present
        // bitField PPTIMER_P3{3, 1, RO}; //16/32-Bit Short General-Purpose Timer 3 Present
        // bitField PPTIMER_P2{2, 1, RO}; //16/32-Bit Short General-Purpose Timer 2 Present
        // bitField PPTIMER_P1{1, 1, RO}; //16/32-Bit Short General-Purpose Timer 1 Present
        // bitField PPTIMER_P0{0, 1, RO}; //16/32-Bit Short General-Purpose Timer 0 Present

        // bitField SRTIMER_R5{5, 1, RW}; //16/32-Bit Short General-Purpose Timer 5 Software Reset
        // bitField SRTIMER_R4{4, 1, RW}; //16/32-Bit Short General-Purpose Timer 4 Software Reset
        // bitField SRTIMER_R3{3, 1, RW}; //16/32-Bit Short General-Purpose Timer 3 Software Reset
        // bitField SRTIMER_R2{2, 1, RW}; //16/32-Bit Short General-Purpose Timer 2 Software Reset
        // bitField SRTIMER_R1{1, 1, RW}; //16/32-Bit Short General-Purpose Timer 1 Software Reset
        // bitField SRTIMER_R0{0, 1, RW}; //16/32-Bit Short General-Purpose Timer 0 Software Reset

        // bitField RCGCTIMER_5{5, 1, RW}; //16/32-Bit Short General-Purpose Timer 5 Run Mode Clock Gating Control
        // bitField RCGCTIMER_4{4, 1, RW}; //16/32-Bit Short General-Purpose Timer 4 Run Mode Clock Gating Control
        // bitField RCGCTIMER_3{3, 1, RW}; //16/32-Bit Short General-Purpose Timer 3 Run Mode Clock Gating Control
        // bitField RCGCTIMER_2{2, 1, RW}; //16/32-Bit Short General-Purpose Timer 2 Run Mode Clock Gating Control
        // bitField RCGCTIMER_1{1, 1, RW}; //16/32-Bit Short General-Purpose Timer 1 Run Mode Clock Gating Control
        // bitField RCGCTIMER_0{0, 1, RW}; //16/32-Bit Short General-Purpose Timer 0 Run Mode Clock Gating Control

        // bitField SCGCTIMER_S5{5, 1, RW}; //16/32-Bit Short General-Purpose Timer 5 Sleep Mode Clock Gating Control
        // bitField SCGCTIMER_S4{4, 1, RW}; //16/32-Bit Short General-Purpose Timer 4 Sleep Mode Clock Gating Control
        // bitField SCGCTIMER_S3{3, 1, RW}; //16/32-Bit Short General-Purpose Timer 3 Sleep Mode Clock Gating Control
        // bitField SCGCTIMER_S2{2, 1, RW}; //16/32-Bit Short General-Purpose Timer 2 Sleep Mode Clock Gating Control
        // bitField SCGCTIMER_S1{1, 1, RW}; //16/32-Bit Short General-Purpose Timer 1 Sleep Mode Clock Gating Control
        // bitField SCGCTIMER_S0{0, 1, RW}; //16/32-Bit Short General-Purpose Timer 0 Sleep Mode Clock Gating Control

        // bitField DCGCTIMER_D5{5, 1, RW}; //16/32-Bit Short General-Purpose Timer 5 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCTIMER_D4{4, 1, RW}; //16/32-Bit Short General-Purpose Timer 4 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCTIMER_D3{3, 1, RW}; //16/32-Bit Short General-Purpose Timer 3 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCTIMER_D2{2, 1, RW}; //16/32-Bit Short General-Purpose Timer 2 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCTIMER_D1{1, 1, RW}; //16/32-Bit Short General-Purpose Timer 1 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCTIMER_D0{0, 1, RW}; //16/32-Bit Short General-Purpose Timer 0 Deep-Sleep Mode Clock Gating Control

        // bitField PRTIMER_R5{5, 1, RO}; //16/32-Bit Short General-Purpose Timer 5 Peripheral Ready
        // bitField PRTIMER_R4{4, 1, RO}; //16/32-Bit Short General-Purpose Timer 4 Peripheral Ready
        // bitField PRTIMER_R3{3, 1, RO}; //16/32-Bit Short General-Purpose Timer 3 Peripheral Ready
        // bitField PRTIMER_R2{2, 1, RO}; //16/32-Bit Short General-Purpose Timer 2 Peripheral Ready
        // bitField PRTIMER_R1{1, 1, RO}; //16/32-Bit Short General-Purpose Timer 1 Peripheral Ready
        // bitField PRTIMER_R0{0, 1, RO}; //16/32-Bit Short General-Purpose Timer 0 Peripheral Ready
        
        // bitField PPWTIMER_P5{5, 1, RO}; //32/64-Bit Wide General-Purpose Timer 5 Present
        // bitField PPWTIMER_P4{4, 1, RO}; //32/64-Bit Wide General-Purpose Timer 4 Present
        // bitField PPWTIMER_P3{3, 1, RO}; //32/64-Bit Wide General-Purpose Timer 3 Present
        // bitField PPWTIMER_P2{2, 1, RO}; //32/64-Bit Wide General-Purpose Timer 2 Present
        // bitField PPWTIMER_P1{1, 1, RO}; //32/64-Bit Wide General-Purpose Timer 1 Present
        // bitField PPWTIMER_P0{0, 1, RO}; //32/64-Bit Wide General-Purpose Timer 0 Present

        // bitField SRWTIMER_R5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Software Reset
        // bitField SRWTIMER_R4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Software Reset
        // bitField SRWTIMER_R3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Software Reset
        // bitField SRWTIMER_R2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Software Reset
        // bitField SRWTIMER_R1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Software Reset
        // bitField SRWTIMER_R0{0, 0, RW}; //32/64-Bit Wide General-Purpose Timer 0 Software Reset

        // bitField RCGCWTIMER_R5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Run Mode Clock Gating Control
        // bitField RCGCWTIMER_R4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Run Mode Clock Gating Control
        // bitField RCGCWTIMER_R3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Run Mode Clock Gating Control
        // bitField RCGCWTIMER_R2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Run Mode Clock Gating Control
        // bitField RCGCWTIMER_R1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Run Mode Clock Gating Control
        // bitField RCGCWTIMER_R0{0, 1, RW}; //32/64-Bit Wide General-Purpose Timer 0 Run Mode Clock Gating Control

        // bitField SCGCWTIMER_S5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Sleep Mode Clock Gating Control
        // bitField SCGCWTIMER_S4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Sleep Mode Clock Gating Control
        // bitField SCGCWTIMER_S3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Sleep Mode Clock Gating Control
        // bitField SCGCWTIMER_S2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Sleep Mode Clock Gating Control
        // bitField SCGCWTIMER_S1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Sleep Mode Clock Gating Control
        // bitField SCGCWTIMER_S0{0, 1, RW}; //32/64-Bit Wide General-Purpose Timer 0 Sleep Mode Clock Gating Control

        // bitField DCGCWTIMER_D5{5, 1, RW}; //32/64-Bit Wide General-Purpose Timer 5 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCWTIMER_D4{4, 1, RW}; //32/64-Bit Wide General-Purpose Timer 4 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCWTIMER_D3{3, 1, RW}; //32/64-Bit Wide General-Purpose Timer 3 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCWTIMER_D2{2, 1, RW}; //32/64-Bit Wide General-Purpose Timer 2 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCWTIMER_D1{1, 1, RW}; //32/64-Bit Wide General-Purpose Timer 1 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCWTIMER_D0{0, 1, RW}; //32/64-Bit Wide General-Purpose Timer 0 Deep-Sleep Mode Clock Gating Control

        // bitField PRWTIMER_R5{5, 1, RO}; //32/64-Bit Wide General-Purpose Timer 5 Peripheral Ready
        // bitField PRWTIMER_R4{4, 1, RO}; //32/64-Bit Wide General-Purpose Timer 4 Peripheral Ready
        // bitField PRWTIMER_R3{3, 1, RO}; //32/64-Bit Wide General-Purpose Timer 3 Peripheral Ready
        // bitField PRWTIMER_R2{2, 1, RO}; //32/64-Bit Wide General-Purpose Timer 2 Peripheral Ready
        // bitField PRWTIMER_R1{1, 1, RO}; //32/64-Bit Wide General-Purpose Timer 1 Peripheral Ready
        // bitField PRWTIMER_R0{0, 1, RO}; //32/64-Bit Wide General-Purpose Timer 0 Peripheral Ready

};


#endif //GENERAL_PURPOSE_TIMER_H
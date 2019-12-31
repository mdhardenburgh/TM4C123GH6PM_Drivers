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

#include "../register.h"

enum timerMode
{
    oneShot, periodic, realTimeClock, inputEdgeCount, inputEdgeTime, PWM
};

class GeneralPurposeTimer
{
    public:
        GeneralPurposeTimer();
        ~GeneralPurposeTimer();

    protected:

        uint32_t GPTMCFG = 0x000; // 0x000 GPTMCFG RW 0x0000.0000 GPTM Configuration 727
        uint32_t GPTMTAMR = 0x004; // 0x004 GPTMTAMR RW 0x0000.0000 GPTM Timer A Mode 729
        uint32_t GPTMTBMR = 0x008; // 0x008 GPTMTBMR RW 0x0000.0000 GPTM Timer B Mode 733
        uint32_t GPTMCTL = 0x00C; // 0x00C GPTMCTL RW 0x0000.0000 GPTM Control 737
        uint32_t GPTMSYNC = 0x010; // 0x010 GPTMSYNC RW 0x0000.0000 GPTM Synchronize 741
        uint32_t GPTMIMR = 0x018; // 0x018 GPTMIMR RW 0x0000.0000 GPTM Interrupt Mask 745
        uint32_t GPTMRIS = 0x01C; // 0x01C GPTMRIS RO 0x0000.0000 GPTM Raw Interrupt Status 748
        uint32_t GPTMMIS = 0x020; // 0x020 GPTMMIS RO 0x0000.0000 GPTM Masked Interrupt Status 751
        uint32_t GPTMICR = 0x024; // 0x024 GPTMICR W1C 0x0000.0000 GPTM Interrupt Clear 754
        uint32_t GPTMTAILR = 0x028; // 0x028 GPTMTAILR RW 0xFFFF.FFFF GPTM Timer A Interval Load 756
        uint32_t GPTMTBILR = 0x02C; // 0x02C GPTMTBILR RW - GPTM Timer B Interval Load 757
        uint32_t GPTMTAMATCHR = 0x030; // 0x030 GPTMTAMATCHR RW 0xFFFF.FFFF GPTM Timer A Match 758
        uint32_t GPTMTBMATCHR = 0x034; // 0x034 GPTMTBMATCHR RW - GPTM Timer B Match 759
        uint32_t GPTMTAPR = 0x038; // 0x038 GPTMTAPR RW 0x0000.0000 GPTM Timer A Prescale 760
        uint32_t GPTMTBPR = 0x03C; // 0x03C GPTMTBPR RW 0x0000.0000 GPTM Timer B Prescale 761
        uint32_t GPTMTAPMR = 0x040; // 0x040 GPTMTAPMR RW 0x0000.0000 GPTM TimerA Prescale Match 762
        uint32_t GPTMTBPMR = 0x044; // 0x044 GPTMTBPMR RW 0x0000.0000 GPTM TimerB Prescale Match 763
        uint32_t GPTMTAR = 0x048; // 0x048 GPTMTAR RO 0xFFFF.FFFF GPTM Timer A 764
        uint32_t GPTMTBR = 0x04C; // 0x04C GPTMTBR RO - GPTM Timer B 765
        uint32_t GPTMTAV = 0x050; // 0x050 GPTMTAV RW 0xFFFF.FFFF GPTM Timer A Value 766
        uint32_t GPTMTBV = 0x054; // 0x054 GPTMTBV RW - GPTM Timer B Value 767
        uint32_t GPTMRTCPD = 0x058; // 0x058 GPTMRTCPD RO 0x0000.7FFF GPTM RTC Predivide 768
        uint32_t GPTMTAPS = 0x05C; // 0x05C GPTMTAPS RO 0x0000.0000 GPTM Timer A Prescale Snapshot 769
        uint32_t GPTMTBPS = 0x060; // 0x060 GPTMTBPS RO 0x0000.0000 GPTM Timer B Prescale Snapshot 770
        uint32_t GPTMTAPV = 0x064; // 0x064 GPTMTAPV RO 0x0000.0000 GPTM Timer A Prescale Value 771
        uint32_t GPTMTBPV = 0x068; // 0x068 GPTMTBPV RO 0x0000.0000 GPTM Timer B Prescale Value 772
        uint32_t GPTMPP = 0xFC0; // 0xFC0 GPTMPP RO 0x0000.0000 GPTM Peripheral Properties 773

    private:

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC2_TIMER3{19, 1, RO}; //Timer Module 3 Present. When set, indicates that General-Purpose Timer module 3 is present.
        bitField DC2_TIMER2{18, 1, RO}; //Timer Module 2 Present. When set, indicates that General-Purpose Timer module 2 is present.
        bitField DC2_TIMER1{17, 1, RO}; //Timer Module 1 Present. When set, indicates that General-Purpose Timer module 1 is present.
        bitField DC2_TIMER0{16, 1, RO}; //Timer Module 0 Present. When set, indicates that General-Purpose Timer module 0 is present.

        bitField SRCR1_TIMER3{19, 1, RO}; //Timer 3 Reset Control
        bitField SRCR1_TIMER2{18, 1, RO}; //Timer 2 Reset Control
        bitField SRCR1_TIMER1{17, 1, RO}; //Timer 1 Reset Control
        bitField SRCR1_TIMER0{16, 1, RO}; //Timer 0 Reset Control

        bitField RCGC1_TIMER3{19, 1, RO}; //Timer 3 Clock Gating Control
        bitField RCGC1_TIMER2{18, 1, RO}; //Timer 2 Clock Gating Control
        bitField RCGC1_TIMER1{17, 1, RO}; //Timer 1 Clock Gating Control
        bitField RCGC1_TIMER0{16, 1, RO}; //Timer 0 Clock Gating Control

        bitField SCGC1_TIMER3{19, 1, RO}; //Timer 3 Clock Gating Control
        bitField SCGC1_TIMER2{18, 1, RO}; //Timer 2 Clock Gating Control
        bitField SCGC1_TIMER1{17, 1, RO}; //Timer 1 Clock Gating Control
        bitField SCGC1_TIMER0{16, 1, RO}; //Timer 0 Clock Gating Control

        bitField DCGC1_TIMER3{19, 1, RO}; //Timer 3 Clock Gating Control
        bitField DCGC1_TIMER2{18, 1, RO}; //Timer 2 Clock Gating Control
        bitField DCGC1_TIMER1{17, 1, RO}; //Timer 1 Clock Gating Control
        bitField DCGC1_TIMER0{16, 1, RO}; //Timer 0 Clock Gating Control
        

};


#endif //GENERAL_PURPOSE_TIMER_H
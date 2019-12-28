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
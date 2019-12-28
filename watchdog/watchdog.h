/**
 * @file watchdog.h
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
 * Watchdog Register Descriptions
 * 
 * The remainder of this section lists and describes the WDT registers, in 
 * numerical order by address offset.
 */
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "../systemControl/systemControl.h"

class Watchdog : SystemControl
{
    public:
        Watchdog();
        ~Watchdog();

    private:
        const uint32_t watchdog0BaseAddress = 0x40000000;
        const uint32_t watchdog1BaseAddress = 0x40001000;

/**********************System Control Register Descriptions********************/

        Register PPWD{(volatile uint32_t*)(systemControlBase + 0x300)}; //0x300 PPWD RO 0x0000.0003 Watchdog Timer Peripheral Present 287
        Register SRWD{(volatile uint32_t*)(systemControlBase + 0x500)}; //0x500 SRWD RW 0x0000.0000 Watchdog Timer Software Reset 310
        Register RCGCWD{(volatile uint32_t*)(systemControlBase + 0x600)}; //0x600 RCGCWD RW 0x0000.0000 Watchdog Timer Run Mode Clock Gating Control 337
        Register SCGCWD{(volatile uint32_t*)(systemControlBase + 0x700)}; //0x700 SCGCWD RW 0x0000.0000 Watchdog Timer Sleep Mode Clock Gating Control 359
        Register DCGCWD{(volatile uint32_t*)(systemControlBase + 0x800)}; //0x800 DCGCWD RW 0x0000.0000 Watchdog Timer Deep-Sleep Mode Clock Gating Control 381
        Register PRWD{(volatile uint32_t*)(systemControlBase + 0xA00)}; //0xA00 PRWD RO 0x0000.0000 Watchdog Timer Peripheral Ready 403

/**************************System Control BitFields****************************/

        bitField RESC_WDT1{5, 1, RW}; //Watchdog Timer 1 Reset
        bitField RESC_WDT0{3, 1, RW}; //Watchdog Timer 0 Reset

        bitField PPWD_P1{1, 1, RO}; //Watchdog Timer 1 Present
        bitField PPWD_P0{0, 1, RO}; //Watchdog Timer 0 Present

        bitField SRWD_R1{1, 1, RW}; //Watchdog Timer 1 Software Reset
        bitField SRWD_R0{0, 1, RW}; //Watchdog Timer 0 Software Reset

        bitField RCGCWD_R1{1, 1, RW}; //Watchdog Timer 1 Run Mode Clock Gating Control
        bitField RCGCWD_R0{0, 1, RW}; //Watchdog Timer 0 Run Mode Clock Gating Control

        bitField SCGCWD_S1{1, 1, RW}; //Watchdog Timer 1 Sleep Mode Clock Gating Control
        bitField SCGCWD_S0{0, 1, RW}; //Watchdog Timer 0 Sleep Mode Clock Gating Control

        bitField DCGCWD_D1{1, 1, RW}; //Watchdog Timer 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCWD_D0{0, 1, RW}; //Watchdog Timer 0 Deep-Sleep Mode Clock Gating Control

        bitField PRWD_R1{1, 1, RO}; //Watchdog Timer 1 Peripheral Ready
        bitField PRWD_R0{0, 1, RO}; //Watchdog Timer 0 Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC1_WDT1{28, 1, RO}; //Watchdog Timer 1 Present. When set, indicates that watchdog timer 1 is present.
        bitField DC1_WDT0{3, 1, RO}; //Watchdog Timer 0 Present. When set, indicates that watchdog timer 0 is present.
        bitField SRCR0_WDT1{28, 1, RO}; //WDT1 Reset Control
        bitField SRCR0_WDT0{3, 1, RO}; //WDT0 Reset Control
        bitField RCGC0_WDT1{28, 1, RO}; //WDT1 Clock Gating Control
        bitField RCGC0_WDT0{3, 1, RO}; //WDT0 Clock Gating Control
        bitField SCGC0_WDT1{28, 1, RO}; //WDT1 Clock Gating Control
        bitField SCGC0_WDT0{3, 1, RO}; //WDT0 Clock Gating Control
        bitField DCGC0_WDT1{28, 1, RO}; //WDT1 Clock Gating Control
        bitField DCGC0_WDT0{3, 1, RO}; //WDT0 Clock Gating Control


};

#endif
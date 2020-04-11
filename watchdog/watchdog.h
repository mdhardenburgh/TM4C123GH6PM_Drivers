/**
 * @file watchdog.h
 * @brief TM4C123GH6PM Watchdog Driver Declaration
 * @author Matthew Hardenburgh
 * @version 0.1
 * @date 3/21/2020
 * @copyright Matthew Hardenburgh 2020
 * 
 * @section license LICENSE
 * 
 * TM4C123GH6PM Drivers
 * Copyright (C) 2020  Matthew Hardenburgh
 * mdhardenburgh@protonmail.com
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
 */

/**
 * @class Watchdog
 * @brief TM4C123GH6PM Watchdog Driver
 * 
 * @section watchdogDescription Watchdog Description
 * 
 * The TM4C123GH6PM microcontroller has 2 Watchdog timer modules. Watchdog Timer
 * 0 is clocked by the main system clock, and Watchdog Timer 2 is clocked by the 
 * precision internal oscillator \c PIOSC . WDT 1 is in a different clock domain
 * and requires synchronizers. To this end, there is a bit in Watchdog Timer 
 * Control Register (WDTCTL) to indicated that a write to WDT1 is completed.
 * Driver software can use this bit to make sure that the previous access has
 * completed before moving on to the nex one. The Watchdog Timer is used to 
 * attempt to regain control of a system that has failed. The Watchdog timer can 
 * generate an interrupt, NMI or system reset when the time out value is reached. 
 * 
 * The Watchdog Timer has the following features:
 *      - 32-bit down counter with a programmable load register
 *      - Separate watchdog clock with an enable
 *      - Programmable interrupt generation logic with interrupt masking and optional NMI function
 *      - Lock register protection from runaway software
 *      - Reset generation logic with an enable/disable
 *      - User-enabled stalling when the microcontroller asserts the CPU Halt flag during debug
 * 
 * The Watchdog Timer has a lock register to prevent the configuration from 
 * being accidentally altered.
 * 
 * For more detailed information on the Watchdog please see page 774 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection watchdogDescription Watchdog  Description
 * 
 * A Watchdog timer is like that strange timer in the bunker from the show Lost.
 * The processor has to periodically check and reset the timer to verify that
 * the processor is not stuck. Else the Watchdog resets the system in the hopes
 * of un-stucking the processor. This is used in embedded enviroments where 
 * the user might not know how to fix or troubleshoot what is going wrong.
 * In the TM4C123GH6PM microcontroller, the Watchdog timer has two countdown 
 * periods. After the first countdown an interupt is generated and a second 
 * count down begins. 
 * 
 */

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "../systemControl/systemControl.h"

class Watchdog
{
    public:
        Watchdog();
        ~Watchdog();

    private:

        static const uint32_t watchdog0BaseAddress = 0x40000000;
        static const uint32_t watchdog1BaseAddress = 0x40001000;

        static const uint32_t PPWD_OFFSET = 0x300; //0x300 PPWD RO 0x0000.0003 Watchdog Timer Peripheral Present 287
        static const uint32_t SRWD_OFFSET = 0x500; //0x500 SRWD RW 0x0000.0000 Watchdog Timer Software Reset 310
        static const uint32_t RCGCWD_OFFSET = 0x600; //0x600 RCGCWD RW 0x0000.0000 Watchdog Timer Run Mode Clock Gating Control 337
        static const uint32_t SCGCWD_OFFSET = 0x700; //0x700 SCGCWD RW 0x0000.0000 Watchdog Timer Sleep Mode Clock Gating Control 359
        static const uint32_t DCGCWD_OFFSET = 0x800; //0x800 DCGCWD RW 0x0000.0000 Watchdog Timer Deep-Sleep Mode Clock Gating Control 381
        static const uint32_t PRWD_OFFSET = 0xA00; //0xA00 PRWD RO 0x0000.0000 Watchdog Timer Peripheral Ready 403

        static const uint32_t WDTLOAD = 0x000; // 0x000 WDTLOAD RW 0xFFFF.FFFF Watchdog Load 778
        static const uint32_t WDTVALUE = 0x004; // 0x004 WDTVALUE RO 0xFFFF.FFFF Watchdog Value 779
        static const uint32_t WDTCTL = 0x008; // 0x008 WDTCTL RW 0x0000.0000 (WDT0) 0x8000.0000 (WDT1) Watchdog Control 780
        static const uint32_t WDTICR = 0x00C; // 0x00C WDTICR WO - Watchdog Interrupt Clear 782
        static const uint32_t WDTRIS = 0x010; // 0x010 WDTRIS RO 0x0000.0000 Watchdog Raw Interrupt Status 783
        static const uint32_t WDTMIS = 0x014; // 0x014 WDTMIS RO 0x0000.0000 Watchdog Masked Interrupt Status 784
        static const uint32_t WDTTEST = 0x418; // 0x418 WDTTEST RW 0x0000.0000 Watchdog Test 785
        static const uint32_t WDTLOCK = 0xC00; // 0xC00 WDTLOCK RW 0x0000.0000 Watchdog Lock 786
        static const uint32_t WDTPeriphID4 = 0xFD0; // 0xFD0 WDTPeriphID4 RO 0x0000.0000 Watchdog Peripheral Identification 4 787
        static const uint32_t WDTPeriphID5 = 0xFD4; // 0xFD4 WDTPeriphID5 RO 0x0000.0000 Watchdog Peripheral Identification 5 788
        static const uint32_t WDTPeriphID6 = 0xFD8; // 0xFD8 WDTPeriphID6 RO 0x0000.0000 Watchdog Peripheral Identification 6 789
        static const uint32_t WDTPeriphID7 = 0xFDC; // 0xFDC WDTPeriphID7 RO 0x0000.0000 Watchdog Peripheral Identification 7 790
        static const uint32_t WDTPeriphID0 = 0xFE0; // 0xFE0 WDTPeriphID0 RO 0x0000.0005 Watchdog Peripheral Identification 0 791
        static const uint32_t WDTPeriphID1 = 0xFE4; // 0xFE4 WDTPeriphID1 RO 0x0000.0018 Watchdog Peripheral Identification 1 792
        static const uint32_t WDTPeriphID2 = 0xFE8; // 0xFE8 WDTPeriphID2 RO 0x0000.0018 Watchdog Peripheral Identification 2 793
        static const uint32_t WDTPeriphID3 = 0xFEC; // 0xFEC WDTPeriphID3 RO 0x0000.0001 Watchdog Peripheral Identification 3 794
        static const uint32_t WDTPCellID0 = 0xFF0; // 0xFF0 WDTPCellID0 RO 0x0000.000D Watchdog PrimeCell Identification 0 795
        static const uint32_t WDTPCellID1 = 0xFF4; // 0xFF4 WDTPCellID1 RO 0x0000.00F0 Watchdog PrimeCell Identification 1 796
        static const uint32_t WDTPCellID2 = 0xFF8; // 0xFF8 WDTPCellID2 RO 0x0000.0006 Watchdog PrimeCell Identification 2 797
        static const uint32_t WDTPCellID3 = 0xFFC; // 0xFFC WDTPCellID3 RO 0x0000.00B1 Watchdog PrimeCell Identification 3 798 
 
};

#endif
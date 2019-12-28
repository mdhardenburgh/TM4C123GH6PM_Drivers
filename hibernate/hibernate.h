/**
 * @file hibernate.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/17/2019
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
 * Register Descriptions
 * 
 * The remainder of this section lists and describes the Hibernation module 
 * registers, in numerical order by address offset.
 */
#ifndef HIBERNATE_H
#define HIBERNATE_H

#include "../systemControl/systemControl.h"

class Hibernate : SystemControl
{
    public:
        Hibernate();
        ~Hibernate();

    private:
        const uint32_t hibernateBase = 0x400FC000;

/**********************System Control Register Descriptions********************/

        Register PPHIB{(volatile uint32_t*)(systemControlBase + 0x314)}; //0x314 PPHIB RO 0x0000.0001 Hibernation Peripheral Present 294
        Register SRHIB{(volatile uint32_t*)(systemControlBase + 0x514)}; //0x514 SRHIB RW 0x0000.0000 Hibernation Software Reset 317
        Register RCGCHIB{(volatile uint32_t*)(systemControlBase + 0x614)}; //0x614 RCGCHIB RW 0x0000.0001 Hibernation Run Mode Clock Gating Control 343
        Register SCGCHIB{(volatile uint32_t*)(systemControlBase + 0x714)}; //0x714 SCGCHIB RW 0x0000.0001 Hibernation Sleep Mode Clock Gating Control 365
        Register DCGCHIB{(volatile uint32_t*)(systemControlBase + 0x814)}; //0x814 DCGCHIB RW 0x0000.0001 Hibernation Deep-Sleep Mode Clock Gating Control 387
        Register PRHIB{(volatile uint32_t*)(systemControlBase + 0xA14)}; //0xA14 PRHIB RO 0x0000.0001 Hibernation Peripheral Ready 409

/**************************System Control BitFields****************************/

        bitField PPHIB_P0{0, 1, RO}; //Hibernation Module Present
        bitField SRHIB_R0{0, 1, RW}; //Hibernation Module Software Reset
        bitField RCGCHIB_RO{0, 1, RW}; //Hibernation Module Run Mode Clock Gating Control
        bitField SCGCHIB_S0{0, 1, RW}; //Hibernation Module Sleep Mode Clock Gating Control
        bitField DCGCHIB_D0{0, 1, RW}; //Hibernation Module Deep-Sleep Mode Clock Gating Control
        bitField PRHIB_R0{0, 1, RO}; //Hibernation Module Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC1_HIB{6, 1, RO}; //Hibernation Module Present. When set, indicates that the Hibernation module is present.
        bitField SRCR0_HIB{6, 1, RO}; //HIB Reset Control
        bitField RCGC0_HIB{6, 1, RO}; //HIB Clock Gating Control
        bitField SCGC0_HIB{6, 1, RO}; //HIB Clock Gating Control
        bitField DCGC0_HIB{6, 1, RO}; //HIB Clock Gating Control


};

#endif
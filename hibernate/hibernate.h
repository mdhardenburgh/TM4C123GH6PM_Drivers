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

class Hibernate
{
    public:
        Hibernate();
        ~Hibernate();

    private:
        static const uint32_t hibernateBase = 0x400FC000;

        static const uint32_t PPHIB_OFFSET = 0x314; //0x314 PPHIB RO 0x0000.0001 Hibernation Peripheral Present 294
        static const uint32_t SRHIB_OFFSET = 0x514; //0x514 SRHIB RW 0x0000.0000 Hibernation Software Reset 317
        static const uint32_t RCGCHIB_OFFSET = 0x614; //0x614 RCGCHIB RW 0x0000.0001 Hibernation Run Mode Clock Gating Control 343
        static const uint32_t SCGCHIB_OFFSET = 0x714; //0x714 SCGCHIB RW 0x0000.0001 Hibernation Sleep Mode Clock Gating Control 365
        static const uint32_t DCGCHIB_OFFSET = 0x814; //0x814 DCGCHIB RW 0x0000.0001 Hibernation Deep-Sleep Mode Clock Gating Control 387
        static const uint32_t PRHIB_OFFSET = 0xA14; //0xA14 PRHIB RO 0x0000.0001 Hibernation Peripheral Ready 409

};

#endif
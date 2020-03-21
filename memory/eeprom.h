/**
 * @file eeprom.h
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
 * EEPROM Register Descriptions (EEPROM Offset)
 * 
 * This section lists and describes the EEPROM registers, in numerical order by 
 * address offset. Registers in this section are relative to the EEPROM base 
 * address of 0x400A.F000.
 * 
 * Note that the EEPROM module clock must be enabled before the registers can be 
 * programmed (see page 356). There must be a delay of 3 system clocks after the 
 * EEPROM module clock is enabled before any EEPROM module registers are 
 * accessed. In addition, after enabling or resetting the EEPROM module, 
 * software must wait until the WORKING bit in the EEDONE register is clear 
 * before accessing any EEPROM registers.
 */

#ifndef EEPROM_H
#define EEPROM_H

#include "../systemControl/systemControl.h"


class Eeprom : SystemControl
{
    public:
        Eeprom();
        ~Eeprom();

    private:

        static const uint32_t eepromBase = 0x400AF000;

        static const uint32_t PPEEPROM = 0x358; //0x358 PPEEPROM RO 0x0000.0001 EEPROM Peripheral Present 307
        static const uint32_t SREEPROM = 0x558; //0x558 SREEPROM RW 0x0000.0000 EEPROM Software Reset 334
        static const uint32_t RCGCEEPROM = 0x658; //0x658 RCGCEEPROM RW 0x0000.0000 EEPROM Run Mode Clock Gating Control 356
        static const uint32_t SCGCEEPROM = 0x758; //0x758 SCGCEEPROM RW 0x0000.0000 EEPROM Sleep Mode Clock Gating Control 378
        static const uint32_t DCGCEEPROM = 0x858; //0x858 DCGCEEPROM RW 0x0000.0000 EEPROM Deep-Sleep Mode Clock Gating Control 400
        static const uint32_t PREEPROM = 0xA58; //0xA58 PREEPROM RO 0x0000.0000 EEPROM Peripheral Ready 422

};


#endif
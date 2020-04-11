/**
 * @file eeprom.h
 * @brief TM4C123GH6PM EEPROM Driver Declaration
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
 * @class Eeprom
 * @brief TM4C123GH6PM EEPROM Driver
 * 
 * @section eepromDescription EEPROM Description
 * 
 * The TM4C123GH6PM microcontroller has 2KB of on chip EEPROM. The EEPROM also 
 * has a register interface to access the EEPROM that can be used in a random
 * access style, rolling or sequential. EEPROM blocks can be password locked by
 * an application.
 * 
 * For more detailed information on the EEPROM please see page 524 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 */

#ifndef EEPROM_H
#define EEPROM_H

#include "../systemControl/systemControl.h"


class Eeprom
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


        static const uint32_t EESIZE_OFFSET = 0x000; // 0x000 EESIZE RO 0x0020.0200 EEPROM Size Information 560
        static const uint32_t EEBLOCK_OFFSET = 0x004; // 0x004 EEBLOCK RW 0x0000.0000 EEPROM Current Block 561
        static const uint32_t EEOFFSET_OFFSET = 0x008; // 0x008 EEOFFSET RW 0x0000.0000 EEPROM Current Offset 562
        static const uint32_t EERDWR_OFFSET = 0x010; // 0x010 EERDWR RW - EEPROM Read-Write 563
        static const uint32_t EERDWRINC_OFFSET = 0x014; // 0x014 EERDWRINC RW - EEPROM Read-Write with Increment 564
        static const uint32_t EEDONE_OFFSET = 0x018; // 0x018 EEDONE RO 0x0000.0000 EEPROM Done Status 565
        static const uint32_t EESUPP_OFFSET = 0x01C; // 0x01C EESUPP RW - EEPROM Support Control and Status 567
        static const uint32_t EEUNLOCK_OFFSET = 0x020; // 0x020 EEUNLOCK RW - EEPROM Unlock 569
        static const uint32_t EEPROT_OFFSET = 0x030; // 0x030 EEPROT RW 0x0000.0000 EEPROM Protection 570
        static const uint32_t EEPASS0_OFFSET = 0x034; // 0x034 EEPASS0 RW - EEPROM Password 572
        static const uint32_t EEPASS1_OFFSET = 0x038; // 0x038 EEPASS1 RW - EEPROM Password 572
        static const uint32_t EEPASS2_OFFSET = 0x03C; // 0x03C EEPASS2 RW - EEPROM Password 572
        static const uint32_t EEINT_OFFSET = 0x040; // 0x040 EEINT RW 0x0000.0000 EEPROM Interrupt 573
        static const uint32_t EEHIDE_OFFSET = 0x050; // 0x050 EEHIDE RW 0x0000.0000 EEPROM Block Hide 574
        static const uint32_t EEDBGME_OFFSET = 0x080; // 0x080 EEDBGME RW 0x0000.0000 EEPROM Debug Mass Erase 575
        static const uint32_t EEPROMPP_OFFSET = 0xFC0; // 0xFC0 EEPROMPP RO 0x0000.001F EEPROM Peripheral Properties 576


};


#endif
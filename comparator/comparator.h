/**
 * @file comparator.h
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
 * Analog Comparators Register Descriptions
 * 
 * The remainder of this section lists and describes the Analog Comparator 
 * registers, in numerical order by address offset.
 */

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "../systemControl/systemControl.h"


class Comparator 
{
    public:
        Comparator();
        ~Comparator();

    private:

        static const uint32_t analogComparatorBaseAddress = 0x4003C000;

        static const uint32_t PPACMP_OFFSET = 0x33C; //0x33C PPACMP RO 0x0000.0001 Analog Comparator Peripheral Present 304
        static const uint32_t SRACMP_OFFSET = 0x53C; //0x53C SRACMP RW 0x0000.0000 Analog Comparator Software Reset 329
        static const uint32_t RCGCACMP_OFFSET = 0x63C; //0x63C RCGCACMP RW 0x0000.0000 Analog Comparator Run Mode Clock Gating Control 353
        static const uint32_t SCGCACMP_OFFSET = 0x73C; //0x73C SCGCACMP RW 0x0000.0000 Analog Comparator Sleep Mode Clock Gating Control 375
        static const uint32_t DCGCACMP_OFFSET = 0x83C; //0x83C DCGCACMP RW 0x0000.0000 Analog Comparator Deep-Sleep Mode Clock Gating Control 397
        static const uint32_t PRACMP_OFFSET = 0xA3C; //0xA3C PRACMP RO 0x0000.0000 Analog Comparator Peripheral Ready 419


};

#endif //COMPARATOR_H
/**
 * @file comparator.h
 * @brief TM4C123GH6PM Comparator Driver Declaration
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
 * @class Comparator
 * @brief TM4C123GH6PM Comparator Driver
 * 
 * @section comparatorDescription Comparator Description
 * 
 * The TM4C123GH6PM microcontroller analog comparator compares two analog 
 * volatages and provides a binary output as the result. Note that not all 
 * comparators can drive an output pin, see Signal Description section 
 * below for more detials. The analog comparator can provide its output to a
 * device pin, replacing the need for a discrete analog comparator on the board.
 * The comparator can also flag the start of an ADC sample sequence. The analog
 * comparator can also generate interrupts.
 *
 * The TM4C123GH6PM microcontroller has two independent analog comparators with 
 * the following functions:
 *      - Compare external pin input to external pin input or to internal 
 *        programmable voltage reference
 *      - Compare a test voltage against any one of the following voltages:
 *          - An individual external reference voltage
 *          - A shared single external reference voltage
 *          - A shared internal reference voltage
 * 
 * For more detailed information on the Analog Comparator please see page 1215 
 * of the TM4C123GH6PM datasheet 
 * @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection comparatorSignalDescription Comparator Signal Description
 * 
 * The following table lists the GPIO pin mux and physical pin number of the
 * pins that can be muxed for use by the Analog Comparator. The \c AFSEL bit in 
 * the GPIO Alternate Function Select (GPIOAFSEL) register should be set to choose 
 * the Analog Comparator function. The number in parentheses is the encoding 
 * that must be programmed into the \c PMCn field in the GPIO Port Control 
 * (GPIOPCTL) register to assign the Analog Comparator signal to the specified 
 * GPIO port pin. The positive and negative input signals are configured by 
 * clearing the DEN bit in the GPIO Digital Enable (GPIODEN) register.
 * 
 * @image html comparatorSignals.png
 * @image latex comparatorSignals.png
 * 
 * @subsection comparatorSystemControlRegisterDescription Comparator System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Legacy registers not supported.
 * 
 * @subsection comparatorRegisterDescription Comparator Register Description
 * 
 * The Comparator class contains a list of CAN registers listed as an offset relative
 * to the hexadecimal base address of the Comparator module block. Note 
 * that the Comparator clock must be enabled before the registers can be 
 * programmed. There must be a delay of 3 system clocks after the comparator  
 * clock is enabled before any comparator registers are accessed.
 * 
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

        static const uint32_t ACMIS_OFFSET = 0x000; // 0x000 ACMIS RW1C 0x0000.0000 Analog Comparator Masked Interrupt Status 1222
        static const uint32_t ACRIS_OFFSET = 0x004; // 0x004 ACRIS RO 0x0000.0000 Analog Comparator Raw Interrupt Status 1223
        static const uint32_t ACINTEN_OFFSET = 0x008; // 0x008 ACINTEN RW 0x0000.0000 Analog Comparator Interrupt Enable 1224
        static const uint32_t ACREFCTL_OFFSET = 0x010; // 0x010 ACREFCTL RW 0x0000.0000 Analog Comparator Reference Voltage Control 1225
        static const uint32_t ACSTAT0_OFFSET = 0x020; // 0x020 ACSTAT0 RO 0x0000.0000 Analog Comparator Status 0 1226
        static const uint32_t ACCTL0_OFFSET = 0x024; // 0x024 ACCTL0 RW 0x0000.0000 Analog Comparator Control 0 1227
        static const uint32_t ACSTAT1_OFFSET = 0x040; // 0x040 ACSTAT1 RO 0x0000.0000 Analog Comparator Status 1 1226
        static const uint32_t ACCTL1_OFFSET = 0x044; // 0x044 ACCTL1 RW 0x0000.0000 Analog Comparator Control 1 1227
        static const uint32_t ACMPPP_OFFSET = 0xFC0; // 0xFC0 ACMPPP RO 0x0003.0003 Analog Comparator Peripheral Properties 1229


};

#endif //COMPARATOR_H
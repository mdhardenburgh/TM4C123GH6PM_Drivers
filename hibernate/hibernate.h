/**
 * @file hibernate.h
 * @brief TM4C123GH6PM Hibernate Driver Declaration
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
 * @class Hibernate
 * @brief TM4C123GH6PM Hibernate Driver
 * 
 * @section hibernateDescription Hibernate Module Description
 * 
 * The hibernatation module allows for power to be removed from the the 
 * processor and peripherals to reduce system power consumption. The hibernation
 * module can be independently powered, seperately from system main power. Main
 * power can be restored based on an external signal or after a certian time 
 * using the RTC. The hibernation module has the following features
 *      - A 32-bit real time counter (RTC)
 *      - System power control using discrete external regulator
 *      - On-chip power control using internal switches under register control
 *      - Dedicated pin for waking using an external signal
 *      - RTC operational and hibernation memory valid as long as VDD or VBAT is valid
 *      - Low-battery detection, signaling, and interrupt generation, with 
 *        optional wake on low battery
 *      - GPIO pin state can be retained during hibernation
 *      - Clock source from a 32.768-kHz external crystal or oscillator
 *      - Sixteen 32-bit words of battery-backed memory to save state during hibernation
 *      - Programmable interrupts for RTC match, External wake, and/or Low battery
 * 
 * For more detailed information on the Hibernate please see page 493 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection hibernateSignalDescription Hibernate Signal Description
 * 
 * The following table lists the hibernate module's external signals. The 
 * Hibernate module has no GPIO connections.
 * 
 * @image html hibernateSignalPins.png
 * @image latex hibernateSignalPins.png
 * 
 * @image html hibernateSignalPins2.png
 * @image latex hibernateSignalPins2.png
 * 
 * @subsection hibernateSystemControlRegisterDescription Hibernate System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Legacy registers not supported.
 * 
 * @subsection hibernateRegisterDescription Hibernate Register Description
 * 
 * The Hibernate class lists registers as an offset of the hexadecimal base 
 * address 0x400FC000. Note that the Hibernate module clock must be enabled 
 * before the registers can be programmed (see page 343). There must be a delay 
 * of 3 system clocks after the Hibernate module clock is enabled before any 
 * Hibernate module registers are accessed. In addition, the \c CLK32EN bit in the 
 * HIBCTL register must be set before accessing any other Hibernation module 
 * register.
 * 
 * Important Note
 * 
 * The Hibernation module registers are on the Hibernation module clock domain 
 * and have special timing requirements. Software should make use of the \c WRC 
 * bit in the HIBCTL register to ensure that the required timing gap has elapsed. 
 * If the \c WRC bit is clear, any attempted write access is ignored. See 
 * “Register Access Timing” on page 495.
 * 
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
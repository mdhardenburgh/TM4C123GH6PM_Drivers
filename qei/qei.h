/**
 * @file qei.h
 * @brief TM4C123GH6PM QEI Driver Declaration
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
 * @class Qei
 * @brief TM4C123GH6PM QEI Driver
 * 
 * @section qeiDescription QEI Description
 * 
 * The TM4C123GH6PM microcontroller has two QEI modules. The QEI module is used 
 * to calculate linar displacement, direction of rotation and speed. This is 
 * useful for robotics to provide control of motors. The QEI has the following
 * features:
 *      - Position integrator that tracks the encoder position
 *      - Programmable noise filter on the inputs
 *      - Velocity capture using built-in timer
 *      - The input frequency of the QEI inputs may be as high as 1/4 of 
 *        the processor frequency (for example, 12.5 MHz for a 50-MHz system)
 *      - Interrupt generation on:
 *          - Index pulse
 *          - Velocity-timer expiration
 *          - Direction change
 *          - Quadrature error detection
 * 
 * For more detailed information on the QEI please see page 1305 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection qeiSignalDescription QEI Signal Description
 * 
 * The following table lists the external signals and thier associtated pins 
 * for the QEI module. The GPIO needs to be configured for the QEI alternate
 * function using the \c AFSEL bit in the GPIO Alternate Function Register 
 * (GPIOAFSEL). The number in parenthesis in the Pin Mux / Pin Assignment 
 * column of the table below is what is programmed into the \c PMCn field in
 * the GPIO Port Control (GPIOPCTL) register to assign a QEI signal to a GPIO. 
 * 
 * @image html qeiSignalPins.png
 * @image latex qeiSignalPins.png
 * 
 */


#ifndef QEI_H
#define QEI_H

#include "../systemControl/systemControl.h"

class Qei
{
    public:
        Qei();
        ~Qei();

    private:

        static const uint32_t qei0BaseAddress = 0x4002C000;
        static const uint32_t qei1BaseAddress = 0x4002D000;

        static const uint32_t PPQEI_OFFSET = 0x344; //0x344 PPQEI RO 0x0000.0003 Quadrature Encoder Interface Peripheral Present 306
        static const uint32_t SRQEI_OFFSET = 0x544; //0x544 SRQEI RW 0x0000.0000 Quadrature Encoder Interface Software Reset 332
        static const uint32_t RCGCQEI_OFFSET = 0x644; //0x644 RCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Run Mode Clock Gating Control 355
        static const uint32_t SCGCQEI_OFFSET = 0x744; //0x744 SCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Sleep Mode Clock Gating Control 377
        static const uint32_t DCGCQEI_OFFSET = 0x844; //0x844 DCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control 399
        static const uint32_t PRQEI_OFFSET = 0xA44; //0xA44 PRQEI RO 0x0000.0000 Quadrature Encoder Interface Peripheral Ready 421

        static const uint32_t QEICTL_OFFSET = 0x000; // 0x000 QEICTL RW 0x0000.0000 QEI Control 1312
        static const uint32_t QEISTAT_OFFSET = 0x004; // 0x004 QEISTAT RO 0x0000.0000 QEI Status 1315
        static const uint32_t QEIPOS_OFFSET = 0x008; // 0x008 QEIPOS RW 0x0000.0000 QEI Position 1316
        static const uint32_t QEIMAXPOS_OFFSET = 0x00C; // 0x00C QEIMAXPOS RW 0x0000.0000 QEI Maximum Position 1317
        static const uint32_t QEILOAD_OFFSET = 0x010; // 0x010 QEILOAD RW 0x0000.0000 QEI Timer Load 1318
        static const uint32_t QEITIME_OFFSET = 0x014; // 0x014 QEITIME RO 0x0000.0000 QEI Timer 1319
        static const uint32_t QEICOUNT_OFFSET = 0x018; // 0x018 QEICOUNT RO 0x0000.0000 QEI Velocity Counter 1320
        static const uint32_t QEISPEED_OFFSET = 0x01C; // 0x01C QEISPEED RO 0x0000.0000 QEI Velocity 1321
        static const uint32_t QEIINTEN_OFFSET = 0x020; // 0x020 QEIINTEN RW 0x0000.0000 QEI Interrupt Enable 1322
        static const uint32_t QEIRIS_OFFSET = 0x024; // 0x024 QEIRIS RO 0x0000.0000 QEI Raw Interrupt Status 1324
        static const uint32_t QEIISC_OFFSET = 0x028; // 0x028 QEIISC RW1C 0x0000.0000 QEI Interrupt Status and Clear 1326

};

#endif //QUI_H
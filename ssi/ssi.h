/**
 * @file ssi.h
 * @brief TM4C123GH6PM SSI Driver Declaration
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
 * @class Ssi
 * @brief TM4C123GH6PM SSI Driver
 * 
 * @section ssiDescription SSI Description
 * 
 * The TM4C123GH6PM microcontroller has four SSI modules. The SSI is used to 
 * communicate with peripheral devices that have the Freescale SPI, Microwire or
 * TI SSI interfaces. Each SSI module can act as a master or slave. The
 * TM4C123GH6PM microcontroller SSI modules have the following features:
 *      - Programmable interface operation for Freescale SPI, MICROWIRE, or 
 *        Texas Instruments synchronous serial interfaces
 *      - Master or slave operation
 *      - Programmable clock bit rate and prescaler
 *      - Separate transmit and receive FIFOs, each 16 bits wide and 8 locations deep
 *      - Programmable data frame size from 4 to 16 bits
 *      - Internal loopback test mode for diagnostic/debug testing
 *      - Standard FIFO-based interrupts and End-of-Transmission interrupt
 *      - Efficient transfers using Micro Direct Memory Access Controller (µDMA)
 *          - Separate channels for transmit and receive
 *          - Receive single request asserted when data is in the FIFO; burst 
 *            request asserted when FIFO contains 4 entries
 *          - Transmit single request asserted when there is space in the FIFO; 
 *            burst request asserted when four or more entries are available to 
 *            be written in the FIFO
 * 
 * @subsection spiCompatability Freescale SPI Compatability Information
 * 
 * Background information first, Freescale is a spinoff of Motorolla and was 
 * purchased by NXP Semiconductor. Motorola developed SPI in the mid 80s. "The 
 * Serial Peripheral Interface (SPI) bus was put together by Motorola 
 * (Freescale/NXP/Qualcomm) in the 1980s for communicating between a 
 * processor and one or more external peripherals. SPI is intended for short 
 * distance communication, typically between chips on the same board." 
 * https://embedded.fm/blog/2017/3/24/i-spi
 * 
 * Generally, SPI is a name given to 4-wire serial communication 
 * protocol that is full duplex and uses a master-slave communication 
 * architecture with a single master (with the option of multiple slaves). While
 * most SPI interfaces and protocol impelementations are the same and compatable
 * with each other, <b> SOME ARE NOT!!! </b> Care must be taken to ensure that 
 * the SPI interfaces are compatable. According to Wikipedia, "the SPI bus is a 
 * de facto standard but not officially established. The lack of a formal standard is 
 * reflected in a wide variety of protocol options. Different word sizes are 
 * common. Every device  defines its own protocol, including whether it supports 
 * commands at all. Some devices are transmit-only; others are receive-only."
 * 
 * For more info on SPI compatability see the link to the following forum 
 * discussion https://www.embeddedrelated.com/showthread/comp.arch.embedded/67876-1.php
 * 
 * Link to Freescale Semiconductor SPI application note
 * https://www.nxp.com/docs/en/application-note/AN3020.pdf
 * 
 * Link to another Freescale Semiconductor SPI application note that uses
 * a Freescale Microcontroller in the example.
 * https://www.nxp.com/docs/en/application-note/AN3904.pdf
 * 
 * For more information on SPI please see the folliwing Wikipeida link
 * https://en.wikipedia.org/wiki/Serial_Peripheral_Interface
 * 
 * SPI is different from the Microwire TI SSI interfaces and implementations. 
 * According to Wikipedia, "The SPI may be accurately described as a synchronous 
 * serial interface, but it is different from the Synchronous Serial Interface 
 * (SSI) protocol, which is also a four-wire synchronous serial communication 
 * protocol."
 * 
 * For information on Microwire see this Wikipedia link 
 * https://en.wikipedia.org/wiki/Serial_Peripheral_Interface#Microwire
 * 
 * For information on Synchronous Serial Interfaces (SSI) see this Wikipedia link
 * https://en.wikipedia.org/wiki/Synchronous_Serial_Interface
 * 
 * For more detailed information on the SSI module please see page 952 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection ssiSignalDescription SSI Signal Description
 * 
 * The following table lists the external signals and thier associtated pins 
 * for the SSI module. The GPIO needs to be configured for the SSI alternate
 * function using the \c AFSEL bit in the GPIO Alternate Function Register 
 * (GPIOAFSEL). The number in parenthesis in the Pin Mux / Pin Assignment 
 * column of the table below is what is programmed into the \c PMCn field in
 * the GPIO Port Control (GPIOPCTL) register to assign a SSI signal to a GPIO. 
 * 
 * @image html ssiSignalPins.png
 * @image latex ssiSignalPins.png
 * 
 */


#ifndef SSI_H
#define SSI_H

#include "../systemControl/systemControl.h"

class Ssi
{
    public:
        Ssi();
        ~Ssi();

    private:
        static const uint32_t ssi0BaseAddress = 0x40008000;
        static const uint32_t ssi1BaseAddress = 0x40009000;
        static const uint32_t ssi2BaseAddress = 0x4000A000;
        static const uint32_t ssi3BaseAddress = 0x4000B000;

        static const uint32_t PPSSI_OFFSET = 0x31C; //0x31C PPSSI RO 0x0000.000F Synchronous Serial Interface Peripheral Present 297
        static const uint32_t SRSSI_OFFSET = 0x51C; //0x51C SRSSI RW 0x0000.0000 Synchronous Serial Interface Software Reset 320
        static const uint32_t RCGCSSI_OFFSET = 0x61C; //0x61C RCGCSSI RW 0x0000.0000 Synchronous Serial Interface Run Mode Clock Gating Control 346
        static const uint32_t SCGCSSI_OFFSET = 0x71C; //0x71C SCGCSSI RW 0x0000.0000 Synchronous Serial Interface Sleep Mode Clock Gating Control 368
        static const uint32_t DCGCSSI_OFFSET = 0x81C; //0x81C DCGCSSI RW 0x0000.0000 Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control 390
        static const uint32_t PRSSI_OFFSET = 0xA1C; //0xA1C PRSSI RO 0x0000.0000 Synchronous Serial Interface Peripheral Ready 412

        static const uint32_t SSICR0_OFFSET = 0x000; // 0x000 SSICR0 RW 0x0000.0000 SSI Control 0 969
        static const uint32_t SSICR1_OFFSET = 0x004; // 0x004 SSICR1 RW 0x0000.0000 SSI Control 1 971
        static const uint32_t SSIDR_OFFSET = 0x008; // 0x008 SSIDR RW 0x0000.0000 SSI Data 973
        static const uint32_t SSISR_OFFSET = 0x00C; // 0x00C SSISR RO 0x0000.0003 SSI Status 974
        static const uint32_t SSICPSR_OFFSET = 0x010; // 0x010 SSICPSR RW 0x0000.0000 SSI Clock Prescale 976
        static const uint32_t SSIIM_OFFSET = 0x014; // 0x014 SSIIM RW 0x0000.0000 SSI Interrupt Mask 977
        static const uint32_t SSIRIS_OFFSET = 0x018; // 0x018 SSIRIS RO 0x0000.0008 SSI Raw Interrupt Status 978
        static const uint32_t SSIMIS_OFFSET = 0x01C; // 0x01C SSIMIS RO 0x0000.0000 SSI Masked Interrupt Status 980
        static const uint32_t SSIICR_OFFSET = 0x020; // 0x020 SSIICR W1C 0x0000.0000 SSI Interrupt Clear 982
        static const uint32_t SSIDMACTL_OFFSET = 0x024; // 0x024 SSIDMACTL RW 0x0000.0000 SSI DMA Control 983
        static const uint32_t SSICC_OFFSET = 0xFC8; // 0xFC8 SSICC RW 0x0000.0000 SSI Clock Configuration 984
        static const uint32_t SSIPeriphID4_OFFSET = 0xFD0; // 0xFD0 SSIPeriphID4 RO 0x0000.0000 SSI Peripheral Identification 4 985
        static const uint32_t SSIPeriphID5_OFFSET = 0xFD4; // 0xFD4 SSIPeriphID5 RO 0x0000.0000 SSI Peripheral Identification 5 986
        static const uint32_t SSIPeriphID6_OFFSET = 0xFD8; // 0xFD8 SSIPeriphID6 RO 0x0000.0000 SSI Peripheral Identification 6 987
        static const uint32_t SSIPeriphID7_OFFSET = 0xFDC; // 0xFDC SSIPeriphID7 RO 0x0000.0000 SSI Peripheral Identification 7 988
        static const uint32_t SSIPeriphID0_OFFSET = 0xFE0; // 0xFE0 SSIPeriphID0 RO 0x0000.0022 SSI Peripheral Identification 0 989
        static const uint32_t SSIPeriphID1_OFFSET = 0xFE4; // 0xFE4 SSIPeriphID1 RO 0x0000.0000 SSI Peripheral Identification 1 990
        static const uint32_t SSIPeriphID2_OFFSET = 0xFE8; // 0xFE8 SSIPeriphID2 RO 0x0000.0018 SSI Peripheral Identification 2 991
        static const uint32_t SSIPeriphID3_OFFSET = 0xFEC; // 0xFEC SSIPeriphID3 RO 0x0000.0001 SSI Peripheral Identification 3 992
        static const uint32_t SSIPCellID0_OFFSET = 0xFF0; // 0xFF0 SSIPCellID0 RO 0x0000.000D SSI PrimeCell Identification 0 993
        static const uint32_t SSIPCellID1_OFFSET = 0xFF4; // 0xFF4 SSIPCellID1 RO 0x0000.00F0 SSI PrimeCell Identification 1 994
        static const uint32_t SSIPCellID2_OFFSET = 0xFF8; // 0xFF8 SSIPCellID2 RO 0x0000.0005 SSI PrimeCell Identification 2 995
        static const uint32_t SSIPCellID3_OFFSET = 0xFFC; // 0xFFC SSIPCellID3 RO 0x0000.00B1 SSI PrimeCell Identification 3 996


};

#endif // SSI_H
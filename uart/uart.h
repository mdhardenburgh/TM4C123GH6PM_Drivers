/**
 * @file uart.h
 * @brief TM4C123GH6PM UART Driver Declaration
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
 * @class Uart
 * @brief TM4C123GH6PM UART Driver
 * 
 * @section uartDescription UART Description
 * 
 * The TM4C123GH6PM microcontroller has 8 UART modules. On the TM4C123GXL 
 * "LaunchPad" by Texas Insturments, UART 0 is connected to the debugger and 
 * enumerates as a virtual com port without additional programming. The debugger
 * performs the UART over USB conversion. UART has the following features:
 *      - Programmable baud-rate generator allowing speeds up to 5 Mbps for 
 *        regular speed (divide by 16) and 10 Mbps for high speed (divide by 8)
 *      - Separate 16x8 transmit (TX) and receive (RX) FIFOs to reduce CPU 
 *        interrupt service loading
 *      - Programmable FIFO length, including 1-byte deep operation providing 
 *        conventional double-buffered interface
 *      - FIFO trigger levels of 1/8, 1/4, 1/2, 3/4, and 7/8
 *      - Standard asynchronous communication bits for start, stop, and parity
 *      - Line-break generation and detection
 *      - Fully programmable serial interface characteristics
 *          - 5, 6, 7, or 8 data bits
 *          - Even, odd, stick, or no-parity bit generation/detection
 *          - 1 or 2 stop bit generation
 *      - IrDA serial-IR (SIR) encoder/decoder providing
 *          - Programmable use of IrDA Serial Infrared (SIR) or UART input/output
 *          - Support of IrDA SIR encoder/decoder functions for data rates up to 
 *            115.2 Kbps half-duplex
 *          - Support of normal 3/16 and low-power (1.41-2.23 μs) bit durations
 *          - Programmable internal clock generator enabling division of 
 *            reference clock by 1 to 256 for low-power mode bit duration
 *      - Support for communication with ISO 7816 smart cards
 *      - Modem flow control (on UART1)
 *      - EIA-485 9-bit support
 *      - Standard FIFO-level and End-of-Transmission interrupts
 *      - Efficient transfers using Micro Direct Memory Access Controller (µDMA)
 *          - Separate channels for transmit and receive
 *          - Receive single request asserted when data is in the FIFO; burst 
 *            request asserted at programmed FIFO level
 *          - Transmit single request asserted when there is space in the FIFO; 
 *            burst request asserted at programmed FIFO level
 * 
 * Jonathan Valvano has a great tutorial on UART specific to the TM4C123GH6PM
 * microcontroller linked here https://users.ece.utexas.edu/~valvano/Volume1/E-Book/C11_SerialInterface.htm
 * 
 * He also has a youtube lecture series on serial interfacing and UART linked
 * here https://www.youtube.com/watch?v=vNHHbwzKdJo&list=PLyg2vmIzGxXFZMY5nLnWPLyFLY92tVPNP
 * 
 * For more detailed information on the UART please see page 893 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection uartSignalDescription UART Signal Description
 * 
 * 
 * The following table lists the external signals and thier associtated pins 
 * for the UART module. UART is an alternate function of the GPIOs and the GPIOs
 * default to GPIO at reset, except \c U0Rx and \c U0Tx . The GPIO needs to be 
 * configured for the UART alternate function using the \c AFSEL bit in the 
 * GPIO Alternate Function Register (GPIOAFSEL). The number in parenthesis in 
 * the Pin Mux / Pin Assignment column of the table below is what is programmed 
 * into the \c PMCn field in the GPIO Port Control (GPIOPCTL) register to 
 * assign a UART signal to a GPIO. 
 * 
 * @image html uartSignalPins.png
 * @image latex uartSignalPins.png
 * 
 */

#ifndef UART_H
#define UART_H

#include "../systemControl/systemControl.h"


class Uart
{
    public:
        Uart();
        ~Uart();

    private:

        static const uint32_t uart0BaseAddress = 0x4000C000;
        static const uint32_t uart1BaseAddress = 0x4000D000;
        static const uint32_t uart2BaseAddress = 0x4000E000;
        static const uint32_t uart3BaseAddress = 0x4000F000;
        static const uint32_t uart4BaseAddress = 0x40010000;
        static const uint32_t uart5BaseAddress = 0x40011000;
        static const uint32_t uart6BaseAddress = 0x40012000;
        static const uint32_t uart6BaseAddress = 0x40013000;

        static const uint32_t PPUART_OFFSET = 0x318; //0x318 PPUART RO 0x0000.00FF Universal Asynchronous Receiver/Transmitter Peripheral Present 295
        static const uint32_t SRUART_OFFSET = 0x518; //0x518 SRUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Software Reset 318
        static const uint32_t RCGCUART_OFFSET = 0x618; //0x618 RCGCUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control 344
        static const uint32_t SCGCUART_OFFSET = 0x718; //0x718 SCGCUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control 366
        static const uint32_t DCGCUART_OFFSET = 0x818; //0x818 DCGCUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control 388
        static const uint32_t PRUART_OFFSET = 0xA18; //0xA18 PRUART RO 0x0000.0000 Universal Asynchronous Receiver/Transmitter Peripheral Ready 410

        static const uint32_t UARTDR_OFFSET = 0x000; // 0x000 UARTDR RW 0x0000.0000 UART Data 906
        static const uint32_t UARTRSR_UARTECR_OFFSET = 0x004; // 0x004 UARTRSR/UARTECR RW 0x0000.0000 UART Receive Status/Error Clear 908
        static const uint32_t UARTFR_OFFSET = 0x018; // 0x018 UARTFR RO 0x0000.0090 UART Flag 911
        static const uint32_t UARTILPR_OFFSET = 0x020; // 0x020 UARTILPR RW 0x0000.0000 UART IrDA Low-Power Register 913
        static const uint32_t UARTIBRD_OFFSET = 0x024; // 0x024 UARTIBRD RW 0x0000.0000 UART Integer Baud-Rate Divisor 914
        static const uint32_t UARTFBRD_OFFSET = 0x028; // 0x028 UARTFBRD RW 0x0000.0000 UART Fractional Baud-Rate Divisor 915
        static const uint32_t UARTLCRH_OFFSET = 0x02C; // 0x02C UARTLCRH RW 0x0000.0000 UART Line Control 916
        static const uint32_t UARTCTL_OFFSET = 0x030; // 0x030 UARTCTL RW 0x0000.0300 UART Control 918
        static const uint32_t UARTIFLS_OFFSET = 0x034; // 0x034 UARTIFLS RW 0x0000.0012 UART Interrupt FIFO Level Select 922
        static const uint32_t UARTIM_OFFSET = 0x038; // 0x038 UARTIM RW 0x0000.0000 UART Interrupt Mask 924
        static const uint32_t UARTRIS_OFFSET = 0x03C; // 0x03C UARTRIS RO 0x0000.0000 UART Raw Interrupt Status 927
        static const uint32_t UARTMIS_OFFSET = 0x040; // 0x040 UARTMIS RO 0x0000.0000 UART Masked Interrupt Status 930
        static const uint32_t UARTICR_OFFSET = 0x044; // 0x044 UARTICR W1C 0x0000.0000 UART Interrupt Clear 933
        static const uint32_t UARTDMACTL_OFFSET = 0x048; // 0x048 UARTDMACTL RW 0x0000.0000 UART DMA Control 935
        static const uint32_t UART9BITADDR_OFFSET = 0x0A4; // 0x0A4 UART9BITADDR RW 0x0000.0000 UART 9-Bit Self Address 936
        static const uint32_t UART9BITAMASK_OFFSET = 0x0A8; // 0x0A8 UART9BITAMASK RW 0x0000.00FF UART 9-Bit Self Address Mask 937
        static const uint32_t UARTPP_OFFSET = 0xFC0; // 0xFC0 UARTPP RO 0x0000.0003 UART Peripheral Properties 938
        static const uint32_t UARTCC_OFFSET = 0xFC8; // 0xFC8 UARTCC RW 0x0000.0000 UART Clock Configuration 939
        static const uint32_t UARTPeriphID4 = 0xFD0; // 0xFD0 UARTPeriphID4 RO 0x0000.0000 UART Peripheral Identification 4 940
        static const uint32_t UARTPeriphID5 = 0xFD4; // 0xFD4 UARTPeriphID5 RO 0x0000.0000 UART Peripheral Identification 5 941
        static const uint32_t UARTPeriphID6 = 0xFD8; // 0xFD8 UARTPeriphID6 RO 0x0000.0000 UART Peripheral Identification 6 942
        static const uint32_t UARTPeriphID7 = 0xFDC; // 0xFDC UARTPeriphID7 RO 0x0000.0000 UART Peripheral Identification 7 943
        static const uint32_t UARTPeriphID0 = 0xFE0; // 0xFE0 UARTPeriphID0 RO 0x0000.0060 UART Peripheral Identification 0 944
        static const uint32_t UARTPeriphID1 = 0xFE4; // 0xFE4 UARTPeriphID1 RO 0x0000.0000 UART Peripheral Identification 1 945
        static const uint32_t UARTPeriphID2 = 0xFE8; // 0xFE8 UARTPeriphID2 RO 0x0000.0018 UART Peripheral Identification 2 946
        static const uint32_t UARTPeriphID3 = 0xFEC; // 0xFEC UARTPeriphID3 RO 0x0000.0001 UART Peripheral Identification 3 947
        static const uint32_t UARTPCellID0 = 0xFF0; // 0xFF0 UARTPCellID0 RO 0x0000.000D UART PrimeCell Identification 0 948
        static const uint32_t UARTPCellID1 = 0xFF4; // 0xFF4 UARTPCellID1 RO 0x0000.00F0 UART PrimeCell Identification 1 949
        static const uint32_t UARTPCellID2 = 0xFF8; // 0xFF8 UARTPCellID2 RO 0x0000.0005 UART PrimeCell Identification 2 950
        static const uint32_t UARTPCellID3 = 0xFFC; // 0xFFC UARTPCellID3 RO 0x0000.00B1 UART PrimeCell Identification 3 951

};

#endif
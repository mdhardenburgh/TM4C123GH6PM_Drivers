/**
 * @file uart.h
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
 * UART Register Descriptions
 * 
 * The remainder of this section lists and describes the UART registers, in 
 * numerical order by address offset.
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

};

#endif
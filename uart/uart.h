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

class Uart : SystemControl
{
    public:
        Uart();
        ~Uart();

    private:

        const uint32_t uart0BaseAddress = 0x4000C000;
        const uint32_t uart1BaseAddress = 0x4000D000;
        const uint32_t uart2BaseAddress = 0x4000E000;
        const uint32_t uart3BaseAddress = 0x4000F000;
        const uint32_t uart4BaseAddress = 0x40010000;
        const uint32_t uart5BaseAddress = 0x40011000;
        const uint32_t uart6BaseAddress = 0x40012000;
        const uint32_t uart6BaseAddress = 0x40013000;

        const uint32_t PPUART_OFFSET = 0x318; //0x318 PPUART RO 0x0000.00FF Universal Asynchronous Receiver/Transmitter Peripheral Present 295
        const uint32_t SRUART_OFFSET = 0x518; //0x518 SRUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Software Reset 318
        const uint32_t RCGCUART_OFFSET = 0x618; //0x618 RCGCUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control 344
        const uint32_t SCGCUART_OFFSET = 0x718; //0x718 SCGCUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control 366
        const uint32_t DCGCUART_OFFSET = 0x818; //0x818 DCGCUART RW 0x0000.0000 Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control 388
        const uint32_t PRUART_OFFSET = 0xA18; //0xA18 PRUART RO 0x0000.0000 Universal Asynchronous Receiver/Transmitter Peripheral Ready 410


/**************************System Control BitFields****************************/

        // bitField PPUART_P7{7, 1, RO}; //UART Module 7 Present
        // bitField PPUART_P6{6, 1, RO}; //UART Module 6 Present
        // bitField PPUART_P5{5, 1, RO}; //UART Module 5 Present
        // bitField PPUART_P4{4, 1, RO}; //UART Module 4 Present
        // bitField PPUART_P3{3, 1, RO}; //UART Module 3 Present
        // bitField PPUART_P2{2, 1, RO}; //UART Module 2 Present
        // bitField PPUART_P1{1, 1, RO}; //UART Module 1 Present
        // bitField PPUART_P0{0, 1, RO}; //UART Module 0 Present

        // bitField SRUART_R7{7, 1, RW}; //UART Module 7 Software Reset
        // bitField SRUART_R6{6, 1, RW}; //UART Module 6 Software Reset
        // bitField SRUART_R5{5, 1, RW}; //UART Module 5 Software Reset
        // bitField SRUART_R4{4, 1, RW}; //UART Module 4 Software Reset
        // bitField SRUART_R3{3, 1, RW}; //UART Module 3 Software Reset
        // bitField SRUART_R2{2, 1, RW}; //UART Module 2 Software Reset
        // bitField SRUART_R1{1, 1, RW}; //UART Module 1 Software Reset
        // bitField SRUART_R0{0, 1, RW}; //UART Module 0 Software Reset

        // bitField RCGCUART_R7{7, 1, RW}; //UART Module 7 Run Mode Clock Gating Control
        // bitField RCGCUART_R6{6, 1, RW}; //UART Module 6 Run Mode Clock Gating Control
        // bitField RCGCUART_R5{5, 1, RW}; //UART Module 5 Run Mode Clock Gating Control
        // bitField RCGCUART_R4{4, 1, RW}; //UART Module 4 Run Mode Clock Gating Control
        // bitField RCGCUART_R3{3, 1, RW}; //UART Module 3 Run Mode Clock Gating Control
        // bitField RCGCUART_R2{2, 1, RW}; //UART Module 2 Run Mode Clock Gating Control
        // bitField RCGCUART_R1{1, 1, RW}; //UART Module 1 Run Mode Clock Gating Control
        // bitField RCGCUART_R0{0, 1, RW}; //UART Module 0 Run Mode Clock Gating Control

        // bitField SCGCUART_S7{7, 1, RW}; //UART Module 7 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S6{6, 1, RW}; //UART Module 6 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S5{5, 1, RW}; //UART Module 5 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S4{4, 1, RW}; //UART Module 4 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S3{3, 1, RW}; //UART Module 3 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S2{2, 1, RW}; //UART Module 2 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S1{1, 1, RW}; //UART Module 1 Sleep Mode Clock Gating Control
        // bitField SCGCUART_S0{0, 1, RW}; //UART Module 0 Sleep Mode Clock Gating Control

        // bitField DCGCUART_D7{7, 1, RW}; //UART Module 7 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D6{6, 1, RW}; //UART Module 6 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D5{5, 1, RW}; //UART Module 5 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D4{4, 1, RW}; //UART Module 4 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D3{3, 1, RW}; //UART Module 3 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D2{2, 1, RW}; //UART Module 2 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D1{1, 1, RW}; //UART Module 1 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCUART_D0{0, 1, RW}; //UART Module 0 Deep-Sleep Mode Clock Gating Control

        // bitField PRUART_R7{7, 1, RO}; //UART Module 7 Peripheral Ready
        // bitField PRUART_R6{6, 1, RO}; //UART Module 6 Peripheral Ready
        // bitField PRUART_R5{5, 1, RO}; //UART Module 5 Peripheral Ready
        // bitField PRUART_R4{4, 1, RO}; //UART Module 4 Peripheral Ready
        // bitField PRUART_R3{3, 1, RO}; //UART Module 3 Peripheral Ready
        // bitField PRUART_R2{2, 1, RO}; //UART Module 2 Peripheral Ready
        // bitField PRUART_R1{1, 1, RO}; //UART Module 1 Peripheral Ready
        // bitField PRUART_R0{0, 1, RO}; //UART Module 0 Peripheral Ready

};

#endif
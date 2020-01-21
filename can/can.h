/**
 * @file can.h
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
 * Controller Area Network (CAN) Register Descriptions
 * 
 * The remainder of this section lists and describes the CAN registers, in 
 * numerical order by address offset. There are two sets of Interface Registers 
 * that are used to access the Message Objects in the Message RAM: CANIF1x and 
 * CANIF2x. The function of the two sets are identical and are used to queue 
 * transactions.
 * 
 */

#ifndef CAN_H
#define CAN_H

#include "../systemControl/systemControl.h"

class Can : SystemControl
{
    public:
        Can();
        ~Can();

    private:
        const uint32_t can0BaseAddress = 0x40040000;
        const uint32_t can1BaseAddress = 0x40041000;

        const uint32_t PPCAN_OFFSET = 0x334; //0x334 PPCAN RO 0x0000.0003 Controller Area Network Peripheral Present 302
        const uint32_t SRCAN_OFFSET = 0x534; //0x534 SRCAN RW 0x0000.0000 Controller Area Network Software Reset 325
        const uint32_t RCGCCAN_OFFSET = 0x634; //0x634 RCGCCAN RW 0x0000.0000 Controller Area Network Run Mode Clock Gating Control 351
        const uint32_t SCGCCAN_OFFSET = 0x734; //0x734 SCGCCAN RW 0x0000.0000 Controller Area Network Sleep Mode Clock Gating Control 373
        const uint32_t DCGCCAN_OFFSET = 0x834; //0x834 DCGCCAN RW 0x0000.0000 Controller Area Network Deep-Sleep Mode Clock Gating Control 395
        const uint32_t PRCAN_OFFSET = 0xA34; //0xA34 PRCAN RO 0x0000.0000 Controller Area Network Peripheral Ready 417


/**************************System Control BitFields****************************/

        // bitField PPCAN_P1{1, 1, RO}; //CAN Module 1 Present
        // bitField PPCAN_P0{0, 1, RO}; //CAN Module 0 Present

        // bitField SRCAN_R1{1, 1, RW}; //CAN Module 1 Software Reset
        // bitField SRCAN_R0{0, 1, RW}; //CAN Module 0 Software Reset

        // bitField RCGCCAN_R1{1, 1, RW}; //CAN Module 1 Run Mode Clock Gating Control
        // bitField RCGCCAN_R0{0, 1, RW}; //CAN Module 0 Run Mode Clock Gating Control

        // bitField SCGCCAN_S1{1, 1, RW}; //CAN Module 1 Sleep Mode Clock Gating Control
        // bitField SCGCCAN_S0{0, 1, RW}; //CAN Module 0 Sleep Mode Clock Gating Control

        // bitField DCGCCAN_D1{1, 1, RW}; //CAN Module 1 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCCAN_D0{0, 1, RW}; //CAN Module 0 Deep-Sleep Mode Clock Gating Control

        // bitField PRCAN_R1{1, 1, RO}; //CAN Module 1 Peripheral Ready
        // bitField PRCAN_R0{0, 1, RO}; //CAN Module 0 Peripheral Ready

};

#endif
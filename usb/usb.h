/**
 * @file usb.h
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
 * Universal Serial Bus (USB) Register Descriptions
 * 
 */

#ifndef USB_H
#define USB_H

#include "../systemControl/systemControl.h"

const uint32_t usbBaseAddress = 0x40050000;

const uint32_t PPUSB_OFFSET = 0x328; //0x328 PPUSB RO 0x0000.0001 Universal Serial Bus Peripheral Present 301
const uint32_t SRUSB_OFFSET = 0x528; //0x528 SRUSB RW 0x0000.0000 Universal Serial Bus Software Reset 324
const uint32_t RCGCUSB_OFFSET = 0x628; //0x628 RCGCUSB RW 0x0000.0000 Universal Serial Bus Run Mode Clock Gating Control 350
const uint32_t SCGCUSB_OFFSET = 0x728; //0x728 SCGCUSB RW 0x0000.0000 Universal Serial Bus Sleep Mode Clock Gating Control 372
const uint32_t DCGCUSB_OFFSET = 0x828; //0x828 DCGCUSB RW 0x0000.0000 Universal Serial Bus Deep-Sleep Mode Clock Gating Control 394
const uint32_t PRUSB_OFFSET = 0xA28;//0xA28 PRUSB RO 0x0000.0000 Universal Serial Bus Peripheral Ready 416

class Usb : SystemControl
{
    public:
        Usb();
        ~Usb();

    private:



/**************************System Control BitFields****************************/

        // bitField RIS_USBPLLLRIS{7, 1, RO}; //USB PLL Lock Raw Interrupt Status

        // bitField IMC_USBPLLLIM{7, 1, RW}; //USB PLL Lock Interrupt Mask

        // bitField MISC_USBPLLLMIS{7, 1, RW1C}; //USB PLL Lock Masked Interrupt Status

        // bitField RCC2_USBPWRDN{14, 1, RW}; //Power-Down USB PLL

        // bitField PPUSB_P0{0, 1, RO}; //USB Module Present
        // bitField SRUSB_R0{0, 1, RW}; //USB Module Software Reset
        // bitField RCGCUSB_R0{0, 1, RW}; //USB Module Run Mode Clock Gating Control
        // bitField SCGCUSB_S0{0, 1, RW}; //USB Module Sleep Mode Clock Gating Control
        // bitField DCGCUSB_D0{0, 1, RW}; //USB Module Deep-Sleep Mode Clock Gating Control
        // bitField PRUSB_R0{0, 1, RO}; //USB Module Peripheral Ready

};

#endif
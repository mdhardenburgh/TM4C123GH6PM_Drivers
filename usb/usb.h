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

class Usb : SystemControl
{
    public:
        Usb();
        ~Usb();

    private:
        const uint32_t usbBaseAddress = 0x40050000;

/**********************System Control Register Descriptions********************/

        Register PPUSB{(volatile uint32_t*)(systemControlBase + 0x328)}; //0x328 PPUSB RO 0x0000.0001 Universal Serial Bus Peripheral Present 301
        Register SRUSB{(volatile uint32_t*)(systemControlBase + 0x528)}; //0x528 SRUSB RW 0x0000.0000 Universal Serial Bus Software Reset 324
        Register RCGCUSB{(volatile uint32_t*)(systemControlBase + 0x628)}; //0x628 RCGCUSB RW 0x0000.0000 Universal Serial Bus Run Mode Clock Gating Control 350
        Register SCGCUSB{(volatile uint32_t*)(systemControlBase + 0x728)}; //0x728 SCGCUSB RW 0x0000.0000 Universal Serial Bus Sleep Mode Clock Gating Control 372
        Register DCGCUSB{(volatile uint32_t*)(systemControlBase + 0x828)}; //0x828 DCGCUSB RW 0x0000.0000 Universal Serial Bus Deep-Sleep Mode Clock Gating Control 394
        Register PRUSB{(volatile uint32_t*)(systemControlBase + 0xA28)}; //0xA28 PRUSB RO 0x0000.0000 Universal Serial Bus Peripheral Ready 416

/**************************System Control BitFields****************************/

        bitField RIS_USBPLLLRIS{7, 1, RO}; //USB PLL Lock Raw Interrupt Status

        bitField IMC_USBPLLLIM{7, 1, RW}; //USB PLL Lock Interrupt Mask

        bitField MISC_USBPLLLMIS{7, 1, RW1C}; //USB PLL Lock Masked Interrupt Status

        bitField RCC2_USBPWRDN{14, 1, RW}; //Power-Down USB PLL

        bitField PPUSB_P0{0, 1, RO}; //USB Module Present
        bitField SRUSB_R0{0, 1, RW}; //USB Module Software Reset
        bitField RCGCUSB_R0{0, 1, RW}; //USB Module Run Mode Clock Gating Control
        bitField SCGCUSB_S0{0, 1, RW}; //USB Module Sleep Mode Clock Gating Control
        bitField DCGCUSB_D0{0, 1, RW}; //USB Module Deep-Sleep Mode Clock Gating Control
        bitField PRUSB_R0{0, 1, RO}; //USB Module Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC6_USB0PHY{4, 1, RO}; //USB Module 0 PHY Present. When set, indicates that the USB module 0 PHY is present.
        bitField DC6_USB0{0, 2, RO}; //USB Module 0 Present. This field indicates that USB module 0 is present and specifies its capability.
        bitField SRCR2_USB0{16, 1, RO}; //USB0 Reset Control
        bitField RCGC2_USB0{16, 1, RO}; //USB0 Clock Gating Control
        bitField SCGC2_USB0{16, 1, RO}; //USB0 Clock Gating Control
        bitField DCGC2_USB0{16, 1, RO}; //USB0 Clock Gating Control

};

#endif
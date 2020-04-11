/**
 * @file usb.h
 * @brief TM4C123GH6PM USB Driver Declaration
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
 * @class Usb
 * @brief TM4C123GH6PM USB Driver
 * 
 * @section usbDescription USB Description
 * 
 * The TM4C123GH6PM microcontroller has a built in USB controller that enables
 * the microcontroller to have USB Host, Device or OTG functions. The controller
 * complies with the USB 2.0 standard. The USB controller supports μDMA access
 * to allow large data transfers without the processor. The USB controller
 * supports the following features:
 *      - Complies with USB-IF (Implementer's Forum) certification standards
 *      - USB 2.0 full-speed (12 Mbps) and low-speed (1.5 Mbps) operation with integrated PHY
 *      - 4 transfer types: Control, Interrupt, Bulk, and Isochronous
 *      - 16 endpoints
 *          - 1 dedicated control IN endpoint and 1 dedicated control OUT endpoint
 *          - 7 configurable IN endpoints and 7 configurable OUT endpoints
 *      - 4 KB dedicated endpoint memory: one endpoint may be defined for 
 *        double-buffered 1023-byte isochronous packet size
 *      - VBUS droop and valid ID detection and interrupt
 *      - Efficient transfers using Micro Direct Memory Access Controller (µDMA)
 *          - Separate channels for transmit and receive for up to three IN 
 *            endpoints and three OUT endpoints
 *          - Channel requests asserted when FIFO contains required amount of data
 * 
 * For more detailed information on the USB please see page 1099 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection usbSignalDescription USB Signal Description
 * 
 * The following table lists the external signals and thier associtated pins 
 * for the USB module. The GPIO needs to be configured for the USB alternate
 * function using the \c AFSEL bit in the GPIO Alternate Function Register 
 * (GPIOAFSEL). The number in parenthesis in the Pin Mux / Pin Assignment 
 * column of the table below is what is programmed into the \c PMCn field in
 * the GPIO Port Control (GPIOPCTL) register to assign a SSI signal to a GPIO. 
 * The \c USB0VBUS and \c USB0ID signals are configured by clearing the 
 * correct \c DEN bit in the GPIODEN register.
 * 
 * @image html usbSignalPins.png
 * @image latex usbSignalPins.png
 * 
 */



#ifndef USB_H
#define USB_H

#include "../systemControl/systemControl.h"

class Usb
{
    public:
        Usb();
        ~Usb();

    private:

        static const uint32_t usbBaseAddress = 0x40050000;

        static const uint32_t PPUSB_OFFSET = 0x328; //0x328 PPUSB RO 0x0000.0001 Universal Serial Bus Peripheral Present 301
        static const uint32_t SRUSB_OFFSET = 0x528; //0x528 SRUSB RW 0x0000.0000 Universal Serial Bus Software Reset 324
        static const uint32_t RCGCUSB_OFFSET = 0x628; //0x628 RCGCUSB RW 0x0000.0000 Universal Serial Bus Run Mode Clock Gating Control 350
        static const uint32_t SCGCUSB_OFFSET = 0x728; //0x728 SCGCUSB RW 0x0000.0000 Universal Serial Bus Sleep Mode Clock Gating Control 372
        static const uint32_t DCGCUSB_OFFSET = 0x828; //0x828 DCGCUSB RW 0x0000.0000 Universal Serial Bus Deep-Sleep Mode Clock Gating Control 394
        static const uint32_t PRUSB_OFFSET = 0xA28;//0xA28 PRUSB RO 0x0000.0000 Universal Serial Bus Peripheral Ready 416

        static const uint32_t USBFADDR_OFFSET = 0x000; // 0x000 USBFADDR RW 0x00 USB Device Functional Address 1122
        static const uint32_t USBPOWER_OFFSET = 0x001; // 0x001 USBPOWER RW 0x20 USB Power 1123
        static const uint32_t USBTXIS_OFFSET = 0x002; // 0x002 USBTXIS RO 0x0000 USB Transmit Interrupt Status 1126
        static const uint32_t USBRXIS_OFFSET = 0x004; // 0x004 USBRXIS RO 0x0000 USB Receive Interrupt Status 1128
        static const uint32_t USBTXIE_OFFSET = 0x006; // 0x006 USBTXIE RW 0xFFFF USB Transmit Interrupt Enable 1129
        static const uint32_t USBRXIE_OFFSET = 0x008; // 0x008 USBRXIE RW 0xFFFE USB Receive Interrupt Enable 1131
        static const uint32_t USBIS_OFFSET = 0x00A; // 0x00A USBIS RO 0x00 USB General Interrupt Status 1132
        static const uint32_t USBIE_OFFSET = 0x00B; // 0x00B USBIE RW 0x06 USB Interrupt Enable 1135
        static const uint32_t USBFRAME_OFFSET = 0x00C; // 0x00C USBFRAME RO 0x0000 USB Frame Value 1138
        static const uint32_t USBEPIDX_OFFSET = 0x00E; // 0x00E USBEPIDX RW 0x00 USB Endpoint Index 1139
        static const uint32_t USBTEST_OFFSET = 0x00F; // 0x00F USBTEST RW 0x00 USB Test Mode 1140
        static const uint32_t USBFIFO0_OFFSET = 0x020; // 0x020 USBFIFO0 RW 0x0000.0000 USB FIFO Endpoint 0 1142
        static const uint32_t USBFIFO1_OFFSET = 0x024; // 0x024 USBFIFO1 RW 0x0000.0000 USB FIFO Endpoint 1 1142
        static const uint32_t USBFIFO2_OFFSET = 0x028; // 0x028 USBFIFO2 RW 0x0000.0000 USB FIFO Endpoint 2 1142
        static const uint32_t USBFIFO3_OFFSET = 0x02C; // 0x02C USBFIFO3 RW 0x0000.0000 USB FIFO Endpoint 3 1142
        static const uint32_t USBFIFO4_OFFSET = 0x030; // 0x030 USBFIFO4 RW 0x0000.0000 USB FIFO Endpoint 4 1142
        static const uint32_t USBFIFO5_OFFSET = 0x034; // 0x034 USBFIFO5 RW 0x0000.0000 USB FIFO Endpoint 5 1142
        static const uint32_t USBFIFO6_OFFSET = 0x038; // 0x038 USBFIFO6 RW 0x0000.0000 USB FIFO Endpoint 6 1142
        static const uint32_t USBFIFO7_OFFSET = 0x03C; // 0x03C USBFIFO7 RW 0x0000.0000 USB FIFO Endpoint 7 1142
        static const uint32_t USBDEVCTL_OFFSET = 0x060; // 0x060 USBDEVCTL RW 0x80 USB Device Control 1143
        static const uint32_t USBTXFIFOSZ_OFFSET = 0x062; // 0x062 USBTXFIFOSZ RW 0x00 USB Transmit Dynamic FIFO Sizing 1145
        static const uint32_t USBRXFIFOSZ_OFFSET = 0x063; // 0x063 USBRXFIFOSZ RW 0x00 USB Receive Dynamic FIFO Sizing 1145
        static const uint32_t USBTXFIFOADD_OFFSET = 0x064; // 0x064 USBTXFIFOADD RW 0x0000 USB Transmit FIFO Start Address 1146
        static const uint32_t USBRXFIFOADD_OFFSET = 0x066;// 0x066 USBRXFIFOADD RW 0x0000 USB Receive FIFO Start Address 1146
        static const uint32_t USBCONTIM_OFFSET = 0x07A; // 0x07A USBCONTIM RW 0x5C USB Connect Timing 1147
        static const uint32_t USBVPLEN_OFFSET = 0x07B; // 0x07B USBVPLEN RW 0x3C USB OTG VBUS Pulse Timing 1148
        static const uint32_t USBFSEOF_OFFSET = 0x07D; // 0x07D USBFSEOF RW 0x77 USB Full-Speed Last Transaction to End of Frame Timing 1149
        static const uint32_t USBLSEOF_OFFSET = 0x07E; // 0x07E USBLSEOF RW 0x72 USB Low-Speed Last Transaction to End of Frame Timing 1150
        static const uint32_t USBTXFUNCADDR0_OFFSET = 0x080; // 0x080 USBTXFUNCADDR0 RW 0x00 USB Transmit Functional Address Endpoint 0 1151
        static const uint32_t USBTXHUBADDR0_OFFSET = 0x082; // 0x082 USBTXHUBADDR0 RW 0x00 USB Transmit Hub Address Endpoint 0 1152
        static const uint32_t USBTXHUBPORT0_OFFSET = 0x083; // 0x083 USBTXHUBPORT0 RW 0x00 USB Transmit Hub Port Endpoint 0 1153
        static const uint32_t USBTXFUNCADDR1_OFFSET = 0x088; // 0x088 USBTXFUNCADDR1 RW 0x00 USB Transmit Functional Address Endpoint 1 1151
        static const uint32_t USBTXHUBADDR1_OFFSET = 0x08A; // 0x08A USBTXHUBADDR1 RW 0x00 USB Transmit Hub Address Endpoint 1 1152
        static const uint32_t USBTXHUBPORT1_OFFSET = 0x08B; // 0x08B USBTXHUBPORT1 RW 0x00 USB Transmit Hub Port Endpoint 1 1153
        static const uint32_t USBRXFUNCADDR1_OFFSET = 0x08C; // 0x08C USBRXFUNCADDR1 RW 0x00 USB Receive Functional Address Endpoint 1 1154
        static const uint32_t USBRXHUBADDR1_OFFSET = 0x08E; // 0x08E USBRXHUBADDR1 RW 0x00 USB Receive Hub Address Endpoint 1 1155
        static const uint32_t USBRXHUBPORT1_OFFSET = 0x08F; // 0x08F USBRXHUBPORT1 RW 0x00 USB Receive Hub Port Endpoint 1 1156
        static const uint32_t USBTXFUNCADDR2_OFFSET = 0x090; // 0x090 USBTXFUNCADDR2 RW 0x00 USB Transmit Functional Address Endpoint 2 1151
        static const uint32_t USBTXHUBADDR2_OFFSET = 0x092; // 0x092 USBTXHUBADDR2 RW 0x00 USB Transmit Hub Address Endpoint 2 1152
        static const uint32_t USBTXHUBPORT2_OFFSET = 0x093; // 0x093 USBTXHUBPORT2 RW 0x00 USB Transmit Hub Port Endpoint 2 1153
        static const uint32_t USBRXFUNCADDR2_OFFSET = 0x094; // 0x094 USBRXFUNCADDR2 RW 0x00 USB Receive Functional Address Endpoint 2 1154
        static const uint32_t USBRXHUBADDR2_OFFSET = 0x096; // 0x096 USBRXHUBADDR2 RW 0x00 USB Receive Hub Address Endpoint 2 1155
        static const uint32_t USBRXHUBPORT2_OFFSET = 0x097; // 0x097 USBRXHUBPORT2 RW 0x00 USB Receive Hub Port Endpoint 2 1156
        static const uint32_t USBTXFUNCADDR3_OFFSET = 0x098; // 0x098 USBTXFUNCADDR3 RW 0x00 USB Transmit Functional Address Endpoint 3 1151
        static const uint32_t USBTXHUBADDR3_OFFSET = 0x09A; // 0x09A USBTXHUBADDR3 RW 0x00 USB Transmit Hub Address Endpoint 3 1152
        static const uint32_t USBTXHUBPORT3_OFFSET = 0x09B; // 0x09B USBTXHUBPORT3 RW 0x00 USB Transmit Hub Port Endpoint 3 1153
        static const uint32_t USBRXFUNCADDR3_OFFSET = 0x09C; // 0x09C USBRXFUNCADDR3 RW 0x00 USB Receive Functional Address Endpoint 3 1154
        static const uint32_t USBRXHUBADDR3_OFFSET = 0x09E; // 0x09E USBRXHUBADDR3 RW 0x00 USB Receive Hub Address Endpoint 3 1155
        static const uint32_t USBRXHUBPORT3_OFFSET = 0x09F; // 0x09F USBRXHUBPORT3 RW 0x00 USB Receive Hub Port Endpoint 3 1156
        static const uint32_t USBTXFUNCADDR4_OFFSET = 0x0A0; // 0x0A0 USBTXFUNCADDR4 RW 0x00 USB Transmit Functional Address Endpoint 4 1151
        static const uint32_t USBTXHUBADDR4_OFFSET = 0x0A2; // 0x0A2 USBTXHUBADDR4 RW 0x00 USB Transmit Hub Address Endpoint 4 1152
        static const uint32_t USBTXHUBPORT4_OFFSET = 0x0A3; // 0x0A3 USBTXHUBPORT4 RW 0x00 USB Transmit Hub Port Endpoint 4 1153
        static const uint32_t USBRXFUNCADDR4_OFFSET = 0x0A4; // 0x0A4 USBRXFUNCADDR4 RW 0x00 USB Receive Functional Address Endpoint 4 1154
        static const uint32_t USBRXHUBADDR4_OFFSET = 0x0A6; // 0x0A6 USBRXHUBADDR4 RW 0x00 USB Receive Hub Address Endpoint 4 1155
        static const uint32_t USBRXHUBPORT4_OFFSET = 0x0A7; // 0x0A7 USBRXHUBPORT4 RW 0x00 USB Receive Hub Port Endpoint 4 1156
        static const uint32_t USBTXFUNCADDR5_OFFSET = 0x0A8; // 0x0A8 USBTXFUNCADDR5 RW 0x00 USB Transmit Functional Address Endpoint 5 1151
        static const uint32_t USBTXHUBADDR5_OFFSET = 0x0AA; // 0x0AA USBTXHUBADDR5 RW 0x00 USB Transmit Hub Address Endpoint 5 1152
        static const uint32_t USBTXHUBPORT5_OFFSET = 0x0AB; // 0x0AB USBTXHUBPORT5 RW 0x00 USB Transmit Hub Port Endpoint 5 1153
        static const uint32_t USBRXFUNCADDR5_OFFSET = 0x0AC; // 0x0AC USBRXFUNCADDR5 RW 0x00 USB Receive Functional Address Endpoint 5 1154
        static const uint32_t USBRXHUBADDR5_OFFSET = 0x0AE; // 0x0AE USBRXHUBADDR5 RW 0x00 USB Receive Hub Address Endpoint 5 1155
        static const uint32_t USBRXHUBPORT5_OFFSET = 0x0AF; // 0x0AF USBRXHUBPORT5 RW 0x00 USB Receive Hub Port Endpoint 5 1156
        static const uint32_t USBTXFUNCADDR6_OFFSET = 0x0B0; // 0x0B0 USBTXFUNCADDR6 RW 0x00 USB Transmit Functional Address Endpoint 6 1151
        static const uint32_t USBTXHUBADDR6_OFFSET = 0x0B2; // 0x0B2 USBTXHUBADDR6 RW 0x00 USB Transmit Hub Address Endpoint 6 1152
        static const uint32_t USBTXHUBPORT6_OFFSET = 0x0B3; // 0x0B3 USBTXHUBPORT6 RW 0x00 USB Transmit Hub Port Endpoint 6 1153
        static const uint32_t USBRXFUNCADDR6_OFFSET = 0x0B4; // 0x0B4 USBRXFUNCADDR6 RW 0x00 USB Receive Functional Address Endpoint 6 1154
        static const uint32_t USBRXHUBADDR6_OFFSET = 0x0B6; // 0x0B6 USBRXHUBADDR6 RW 0x00 USB Receive Hub Address Endpoint 6 1155
        static const uint32_t USBRXHUBPORT6_OFFSET = 0x0B7; // 0x0B7 USBRXHUBPORT6 RW 0x00 USB Receive Hub Port Endpoint 6 1156
        static const uint32_t USBTXFUNCADDR7_OFFSET = 0x0B8; // 0x0B8 USBTXFUNCADDR7 RW 0x00 USB Transmit Functional Address Endpoint 7 1151
        static const uint32_t USBTXHUBADDR7_OFFSET = 0x0BA; // 0x0BA USBTXHUBADDR7 RW 0x00 USB Transmit Hub Address Endpoint 7 1152
        static const uint32_t USBTXHUBPORT7_OFFSET = 0x0BB; // 0x0BB USBTXHUBPORT7 RW 0x00 USB Transmit Hub Port Endpoint 7 1153
        static const uint32_t USBRXFUNCADDR7_OFFSET = 0x0BC; // 0x0BC USBRXFUNCADDR7 RW 0x00 USB Receive Functional Address Endpoint 7 1154
        static const uint32_t USBRXHUBADDR7_OFFSET = 0x0BE; // 0x0BE USBRXHUBADDR7 RW 0x00 USB Receive Hub Address Endpoint 7 1155
        static const uint32_t USBRXHUBPORT7_OFFSET = 0x0BF; // 0x0BF USBRXHUBPORT7 RW 0x00 USB Receive Hub Port Endpoint 7 1156
        static const uint32_t USBCSRL0_OFFSET = 0x102; // 0x102 USBCSRL0 W1C 0x00 USB Control and Status Endpoint 0 Low 1158
        static const uint32_t USBCSRH0_OFFSET = 0x103; // 0x103 USBCSRH0 W1C 0x00 USB Control and Status Endpoint 0 High 1162
        static const uint32_t USBCOUNT0_OFFSET = 0x108; // 0x108 USBCOUNT0 RO 0x00 USB Receive Byte Count Endpoint 0 1164
        static const uint32_t USBTYPE0_OFFSET = 0x10A; // 0x10A USBTYPE0 RW 0x00 USB Type Endpoint 0 1165
        static const uint32_t USBNAKLMT_OFFSET = 0x10B; // 0x10B USBNAKLMT RW 0x00 USB NAK Limit 1166
        static const uint32_t USBTXMAXP1_OFFSET = 0x110; // 0x110 USBTXMAXP1 RW 0x0000 USB Maximum Transmit Data Endpoint 1 1157
        static const uint32_t USBTXCSRL1_OFFSET = 0x112; // 0x112 USBTXCSRL1 RW 0x00 USB Transmit Control and Status Endpoint 1 Low 1167
        static const uint32_t USBTXCSRH1_OFFSET = 0x113; // 0x113 USBTXCSRH1 RW 0x00 USB Transmit Control and Status Endpoint 1 High 1171
        static const uint32_t USBRXMAXP1_OFFSET = 0x114; // 0x114 USBRXMAXP1 RW 0x0000 USB Maximum Receive Data Endpoint 1 1175
        static const uint32_t USBRXCSRL1_OFFSET = 0x116; // 0x116 USBRXCSRL1 RW 0x00 USB Receive Control and Status Endpoint 1 Low 1176
        static const uint32_t USBRXCSRH1_OFFSET = 0x117; // 0x117 USBRXCSRH1 RW 0x00 USB Receive Control and Status Endpoint 1 High 1181
        static const uint32_t USBRXCOUNT1_OFFSET = 0x118; // 0x118 USBRXCOUNT1 RO 0x0000 USB Receive Byte Count Endpoint 1 1185
        static const uint32_t USBTXTYPE1_OFFSET = 0x11A; // 0x11A USBTXTYPE1 RW 0x00 USB Host Transmit Configure Type Endpoint 1 1186
        static const uint32_t USBTXINTERVAL1_OFFSET = 0x11B; // 0x11B USBTXINTERVAL1 RW 0x00 USB Host Transmit Interval Endpoint 1 1188
        static const uint32_t USBRXTYPE1_OFFSET = 0x11C; // 0x11C USBRXTYPE1 RW 0x00 USB Host Configure Receive Type Endpoint 1 1189
        static const uint32_t USBRXINTERVAL1_OFFSET = 0x11D; // 0x11D USBRXINTERVAL1 RW 0x00 USB Host Receive Polling Interval Endpoint 1 1191
        static const uint32_t USBTXMAXP2_OFFSET = 0x120; // 0x120 USBTXMAXP2 RW 0x0000 USB Maximum Transmit Data Endpoint 2 1157
        static const uint32_t USBTXCSRL2_OFFSET = 0x122; // 0x122 USBTXCSRL2 RW 0x00 USB Transmit Control and Status Endpoint 2 Low 1167
        static const uint32_t USBTXCSRH2_OFFSET = 0x123; // 0x123 USBTXCSRH2 RW 0x00 USB Transmit Control and Status Endpoint 2 High 1171
        static const uint32_t USBRXMAXP2_OFFSET = 0x124; // 0x124 USBRXMAXP2 RW 0x0000 USB Maximum Receive Data Endpoint 2 1175
        static const uint32_t USBRXCSRL2_OFFSET = 0x126; // 0x126 USBRXCSRL2 RW 0x00 USB Receive Control and Status Endpoint 2 Low 1176
        static const uint32_t USBRXCSRH2_OFFSET = 0x127; // 0x127 USBRXCSRH2 RW 0x00 USB Receive Control and Status Endpoint 2 High 1181
        static const uint32_t USBRXCOUNT2_OFFSET = 0x128; // 0x128 USBRXCOUNT2 RO 0x0000 USB Receive Byte Count Endpoint 2 1185
        static const uint32_t USBTXTYPE2_OFFSET = 0x12A; // 0x12A USBTXTYPE2 RW 0x00 USB Host Transmit Configure Type Endpoint 2 1186
        static const uint32_t USBTXINTERVAL2 = 0x12B; // 0x12B USBTXINTERVAL2 RW 0x00 USB Host Transmit Interval Endpoint 2 1188
        static const uint32_t USBRXTYPE2 = 0x12C; // 0x12C USBRXTYPE2 RW 0x00 USB Host Configure Receive Type Endpoint 2 1189
        static const uint32_t USBRXINTERVAL2 = 0x12D; // 0x12D USBRXINTERVAL2 RW 0x00 USB Host Receive Polling Interval Endpoint 2 1191
        static const uint32_t USBTXMAXP3 = 0x130; // 0x130 USBTXMAXP3 RW 0x0000 USB Maximum Transmit Data Endpoint 3 1157
        static const uint32_t USBTXCSRL3 = 0x132; // 0x132 USBTXCSRL3 RW 0x00 USB Transmit Control and Status Endpoint 3 Low 1167
        static const uint32_t USBTXCSRH3 = 0x133; // 0x133 USBTXCSRH3 RW 0x00 USB Transmit Control and Status Endpoint 3 High 1171
        static const uint32_t USBRXMAXP3 = 0x134; // 0x134 USBRXMAXP3 RW 0x0000 USB Maximum Receive Data Endpoint 3 1175
        static const uint32_t USBRXCSRL3 = 0x136; // 0x136 USBRXCSRL3 RW 0x00 USB Receive Control and Status Endpoint 3 Low 1176
        static const uint32_t USBRXCSRH3 = 0x137; // 0x137 USBRXCSRH3 RW 0x00 USB Receive Control and Status Endpoint 3 High 1181
        static const uint32_t USBRXCOUNT3 = 0x138; // 0x138 USBRXCOUNT3 RO 0x0000 USB Receive Byte Count Endpoint 3 1185
        static const uint32_t USBTXTYPE3 = 0x13A; // 0x13A USBTXTYPE3 RW 0x00 USB Host Transmit Configure Type Endpoint 3 1186
        static const uint32_t USBTXINTERVAL3 = 0x13B; // 0x13B USBTXINTERVAL3 RW 0x00 USB Host Transmit Interval Endpoint 3 1188
        static const uint32_t USBRXTYPE3 = 0x13C; // 0x13C USBRXTYPE3 RW 0x00 USB Host Configure Receive Type Endpoint 3 1189
        static const uint32_t USBRXINTERVAL3 = 0x13D; // 0x13D USBRXINTERVAL3 RW 0x00 USB Host Receive Polling Interval Endpoint 3 1191
        static const uint32_t USBTXMAXP4 = 0x140; // 0x140 USBTXMAXP4 RW 0x0000 USB Maximum Transmit Data Endpoint 4 1157
        static const uint32_t USBTXCSRL4 = 0x142; // 0x142 USBTXCSRL4 RW 0x00 USB Transmit Control and Status Endpoint 4 Low 1167
        static const uint32_t USBTXCSRH4 = 0x143; // 0x143 USBTXCSRH4 RW 0x00 USB Transmit Control and Status Endpoint 4 High 1171
        static const uint32_t USBRXMAXP4 = 0x144; // 0x144 USBRXMAXP4 RW 0x0000 USB Maximum Receive Data Endpoint 4 1175
        static const uint32_t USBRXCSRL4 = 0x146; // 0x146 USBRXCSRL4 RW 0x00 USB Receive Control and Status Endpoint 4 Low 1176
        static const uint32_t USBRXCSRH4 = 0x147; // 0x147 USBRXCSRH4 RW 0x00 USB Receive Control and Status Endpoint 4 High 1181
        static const uint32_t USBRXCOUNT4 = 0x148; // 0x148 USBRXCOUNT4 RO 0x0000 USB Receive Byte Count Endpoint 4 1185
        static const uint32_t USBTXTYPE4 = 0x14A; // 0x14A USBTXTYPE4 RW 0x00 USB Host Transmit Configure Type Endpoint 4 1186
        static const uint32_t USBTXINTERVAL4 = 0x14B; // 0x14B USBTXINTERVAL4 RW 0x00 USB Host Transmit Interval Endpoint 4 1188
        static const uint32_t USBRXTYPE4 = 0x14C; // 0x14C USBRXTYPE4 RW 0x00 USB Host Configure Receive Type Endpoint 4 1189
        static const uint32_t USBRXINTERVAL4 = 0x14D; // 0x14D USBRXINTERVAL4 RW 0x00 USB Host Receive Polling Interval Endpoint 4 1191
        static const uint32_t USBTXMAXP5 = 0x150; // 0x150 USBTXMAXP5 RW 0x0000 USB Maximum Transmit Data Endpoint 5 1157
        static const uint32_t USBTXCSRL5 = 0x152; // 0x152 USBTXCSRL5 RW 0x00 USB Transmit Control and Status Endpoint 5 Low 1167
        static const uint32_t USBTXCSRH5 = 0x153; // 0x153 USBTXCSRH5 RW 0x00 USB Transmit Control and Status Endpoint 5 High 1171
        static const uint32_t USBRXMAXP5 = 0x154; // 0x154 USBRXMAXP5 RW 0x0000 USB Maximum Receive Data Endpoint 5 1175
        static const uint32_t USBRXCSRL5 = 0x156; // 0x156 USBRXCSRL5 RW 0x00 USB Receive Control and Status Endpoint 5 Low 1176
        static const uint32_t USBRXCSRH5 = 0x157; // 0x157 USBRXCSRH5 RW 0x00 USB Receive Control and Status Endpoint 5 High 1181
        static const uint32_t USBRXCOUNT5 = 0x158; // 0x158 USBRXCOUNT5 RO 0x0000 USB Receive Byte Count Endpoint 5 1185
        static const uint32_t USBTXTYPE5 = 0x15A; // 0x15A USBTXTYPE5 RW 0x00 USB Host Transmit Configure Type Endpoint 5 1186
        static const uint32_t USBTXINTERVAL5 = 0x15B; // 0x15B USBTXINTERVAL5 RW 0x00 USB Host Transmit Interval Endpoint 5 1188
        static const uint32_t USBRXTYPE5 = 0x15C; // 0x15C USBRXTYPE5 RW 0x00 USB Host Configure Receive Type Endpoint 5 1189
        static const uint32_t USBRXINTERVAL5 = 0x15D; // 0x15D USBRXINTERVAL5 RW 0x00 USB Host Receive Polling Interval Endpoint 5 1191
        static const uint32_t USBTXMAXP6 = 0x160; // 0x160 USBTXMAXP6 RW 0x0000 USB Maximum Transmit Data Endpoint 6 1157
        static const uint32_t USBTXCSRL6 = 0x162; // 0x162 USBTXCSRL6 RW 0x00 USB Transmit Control and Status Endpoint 6 Low 1167
        static const uint32_t USBTXCSRH6 = 0x163; // 0x163 USBTXCSRH6 RW 0x00 USB Transmit Control and Status Endpoint 6 High 1171
        static const uint32_t USBRXMAXP6 = 0x164; // 0x164 USBRXMAXP6 RW 0x0000 USB Maximum Receive Data Endpoint 6 1175
        static const uint32_t USBRXCSRL6 = 0x166; // 0x166 USBRXCSRL6 RW 0x00 USB Receive Control and Status Endpoint 6 Low 1176
        static const uint32_t USBRXCSRH6 = 0x167; // 0x167 USBRXCSRH6 RW 0x00 USB Receive Control and Status Endpoint 6 High 1181
        static const uint32_t USBRXCOUNT6 = 0x168; // 0x168 USBRXCOUNT6 RO 0x0000 USB Receive Byte Count Endpoint 6 1185
        static const uint32_t USBTXTYPE6 = 0x16A; // 0x16A USBTXTYPE6 RW 0x00 USB Host Transmit Configure Type Endpoint 6 1186
        static const uint32_t USBTXINTERVAL6 = 0x16B; // 0x16B USBTXINTERVAL6 RW 0x00 USB Host Transmit Interval Endpoint 6 1188
        static const uint32_t USBRXTYPE6 = 0x16C; // 0x16C USBRXTYPE6 RW 0x00 USB Host Configure Receive Type Endpoint 6 1189
        static const uint32_t USBRXINTERVAL6 = 0x16D; // 0x16D USBRXINTERVAL6 RW 0x00 USB Host Receive Polling Interval Endpoint 6 1191
        static const uint32_t USBTXMAXP7 = 0x170; // 0x170 USBTXMAXP7 RW 0x0000 USB Maximum Transmit Data Endpoint 7 1157
        static const uint32_t USBTXCSRL7 = 0x172; // 0x172 USBTXCSRL7 RW 0x00 USB Transmit Control and Status Endpoint 7 Low 1167
        static const uint32_t USBTXCSRH7 = 0x173; // 0x173 USBTXCSRH7 RW 0x00 USB Transmit Control and Status Endpoint 7 High 1171
        static const uint32_t USBRXMAXP7 = 0x174; // 0x174 USBRXMAXP7 RW 0x0000 USB Maximum Receive Data Endpoint 7 1175
        static const uint32_t USBRXCSRL7 = 0x176; // 0x176 USBRXCSRL7 RW 0x00 USB Receive Control and Status Endpoint 7 Low 1176
        static const uint32_t USBRXCSRH7 = 0x177; // 0x177 USBRXCSRH7 RW 0x00 USB Receive Control and Status Endpoint 7 High 1181
        static const uint32_t USBRXCOUNT7 = 0x178; // 0x178 USBRXCOUNT7 RO 0x0000 USB Receive Byte Count Endpoint 7 1185
        static const uint32_t USBTXTYPE7 = 0x17A; // 0x17A USBTXTYPE7 RW 0x00 USB Host Transmit Configure Type Endpoint 7 1186
        static const uint32_t USBTXINTERVAL7 = 0x17B; // 0x17B USBTXINTERVAL7 RW 0x00 USB Host Transmit Interval Endpoint 7 1188
        static const uint32_t USBRXTYPE7 = 0x17C; // 0x17C USBRXTYPE7 RW 0x00 USB Host Configure Receive Type Endpoint 7 1189
        static const uint32_t USBRXINTERVAL7 = 0x17D; // 0x17D USBRXINTERVAL7 RW 0x00 USB Host Receive Polling Interval Endpoint 7 1191
        static const uint32_t USBRQPKTCOUNT1 = 0x304; // 0x304 USBRQPKTCOUNT1 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 1 1192
        static const uint32_t USBRQPKTCOUNT2 = 0x308; // 0x308 USBRQPKTCOUNT2 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 2 1192
        static const uint32_t USBRQPKTCOUNT3 = 0x30C; // 0x30C USBRQPKTCOUNT3 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 3 1192
        static const uint32_t USBRQPKTCOUNT4 = 0x310; // 0x310 USBRQPKTCOUNT4 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 4 1192
        static const uint32_t USBRQPKTCOUNT5 = 0x314; // 0x314 USBRQPKTCOUNT5 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 5 1192
        static const uint32_t USBRQPKTCOUNT6 = 0x318; // 0x318 USBRQPKTCOUNT6 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 6 1192
        static const uint32_t USBRQPKTCOUNT7 = 0x31C; // 0x31C USBRQPKTCOUNT7 RW 0x0000 USB Request Packet Count in Block Transfer Endpoint 6 1192
        static const uint32_t USBRXDPKTBUFDIS = 0x340; // 0x340 USBRXDPKTBUFDIS RW 0x0000 USB Receive Double Packet Buffer Disable 1193
        static const uint32_t USBTXDPKTBUFDIS = 0x342; // 0x342 USBTXDPKTBUFDIS RW 0x0000 USB Transmit Double Packet Buffer Disable 1194
        static const uint32_t USBEPC = 0x400; // 0x400 USBEPC RW 0x0000.0000 USB External Power Control 1195
        static const uint32_t USBEPCRIS = 0x404; // 0x404 USBEPCRIS RO 0x0000.0000 USB External Power Control Raw Interrupt Status 1198
        static const uint32_t USBEPCIM = 0x408; // 0x408 USBEPCIM RW 0x0000.0000 USB External Power Control Interrupt Mask 1199
        static const uint32_t USBEPCISC = 0x40C; // 0x40C USBEPCISC RW 0x0000.0000 USB External Power Control Interrupt Status and Clear 1200
        static const uint32_t USBDRRIS = 0x410; // 0x410 USBDRRIS RO 0x0000.0000 USB Device RESUME Raw Interrupt Status 1201
        static const uint32_t USBDRIM = 0x414; // 0x414 USBDRIM RW 0x0000.0000 USB Device RESUME Interrupt Mask 1202
        static const uint32_t USBDRISC = 0x418; // 0x418 USBDRISC W1C 0x0000.0000 USB Device RESUME Interrupt Status and Clear 1203
        static const uint32_t USBGPCS = 0x41C; // 0x41C USBGPCS RW 0x0000.0003 USB General-Purpose Control and Status 1204
        static const uint32_t USBVDC = 0x430; // 0x430 USBVDC RW 0x0000.0000 USB VBUS Droop Control 1205
        static const uint32_t USBVDCRIS = 0x434; // 0x434 USBVDCRIS RO 0x0000.0000 USB VBUS Droop Control Raw Interrupt Status 1206
        static const uint32_t USBVDCIM = 0x438; // 0x438 USBVDCIM RW 0x0000.0000 USB VBUS Droop Control Interrupt Mask 1207
        static const uint32_t USBVDCISC = 0x43C; // 0x43C USBVDCISC RW 0x0000.0000 USB VBUS Droop Control Interrupt Status and Clear 1208
        static const uint32_t USBIDVRIS = 0x444; // 0x444 USBIDVRIS RO 0x0000.0000 USB ID Valid Detect Raw Interrupt Status 1209
        static const uint32_t USBIDVIM = 0x448; // 0x448 USBIDVIM RW 0x0000.0000 USB ID Valid Detect Interrupt Mask 1210
        static const uint32_t USBIDVISC = 0x44C; // 0x44C USBIDVISC RW1C 0x0000.0000 USB ID Valid Detect Interrupt Status and Clear 1211
        static const uint32_t USBDMASEL = 0x450; // 0x450 USBDMASEL RW 0x0033.2211 USB DMA Select 1212
        static const uint32_t USBPP = 0xFC0; // 0xFC0 USBPP RO 0x0000.10D0 USB Peripheral Properties 1214
}; 

#endif
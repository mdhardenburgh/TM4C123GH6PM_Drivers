/**
 * @file adc.h
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
 * ADC Register Descriptions
 * 
 * The remainder of this section lists and describes the ADC registers, in 
 * numerical order by address offset.
 */

#ifndef ADC_H
#define ADC_H

#include "../systemControl/systemControl.h"

class Adc : SystemControl
{
    public:
        Adc();
        ~Adc();

    private:
        const uint32_t adc0BaseAddress = 0x40038000;
        const uint32_t adc1BaseAddress = 0x40039000;

/**********************System Control Register Descriptions********************/

        Register PPADC{(volatile uint32_t*)(systemControlBase + 0x338)}; //0x338 PPADC RO 0x0000.0003 Analog-to-Digital Converter Peripheral Present 303
        Register SRADC{(volatile uint32_t*)(systemControlBase + 0x538)}; //0x538 SRADC RW 0x0000.0000 Analog-to-Digital Converter Software Reset 327
        Register RCGCADC{(volatile uint32_t*)(systemControlBase + 0x638)}; //0x638 RCGCADC RW 0x0000.0000 Analog-to-Digital Converter Run Mode Clock Gating Control 352
        Register SCGCADC{(volatile uint32_t*)(systemControlBase + 0x738)}; //0x738 SCGCADC RW 0x0000.0000 Analog-to-Digital Converter Sleep Mode Clock Gating Control 374
        Register DCGCADC{(volatile uint32_t*)(systemControlBase + 0x838)}; //0x838 DCGCADC RW 0x0000.0000 Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control 396
        Register PRADC{(volatile uint32_t*)(systemControlBase + 0xA38)}; //0xA38 PRADC RO 0x0000.0000 Analog-to-Digital Converter Peripheral Ready 418

/**************************System Control BitFields****************************/

        bitField PPADC_P1{1, 1, RO}; //ADC Module 1 Present
        bitField PPADC_P0{0, 1, RO}; //ADC Module 0 Present

        bitField SRADC_R1{1, 1, RW}; //ADC Module 1 Software Reset
        bitField SRADC_R0{0, 1, RW}; //ADC Module 0 Software Reset

        bitField RCGCADC_R1{1, 1, RW}; //ADC Module 1 Run Mode Clock Gating Control
        bitField RCGCADC_R0{0, 1, RW}; //ADC Module 0 Run Mode Clock Gating Control

        bitField SCGCADC_S1{1, 1, RW}; //ADC Module 1 Sleep Mode Clock Gating Control
        bitField SCGCADC_S0{0, 1, RW}; //ADC Module 0 Sleep Mode Clock Gating Control

        bitField DCGCADC_D1{1, 1, RW}; //ADC Module 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCADC_D0{0, 1, RW}; //ADC Module 0 Deep-Sleep Mode Clock Gating Control

        bitField PRADC_R1{1, 1, RO}; //ADC Module 1 Peripheral Ready
        bitField PRADC_R0{0, 1, RO}; //ADC Module 0 Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC1_ADC1{17, 1, RO}; //ADC Module 1 Present. When set, indicates that ADC module 1 is present.
        bitField DC1_ADC0{16, 1, RO}; //ADC Module 0 Present. When set, indicates that ADC module 0 is present.
        bitField DC1_MAXADC1SPD{10, 2, RO}; //Max ADC1 Speed. This field indicates the maximum rate at which the ADC samples data.
        bitField DC1_MAXADC0SPD{8, 2, RO}; //Max ADC0 Speed. This field indicates the maximum rate at which the ADC samples data.

        bitField DC3_ADC0AIN7{23, 1, RO}; //ADC Module 0 AIN7 Pin Present. When set, indicates that ADC module 0 input pin 7 is present.
        bitField DC3_ADC0AIN6{22, 1, RO}; //ADC Module 0 AIN6 Pin Present. When set, indicates that ADC module 0 input pin 6 is present.
        bitField DC3_ADC0AIN5{21, 1, RO}; //ADC Module 0 AIN5 Pin Present. When set, indicates that ADC module 0 input pin 5 is present.
        bitField DC3_ADC0AIN4{20, 1, RO}; //ADC Module 0 AIN4 Pin Present. When set, indicates that ADC module 0 input pin 4 is present.
        bitField DC3_ADC0AIN3{19, 1, RO}; //ADC Module 0 AIN3 Pin Present. When set, indicates that ADC module 0 input pin 3 is present.
        bitField DC3_ADC0AIN2{18, 1, RO}; //ADC Module 0 AIN2 Pin Present. When set, indicates that ADC module 0 input pin 2 is present.
        bitField DC3_ADC0AIN1{17, 1, RO}; //ADC Module 0 AIN1 Pin Present. When set, indicates that ADC module 0 input pin 1 is present.
        bitField DC3_ADC0AIN0{16, 1, RO}; //ADC Module 0 AIN0 Pin Present. When set, indicates that ADC module 0 input pin 0 is present.

        bitField DC8_ADC1AIN15{31, 1, RO}; //ADC Module 1 AIN15 Pin Present. When set, indicates that ADC module 1 input pin 15 is present.
        bitField DC8_ADC1AIN14{30, 1, RO}; //ADC Module 1 AIN14 Pin Present. When set, indicates that ADC module 1 input pin 14 is present.
        bitField DC8_ADC1AIN13{29, 1, RO}; //ADC Module 1 AIN13 Pin Present. When set, indicates that ADC module 1 input pin 13 is present.
        bitField DC8_ADC1AIN12{28, 1, RO}; //ADC Module 1 AIN12 Pin Present. When set, indicates that ADC module 1 input pin 12 is present.
        bitField DC8_ADC1AIN11{27, 1, RO}; //ADC Module 1 AIN11 Pin Present. When set, indicates that ADC module 1 input pin 11 is present.
        bitField DC8_ADC1AIN10{26, 1, RO}; //ADC Module 1 AIN10 Pin Present. When set, indicates that ADC module 1 input pin 10 is present.
        bitField DC8_ADC1AIN9{25, 1, RO}; //ADC Module 1 AIN9 Pin Present. When set, indicates that ADC module 1 input pin 9 is present.
        bitField DC8_ADC1AIN8{24, 1, RO}; //ADC Module 1 AIN8 Pin Present. When set, indicates that ADC module 1 input pin 8 is present.
        bitField DC8_ADC1AIN7{23, 1, RO}; //ADC Module 1 AIN7 Pin Present. When set, indicates that ADC module 1 input pin 7 is present.
        bitField DC8_ADC1AIN6{22, 1, RO}; //ADC Module 1 AIN6 Pin Present. When set, indicates that ADC module 1 input pin 6 is present.
        bitField DC8_ADC1AIN5{21, 1, RO}; //ADC Module 1 AIN5 Pin Present. When set, indicates that ADC module 1 input pin 5 is present.
        bitField DC8_ADC1AIN4{20, 1, RO}; //ADC Module 1 AIN4 Pin Present. When set, indicates that ADC module 1 input pin 4 is present.
        bitField DC8_ADC1AIN3{19, 1, RO}; //ADC Module 1 AIN3 Pin Present. When set, indicates that ADC module 1 input pin 3 is present.
        bitField DC8_ADC1AIN2{18, 1, RO}; //ADC Module 1 AIN2 Pin Present. When set, indicates that ADC module 1 input pin 2 is present.
        bitField DC8_ADC1AIN1{17, 1, RO}; //ADC Module 1 AIN1 Pin Present. When set, indicates that ADC module 1 input pin 1 is present.
        bitField DC8_ADC1AIN0{16, 1, RO}; //ADC Module 1 AIN0 Pin Present. When set, indicates that ADC module 1 input pin 0 is present.
        bitField DC8_ADC0AIN15{15, 1, RO}; //ADC Module 0 AIN15 Pin Present. When set, indicates that ADC module 0 input pin 15 is present.
        bitField DC8_ADC0AIN14{14, 1, RO}; //ADC Module 0 AIN14 Pin Present. When set, indicates that ADC module 0 input pin 14 is present.
        bitField DC8_ADC0AIN13{13, 1, RO}; //ADC Module 0 AIN13 Pin Present. When set, indicates that ADC module 0 input pin 13 is present.
        bitField DC8_ADC0AIN12{12, 1, RO}; //ADC Module 0 AIN12 Pin Present. When set, indicates that ADC module 0 input pin 12 is present.
        bitField DC8_ADC0AIN11{11, 1, RO}; //ADC Module 0 AIN11 Pin Present. When set, indicates that ADC module 0 input pin 11 is present.
        bitField DC8_ADC0AIN10{10, 1, RO}; //ADC Module 0 AIN10 Pin Present. When set, indicates that ADC module 0 input pin 10 is present.
        bitField DC8_ADC0AIN9{9, 1, RO}; //ADC Module 0 AIN9 Pin Present. When set, indicates that ADC module 0 input pin 9 is present.
        bitField DC8_ADC0AIN8{8, 1, RO}; //ADC Module 0 AIN8 Pin Present. When set, indicates that ADC module 0 input pin 8 is present.
        bitField DC8_ADC0AIN7{7, 1, RO}; //ADC Module 0 AIN7 Pin Present. When set, indicates that ADC module 0 input pin 7 is present.
        bitField DC8_ADC0AIN6{6, 1, RO}; //ADC Module 0 AIN6 Pin Present. When set, indicates that ADC module 0 input pin 6 is present.
        bitField DC8_ADC0AIN5{5, 1, RO}; //ADC Module 0 AIN5 Pin Present. When set, indicates that ADC module 0 input pin 5 is present.
        bitField DC8_ADC0AIN4{4, 1, RO}; //ADC Module 0 AIN4 Pin Present. When set, indicates that ADC module 0 input pin 4 is present.
        bitField DC8_ADC0AIN3{3, 1, RO}; //ADC Module 0 AIN3 Pin Present. When set, indicates that ADC module 0 input pin 3 is present.
        bitField DC8_ADC0AIN2{2, 1, RO}; //ADC Module 0 AIN2 Pin Present. When set, indicates that ADC module 0 input pin 2 is present.
        bitField DC8_ADC0AIN1{1, 1, RO}; //ADC Module 0 AIN1 Pin Present. When set, indicates that ADC module 0 input pin 1 is present.
        bitField DC8_ADC0AIN0{0, 1, RO}; //ADC Module 0 AIN0 Pin Present. When set, indicates that ADC module 0 input pin 0 is present.

        bitField SRCR0_ADC1{17, 1, RO}; //ADC1 Reset Control
        bitField SRCR0_ADC0{16, 1, RO}; //ADC0 Reset Control

        bitField RCGC0_ADC1{17, 1, RO}; //ADC1 Clock Gating Control
        bitField RCGC0_ADC0{16, 1, RO}; //ADC0 Clock Gating Control
        bitField RCGC0_MAXADC1SPD{10, 2, RO}; //ADC1 Sample Speed
        bitField RCGC0_MAXADC0SPD{8, 2, RO}; //ADC0 Sample Speed

        bitField SCGC0_ADC1{17, 1, RO}; //ADC1 Clock Gating Control
        bitField SCGC0_ADC0{16, 1, RO}; //ADC0 Clock Gating Control

        bitField DCGC0_ADC1{17, 1, RO}; //ADC1 Clock Gating Control
        bitField DCGC0_ADC0{16, 1, RO}; //ADC0 Clock Gating Control

        bitField DC9_ADC1DC7{23, 1, RO}; //ADC1 DC7 Present. When set, indicates that ADC module 1 Digital Comparator 7 is present.
        bitField DC9_ADC1DC6{22, 1, RO}; //ADC1 DC6 Present. When set, indicates that ADC module 1 Digital Comparator 6 is present.
        bitField DC9_ADC1DC5{21, 1, RO}; //ADC1 DC5 Present. When set, indicates that ADC module 1 Digital Comparator 5 is present.
        bitField DC9_ADC1DC4{20, 1, RO}; //ADC1 DC4 Present. When set, indicates that ADC module 1 Digital Comparator 4 is present.
        bitField DC9_ADC1DC3{19, 1, RO}; //ADC1 DC3 Present. When set, indicates that ADC module 1 Digital Comparator 3 is present.
        bitField DC9_ADC1DC2{18, 1, RO}; //ADC1 DC2 Present. When set, indicates that ADC module 1 Digital Comparator 2 is present.
        bitField DC9_ADC1DC1{17, 1, RO}; //ADC1 DC1 Present. When set, indicates that ADC module 1 Digital Comparator 1 is present.
        bitField DC9_ADC1DC0{16, 1, RO}; //ADC1 DC0 Present. When set, indicates that ADC module 1 Digital Comparator 0 is present.
        bitField DC9_ADC0DC7{7, 1, RO}; //ADC1 DC7 Present. When set, indicates that ADC module 0 Digital Comparator 7 is present.
        bitField DC9_ADC0DC6{6, 1, RO}; //ADC1 DC6 Present. When set, indicates that ADC module 0 Digital Comparator 6 is present.
        bitField DC9_ADC0DC5{5, 1, RO}; //ADC1 DC5 Present. When set, indicates that ADC module 0 Digital Comparator 5 is present.
        bitField DC9_ADC0DC4{4, 1, RO}; //ADC1 DC4 Present. When set, indicates that ADC module 0 Digital Comparator 4 is present.
        bitField DC9_ADC0DC3{3, 1, RO}; //ADC1 DC3 Present. When set, indicates that ADC module 0 Digital Comparator 3 is present.
        bitField DC9_ADC0DC2{2, 1, RO}; //ADC1 DC2 Present. When set, indicates that ADC module 0 Digital Comparator 2 is present.
        bitField DC9_ADC0DC1{1, 1, RO}; //ADC1 DC1 Present. When set, indicates that ADC module 0 Digital Comparator 1 is present.
        bitField DC9_ADC0DC0{0, 1, RO}; //ADC1 DC0 Present. When set, indicates that ADC module 0 Digital Comparator 0 is present.
};

#endif //ADC_H
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

const uint32_t adc0BaseAddress = 0x40038000;
const uint32_t adc1BaseAddress = 0x40039000;

const uint32_t PPADC_OFFSET = 0x338; //0x338 PPADC RO 0x0000.0003 Analog-to-Digital Converter Peripheral Present 303
const uint32_t SRADC_OFFSET = 0x538; //0x538 SRADC RW 0x0000.0000 Analog-to-Digital Converter Software Reset 327
const uint32_t RCGCADC_OFFSET = 0x638; //0x638 RCGCADC RW 0x0000.0000 Analog-to-Digital Converter Run Mode Clock Gating Control 352
const uint32_t SCGCADC_OFFSET = 0x738; //0x738 SCGCADC RW 0x0000.0000 Analog-to-Digital Converter Sleep Mode Clock Gating Control 374
const uint32_t DCGCADC_OFFSET = 0x838; //0x838 DCGCADC RW 0x0000.0000 Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control 396
const uint32_t PRADC_OFFSET = 0xA38; //0xA38 PRADC RO 0x0000.0000 Analog-to-Digital Converter Peripheral Ready 418

class Adc : SystemControl
{
    public:
        Adc();
        ~Adc();

    private:

/**************************System Control BitFields****************************/

        // bitField PPADC_P1{1, 1, RO}; //ADC Module 1 Present
        // bitField PPADC_P0{0, 1, RO}; //ADC Module 0 Present

        // bitField SRADC_R1{1, 1, RW}; //ADC Module 1 Software Reset
        // bitField SRADC_R0{0, 1, RW}; //ADC Module 0 Software Reset

        // bitField RCGCADC_R1{1, 1, RW}; //ADC Module 1 Run Mode Clock Gating Control
        // bitField RCGCADC_R0{0, 1, RW}; //ADC Module 0 Run Mode Clock Gating Control

        // bitField SCGCADC_S1{1, 1, RW}; //ADC Module 1 Sleep Mode Clock Gating Control
        // bitField SCGCADC_S0{0, 1, RW}; //ADC Module 0 Sleep Mode Clock Gating Control

        // bitField DCGCADC_D1{1, 1, RW}; //ADC Module 1 Deep-Sleep Mode Clock Gating Control
        // bitField DCGCADC_D0{0, 1, RW}; //ADC Module 0 Deep-Sleep Mode Clock Gating Control

        // bitField PRADC_R1{1, 1, RO}; //ADC Module 1 Peripheral Ready
        // bitField PRADC_R0{0, 1, RO}; //ADC Module 0 Peripheral Ready


};

#endif //ADC_H
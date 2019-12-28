/**
 * @file systemClock.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/21/2019
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
 * Class header for the system clock for the Texas Instruments Tiva C ARM4F 
 * microcontroller, TM4C123GH6PM. 
 * 
 * System clock sets the clock frequency. Default is to use the 80MHz clock 
 * generated from the PLL.
 * 
 * The clock can be configured for other frequencies and to use other
 * oscillators such as the internal oscilator, LF internal oscilator, and the
 * 32.768-kHz external oscillator.
 * 
 * Clock calibration and PLL information can be accessed as well.
 */

#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

#include "systemControl.h"

class SystemClock : SystemControl
{
    public:
        SystemClock();
        SystemClock(uint32_t frequency);
        ~SystemClock();

        enum SYSDIV2
        {
            /* reserved = 2; //reserved = 3; //reserved = 4; */ _80MHz = 5,
             _66_67MHz = 6, /* reserved = 7; */ _50MHz = 8, _44_44MHz = 9,
            _40MHz = 10, _36_36MHz = 11, _33_33MHz = 12, _30_77MHz = 13,
            _28_57MHz = 14, _26_66MHz = 15, _25MHz = 16, _23_53MHz = 17,
            _22_22MHz = 18, _21_05MHz = 19, _20MHz = 20, _19_05MHz = 21,
            _18_18MHz = 22, _17_39MHz = 23, _16_66MHz = 24, _16MHz = 25,
            _15_38MHz = 26, _14_81MHz = 27, _14_28MHz = 28, _13_79MHz = 29,
            _13_33MHz = 30, _12_90MHz = 31, _12_50MHz = 32, _12_12MHz = 33,
            _11_76MHz = 34, _11_43MHz = 35, _11_11MHz = 36,_10_81MHz = 37,
            _10_53MHz = 38, _10_25MHz = 39, _10MHz = 40, _9_76MHz = 41,
            _9_52MHz = 42, _9_30MHz = 43, _9_09MHz = 44, _8_89MHz = 45,
            _8_69MHz = 46, _8_51MHz = 47, _8_33MHz = 48, _8_16MHz = 49,
            _8MHz = 50, _7_84MHz = 51, _7_69MHz = 52, _7_55MHz = 53,
            _7_41MHz = 54, _7_27MHz = 55, _7_14MHz = 56, _7_02MHz = 57,
            _6_89MHz = 58, _6_78MHz = 59, _6_66MHz = 60, _6_55MHz = 61,
            _6_45MHz = 62, _6_34MHz = 63, _6_25MHz = 64, _6_15MHz = 65,
            _6_06MHz = 66, _5_97MHz = 67, _5_88MHz = 68, _5_79MHz = 69,
            _5_71MHz = 70, _5_63MHz = 71, _5_55MHz = 72, _5_47MHz = 73,
            _5_40MHz = 74, _5_33MHz = 75, _5_26MHz = 76, _5_19MHz = 77,
            _5_12MHz = 78, _5_06MHz = 79, _5MHz = 80, _4_93MHz = 81,
            _4_87MHz = 82, _4_81MHz = 83, _4_76MHz = 84, _4_70MHz = 85,
            _4_65MHz = 86, _4_59MHz = 87, _4_54MHz = 88, _4_49MHz = 89,
            _4_44MHz = 90, _4_39MHz = 91, _4_34MHz = 92, _4_30MHz = 93,
            _4_25MHz = 94, _4_21MHz = 95, _4_16MHz = 96, _4_12MHz = 97,
            _4_08MHz = 98, _4_04MHz = 99, _4MHz = 100, _3_96MHz = 101,
            _3_92MHz = 102, _3_88MHz = 103, _3_84MHz = 104, _3_81MHz = 105,
            _3_77MHz = 106, _3_73MHz = 107, _3_70MHz = 108, _3_67MHz = 109,
            _3_63MHz = 110, _3_60MHz = 111, _3_57MHz = 112,_3_54MHz = 113,
            _3_50MHz = 114, _3_47MHz = 115, _3_44MHz = 116, _3_41MHz = 117,
            _3_90MHz = 118, _3_36MHz = 119, _3_33MHz = 120, _3_30MHz = 121,
            _3_27MHz = 122, _3_25MHz = 123, _3_22MHz = 124,_3_20MHz = 125,
            _3_17MHz = 126, _3_15MHz = 127, _3_12MHz = 128
        };

    private:
        void activatePll(uint32_t frequency);

        enum XTAL_VAL
        {
            _4MHz_XTAL = 0x09u, _6MHz_XTAL = 0x0Bu, _8MHz_XTAL = 0x0Eu,
            _10MHz_XTAL = 0x10u, _12MHz_XTAL = 0x11u, _16MHz_XTAL = 0x15u,
            _18MHz_XTAL = 0x17u, _20MHz_XTAL = 0x18u, _24MHz_XTAL = 0x19u,
            _25MHz_XTAL = 0x1Au
        };

        enum OSCSRC
        {
            MOSC = 0x0u, //Main oscillator
            PIOSC = 0x1u, //Precision internal oscillator (default)
            PIOSC4 = 0x2u, //Precision internal oscillator / 4
            LFIOSC = 0x3u, //Low-frequency internal oscillator
            //reserved = 0x4,
            //reserved = 0x5,
            //reserved = 0x6,
            _32_768kHz = 0x7 //32.768-kHz external oscillator
        };

        Register MOSCCTL{(volatile uint32_t*)(systemControlBase + 0x07C)}; //0x07C MOSCCTL RW 0x0000.0000 Main Oscillator Control 263
        Register DSLPCLKCFG{(volatile uint32_t*)(systemControlBase + 0x144)}; //0x144 DSLPCLKCFG RW 0x0780.0000 Deep Sleep Clock Configuration 264
        Register PIOSCCAL{(volatile uint32_t*)(systemControlBase + 0x150)}; //0x150 PIOSCCAL RW 0x0000.0000 Precision Internal Oscillator Calibration 268
        Register PIOSCSTAT{(volatile uint32_t*)(systemControlBase + 0x154)}; //0x154 PIOSCSTAT RO 0x0000.0040 Precision Internal Oscillator Statistics 270
        Register PLLFREQ0{(volatile uint32_t*)(systemControlBase + 0x160)}; //0x160 PLLFREQ0 RO 0x0000.0032 PLL Frequency 0 271
        Register PLLFREQ1{(volatile uint32_t*)(systemControlBase + 0x164)}; //0x164 PLLFREQ1 RO 0x0000.0001 PLL Frequency 1 272
        Register PLLSTAT{(volatile uint32_t*)(systemControlBase + 0x168)}; //0x168 PLLSTAT RO 0x0000.0000 PLL Status 273

        bitField RIS_MOSCPUPRIS{8, 1, RO}; //MOSC Power Up Raw Interrupt Status
        bitField RIS_PLLLRIS{6, 1, RO}; //PLL Lock Raw Interrupt Status
        bitField RIS_MOFRIS{3, 1, RO}; //Main Oscillator Failure Raw Interrupt Status

        bitField IMC_MOSCPUPIM{8, 1, RW}; //MOSC Power Up Interrupt Mask
        bitField IMC_PLLLIM{6, 1, RW}; //PLL Lock Interrupt Mask
        bitField IMC_MOFIM{3, 1, RW}; //Main Oscillator Failure Interrupt Mask

        bitField MISC_MOSCPUPMIS{8, 1, RW1C}; //MOSC Power Up Masked Interrupt Status
        bitField MISC_PLLLMIS{6, 1, RW1C}; //PLL Lock Masked Interrupt Status
        bitField MISC_MOFMIS{3, 1, RO}; //Main Oscillator Failure Masked Interrupt Status

        bitField RESC_MOSCFAIL{16, 1, RW}; //MOSC Failure Reset

        bitField RCC_ACG{27, 1, RW}; //Auto Clock Gating
        bitField RCC_SYSDIV{23, 4, RW}; //System Clock Divisor
        bitField RCC_BYPASS{11, 1, RW}; //PLL Bypass
        bitField RCC_USESYSDIV{22, 1, RW}; //Enable System Clock Divider
        bitField RCC_XTAL{6, 5, RW}; //Crystal Value
        bitField RCC_OSCSRC{4, 2, RW}; //Oscillator Source
        bitField RCC_PWRDN{13, 1, RW}; //PLL Power Down
        bitField RCC_MOSCDIS{0, 1, RW}; //Main Oscillator Disable

        bitField RCC2_USERCC2{31, 1, RW}; //Use RCC2
        bitField RCC2_DIV400{30, 1, RW}; //Divide PLL as 400 MHz versus 200 MHz
        bitField RCC2_SYSDIV2{23, 6, RW}; //System Clock Divisor 2
        bitField RCC2_SYSDIV2LSB{22, 1, RW}; //Additional LSB for SYSDIV2
        bitField RCC2_PWRDN2{13, 1, RW}; //Power-Down PLL 2
        bitField RCC2_BYPASS2{11, 1, RW}; //PLL Bypass 2
        bitField RCC2_OSCSRC2{4, 3, RW}; //Oscillator Source 2

        bitField MOSCCTL_NOXTAL{2, 1, RW}; //No Crystal Connected
        bitField MOSCCTL_MOSCIM{1, 1, RW}; //MOSC Failure Action
        bitField MOSCCTL_CVAL{0, 1, RW}; //Clock Validation for MOSC

        bitField DSLPCLKCFG_DSDIVORIDE{23, 6, RW}; //Divider Field Override
        bitField DSLPCLKCFG_DSOSCSRC{4, 3, RW}; //Clock Source, Specifies the clock source during Deep-Sleep mode.
        bitField DSLPCLKCFG_PIOSCPD{1, 1, RW}; //PIOSC Power Down Request

        bitField SYSPROP_PIOSCPDE{12, 1, RO}; //PIOSC Power Down Present

        bitField PIOSCCAL_UTEN{31, 1, RW}; //Use User Trim Value
        bitField PIOSCCAL_CAL{9, 1, RW}; //Start Calibration
        bitField PIOSCCAL_UPDATE{8, 1, RW}; //Update Trim
        bitField PIOSCCAL_UT{0, 7, RW}; //User Trim Value. User trim value that can be loaded into the PIOSC.

        bitField PIOSCSTAT_DT{16, 7, RO}; //Default Trim Value. This field contains the default trim value.
        bitField PIOSCSTAT_RESULT{8, 2, RO}; //Calibration Result
        bitField PIOSCSTAT_CT{0, 7, RO}; //Calibration Trim Value

        bitField PLLFREQ0_MFRAC{10, 10, RO}; //PLL M Fractional Value. This field contains the integer value of the PLL M value.
        bitField PLLFREQ0_MINT{0, 10, RO}; //PLL M Integer Value. This field contains the integer value of the PLL M value.

        bitField PLLFREQ1_Q{8, 5, RO}; //PLL Q Value. This field contains the PLL Q value.
        bitField PLLFREQ1_N{0, 5, RO}; //PLL N Value. This field contains the PLL N value.

        bitField PLLSTAT_LOCK{0, 1, RO}; //PLL Lock

};

#endif //SYSTEM_CLOCK_H

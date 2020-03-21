/**
 * @file systemControl.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/15/2019
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
 */



#ifndef SYSTEM_CONTROL_H
#define SYSTEM_CONTROL_H

#include "../register/register.h"
#include "../corePeripherals/nvic/nvic.h"

const uint32_t systemControlBase = 0x400FE000;


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

class SystemControl
{

    public:
        SystemControl();
        ~SystemControl();

        static void initializeGPIOHB(void);
        static void initializeClock(SYSDIV2 frequency);

    private:

        static const uint32_t RCC_OFFSET = 0x060; //RCC RW 0x078E.3AD1 Run-Mode Clock Configuration 254
        static const uint32_t RCC2_OFFSET = 0x070; //RCC2 RW 0x07C0.6810 Run-Mode Clock Configuration 2 260
        static const uint32_t RIS_OFFSET = 0x050; //0x050 RIS RO 0x0000.0000 Raw Interrupt Status 244

        static const uint32_t DID0_OFFSET = 0x000; //0x000 DID0 RO - Device Identification 238
        static const uint32_t DID1_OFFSET = 0x004; //0x004 DID1 RO 0x10A1.606E Device Identification 1 240
        static const uint32_t PBORCTL_OFFSET = 0x030; //0x030 PBORCTL RW 0x0000.7FFF Brown-Out Reset Control 243
        static const uint32_t IMC_OFFSET = 0x054; //0x054 IMC RW 0x0000.0000 Interrupt Mask Control 247
        static const uint32_t MISC_OFFSET = 0x058; //0x058 MISC RW1C 0x0000.0000 Masked Interrupt Status and Clear 249
        static const uint32_t RESC_OFFSET = 0x05C; //0x05C RESC RW - Reset Cause 252
        static const uint32_t MOSCCTL_OFFSET = 0x07C; //0x07C MOSCCTL RW 0x0000.0000 Main Oscillator Control 263
        static const uint32_t DSLPCLKCFG_OFFSET = 0x144; //0x144 DSLPCLKCFG RW 0x0780.0000 Deep Sleep Clock Configuration 264
        static const uint32_t SYSPROP_OFFSET = 0x14C; //0x14C SYSPROP RO 0x0000.1D31 System Properties 266
        static const uint32_t PIOSCCAL_OFFSET = 0x150; //0x150 PIOSCCAL RW 0x0000.0000 Precision Internal Oscillator Calibration 268
        static const uint32_t PIOSCSTAT_OFFSET = 0x154; //0x154 PIOSCSTAT RO 0x0000.0040 Precision Internal Oscillator Statistics 270
        static const uint32_t PLLFREQ0_OFFSET = 0x160; //0x160 PLLFREQ0 RO 0x0000.0032 PLL Frequency 0 271
        static const uint32_t PLLFREQ1_OFFSET = 0x164; //0x164 PLLFREQ1 RO 0x0000.0001 PLL Frequency 1 272
        static const uint32_t PLLSTAT_OFFSET = 0x168; //0x168 PLLSTAT RO 0x0000.0000 PLL Status 273
        static const uint32_t SLPPWRCFG_OFFSET = 0x188; //0x188 SLPPWRCFG RW 0x0000.0000 Sleep Power Configuration 274
        static const uint32_t DSLPPWRCFG_OFFSET = 0x18C; //0x18C DSLPPWRCFG RW 0x0000.0000 Deep-Sleep Power Configuration 276
        static const uint32_t LDOSPCTL_OFFSET = 0x1B4; //0x1B4 LDOSPCTL RW 0x0000.0018 LDO Sleep Power Control 278
        static const uint32_t LDOSPCAL_OFFSET = 0x1B8; //0x1B8 LDOSPCAL RO 0x0000.1818 LDO Sleep Power Calibration 280
        static const uint32_t LDODPCTL_OFFSET = 0x1BC; //0x1BC LDODPCTL RW 0x0000.0012 LDO Deep-Sleep Power Control 28
        static const uint32_t LDODPCAL_OFFSET = 0x1C0; //0x1C0 LDODPCAL RO 0x0000.1212 LDO Deep-Sleep Power Calibration 283
        static const uint32_t SDPMST_OFFSET = 0x1CC; //0x1CC SDPMST RO 0x0000.0000 Sleep/Deep-Sleep Power Mode Status 284
        static const uint32_t GPIOHBCTL_OFFSET = 0x06C; //0x06C GPIOHBCTL RW 0x0000.7E00 GPIO High-Performance Bus Control 258
};

#endif //SYSTEM_CONTROL_H
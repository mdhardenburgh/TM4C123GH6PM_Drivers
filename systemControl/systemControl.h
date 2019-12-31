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

#include "../register.h"

const uint32_t systemControlBase = 0x400FE000;

class SystemControl
{

    public:
        SystemControl();
        ~SystemControl();

    protected:
        // const uint32_t systemControlBase = 0x400FE000;

        Register RCC{(volatile uint32_t*)(systemControlBase + 0x060)}; //0x060 RCC RW 0x078E.3AD1 Run-Mode Clock Configuration 254
        Register RCC2{(volatile uint32_t*)(systemControlBase + 0x070)}; //0x070 RCC2 RW 0x07C0.6810 Run-Mode Clock Configuration 2 260
        Register RIS{(volatile uint32_t*)(systemControlBase + 0x050)}; //0x050 RIS RO 0x0000.0000 Raw Interrupt Status 244

    private:

/**********************System Control Register Descriptions********************/

///////////////////////////////////////////////////////////////////////////Offset Name Type Reset Description See page

        Register DID0{(volatile uint32_t*)(systemControlBase + 0x000)}; //0x000 DID0 RO - Device Identification 238
        Register DID1{(volatile uint32_t*)(systemControlBase + 0x004)}; //0x004 DID1 RO 0x10A1.606E Device Identification 1 240
        Register PBORCTL{(volatile uint32_t*)(systemControlBase + 0x030)}; //0x030 PBORCTL RW 0x0000.7FFF Brown-Out Reset Control 243
        Register IMC{(volatile uint32_t*)(systemControlBase + 0x054)}; //0x054 IMC RW 0x0000.0000 Interrupt Mask Control 247
        Register MISC{(volatile uint32_t*)(systemControlBase + 0x058)}; //0x058 MISC RW1C 0x0000.0000 Masked Interrupt Status and Clear 249
        Register RESC{(volatile uint32_t*)(systemControlBase + 0x05C)}; //0x05C RESC RW - Reset Cause 252
        // Register GPIOHBCTL{(volatile uint32_t*)(systemControlBase + 0x06C)}; 
        Register SLPPWRCFG{(volatile uint32_t*)(systemControlBase + 0x188)}; //0x188 SLPPWRCFG RW 0x0000.0000 Sleep Power Configuration 274
        Register DSLPPWRCFG{(volatile uint32_t*)(systemControlBase + 0x18C)}; //0x18C DSLPPWRCFG RW 0x0000.0000 Deep-Sleep Power Configuration 276
        Register LDOSPCTL{(volatile uint32_t*)(systemControlBase + 0x1B4)}; //0x1B4 LDOSPCTL RW 0x0000.0018 LDO Sleep Power Control 278
        Register LDOSPCAL{(volatile uint32_t*)(systemControlBase + 0x1B8)}; //0x1B8 LDOSPCAL RO 0x0000.1818 LDO Sleep Power Calibration 280
        Register LDODPCTL{(volatile uint32_t*)(systemControlBase + 0x1BC)}; //0x1BC LDODPCTL RW 0x0000.0012 LDO Deep-Sleep Power Control 28
        Register LDODPCAL{(volatile uint32_t*)(systemControlBase + 0x1C0)}; //0x1C0 LDODPCAL RO 0x0000.1212 LDO Deep-Sleep Power Calibration 283
        Register SDPMST{(volatile uint32_t*)(systemControlBase + 0x1CC)}; //0x1CC SDPMST RO 0x0000.0000 Sleep/Deep-Sleep Power Mode Status 284

/********************System Control Legacy Register Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        Register DC0{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x008 DC0 RO 0x007F.007F Device Capabilities 0 425
        Register DC1{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x010 DC1 RO 0x1333.2FFF Device Capabilities 1 427
        Register DC2{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x014 DC2 RO 0x030F.F337 Device Capabilities 2 430
        Register DC3{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x018 DC3 RO 0xBFFF.8FFF Device Capabilities 3 433
        Register DC4{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x01C DC4 RO 0x0004.F03F Device Capabilities 4 437
        Register DC5{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x020 DC5 RO 0x0130.00FF Device Capabilities 5 440
        Register DC6{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x024 DC6 RO 0x0000.0013 Device Capabilities 6 442
        Register DC7{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x028 DC7 RO 0xFFFF.FFFF Device Capabilities 7 443
        Register DC8{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x02C DC8 RO 0x0FFF.0FFF Device Capabilities 8 446
        Register SRCR0{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x040 SRCR0 RO 0x0000.0000 Software Reset Control 0 449
        Register SRCR1{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x044 SRCR1 RO 0x0000.0000 Software Reset Control 1 451
        Register SRCR2{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x048 SRCR2 RO 0x0000.0000 Software Reset Control 2 454
        Register RCGC0{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x100 RCGC0 RO 0x0000.0040 Run Mode Clock Gating Control Register 0 456
        Register RCGC1{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x104 RCGC1 RO 0x0000.0000 Run Mode Clock Gating Control Register 1 460
        Register RCGC2{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x108 RCGC2 RO 0x0000.0000 Run Mode Clock Gating Control Register 2 464
        
        Register SCGC0{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x110 SCGC0 RO 0x0000.0040 Sleep Mode Clock Gating Control Register 0 466
        Register SCGC1{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x114 SCGC1 RO 0x0000.0000 Sleep Mode Clock Gating Control Register 1 469
        Register SCGC2{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x118 SCGC2 RO 0x0000.0000 Sleep Mode Clock Gating Control Register 2 472
        Register DCGC0{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x120 DCGC0 RO 0x0000.0040 Deep Sleep Mode Clock Gating Control Register 0 474
        Register DCGC1{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x124 DCGC1 RO 0x0000.0000 Deep-Sleep Mode Clock Gating Control Register 1 477
        Register DCGC2 {(volatile uint32_t*)(systemControlBase + 0xA5C)};//0x128 DCGC2 RO 0x0000.0000 Deep Sleep Mode Clock Gating Control Register 2 480
        Register DC9 {(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x190 DC9 RO 0x00FF.00FF Device Capabilities 9 482
        Register NVMSTAT{(volatile uint32_t*)(systemControlBase + 0xA5C)}; //0x1A0 NVMSTAT RO 0x0000.0001 Non-Volatile Memory Information 484

/**************************System Control BitFields****************************/

        bitField DID0_VER{28, 3, RO}; //DID0 Version
        bitField DID0_CLASS{16, 8, RO}; //Device Class
        bitField DID0_MAJOR{8, 8, RO}; //Major Die Revision
        bitField DID0_MINOR{0, 8, RO}; //Minor Die Revision

        bitField DID1_VER{28, 4, RO}; //DID1 Version
        bitField DID1_FAM{24, 4, RO}; //Family
        bitField DID1_PARTNO{16, 8, RO}; //Part Number
        bitField DID1_PINCOUNT{13, 3, RO}; //Package Pin Count
        bitField DID1_TEMP{5, 3, RO}; //Temperature Range
        bitField DID1_PKG{3, 2, RO}; //Package Type
        bitField DID1_ROHS{2, 1, RO}; //RoHS-Compliance
        bitField DID1_QUAL{0, 2, RO}; //Qualification Status

        bitField PBORCTL_BOR0{2, 1, RW}; //VDD under BOR0 Event Action
        bitField PBORCTL_BOR1{1, 1, RW}; //VDD under BOR1 Event Action

        bitField RIS_BOR0RIS{11, 1, RO}; //VDD under BOR0 Raw Interrupt Status
        bitField RIS_VDDARIS{10, 1, RO}; //VDDA Power OK Event Raw Interrupt Status
        bitField RIS_BOR1RIS{1, 1, RO}; //VDD under BOR1 Raw Interrupt Status

        bitField IMC_BOR0IM{11, 1, RW}; //VDD under BOR0 Interrupt Mask
        bitField IMC_VDDAIM{10, 1, RW}; //VDDA Power OK Interrupt Mask
        bitField IMC_BOR1IM{1, 1, RW}; //VDD under BOR1 Interrupt Mask

        bitField MISC_BOR0MIS{11, 1, RW1C}; //VDD under BOR0 Masked Interrupt Status
        bitField MISC_VDDAMIS{10, 1, RW1C}; //VDDA Power OK Masked Interrupt Status
        bitField MISC_BOR1MIS{1, 1, RW1C}; //VDD under BOR1 Masked Interrupt Status
        
        bitField RESC_SW{4, 1, RW}; //Software Reset
        bitField RESC_BOR{2, 1, RW}; //Brown-Out Reset
        bitField RESC_POR{1, 1, RW}; //Power-On Reset
        bitField RESC_EXT{0, 1, RW}; //External Reset

        // bitField GPIOHBCTL_PORTF{5, 1, RW}; //Port F Advanced High-Performance Bus
        // bitField GPIOHBCTL_PORTE{4, 1, RW}; //Port E Advanced High-Performance Bus
        // bitField GPIOHBCTL_PORTD{3, 1, RW}; //Port D Advanced High-Performance Bus
        // bitField GPIOHBCTL_PORTC{2, 1, RW}; //Port C Advanced High-Performance Bus
        // bitField GPIOHBCTL_PORTB{1, 1, RW}; //Port B Advanced High-Performance Bus
        // bitField GPIOHBCTL_PORTA{0, 1, RW}; //Port A Advanced High-Performance Bus
        // bitField GPIOHBCTL_PORT[6] = {GPIOHBCTL_PORTA, GPIOHBCTL_PORTB, GPIOHBCTL_PORTC, GPIOHBCTL_PORTD, GPIOHBCTL_PORTE, GPIOHBCTL_PORTF};
   
        bitField SYSPROP_SRAMSM{11, 1, RO}; //SRAM Sleep/Deep-Sleep Standby Mode Present
        bitField SYSPROP_SRAMLPM{10, 1, RO}; //SRAM Sleep/Deep-Sleep Low Power Mode Present
        bitField SYSPROP_FLASHLPM{8, 1, RO}; //Flash Memory Sleep/Deep-Sleep Low Power Mode Present
        bitField SYSPROP_FPU{0, 1, RO}; //FPU Present. This bit indicates if the FPU is present in the Cortex-M4 core.

        bitField SLPPWRCFG_FLASHPM{4, 2, RW}; //Flash Power Modes
        bitField SLPPWRCFG_SRAMPM{0, 2, RW}; //SRAM Power Modes

        bitField DSLPPWRCFG_FLASHPM{4, 2, RW}; //Flash Power Modes
        bitField DSLPPWRCFG_SRAMPM{0, 2, RW}; //SRAM Power Modes

        bitField LDOSPCTL_VADJEN{31, 1, RW}; //Voltage Adjust Enable
        bitField LDOSPCTL_VLDO{0, 8, RW}; //LDO Output Voltage

        bitField LDOSPCAL_WITHPLL{8, 8, RO}; //Sleep with PLL
        bitField LDOSPCAL_NOPLL{0, 8, RO}; //Sleep without PLL

        bitField LDODPCTL_VADJEN{31, 1, RW}; //Voltage Adjust Enable
        bitField LDODPCTL_VLDO{0, 8, RW}; //LDO Output Voltage

        bitField LDODPCAL_NOPLL{8, 8, RO}; //Deep-Sleep without PLL
        bitField LDODPCAL_30KHZ{0, 8, RO}; //Deep-Sleep with IOSC

        bitField SDPMST_LDOUA{19, 1, RO}; //LDO Update Active
        bitField SDPMST_FLASHLP{18, 1, RO}; //Flash Memory in Low Power State
        bitField SDPMST_LOWPWR{17, 1, RO}; //Sleep or Deep-Sleep Mode
        bitField SDPMST_PRACT{16, 1, RO}; //Sleep or Deep-Sleep Power Request Active
        bitField SDPMST_PPDW{7, 1, RO}; //PIOSC Power Down Request Warning
        bitField SDPMST_LMAXERR{6, 1, RO}; //VLDO Value Above Maximum Error
        bitField SDPMST_LSMINERR{4, 1, RO}; //VLDO Value Below Minimum Error in Sleep Mode
        bitField SDPMST_LDMINERR{3, 1, RO}; //VLDO Value Below Minimum Error in Deep-Sleep Mode
        bitField SDPMST_PPDERR{2, 1, RO}; //PIOSC Power Down Request Error
        bitField SDPMST_FPDERR{1, 1, RO}; //Flash Memory Power Down Request Error
        bitField SDPMST_SPDERR{0, 1, RO}; //SRAM Power Down Request Error

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC0_SRAMSZ{16, 16, RO}; //SRAM Size. Indicates the size of the on-chip SRAM.
        bitField DC0_FLASHSZ{0, 16, RO}; //Flash Size. Indicates the size of the on-chip Flash memory.

        bitField DC1_MINSYSDIV{12, 4, RO}; //System Clock Divider
        bitField DC1_MPU{7, 1, RO}; //MPU Present. When set, indicates that the Cortex-M4F Memory Protection Unit (MPU) module is present.
        bitField DC1_TEMPSNS{5, 1, RO}; //Temp Sensor Present. When set, indicates that the on-chip temperature sensor is present.
        bitField DC1_PLL{4, 1, RO}; //PLL Present. When set, indicates that the on-chip Phase Locked Loop (PLL) is present.
        bitField DC1_SWO{2, 1, RO}; //SWO Trace Port Present. When set, indicates that the Serial Wire Output (SWO) trace port is present.
        bitField DC1_SWD{1, 1, RO}; //SWD Present When set, indicates that the Serial Wire Debugger (SWD) is present.
        bitField DC1_JTAG{0, 1, RO}; //JTAG Present. When set, indicates that the JTAG debugger interface is present.

        bitField DC2_EPI0{30, 1, RO}; //EPI Module 0 Present. When set, indicates that EPI module 0 is present.
        bitField DC2_I2S0{28, 1, RO}; //I2S Module 0 Present. When set, indicates that I2S module 0 is present.

        bitField DC3_32KHZ{31, 1, RO}; //32KHz Input Clock Available. When set, indicates an even CCP pin is present and can be used as a 32-KHz input clock.

        bitField DC4_EPHY0{30, 1, RO}; //Ethernet PHY Layer 0 Present. When set, indicates that Ethernet PHY layer 0 is present.
        bitField DC4_EMAC0{28, 1, RO}; //Ethernet MAC Layer 0 Present. When set, indicates that Ethernet MAC layer 0 is present.
        bitField DC4_E1588{24, 1, RO}; //588 Capable. When set, indicates that Ethernet MAC layer 0 is 1588 capable.
        bitField DC4_PICAL{18, 1, RO}; //PIOSC Calibrate. When set, indicates that the PIOSC can be calibrated by software.
        bitField DC4_ROM{12, 1, RO}; //Internal Code ROM Present. When set, indicates that internal code ROM is present.

        bitField NVMSTAT_FWB{0, 1, RO}; //32 Word Flash Write Buffer Available. When set, indicates that the 32 word Flash memory write buffer feature is available.

};

#endif //SYSTEM_CONTROL_H
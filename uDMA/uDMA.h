/**
 * @file uDMA.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/17/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019 Matthew Hardenburgh
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
 * μDMA Register Descriptions
 * 
 * The register addresses given are relative to the μDMA base address of 0x400F.F000.
 * 
 */

#ifndef uDMA_H
#define uDMA_H

#include "../systemControl/systemControl.h"

class uDMA : SystemControl
{
    public:
        uDMA();
        ~uDMA();

    private:
        const uint32_t uDMA_Base = 0x400FF000;

/**********************System Control Register Descriptions********************/

        Register PPDMA{(volatile uint32_t*)(systemControlBase + 0x30C)}; //0x30C PPDMA RO 0x0000.0001 Micro Direct Memory Access Peripheral Present 293
        Register SRDMA{(volatile uint32_t*)(systemControlBase + 0x50C)}; //0x50C SRDMA RW 0x0000.0000 Micro Direct Memory Access Software Reset 316
        Register RCGCDMA{(volatile uint32_t*)(systemControlBase + 0x60C)}; //0x60C RCGCDMA RW 0x0000.0000 Micro Direct Memory Access Run Mode Clock Gating Control 342
        Register SCGCDMA{(volatile uint32_t*)(systemControlBase + 0x70C)}; //0x70C SCGCDMA RW 0x0000.0000 Micro Direct Memory Access Sleep Mode Clock Gating Control 364
        Register DCGCDMA{(volatile uint32_t*)(systemControlBase + 0x80C)}; //0x80C DCGCDMA RW 0x0000.0000 Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control 386
        Register PRDMA{(volatile uint32_t*)(systemControlBase + 0xA0C)}; //0xA0C PRDMA RO 0x0000.0000 Micro Direct Memory Access Peripheral Ready 408

/**************************System Control BitFields****************************/

        bitField PPDMA_P0{0, 1, RO}; //μDMA Module Present
        bitField SRDMA_R0{0, 1, RW}; //μDMA Module Software Reset
        bitField RCGCDMA_R0{0, 1, RW}; //μDMA Module Run Mode Clock Gating Control
        bitField SCGCDMA_S0{0, 1, RW}; //μDMA Module Sleep Mode Clock Gating Control
        bitField DCGCDMA_D0{0, 1, RW}; //μDMA Module Deep-Sleep Mode Clock Gating Control
        bitField PRDMA_R0{0, 1, RO}; //μDMA Module Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC4_UDMA{13, 1, RO}; //Micro-DMA Module Present. When set, indicates that the micro-DMA module present.
        bitField SRCR2_UDMA{13, 1, RO}; //Micro-DMA Reset Control
        bitField RCGC2_UDMA{13, 1, RO}; //Micro-DMA Clock Gating Control
        bitField SCGC2_UDMA{13, 1, RO}; //Micro-DMA Clock Gating Control
        bitField DCGC2_UDMA{13, 1, RO}; //Micro-DMA Clock Gating Control

        bitField DC7_DMACH30{30, 1, RO}; //DMA Channel 30. When set, indicates μDMA channel 30 is available.
        bitField DC7_DMACH29{29, 1, RO}; //DMA Channel 29. When set, indicates μDMA channel 29 is available.
        bitField DC7_DMACH28{28, 1, RO}; //DMA Channel 28. When set, indicates μDMA channel 28 is available.
        bitField DC7_DMACH27{27, 1, RO}; //DMA Channel 27. When set, indicates μDMA channel 27 is available.
        bitField DC7_DMACH26{26, 1, RO}; //DMA Channel 26. When set, indicates μDMA channel 26 is available.
        bitField DC7_DMACH25{25, 1, RO}; //DMA Channel 25. When set, indicates μDMA channel 25 is available.
        bitField DC7_DMACH24{24, 1, RO}; //DMA Channel 24. When set, indicates μDMA channel 24 is available.
        bitField DC7_DMACH23{23, 1, RO}; //DMA Channel 23. When set, indicates μDMA channel 23 is available.
        bitField DC7_DMACH22{22, 1, RO}; //DMA Channel 22. When set, indicates μDMA channel 22 is available.
        bitField DC7_DMACH21{21, 1, RO}; //DMA Channel 21. When set, indicates μDMA channel 21 is available.
        bitField DC7_DMACH20{20, 1, RO}; //DMA Channel 20. When set, indicates μDMA channel 20 is available.
        bitField DC7_DMACH19{19, 1, RO}; //DMA Channel 19. When set, indicates μDMA channel 19 is available.
        bitField DC7_DMACH18{18, 1, RO}; //DMA Channel 18. When set, indicates μDMA channel 18 is available.
        bitField DC7_DMACH17{17, 1, RO}; //DMA Channel 17. When set, indicates μDMA channel 17 is available.
        bitField DC7_DMACH16{16, 1, RO}; //DMA Channel 16. When set, indicates μDMA channel 16 is available.
        bitField DC7_DMACH15{15, 1, RO}; //DMA Channel 15. When set, indicates μDMA channel 15 is available.
        bitField DC7_DMACH14{14, 1, RO}; //DMA Channel 14. When set, indicates μDMA channel 14 is available.
        bitField DC7_DMACH13{13, 1, RO}; //DMA Channel 13. When set, indicates μDMA channel 13 is available.
        bitField DC7_DMACH12{12, 1, RO}; //DMA Channel 12. When set, indicates μDMA channel 12 is available.
        bitField DC7_DMACH11{11, 1, RO}; //DMA Channel 11. When set, indicates μDMA channel 11 is available.
        bitField DC7_DMACH10{10, 1, RO}; //DMA Channel 10. When set, indicates μDMA channel 10 is available.
        bitField DC7_DMACH9{9, 1, RO}; //DMA Channel 9. When set, indicates μDMA channel 9 is available.
        bitField DC7_DMACH8{8, 1, RO}; //DMA Channel 8. When set, indicates μDMA channel 8 is available.
        bitField DC7_DMACH7{7, 1, RO}; //DMA Channel 7. When set, indicates μDMA channel 7 is available.
        bitField DC7_DMACH6{6, 1, RO}; //DMA Channel 6. When set, indicates μDMA channel 6 is available.
        bitField DC7_DMACH5{5, 1, RO}; //DMA Channel 5. When set, indicates μDMA channel 5 is available.
        bitField DC7_DMACH4{4, 1, RO}; //DMA Channel 4. When set, indicates μDMA channel 4 is available.
        bitField DC7_DMACH3{3, 1, RO}; //DMA Channel 3. When set, indicates μDMA channel 3 is available.
        bitField DC7_DMACH2{2, 1, RO}; //DMA Channel 2. When set, indicates μDMA channel 2 is available.
        bitField DC7_DMACH1{1, 1, RO}; //DMA Channel 1. When set, indicates μDMA channel 1 is available.
        bitField DC7_DMACH0{0, 1, RO}; //DMA Channel 0. When set, indicates μDMA channel 0 is available.


};


#endif //uDMA_H
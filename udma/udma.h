/**
 * @file udma.h
 * @brief TM4C123GH6PM μDMA Driver Declaration
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
 * @class Dma
 * @brief TM4C123GH6PM μDMA Driver
 * 
 * @section udmaDescription μDMA Description
 * 
 *  The TM4C123GH6PM a Direct Memory Access (DMA) controller, known as μDMA. DMA
 * provides a way to offload memory transfer tasks from the processor. the μDMA
 * controller transfers data between memory and peripherals and has a dedicated
 * channel for each supported peripheral. The μDMA controller can be programmed
 * to automatically transfer data between peripherals and memory as soon as the
 * peripheral is ready to transfer more data. The μDMA controller has the 
 * following features:
 *      - ARM® PrimeCell® 32-channel configurable µDMA controller
 *      - Support for memory-to-memory, memory-to-peripheral, and peripheral-to-
 *        memory in multiple transfer modes
 *          - Basic for simple transfer scenarios
 *          - Ping-pong for continuous data flow
 *          - Scatter-gather for a programmable list of up to 256 arbitrary 
 *            transfers initiated from a single request
 *      - Highly flexible and configurable channel operation
 *          - Independently configured and operated channels
 *          - Dedicated channels for supported on-chip modules
 *          - Flexible channel assignments
 *          - One channel each for receive and transmit path for bidirectional modules
 *          - Dedicated channel for software-initiated transfers
 *          - Per-channel configurable priority scheme
 *          - Optional software-initiated requests for any channel
 *      - Two levels of priority
 *      - Design optimizations for improved bus access performance between µDMA 
 *        controller and the processor core
 *          - µDMA controller access is subordinate to core access
 *          - RAM striping
 *          -  Peripheral bus segmentation
 *      - Data sizes of 8, 16, and 32 bits
 *      - Transfer size is programmable in binary steps from 1 to 1024
 *      - Source and destination address increment size of byte, half-word, word, or no increment
 *      - Maskable peripheral requests
 *      - Interrupt on transfer completion, with a separate interrupt per channel
 * 
 * For more detailed information on the μDMA please see page 585 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection udmaSignalDescription μDMA Signal Description
 * 
 * Each DMA channel can be programmed with up to 5 possible assignments. There
 * are 4 DMA Channel Map Select registers (DMACHMAPn) and each register has 8
 * 4-bit assignment fields, making a total of 32 assignment fields, one field 
 * each for the 32 DMA channels. 
 * 
 * The table below shows the μDMA channel mappings. The \c Enc. column indicates
 * the encoding the should be programmed into the DMACHMAPn bit field to use a 
 * channel with a specified peripheral. Encodings 0x5 to 0xF are reserved and
 * not used. The \c Type column in the table indicates if a peripheral uses 
 * (S)ingle request, (B)urst request, or both (SB). Peripheral encodings that
 * are "Software" may be assigned to peripherals in the future, but are
 * currently available for software use. Channel 30 is dedicated to software 
 * use. USB endpoints mapped to DMA channels 0-3 can be changed using the USB
 * register USBDMASEL
 * 
 * 
 * @image html udmaChannelAssignments.png
 * @image html udmaChannelAssignments2.png
 * @image latex udmaChannelAssignments.png
 * @image latex udmaChannelAssignments2.png
 * 
 */


#ifndef UDMA_H
#define UDMA_H

#include "../systemControl/systemControl.h"

class Dma
{
    public:
        Dma();
        ~Dma();

    private:

        static const uint32_t uDMA_Base = 0x400FF000;

        static const uint32_t PPDMA_OFFSET = 0x30C; //0x30C PPDMA RO 0x0000.0001 Micro Direct Memory Access Peripheral Present 293
        static const uint32_t SRDMA_OFFSET = 0x50C; //0x50C SRDMA RW 0x0000.0000 Micro Direct Memory Access Software Reset 316
        static const uint32_t RCGCDMA_OFFSET = 0x60C; //0x60C RCGCDMA RW 0x0000.0000 Micro Direct Memory Access Run Mode Clock Gating Control 342
        static const uint32_t SCGCDMA_OFFSET = 0x70C; //0x70C SCGCDMA RW 0x0000.0000 Micro Direct Memory Access Sleep Mode Clock Gating Control 364
        static const uint32_t DCGCDMA_OFFSET = 0x80C; //0x80C DCGCDMA RW 0x0000.0000 Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control 386
        static const uint32_t PRDMA_OFFSET = 0xA0C; //0xA0C PRDMA RO 0x0000.0000 Micro Direct Memory Access Peripheral Ready 408

        /*
         * μDMA Channel Control Structure (Offset from Channel Control Table Base)
         */

        static const uint32_t DMASRCENDP_OFFSET = 0x000; // 0x000 DMASRCENDP RW - DMA Channel Source Address End Pointer 609
        static const uint32_t DMADSTENDP_OFFSET = 0x004; // 0x004 DMADSTENDP RW - DMA Channel Destination Address End Pointer 610
        static const uint32_t DMACHCTL_OFFSET = 0x008; // 0x008 DMACHCTL RW - DMA Channel Control Word 611


        /*
         * μDMA Registers (Offset from μDMA Base Address)
         */

        static const uint32_t DMASTAT_OFFSET = 0x000; // 0x000 DMASTAT RO 0x001F.0000 DMA Status 616
        static const uint32_t DMACFG_OFFSET = 0x004; // 0x004 DMACFG WO - DMA Configuration 618
        static const uint32_t DMACTLBASE_OFFSET = 0x008; // 0x008 DMACTLBASE RW 0x0000.0000 DMA Channel Control Base Pointer 619
        static const uint32_t DMAALTBASE_OFFSET = 0x00C; // 0x00C DMAALTBASE RO 0x0000.0200 DMA Alternate Channel Control Base Pointer 620
        static const uint32_t DMAWAITSTAT_OFFSET = 0x010; // 0x010 DMAWAITSTAT RO 0x03C3.CF00 DMA Channel Wait-on-Request Status 621
        static const uint32_t DMASWREQ_OFFSET = 0x014; // 0x014 DMASWREQ WO - DMA Channel Software Request 622
        static const uint32_t DMAUSEBURSTSET_OFFSET = 0x018; // 0x018 DMAUSEBURSTSET RW 0x0000.0000 DMA Channel Useburst Set 623
        static const uint32_t DMAUSEBURSTCLR_OFFSET = 0x01C; // 0x01C DMAUSEBURSTCLR WO - DMA Channel Useburst Clear 624
        static const uint32_t DMAREQMASKSET_OFFSET = 0x020; // 0x020 DMAREQMASKSET RW 0x0000.0000 DMA Channel Request Mask Set 625
        static const uint32_t DMAREQMASKCLR_OFFSET = 0x024; // 0x024 DMAREQMASKCLR WO - DMA Channel Request Mask Clear 626
        static const uint32_t DMAENASET_OFFSET = 0x028; // 0x028 DMAENASET RW 0x0000.0000 DMA Channel Enable Set 627
        static const uint32_t DMAENACLR_OFFSET = 0x02C; // 0x02C DMAENACLR WO - DMA Channel Enable Clear 628
        static const uint32_t DMAALTSET_OFFSET = 0x030; // 0x030 DMAALTSET RW 0x0000.0000 DMA Channel Primary Alternate Set 629
        static const uint32_t DMAALTCLR_OFFSET = 0x034; // 0x034 DMAALTCLR WO - DMA Channel Primary Alternate Clear 630
        static const uint32_t DMAPRIOSET_OFFSET = 0x038; // 0x038 DMAPRIOSET RW 0x0000.0000 DMA Channel Priority Set 631
        static const uint32_t DMAPRIOCLR_OFFSET = 0x03C; // 0x03C DMAPRIOCLR WO - DMA Channel Priority Clear 632
        static const uint32_t DMAERRCLR_OFFSET = 0x04C; // 0x04C DMAERRCLR RW 0x0000.0000 DMA Bus Error Clear 633
        static const uint32_t DMACHASGN_OFFSET = 0x500; // 0x500 DMACHASGN RW 0x0000.0000 DMA Channel Assignment 634
        static const uint32_t DMACHIS_OFFSET = 0x504; // 0x504 DMACHIS RW1C 0x0000.0000 DMA Channel Interrupt Status 635
        static const uint32_t DMACHMAP0_OFFSET = 0x510; // 0x510 DMACHMAP0 RW 0x0000.0000 DMA Channel Map Select 0 636
        static const uint32_t DMACHMAP1_OFFSET = 0x514; // 0x514 DMACHMAP1 RW 0x0000.0000 DMA Channel Map Select 1 637
        static const uint32_t DMACHMAP2_OFFSET = 0x518; // 0x518 DMACHMAP2 RW 0x0000.0000 DMA Channel Map Select 2 638
        static const uint32_t DMACHMAP3_OFFSET = 0x51C; // 0x51C DMACHMAP3 RW 0x0000.0000 DMA Channel Map Select 3 639
        static const uint32_t DMAPeriphID4_OFFSET = 0xFD0; // 0xFD0 DMAPeriphID4 RO 0x0000.0004 DMA Peripheral Identification 4 644
        static const uint32_t DMAPeriphID0_OFFSET = 0xFE0; // 0xFE0 DMAPeriphID0 RO 0x0000.0030 DMA Peripheral Identification 0 640
        static const uint32_t DMAPeriphID1_OFFSET = 0xFE4; // 0xFE4 DMAPeriphID1 RO 0x0000.00B2 DMA Peripheral Identification 1 641
        static const uint32_t DMAPeriphID2_OFFSET = 0xFE8; // 0xFE8 DMAPeriphID2 RO 0x0000.000B DMA Peripheral Identification 2 642
        static const uint32_t DMAPeriphID3_OFFSET = 0xFEC; // 0xFEC DMAPeriphID3 RO 0x0000.0000 DMA Peripheral Identification 3 643
        static const uint32_t DMAPCellID0_OFFSET = 0xFF0; // 0xFF0 DMAPCellID0 RO 0x0000.000D DMA PrimeCell Identification 0 645
        static const uint32_t DMAPCellID1_OFFSET = 0xFF4; // 0xFF4 DMAPCellID1 RO 0x0000.00F0 DMA PrimeCell Identification 1 646
        static const uint32_t DMAPCellID2_OFFSET = 0xFF8; // 0xFF8 DMAPCellID2 RO 0x0000.0005 DMA PrimeCell Identification 2 647
        static const uint32_t DMAPCellID3_OFFSET = 0xFFC; // 0xFFC DMAPCellID3 RO 0x0000.00B1 DMA PrimeCell Identification 3 648

};


#endif //UDMA_H
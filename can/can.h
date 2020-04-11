
/**
 * @file can.h
 * @brief TM4C123GH6PM CAN Driver Declaration
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
 * @class Can
 * @brief TM4C123GH6PM CAN Driver
 * 
 * @section canDescription CAN Description
 * 
 * The TM4C123GH6PM microcontroller CAN module provides two independently 
 * operating CAN units. Designed specifically to operate in EM noisy enviroments
 * CAN is perfect for industrial purposes. The two CAN units in the TM4C123GH6PM
 * microcontroller has the following features:
 *      - CAN protocol version 2.0 part A/B
 *      - Bit rates up to 1 Mbps for network lengths less than 40 meters
 *          - Decreased bit rates allow longer network distances (for example, 
 *            125 Kbps at 500 meters)
 *      - 32 message objects with individual identifier masks
 *      - Maskable interrupt
 *      - Disable Automatic Retransmission mode for Time-Triggered CAN (TTCAN) 
 *        applications
 *      - Programmable loopback mode for self-test operation
 *      - Programmable FIFO mode enables storage of multiple message objects
 *      - Gluelessly attaches to an external CAN transceiver through the 
 *        \c CANnTX and \c CANnRX signals
 * 
 * For more detailed information on the CAN please see page 1048 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection canSignalDescription CAN Signal Description
 * 
 * The following table lists the GPIO pin mux and physical pin number of the
 * pins that can be muxed for use by the CAN. To use a pin for operation by the 
 * CAN, the \c AFSEL bit in the GPIO Alternate Function Select (GPIOAFSEL) 
 * register should be set to choose the CAN controller function. The number in 
 * parentheses is the encoding that must be programmed into the \c PMCn field in 
 * the GPIO Port Control (GPIOPCTL) register to assign the CAN signal to the 
 * specified GPIO port pin. 
 * 
 * @image html canSignals.png
 * @image latex canSignals.png
 * 
 * @subsection canSystemControlRegisterDescription CAN System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Legacy registers not supported.
 * 
 * @subsection canRegisterDescription CAN Register Description
 * 
 * The Can class contains a list of CAN registers listed as an offset relative
 * to the hexadecimal base address of the CAN module block, CAN0 or CAN1. Note 
 * that the CAN controller clock must be enabled before the registers can be 
 * programmed. There must be a delay of 3 system clocks after the CAN module 
 * clock is enabled before any CAN module registers are accessed.
 * 
 */

#ifndef CAN_H
#define CAN_H

#include "../systemControl/systemControl.h"

class Can
{
    public:
        Can();
        ~Can();

    private:

        static const uint32_t can0BaseAddress = 0x40040000;
        static const uint32_t can1BaseAddress = 0x40041000;

        static const uint32_t PPCAN_OFFSET = 0x334; //0x334 PPCAN RO 0x0000.0003 Controller Area Network Peripheral Present 302
        static const uint32_t SRCAN_OFFSET = 0x534; //0x534 SRCAN RW 0x0000.0000 Controller Area Network Software Reset 325
        static const uint32_t RCGCCAN_OFFSET = 0x634; //0x634 RCGCCAN RW 0x0000.0000 Controller Area Network Run Mode Clock Gating Control 351
        static const uint32_t SCGCCAN_OFFSET = 0x734; //0x734 SCGCCAN RW 0x0000.0000 Controller Area Network Sleep Mode Clock Gating Control 373
        static const uint32_t DCGCCAN_OFFSET = 0x834; //0x834 DCGCCAN RW 0x0000.0000 Controller Area Network Deep-Sleep Mode Clock Gating Control 395
        static const uint32_t PRCAN_OFFSET = 0xA34; //0xA34 PRCAN RO 0x0000.0000 Controller Area Network Peripheral Ready 417

        static const uint32_t CANCTL_OFFSET = 0x000; // 0x000 CANCTL RW 0x0000.0001 CAN Control 1070
        static const uint32_t CANSTS_OFFSET = 0x004; // 0x004 CANSTS RW 0x0000.0000 CAN Status 1072
        static const uint32_t CANERR_OFFSET = 0x008; // 0x008 CANERR RO 0x0000.0000 CAN Error Counter 1075
        static const uint32_t CANBIT_OFFSET = 0x00C; // 0x00C CANBIT RW 0x0000.2301 CAN Bit Timing 1076
        static const uint32_t CANINT_OFFSET = 0x010; // 0x010 CANINT RO 0x0000.0000 CAN Interrupt 1077
        static const uint32_t CANTST_OFFSET = 0x014; // 0x014 CANTST RW 0x0000.0000 CAN Test 1078
        static const uint32_t CANBRPE_OFFSET = 0x018; // 0x018 CANBRPE RW 0x0000.0000 CAN Baud Rate Prescaler Extension 1080
        static const uint32_t CANIF1CRQ_OFFSET = 0x020; // 0x020 CANIF1CRQ RW 0x0000.0001 CAN IF1 Command Request 1081
        static const uint32_t CANIF1MSK1_OFFSET = 0x028; // 0x028 CANIF1MSK1 RW 0x0000.FFFF CAN IF1 Mask 1 1085
        static const uint32_t CANIF1MSK2_OFFSET = 0x02C; // 0x02C CANIF1MSK2 RW 0x0000.FFFF CAN IF1 Mask 2 1086
        static const uint32_t CANIF1ARB1_OFFSET = 0x030; // 0x030 CANIF1ARB1 RW 0x0000.0000 CAN IF1 Arbitration 1 1088
        static const uint32_t CANIF1ARB2_OFFSET = 0x034; // 0x034 CANIF1ARB2 RW 0x0000.0000 CAN IF1 Arbitration 2 1089
        static const uint32_t CANIF1MCTL_OFFSET = 0x038; // 0x038 CANIF1MCTL RW 0x0000.0000 CAN IF1 Message Control 1091
        static const uint32_t CANIF1DA1_OFFSET = 0x03C; // 0x03C CANIF1DA1 RW 0x0000.0000 CAN IF1 Data A1 1094
        static const uint32_t CANIF1DA2_OFFSET = 0x040; // 0x040 CANIF1DA2 RW 0x0000.0000 CAN IF1 Data A2 1094
        static const uint32_t CANIF1DB1_OFFSET = 0x044; // 0x044 CANIF1DB1 RW 0x0000.0000 CAN IF1 Data B1 1094
        static const uint32_t CANIF1DB2_OFFSET = 0x048; // 0x048 CANIF1DB2 RW 0x0000.0000 CAN IF1 Data B2 1094
        static const uint32_t CANIF2CRQ_OFFSET = 0x080; // 0x080 CANIF2CRQ RW 0x0000.0001 CAN IF2 Command Request 1081
        static const uint32_t CANIF2CMSK_OFFSET = 0x084; // 0x084 CANIF2CMSK RW 0x0000.0000 CAN IF2 Command Mask 1082
        static const uint32_t CANIF2MSK1_OFFSET = 0x088; // 0x088 CANIF2MSK1 RW 0x0000.FFFF CAN IF2 Mask 1 1085
        static const uint32_t CANIF2MSK2_OFFSET = 0x08C; // 0x08C CANIF2MSK2 RW 0x0000.FFFF CAN IF2 Mask 2 1086
        static const uint32_t CANIF2ARB1_OFFSET = 0x090; // 0x090 CANIF2ARB1 RW 0x0000.0000 CAN IF2 Arbitration 1 1088
        static const uint32_t CANIF2ARB2_OFFSET = 0x094; // 0x094 CANIF2ARB2 RW 0x0000.0000 CAN IF2 Arbitration 2 1089
        static const uint32_t CANIF2MCTL_OFFSET = 0x098; // 0x098 CANIF2MCTL RW 0x0000.0000 CAN IF2 Message Control 1091
        static const uint32_t CANIF2DA1_OFFSET = 0x09C; // 0x09C CANIF2DA1 RW 0x0000.0000 CAN IF2 Data A1 1094
        static const uint32_t CANIF2DA2_OFFSET = 0x0A0; // 0x0A0 CANIF2DA2 RW 0x0000.0000 CAN IF2 Data A2 1094
        static const uint32_t CANIF2DB1_OFFSET = 0x0A4; // 0x0A4 CANIF2DB1 RW 0x0000.0000 CAN IF2 Data B1 1094
        static const uint32_t CANIF2DB2_OFFSET = 0x0A8; // 0x0A8 CANIF2DB2 RW 0x0000.0000 CAN IF2 Data B2 1094
        static const uint32_t CANTXRQ1_OFFSET = 0x100; // 0x100 CANTXRQ1 RO 0x0000.0000 CAN Transmission Request 1 1095
        static const uint32_t CANTXRQ2_OFFSET = 0x104; // 0x104 CANTXRQ2 RO 0x0000.0000 CAN Transmission Request 2 1095
        static const uint32_t CANNWDA1_OFFSET = 0x120; // 0x120 CANNWDA1 RO 0x0000.0000 CAN New Data 1 1096
        static const uint32_t CANNWDA2_OFFSET = 0x124; // 0x124 CANNWDA2 RO 0x0000.0000 CAN New Data 2 1096
        static const uint32_t CANMSG1INT_OFFSET = 0x140; // 0x140 CANMSG1INT RO 0x0000.0000 CAN Message 1 Interrupt Pending 1097
        static const uint32_t CANMSG2INT_OFFSET = 0x144; // 0x144 CANMSG2INT RO 0x0000.0000 CAN Message 2 Interrupt Pending 1097
        static const uint32_t CANMSG1VAL_OFFSET = 0x160; // 0x160 CANMSG1VAL RO 0x0000.0000 CAN Message 1 Valid 1098
        static const uint32_t CANMSG2VAL_OFFSET = 0x164; // 0x164 CANMSG2VAL RO 0x0000.0000 CAN Message 2 Valid 1098


};

#endif
/**
 * @file nvic.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 11/07/2019
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
 * Class header for the nested vector interrupt controller for the Texas 
 * Instruments Tiva C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * This section lists and describes the NVIC registers, in numerical order by address offset.
 * 
 * The NVIC registers can only be fully accessed from privileged mode, but 
 * interrupts can be pended while in unprivileged mode by enabling the 
 * Configuration and Control (CFGCTRL) register. Any other unprivileged mode 
 * access causes a bus fault.
 * 
 * Ensure software uses correctly aligned register accesses. The processor does 
 * not support unaligned accesses to NVIC registers.
 * 
 * An interrupt can enter the pending state even if it is disabled.
 * 
 * Before programming the VTABLE register to relocate the vector table, ensure 
 * the vector table entries of the new vector table are set up for fault 
 * handlers, NMI, and all enabled exceptions such as interrupts. For more 
 * information, see page 163.
 * 
 */

#ifndef NVIC_H
#define NVIC_H

// #include <stdint-gcc.h>
// #include <stddef.h>
#include "../../register/register.h"

enum interrupt
{
    GPIO_Port_A_Interrupt = 0u,
    GPIO_Port_B_Interrupt = 1u,
    GPIO_Port_C_Interrupt = 2u,
    GPIO_Port_D_Interrupt = 3u,
    GPIO_Port_E_Interrupt = 4u,
    UART_0_Interrupt = 5u,
    UART_1_Interrupt = 6u,
    SSI_0_Interrupt = 7u,
    I2C_0_Interrupt = 8u,
    PWM_0_Fault_Interrupt = 9u,
    PWM_0_Generator_0_Interrupt = 10u,
    PWM_0_Generator_1_Interrupt = 11u,
    PWM_0_Generator_2_Interrupt = 12u,
    QEI_0_Interrupt = 13u,
    ADC_0_Sequence_0_Interrupt = 14u,
    ADC_0_Sequence_1_Interrupt = 15u,
    ADC_0_Sequence_2_Interrupt = 16u,
    ADC_0_Sequence_3_Interrupt = 17u,
    Watchdog_0_and_1_Interrupt = 18u,
    _16_32_Bit_Timer_0A_Interrupt = 19u,
    _16_32_Bit_Timer_0B_Interrupt = 20u,
    _16_32_Bit_Timer_1A_Interrupt = 21u,
    _16_32_Bit_Timer_1B_Interrupt = 22u,
    _16_32_Bit_Timer_2A_Interrupt = 23u,
    _16_32_Bit_Timer_2B_Interrupt = 24u,
    Analog_Comparator_0_Interrupt = 25u,
    Analog_Comparator_1_Interrupt = 26u,
    System_Control_Interrupt = 28u,
    Flash_and_EEPROM_Control_Interrupt = 29u,
    GPIO_Port_F_Interrupt = 30u,
    UART_2_Interrupt = 33u,
    SSI_1_Interrupt = 34u,
    _16_32_Bit_Timer_3A_Interrupt = 35u,
    _16_32_Bit_Timer_3B_Interrupt = 36u,
    I2C_1_Interrupt = 37u,
    QEI_1_Interrupt = 38u,
    CAN_0_Interrupt = 39u,
    CAN_1_Interrupt = 40u,
    Hibernation_Module_Interrupt = 43u,
    USB_Interrupt = 44u,
    PWM_Generator_3_Interrupt = 45u,
    uDMA_Software_Interrupt = 46u,
    uDMA_Error_Interrupt = 47u,
    ADC_1_Sequence_0_Interrupt = 48u,
    ADC_1_Sequence_1_Interrupt = 49u,
    ADC_1_Sequence_2_Interrupt = 50u,
    ADC_1_Sequence_3_Interrupt = 51u,
    SSI_2_Interrupt = 57u,
    SSI_3_Interrupt = 58u,
    UART_3_Interrupt = 59u,
    UART_4_Interrupt = 60u,
    UART_5_Interrupt = 61u,
    UART_6_Interrupt = 62u,
    UART_7_Interrupt = 63u,
    I2C_2_Interrupt = 68u,
    I2C_3_Interrupt = 69u,
    _16_32_Bit_Timer_4A_Interrupt = 70u,
    _16_32_Bit_Timer_4B_Interrupt = 71u,
    _16_32_Bit_Timer_5A_Interrupt = 92u,
    _16_32_Bit_Timer_5B_Interrupt = 93u,
    _32_64_Bit_Timer_0A_Interrupt = 94u,
    _32_64_Bit_Timer_0B_Interrupt = 95u,
    _32_64_Bit_Timer_1A_Interrupt = 96u,
    _32_64_Bit_Timer_1B_Interrupt = 97u,
    _32_64_Bit_Timer_2A_Interrupt = 98u,
    _32_64_Bit_Timer_2B_Interrupt = 99u,
    _32_64_Bit_Timer_3A_Interrupt = 100u,
    _32_64_Bit_Timer_3B_Interrupt = 101u,
    _32_64_Bit_Timer_4A_Interrupt = 102u,
    _32_64_Bit_Timer_4B_Interrupt = 103u,
    _32_64_Bit_Timer_5A_Interrupt = 104u,
    _32_64_Bit_Timer_5B_Interrupt = 105u,
    System_Exception_Interrupt = 106u,
    PWM_1_Generator_0_Interrupt = 134u,
    PWM_1_Generator_1_Interrupt = 135u,
    PWM_1_Generator_2_Interrupt = 136u,
    PWM_1_Generator_3_Interrupt = 137u,
    PWM_1_Fault_Interrupt = 138u
};

class Nvic
{
    public:   
        
        Nvic();
        ~Nvic();
        static void activateInterrupt(interrupt myInterrupt, uint32_t priority);
        static uint32_t disableInterrupts(void);
        static uint32_t enableInterrupts(void);
        static void wfi(void);

    private:
        static const uint32_t nvicRegisterOffset = 0x4;
        
        static const uint32_t EN0_OFFSET = 0x100; // 0x100 EN0 RW 0x0000.0000 Interrupt 0-31 Set Enable 142
        static const uint32_t EN1_OFFSET = 0x104; // 0x104 EN1 RW 0x0000.0000 Interrupt 32-63 Set Enable 142
        static const uint32_t EN2_OFFSET = 0x108; // 0x108 EN2 RW 0x0000.0000 Interrupt 64-95 Set Enable 142
        static const uint32_t EN3_OFFSET = 0x10C; // 0x10C EN3 RW 0x0000.0000 Interrupt 96-127 Set Enable 142
        static const uint32_t EN4_OFFSET = 0x110; // 0x110 EN4 RW 0x0000.0000 Interrupt 128-138 Set Enable 143
        static const uint32_t ENn_OFFSET[5];

        static const uint32_t DIS0_OFFSET = 0x180; // 0x180 DIS0 RW 0x0000.0000 Interrupt 0-31 Clear Enable 144
        static const uint32_t DIS1_OFFSET = 0x184; // 0x184 DIS1 RW 0x0000.0000 Interrupt 32-63 Clear Enable 144
        static const uint32_t DIS2_OFFSET = 0x188; // 0x188 DIS2 RW 0x0000.0000 Interrupt 64-95 Clear Enable 144
        static const uint32_t DIS3_OFFSET = 0x18C; // 0x18C DIS3 RW 0x0000.0000 Interrupt 96-127 Clear Enable 144
        static const uint32_t DIS4_OFFSET = 0x190; // 0x190 DIS4 RW 0x0000.0000 Interrupt 128-138 Clear Enable 145
        static const uint32_t DISn_OFFSET[5];

        static const uint32_t PEND0_OFFSET = 0x200; // 0x200 PEND0 RW 0x0000.0000 Interrupt 0-31 Set Pending 146
        static const uint32_t PEND1_OFFSET = 0x204; // 0x204 PEND1 RW 0x0000.0000 Interrupt 32-63 Set Pending 146
        static const uint32_t PEND2_OFFSET = 0x208; // 0x208 PEND2 RW 0x0000.0000 Interrupt 64-95 Set Pending 146
        static const uint32_t PEND3_OFFSET = 0x20C; // 0x20C PEND3 RW 0x0000.0000 Interrupt 96-127 Set Pending 146
        static const uint32_t PEND4_OFFSET = 0x210; // 0x210 PEND4 RW 0x0000.0000 Interrupt 128-138 Set Pending 147
        static const uint32_t PENDn_OFFSET[5];

        static const uint32_t UNPEND0_OFFSET = 0x280; // 0x280 UNPEND0 RW 0x0000.0000 Interrupt 0-31 Clear Pending 148
        static const uint32_t UNPEND1_OFFSET = 0x284; // 0x284 UNPEND1 RW 0x0000.0000 Interrupt 32-63 Clear Pending 148
        static const uint32_t UNPEND2_OFFSET = 0x288; // 0x288 UNPEND2 RW 0x0000.0000 Interrupt 64-95 Clear Pending 148
        static const uint32_t UNPEND3_OFFSET = 0x28C; // 0x28C UNPEND3 RW 0x0000.0000 Interrupt 96-127 Clear Pending 148
        static const uint32_t UNPEND4_OFFSET = 0x290; // 0x290 UNPEND4 RW 0x0000.0000 Interrupt 128-138 Clear Pending 149
        static const uint32_t UNPENDn_OFFSET[5];

        /** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * CAUTION – DO NOT manually set or clear the bits in the ACTIVE 
         * register or you will have a VERY bad day.
         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         */ 
        static const uint32_t ACTIVE0_OFFSET = 0x300; // 0x300 ACTIVE0 RO 0x0000.0000 Interrupt 0-31 Active Bit 150
        static const uint32_t ACTIVE1_OFFSET = 0x304; // 0x304 ACTIVE1 RO 0x0000.0000 Interrupt 32-63 Active Bit 150
        static const uint32_t ACTIVE2_OFFSET = 0x308; // 0x308 ACTIVE2 RO 0x0000.0000 Interrupt 64-95 Active Bit 150
        static const uint32_t ACTIVE3_OFFSET = 0x30C; // 0x30C ACTIVE3 RO 0x0000.0000 Interrupt 96-127 Active Bit 150
        static const uint32_t ACTIVE4_OFFSET = 0x310; // 0x310 ACTIVE4 RO 0x0000.0000 Interrupt 128-138 Active Bit 151
        static const uint32_t ACTIVEn_OFFSET[5];

        static const uint32_t PRI0_OFFSET = 0x400; // 0x400 PRI0 RW 0x0000.0000 Interrupt 0-3 Priority 152
        static const uint32_t PRI1_OFFSET = 0x404; // 0x404 PRI1 RW 0x0000.0000 Interrupt 4-7 Priority 152
        static const uint32_t PRI2_OFFSET = 0x408; // 0x408 PRI2 RW 0x0000.0000 Interrupt 8-11 Priority 152
        static const uint32_t PRI3_OFFSET = 0x40C; // 0x40C PRI3 RW 0x0000.0000 Interrupt 12-15 Priority 152
        static const uint32_t PRI4_OFFSET = 0x40C; // 0x410 PRI4 RW 0x0000.0000 Interrupt 16-19 Priority 152
        static const uint32_t PRI5_OFFSET = 0x414; // 0x414 PRI5 RW 0x0000.0000 Interrupt 20-23 Priority 152
        static const uint32_t PRI6_OFFSET = 0x418; // 0x418 PRI6 RW 0x0000.0000 Interrupt 24-27 Priority 152
        static const uint32_t PRI7_OFFSET = 0x41C; // 0x41C PRI7 RW 0x0000.0000 Interrupt 28-31 Priority 152
        static const uint32_t PRI8_OFFSET = 0x420; // 0x420 PRI8 RW 0x0000.0000 Interrupt 32-35 Priority 152
        static const uint32_t PRI9_OFFSET = 0x424; // 0x424 PRI9 RW 0x0000.0000 Interrupt 36-39 Priority 152
        static const uint32_t PRI10_OFFSET = 0x428; // 0x428 PRI10 RW 0x0000.0000 Interrupt 40-43 Priority 152
        static const uint32_t PRI11_OFFSET = 0x42C; // 0x42C PRI11 RW 0x0000.0000 Interrupt 44-47 Priority 152
        static const uint32_t PRI12_OFFSET = 0x430; // 0x430 PRI12 RW 0x0000.0000 Interrupt 48-51 Priority 152
        static const uint32_t PRI13_OFFSET = 0x434; // 0x434 PRI13 RW 0x0000.0000 Interrupt 52-55 Priority 152
        static const uint32_t PRI14_OFFSET = 0x438; // 0x438 PRI14 RW 0x0000.0000 Interrupt 56-59 Priority 152
        static const uint32_t PRI15_OFFSET = 0x43C; // 0x43C PRI15 RW 0x0000.0000 Interrupt 60-63 Priority 152
        static const uint32_t PRI16_OFFSET = 0x440; // 0x440 PRI16 RW 0x0000.0000 Interrupt 64-67 Priority 154
        static const uint32_t PRI17_OFFSET = 0x444; // 0x444 PRI17 RW 0x0000.0000 Interrupt 68-71 Priority 154
        static const uint32_t PRI18_OFFSET = 0x448; // 0x448 PRI18 RW 0x0000.0000 Interrupt 72-75 Priority 154
        static const uint32_t PRI19_OFFSET = 0x44C; // 0x44C PRI19 RW 0x0000.0000 Interrupt 76-79 Priority 154
        static const uint32_t PRI20_OFFSET = 0x450; // 0x450 PRI20 RW 0x0000.0000 Interrupt 80-83 Priority 154
        static const uint32_t PRI21_OFFSET = 0x454; // 0x454 PRI21 RW 0x0000.0000 Interrupt 84-87 Priority 154
        static const uint32_t PRI22_OFFSET = 0x458; // 0x458 PRI22 RW 0x0000.0000 Interrupt 88-91 Priority 154
        static const uint32_t PRI23_OFFSET = 0x45C; // 0x45C PRI23 RW 0x0000.0000 Interrupt 92-95 Priority 154
        static const uint32_t PRI24_OFFSET = 0x460; // 0x460 PRI24 RW 0x0000.0000 Interrupt 96-99 Priority 154
        static const uint32_t PRI25_OFFSET = 0x464; // 0x464 PRI25 RW 0x0000.0000 Interrupt 100-103 Priority 154
        static const uint32_t PRI26_OFFSET = 0x468; // 0x468 PRI26 RW 0x0000.0000 Interrupt 104-107 Priority 154
        static const uint32_t PRI27_OFFSET = 0x46C; // 0x46C PRI27 RW 0x0000.0000 Interrupt 108-111 Priority 154
        static const uint32_t PRI28_OFFSET = 0x470; // 0x470 PRI28 RW 0x0000.0000 Interrupt 112-115 Priority 154
        static const uint32_t PRI29_OFFSET = 0x474; // 0x474 PRI29 RW 0x0000.0000 Interrupt 116-119 Priority 154
        static const uint32_t PRI30_OFFSET = 0x478; // 0x478 PRI30 RW 0x0000.0000 Interrupt 120-123 Priority 154
        static const uint32_t PRI31_OFFSET = 0x47C; // 0x47C PRI31 RW 0x0000.0000 Interrupt 124-127 Priority 154
        static const uint32_t PRI32_OFFSET = 0x480; // 0x480 PRI32 RW 0x0000.0000 Interrupt 128-131 Priority 154
        static const uint32_t PRI33_OFFSET = 0x484; // 0x484 PRI33 RW 0x0000.0000 Interrupt 132-135 Priority 154
        static const uint32_t PRI34_OFFSET = 0x488; // 0x488 PRI34 RW 0x0000.0000 Interrupt 136-138 Priority 154
        static const uint32_t PRIn_OFFSET[35];

        static const uint32_t SWTRIG_OFFSET = 0xF00; // 0xF00 SWTRIG WO 0x0000.0000 Software Trigger Interrupt 156


        /**
         * bitField INT{0, 1, RW}; //bit place isn't being used. Renaming 1 to INT.bitWidth to eliminate magic numbers
         * 
         * bitField PRIORITY_INT{5, 3, RW}; //bit place isn't being used. Renaming 3 to INT_PRIORITY.size to eliminate magic numbers
         * 
         * 
         * Description: Interrupt ID
         * 
         * This field holds the interrupt ID of the required SGI. For example, 
         * a value of 0x3 generates an interrupt on IRQ3.
         * 
         * bitField INTID{0, 8, WO}; //bit place and field size
         */

};
#endif //NVIC
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
        uint32_t disableInterrupts(void);
        uint32_t enableInterrupts(void);
        void wfi(void);
        void activateInterrupt(interrupt myInterrupt, uint32_t priority);

    protected:

    private:
        const uint32_t corePeripheralBase = 0xE000E000;
        const uint32_t nvicRegisterOffset = 0x4;


        /**
         * Interrupt enable registers
         * 
         * Register 4: Interrupt 0-31 Set Enable (EN0), offset 0x100 P.142 
         * Register 5: Interrupt 32-63 Set Enable (EN1), offset 0x104 P.142
         * Register 6: Interrupt 64-95 Set Enable (EN2), offset 0x108 P.142
         * Register 7: Interrupt 96-127 Set Enable (EN3), offset 0x10C P.142
         * Register 8: Interrupt 128-138 Set Enable (EN4), offset 0x110 P.143
         */
        const uint32_t EN_OFFSET = 0x100;

        /**
         * Interrupt clear enable (disable) registers
         * 
         * Register 9: Interrupt 0-31 Clear Enable (DIS0), offset 0x180 P.144
         * Register 10: Interrupt 32-63 Clear Enable (DIS1), offset 0x184 P.144
         * Register 11: Interrupt 64-95 Clear Enable (DIS2), offset 0x188 P.144
         * Register 12: Interrupt 96-127 Clear Enable (DIS3), offset 0x18C P.144
         * Register 13: Interrupt 128-138 Clear Enable (DIS4), offset 0x190 P.145
         */
        const uint32_t DIS_OFFSET = 0x180;

        /**
         * Set interrupt pending registers
         * 
         * Register 14: Interrupt 0-31 Set Pending (PEND0), offset 0x200 P.146
         * Register 15: Interrupt 32-63 Set Pending (PEND1), offset 0x204 P.146
         * Register 16: Interrupt 64-95 Set Pending (PEND2), offset 0x208 P.146
         * Register 17: Interrupt 96-127 Set Pending (PEND3), offset 0x20C P.146
         * Register 18: Interrupt 128-138 Set Pending (PEND4), offset 0x210 P.147
         */
        const uint32_t PEND_OFFSET = 0x200;

        /**
         * Clear pending interrupt register
         * 
         * Register 19: Interrupt 0-31 Clear Pending (UNPEND0), offset 0x280 P.148
         * Register 20: Interrupt 32-63 Clear Pending (UNPEND1), offset 0x284 P.148
         * Register 21: Interrupt 64-95 Clear Pending (UNPEND2), offset 0x288 P.148
         * Register 22: Interrupt 96-127 Clear Pending (UNPEND3), offset 0x28C P.148
         * Register 23: Interrupt 128-138 Clear Pending (UNPEND4), offset 0x290 P.149
         */
        const uint32_t UNPEND_OFFSET = 0x280;

        /**
         * The interrupt is active or active and pending registers
         * 
         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * CAUTION – DO NOT manually set or clear the bits in the ACTIVE register or you
         * will have a VERY bad day.
         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * 
         * Register 24: Interrupt 0-31 Active Bit (ACTIVE0), offset 0x300 P.150
         * Register 25: Interrupt 32-63 Active Bit (ACTIVE1), offset 0x304 P.150
         * Register 26: Interrupt 64-95 Active Bit (ACTIVE2), offset 0x308 P.15
         * Register 27: Interrupt 96-127 Active Bit (ACTIVE3), offset 0x30C P.150
         * Register 28: Interrupt 128-138 Active Bit (ACTIVE4), offset 0x310 P.151
         */
        const uint32_t ACTIVE_OFFSET = 0x300;

        /**
         * Sets the priority of the interrupt. 0 Is highest priority, 7 is lowest priority.
         * 
         * Register 29: Interrupt 0-3 Priority (PRI0), offset 0x400 P.152
         * Register 30: Interrupt 4-7 Priority (PRI1), offset 0x404 P.152
         * Register 31: Interrupt 8-11 Priority (PRI2), offset 0x408 P.152
         * Register 32: Interrupt 12-15 Priority (PRI3), offset 0x40C P.152
         * Register 33: Interrupt 16-19 Priority (PRI4), offset 0x410 P.152
         * Register 34: Interrupt 20-23 Priority (PRI5), offset 0x414 P.152
         * Register 35: Interrupt 24-27 Priority (PRI6), offset 0x418 P.152
         * Register 36: Interrupt 28-31 Priority (PRI7), offset 0x41C P.152
         * Register 37: Interrupt 32-35 Priority (PRI8), offset 0x420 P.152
         * Register 38: Interrupt 36-39 Priority (PRI9), offset 0x424 P.152
         * Register 39: Interrupt 40-43 Priority (PRI10), offset 0x428 P.152
         * Register 40: Interrupt 44-47 Priority (PRI11), offset 0x42C P.152
         * Register 41: Interrupt 48-51 Priority (PRI12), offset 0x430 P.152
         * Register 42: Interrupt 52-55 Priority (PRI13), offset 0x434 P.152
         * Register 43: Interrupt 56-59 Priority (PRI14), offset 0x438 P.152
         * Register 44: Interrupt 60-63 Priority (PRI15), offset 0x43C P.152
         * Register 45: Interrupt 64-67 Priority (PRI16), offset 0x440 P.154
         * Register 46: Interrupt 68-71 Priority (PRI17), offset 0x444 P.154
         * Register 47: Interrupt 72-75 Priority (PRI18), offset 0x448 P.154
         * Register 48: Interrupt 76-79 Priority (PRI19), offset 0x44C P.154
         * Register 49: Interrupt 80-83 Priority (PRI20), offset 0x450 P.154
         * Register 50: Interrupt 84-87 Priority (PRI21), offset 0x454 P.154
         * Register 51: Interrupt 88-91 Priority (PRI22), offset 0x458 P.154
         * Register 52: Interrupt 92-95 Priority (PRI23), offset 0x45C P.154
         * Register 53: Interrupt 96-99 Priority (PRI24), offset 0x460 P.154
         * Register 54: Interrupt 100-103 Priority (PRI25), offset 0x464 P.154
         * Register 55: Interrupt 104-107 Priority (PRI26), offset 0x468 P.154
         * Register 56: Interrupt 108-111 Priority (PRI27), offset 0x46C P.154
         * Register 57: Interrupt 112-115 Priority (PRI28), offset 0x470 P.154
         * Register 58: Interrupt 116-119 Priority (PRI29), offset 0x474 P.154
         * Register 59: Interrupt 120-123 Priority (PRI30), offset 0x478 P.154
         * Register 60: Interrupt 124-127 Priority (PRI31), offset 0x47C P.154
         * Register 61: Interrupt 128-131 Priority (PRI32), offset 0x480 P.154
         * Register 62: Interrupt 132-135 Priority (PRI33), offset 0x484 P.154
         * Register 63: Interrupt 136-138 Priority (PRI34), offset 0x488 P.154
         */
        const uint32_t PRI_OFFSET = 0x400;

        /**
         * Register 64: Software Trigger Interrupt (SWTRIG), offset 0xF00
         * 
         * Note: Only privileged software can enable unprivileged access to the 
         * SWTRIG register.
         * 
         * Writing an interrupt number to the SWTRIG register generates a 
         * Software Generated Interrupt (SGI). See Table 2-9 on page 104 for 
         * interrupt assignments.
         * 
         * When the MAINPEND bit in the Configuration and Control (CFGCTRL) 
         * register (see page 168) is set, unprivileged software can access the 
         * SWTRIG register.
         */
        const uint32_t SWTRIG_OFFSET = 0xF00;



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
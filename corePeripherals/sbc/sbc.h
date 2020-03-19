/**
 * @file sbc.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 11/11/2019
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
 * Driver header for the system block controller for the Texas Instruments Tiva
 * C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Block (SCB) Register Descriptions
 * 
 * This section lists and describes the System Control Block (SCB) registers, 
 * in numerical order by address offset. The SCB registers can only be accessed 
 * from privileged mode.
 * 
 * All registers must be accessed with aligned word accesses except for the 
 * FAULTSTAT and SYSPRI1-SYSPRI3 registers, which can be accessed with byte or 
 * aligned halfword or word accesses. The processor does not support unaligned 
 * accesses to system control block registers.
 */

#ifndef SBC_H
#define SBC_H

#include <stdint-gcc.h>
#include <stddef.h>
#include "../../register/register.h"

const uint32_t ACTLR_OFFSET = 0x008;
const uint32_t CPUID_OFFSET = 0xD00; 
const uint32_t INTCTRL_OFFSET = 0xD04;
const uint32_t VTABLE_OFFSET = 0xD08;
const uint32_t APINT_OFFSET = 0xD0C;
const uint32_t SYSCTRL_OFFSET = 0xD10;
const uint32_t CFGCTRL_OFFSET = 0xD14;
const uint32_t SYSPRI1_OFFSET = 0xD18;
const uint32_t SYSPRI2_OFFSET = 0xD1C;
const uint32_t SYSPRI3_OFFSET = 0xD20;
const uint32_t SYSHNDCTRL_OFFSET = 0xD24;
const uint32_t FAULTSTAT_OFFSET = 0xD28;
const uint32_t HFAULTSTAT_OFFSET = 0xD2C;       
const uint32_t MMADDR_OFFSET = 0xD34;
const uint32_t FAULTADDR_OFFSET = 0xD38;

class Sbc
{
    public:
        Sbc();
        ~Sbc();
        

    private:

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  




        /**
         * Description: Disable Out-Of-Order Floating Point
         * 
         * Disables floating-point instructions completing out of order with
         * respect to integer instructions.
         */
        // bitField ACTLR_DISOOFP{9, 1, RW};

        /**
         * Description: Disable CONTROL.FPCA
         * 
         * Disable automatic update of the FPCA bit in the CONTROL register.
         * ____________________________________________________________________
         * Important: Two bits control when FPCA can be enabled: the ASPEN bit
         * in the Floating-Point Context Control (FPCC) register and the 
         * DISFPCA bit in the Auxiliary Control (ACTLR) register.
         * ____________________________________________________________________
         */
        // bitField ACTLR_DISFPCA{8, 1, RW};

        /**        
         * Description: Disable IT Folding         
         * 
         * Value__Description
         * 0______No effect.
         * 
         * 1______Disables IT folding.
         *          
         * In some situations, the processor can start executing the first 
         * instruction in an IT block while it is still executing the IT 
         * instruction. This behavior is called IT folding, and improves 
         * performance, However, IT folding can cause jitter in looping. If a 
         * task must avoid jitter, set the DISFOLD bit before executing the 
         * task, to disable IT folding.
         */
        // bitField ACTLR_DISFOLD{2, 1, RW};

        /**
         * Description: Disable Write Buffer
         * 
         * Value__Description
         * 0______No effect.
         * 
         * 1______Disables write buffer use during default memory map accesses.
         * _______In this situation, all bus faults are precise bus faults but
         * _______performance is decreased because any store to memory must
         * _______complete before the processor can execute the next 
         * _______instruction.
         * 
         * Note: This bit only affects write buffers implemented in the
         *       Cortex-M4 processor.
         */
        // bitField ACTLR_DISWBUF{1, 1, RW};

        /**
         * Description: Disable Interrupts of Multiple Cycle Instructions
         * 
         * Value__Description
         * 0______No effect.
         * 
         * 1______Disables interruption of load multiple and store multiple
         * _______instructions. In this situation, the interrupt latency of the
         * _______processor is increased because any LDM or STM must complete
         * _______before the processor can stack the current state and enter the
         * _______interrupt handler.
         */
        // bitField ACTLR_DISMCYC{0, 1, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: Implementer Code
         * 
         * Value_Description      
         * 0x41__ARM
         */
        // bitField CPUID_IMP{24, 8, RO};

        /**
         * Description: Variant Number
         * 
         * Value_Description
         * 0x0___The rn value in the rnpn product revision identifier, for 
         * ______example, the 0 in r0p0.
         */
        // bitField CPUID_VAR{20, 4, RO};

        /**
         * Description: Constant
         * 
         * Value_Description
         * 0xF___Always reads as 0xF.
         */
        // bitField CPUID_CON{16, 4, RO};

        /**
         * Description: Part Number
         * 
         * Value___Description
         * 0xC24___Cortex-M4 processor.
         */
        // bitField CPUID_PARTNO{4, 12, RO};

        /**
         * Description: Revision Number
         * 
         * Value__Description
         * 0x1____The pn value in the rnpn product revision identifier,
         * _______for example, the 1 in r0p1.
         */
        // bitField CPUID_REV{0, 4, RO};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /**
         * Description: NMI Set Pending
         * 
         * Value__Description
         * 0______On a read, indicates an NMI exception is not pending.
         * _______On a write, no effect.
         * 
         * 
         * 1______On a read, indicates an NMI exception is pending
         * _______On a write, changes the NMI exception state to pending.
         * 
         * Because NMI is the highest-priority exception, normally the processor enters
         * the NMI exception handler as soon as it registers the setting of this bit, 
         * and clears this bit on entering the interrupt handler. A read of this bit by 
         * the NMI exception handler returns 1 only if the NMI signal is reasserted 
         * while the processor is executing that handler.
         */
        // bitField INTCTRL_NMISET{31, 1, RW};

        /**
         * Description: PendSV Set Pending
         * 
         * Value__Description
         * 0______On a read, indicates a PendSV exception is not pending.
         * _______On a write, no effect.
         * 
         * 1______On a read, indicates a PendSV exception is pending.
         * _______On a write, changes the PendSV exception state to pending.
         * 
         * Setting this bit is the only way to set the PendSV exception state 
         * to pending. This bit is cleared by writing a 1 to the UNPENDSV bit.
         */
        // bitField INTCTRL_PENDSV{28, 1, RW};

        /**
         * Description: PendSV Clear Pending
         * 
         * Value__Description
         * 0______On a write, no effect.
         * 
         * 1______On a write, removes the pending state from the PendSV exception.
         * 
         * This bit is write only; on a register read, its value is unknown.
         */
        // bitField INTCTRL_UNPENDSV{27, 1, WO};

        /**
         * Description: SysTick Set Pending
         * 
         * Value__Description
         * 0______On a read, indicates a SysTick exception is not pending.
         * _______On a write, no effect.
         * 
         * 1______On a read, indicates a SysTick exception is pending.
         * _______On a write, changes the SysTick exception state to pending.
         * 
         * This bit is cleared by writing a 1 to the PENDSTCLR bit.
         */
        // bitField INTCTRL_PENDSTSET{26, 1, RW};

        /**
         * Description: SysTick Clear Pending
         * 
         * Value_Description
         * 0_____On a write, no effect.
         * 
         * 1_____On a write, removes the pending state from the SysTick exception.
         * 
         * This bit is write only; on a register read, its value is unknown.
         */
        // bitField INTCTRL_PENDSTCLR{25, 1, WO};

        /**
         * Description: Debug Interrupt Handling
         * 
         * Value_Description
         * 0_____The release from halt does not take an interrupt.
         * 
         * 1_____The release from halt takes an interrupt.
         * 
         * This bit is only meaningful in Debug mode and reads as zero when the
         * processor is not in Debug mode.
         */
        // bitField INTCTRL_ISRPRE{23, 1, RO};

        /**
         * Description: Interrupt Pending
         * 
         * Value_Description
         * 0_____No interrupt is pending.
         * 
         * 1_____An interrupt is pending.
         * 
         * This bit provides status for all interrupts excluding NMI and Faults.
         */
        // bitField INTCTRL_ISRPEND{22, 1, RO};

        /**
         * Description: Interrupt Pending Vector Number
         * 
         * This field contains the exception number of the highest priority 
         * pending enabled exception. The value indicated by this field includes 
         * the effect of the BASEPRI and FAULTMASK registers, but not any effect 
         * of the PRIMASK register.
         * 
         * Value       Description
         * 0x00________No exceptions are pending
         * 0x01________Reserved
         * 0x02________NMI
         * 0x03________Hard fault
         * 0x04________Memory management fault
         * 0x05________Bus fault
         * 0x06________Usage fault
         * 0x07-0x0A___Reserved
         * 0x0B________SVCall
         * 0x0C________Reserved for Debug
         * 0x0D________Reserved
         * 0x0E________PendSV
         * 0x0F________SysTick
         * 0x10________Interrupt Vector 0
         * 0x11________Interrupt Vector 1
         * ....________....
         * 0x9A________Interrupt Vector 138
         */
        // bitField INTCTRL_VECPEND{12, 8, RO};

        /**
         * Description: Return to Base
         * 
         * Value_Description
         * 0_____There are preempted active exceptions to execute.
         * 
         * 1_____There are no active exceptions, or the currently executing
         * ______exception is the only active exception.
         * 
         * This bit provides status for all interrupts excluding NMI and Faults. 
         * This bit only has meaning if the processor is currently executing an 
         * ISR (the Interrupt Program Status (IPSR) register is non-zero).
         */
        // bitField INTCTRL_RETBASE{11, 1, RO};

        /**
         * Description: Interrupt Pending Vector Number
         * 
         * This field contains the active exception number. The exception numbers
         * can be found in the description for the VECPEND field. If this field 
         * is clear,the processor is in Thread mode. This field contains the 
         * same value as the ISRNUM field in the IPSR register.
         * 
         * Subtract 16 from this value to obtain the IRQ number required to 
         * index into the Interrupt Set Enable (ENn), Interrupt Clear Enable (DISn),
         * Interrupt Set Pending (PENDn), Interrupt Clear Pending (UNPENDn),and 
         * Interrupt Priority (PRIn) registers (see page 81).
         */
        // bitField INTCTRL_VECACT{0, 8, RO};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: Vector Table Offset
         * 
         * When configuring the OFFSET field, the offset must be aligned to the
         * number of exception entries in the vector table. Because there are 
         * 138 interrupts, the offset must be aligned on a 1024-byte boundary.
         */
        // bitField VTABLE_FIELD_OFFSET{10, 22, RW};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Register Key
         * 
         * This field is used to guard against accidental writes to this 
         * register. 0x05FA must be written to this field in order to change the 
         * bits in this register. On a read, 0xFA05 is returned.
         */
        // bitField APINT_VECTKEY{16, 16, RW};

        /**
         * Description: Data Endianess
         * 
         * The TivaTM C Series implementation uses only little-endian mode so
         * this is cleared to 0.
         */
        // bitField APINT_ENDIANESS{15, 1, RO};

        /**
         * Description: Interrupt Priority Grouping
         * 
         * This field determines the split of group priority from subpriority 
         * (see Table 3-9 on page 164 for more information).
         */
        // bitField APINT_PRIGROUP{8, 3, RW};

        /**
         * Description: System Reset Request
         * 
         * Value_Description
         * 0_____No effect.
         * 
         * 1_____Resets the core and all on-chip peripherals except the Debug interface.
         * 
         * This bit is automatically cleared during the reset of the core and 
         * reads as 0.
         */
        // bitField APINT_SYSRESREQ{2, 1, WO};

        /**
         * Description: Clear Active NMI / Fault
         * 
         * This bit is reserved for Debug use and reads as 0. This bit must be
         * written as a 0, otherwise behavior is unpredictable.
         */
        // bitField APINT_VECTCLRACT{1, 1, WO};

        /**
         * Description: System Reset
         * 
         * This bit is reserved for Debug use and reads as 0. This bit must be
         * written as a 0, otherwise behavior is unpredictable.
         */
        // bitField APINT_VECTRESET{0, 1, WO};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: Wake Up on Pending
         * 
         * Value Description
         * 0_____Only enabled interrupts or events can wake up the processor;
         *  _____disabled interrupts are excluded.
         * 
         * 1_____Enabled events and all interrupts, including disabled interrupts,
         *  _____can wake up the processor.
         * 
         * When an event or interrupt enters the pending state, the event signal
         * wakes up the processor from WFE. If the processor is not waiting for 
         * an event, the event is registered and affects the next WFE. 
         * 
         * The processor also wakes up on execution of a SEV instruction or an 
         * external event.
         */
        // bitField SYSCTRL_SEVONPEND{4, 1, RW};

        /**
         * Description: Deep Sleep Enable
         * 
         * Value_Description
         * 0_____Use Sleep mode as the low power mode.
         * 
         * 1_____Use Deep-sleep mode as the low power mode
         */
        // bitField SYSCTRL_SLEEPDEEP{2, 1, RW};

        /**
         * Description: Sleep on ISR Exit
         * 
         * Value_Description
         * 0_____When returning from Handler mode to Thread mode, do not
         * ______sleep when returning to Thread mode.
         * 
         * 1_____When returning from Handler mode to Thread mode, enter sleep
         * ______or deep sleep on return from an ISR.
         * 
         * Setting this bit enables an interrupt-driven application to avoid returning
         * to an empty main application.
         */
        // bitField SYSCTRL_SLEEPEXIT{1, 1, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: Stack Alignment on Exception Entry
         * 
         * Value_Description
         * 0_____The stack is 4-byte aligned.
         * 
         * 1_____The stack is 8-byte aligned.
         * 
         * On exception entry, the processor uses bit 9 of the stacked PSR to
         * indicate the stack alignment. On return from the exception, it uses 
         * this stacked bit to restore the correct stack alignment.
         */
        // bitField CFGCTRL_STKALIGN{9, 1, RW};

        /**
         * Description: Ignore Bus Fault in NMI and Fault
         * 
         * This bit enables handlers with priority -1 or -2 to ignore data bus 
         * faults caused by load and store instructions. The setting of this bit 
         * applies to the hard fault, NMI, and FAULTMASK escalated handlers.
         * 
         * Value_Description
         * 0_____Data bus faults caused by load and store instructions cause a
         *  _____lock-up.
         * 
         * 1_____Handlers running at priority -1 and -2 ignore data bus faults
         * ______caused by load and store instructions.
         * 
         * Set this bit only when the handler and its data are in absolutely 
         * safe memory. The normal use of this bit is to probe system devices 
         * and bridges to detect control path problems and fix them.
         */
        // bitField CFGCTRL_BFHFNMIGN{8, 1, RW};

        /**
         * Description: Trap on Divide by 0
         * 
         * This bit enables faulting or halting when the processor executes an
         * SDIV or UDIV instruction with a divisor of 0.
         * 
         * Value_Description
         * 0_____Do not trap on divide by 0. A divide by zero returns a quotient
         *  _____of 0.
         * 
         * 1_____Trap on divide by 0.
         */
        // bitField CFGCTRL_DIV0{4, 1, RW};

        /**
         * Description: Trap on Unaligned Access
         * 
         * Value_Description
         * 0_____Do not trap on unaligned halfword and word accesses.
         * 
         * 1_____Trap on unaligned halfword and word accesses. An unaligned
         * ______access generates a usage fault.
         * 
         * Unaligned LDM, STM, LDRD, and STRD instructions always fault
         * regardless of whether UNALIGNED is set.
         */
        // bitField CFGCTRL_UNALIGNED{3, 1, RW};

        /**
         * Description: Allow Main Interrupt Trigger
         * 
         * Value Description
         * 0_____Disables unprivileged software access to the SWTRIG register.
         * 
         * 1_____Enables unprivileged software access to the SWTRIG register
         * ______(see page 156).
         */
        // bitField CFGCTRL_MAINPEND{1, 1, RW};

        /**
         * Description: Thread State Control
         * 
         * Value_Description
         * 0_____The processor can enter Thread mode only when no exception
         * ______is active.
         * 
         * 1_____The processor can enter Thread mode from any level under the
         * ______control of an EXC_RETURN value (see “Exception Return” on page 
         * ______110 for more information).
         */
        // bitField CFGCTRL_BASETHR{0, 1, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: Usage Fault Priority
         * 
         * This field configures the priority level of the usage fault. 
         * Configurable priority values are in the range 0-7, with lower values 
         * having higher priority.
         */
        // bitField SYSPRI1_USAGE{32, 3, RW};

        /**
         * Description: Bus Fault Priority
         * 
         * This field configures the priority level of the bus fault. 
         * Configurable priority values are in the range 0-7, with lower values 
         * having higher priority.
         */
        // bitField SYSPRI1_BUS{13, 3, RW};

        /**
         * Description: Memory Management Fault Priority
         * 
         * This field configures the priority level of the memory management 
         * fault. Configurable priority values are in the range 0-7, with lower 
         * values having higher priority.
         */
        // bitField SYSPRI1_MEM{5, 3, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: SVCall Priority
         * 
         * This field configures the priority level of SVCall. Configurable 
         * priority values are in the range 0-7, with lower values having higher 
         * priority.
         */
        // bitField SYSPRI2_SVC{29, 3, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         * Description: SysTick Exception Priority
         * 
         * This field configures the priority level of the SysTick exception.
         * Configurable priority values are in the range 0-7, with lower values
         * having higher priority.
         */
        // bitField SYSPRI3_TICK{29, 3, RW};

        /**
         * Description: PendSV Priority
         * 
         * This field configures the priority level of PendSV. Configurable 
         * priority values are in the range 0-7, with lower values having higher 
         * priority.
         */
        // bitField SYSPRI3_PENDSV{21, 3, RW};

        /**
         * Description: Debug Priority
         * 
         * This field configures the priority level of Debug. Configurable 
         * priority values are in the range 0-7, with lower values having higher 
         * priority.
         */
        // bitField SYSPRI3_DEBUG{5, 3, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Usage Fault Enable
         * 
         * Value_Description
         * 0_____Disables the usage fault exception.
         * 
         * 1_____Enables the usage fault exception.
         */
        // bitField SYSHNDCTRL_USAGE{18, 1, RW};

        /**
         * Description: Bus Fault Enable
         * 
         * Value_Description
         * 0_____Disables the bus fault exception.
         * 
         * 1_____Enables the bus fault exception.
         */
        // bitField SYSHNDCTRL_BUS{17, 1, RW};

        /**
         * Description: Memory Management Fault Enable
         * 
         * Value_Description
         * 0_____Disables the memory management fault exception.
         * 
         * 1_____Enables the memory management fault exception.
         */
        // bitField SYSHNDCTRL_MEM{16, 1, RW};

        /**
         * Description: SVC Call Pending
         * 
         * Value_Description
         * 0_____An SVC call exception is not pending.
         * 
         * 1_____An SVC call exception is pending.
         * 
         * This bit can be modified to change the pending status of the SVC call
         * exception.
         */
        // bitField SYSHNDCTRL_SVC{15, 1, RW};

        /**
         * Description: Bus Fault Pending
         * 
         * Value_Description
         * 0_____A bus fault exception is not pending.
         * 
         * 1_____A bus fault exception is pending.
         * 
         * This bit can be modified to change the pending status of the bus 
         * fault exception.
         */
        // bitField SYSHNDCTRL_BUSP{14, 1, RW};

        /**
         * Description: Memory Management Fault Pending
         * 
         * Value_Description
         * 0_____A memory management fault exception is not pending.
         * 
         * 1_____A memory management fault exception is pending.
         * 
         * This bit can be modified to change the pending status of the memory
         * management fault exception.
         */
        // bitField SYSHNDCTRL_MEMP{13, 1, RW};

        /**
         * Description: Usage Fault Pending
         * 
         * Value_Description
         * 0_____A usage fault exception is not pending.
         * 
         * 1_____A usage fault exception is pending.
         * 
         * This bit can be modified to change the pending status of the usage 
         * fault exception.
         */
        // bitField SYSHNDCTRL_USAGEP{12, 1, RW};

        /**
         * Description: SysTick Exception Active
         * 
         * Value_Description
         * 0_____A SysTick exception is not active.
         * 
         * 1_____A SysTick exception is active.
         * 
         * This bit can be modified to change the active status of the SysTick
         * exception, however, see the Caution above before setting this bit.
         */
        // bitField SYSHNDCTRL_TICK{11, 1, RW};

        /**
         * Description: PendSV Exception Active
         * 
         * Value_Description
         * 0_____A PendSV exception is not active.
         * 
         * 1_____A PendSV exception is active.
         * 
         * This bit can be modified to change the active status of the PendSV
         * exception, however, see the Caution above before setting this bit.
         */
        // bitField SYSHNDCTRL_PNDSV{10, 1, RW};

        /**
         * Description: Debug Monitor Active
         * 
         * Value_Description
         * 0_____The Debug monitor is not active.
         * 
         * 1_____The Debug monitor is active.
         */
        // bitField SYSHNDCTRL_MON{8, 1, RW};

        /**
         * Description: SVC Call Active
         * 
         * Value_Description
         * 0_____SVC call is not active.
         * 
         * 1_____SVC call is active.
         * 
         * This bit can be modified to change the active status of the SVC call
         * exception, however, see the Caution above before setting this bit.
         */
        // bitField SYSHNDCTRL_SVCA{7, 1, RW};

        /**
         * Description: Usage Fault Active
         * 
         * Value_Description
         * 0_____Usage fault is not active.
         * 
         * 1_____Usage fault is active.
         * 
         * This bit can be modified to change the active status of the usage 
         * fault exception, however, see the Caution above before setting this bit.
         */
        // bitField SYSHNDCTRL_USGA{3, 1, RW};

        /**
         * Description: Bus Fault Active
         * 
         * Value_Description
         * 0_____Bus fault is not active.
         * 
         * 1_____Bus fault is active.
         * 
         * This bit can be modified to change the active status of the bus fault
         * exception, however, see the Caution above before setting this bit.
         */
        // bitField SYSHNDCTRL_BUSA{1, 1, RW};

        /**
         * Description: Memory Management Fault Active
         * 
         * Value_Description
         * 0_____Memory management fault is not active.
         * 
         * 1_____Memory management fault is active.
         * 
         * This bit can be modified to change the active status of the memory
         * management fault exception, however, see the Caution above before
         * setting this bit.
         */
        // bitField SYSHNDCTRL_MEMA{0, 1, RW};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Divide-by-Zero Usage Fault
         * 
         * Value Description
         * 0_____No divide-by-zero fault has occurred, or divide-by-zero trapping
         * ______is not enabled.
         * 
         * 1_____The processor has executed an SDIV or UDIV instruction with
         * ______a divisor of 0.
         * 
         * When this bit is set, the PC value stacked for the exception return 
         * points to the instruction that performed the divide by zero.
         * 
         * Trapping on divide-by-zero is enabled by setting the DIV0 bit in the
         * Configuration and Control (CFGCTRL) register (see page 168).
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_DIV0{25, 1, RW1C};

        /**
         * Description: Unaligned Access Usage Fault
         * 
         * Value Description
         * 0_____No unaligned access fault has occurred, or unaligned access
         * ______trapping is not enabled.
         * 
         * 1_____The processor has made an unaligned memory access.
         * 
         * Unaligned LDM, STM, LDRD, and STRD instructions always fault
         * regardless of the configuration of this bit.
         * 
         * Trapping on unaligned access is enabled by setting the UNALIGNED bit
         * in the CFGCTRL register (see page 168).
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_UNALIGN{24, 1, RW1C};

        /**
         * Description: No Coprocessor Usage Fault
         * 
         * Value Description
         * 0_____A usage fault has not been caused by attempting to access a
         * ______coprocessor.
         * 
         * 1_____The processor has attempted to access a coprocessor.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_NOCP{19, 1, RW1C};

        /**
         * Description: Invalid PC Load Usage Fault
         * 
         * Value Description
         * 0_____A usage fault has not been caused by attempting to load an
         * ______invalid PC value.
         * 
         * 1_____The processor has attempted an illegal load of EXC_RETURN to 
         * ______the PC as a result of an invalid context or an invalid
         * ______EXC_RETURN value.
         * 
         * When this bit is set, the PC value stacked for the exception return 
         * points to the instruction that tried to perform the illegal load of 
         * the PC.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_INVPC{18, 1, RW1C};

        /**
         * Description: Invalid State Usage Fault
         * 
         * Value Description
         * 0_____A usage fault has not been caused by an invalid state.
         * 
         * 1_____The processor has attempted to execute an instruction that
         * ______makes illegal use of the EPSR register.
         * 
         * When this bit is set, the PC value stacked for the exception return 
         * points to the instruction that attempted the illegal use of the 
         * Execution Program Status Register (EPSR) register.
         * 
         * This bit is not set if an undefined instruction uses the EPSR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_INVSTAT{17, 1, RW1C};

        /**
         * Description: Undefined Instruction Usage Fault
         * 
         * Value Description
         * 0_____A usage fault has not been caused by an undefined instruction.
         * 
         * 1_____The processor has attempted to execute an undefined instruction.
         * 
         * When this bit is set, the PC value stacked for the exception return points
         * to the undefined instruction.
         * 
         * An undefined instruction is an instruction that the processor cannot
         * decode.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_UNDEF{16, 1, RW1C};

        /**
         * Description: Bus Fault Address Register Valid
         * 
         * Value Description
         * 0_____The value in the Bus Fault Address (FAULTADDR) register is not 
         * ______a valid fault address.
         * 
         * 1_____The FAULTADDR register is holding a valid fault address.
         * 
         * This bit is set after a bus fault, where the address is known. Other 
         * faults can clear this bit, such as a memory management fault 
         * occurring later.
         * 
         * If a bus fault occurs and is escalated to a hard fault because of 
         * priority, the hard fault handler must clear this bit. This action 
         * prevents problems if returning to a stacked active bus fault handler 
         * whose FAULTADDR register value has been overwritten.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_BFARV{15, 1, RW1C};

        /**
         * Description: Bus Fault on Floating-Point Lazy State Preservation
         * 
         * Value Description
         * 0_____No bus fault has occurred during floating-point lazy state
         * ______preservation.
         * 
         * 1_____A bus fault has occurred during floating-point lazy state
         * ______preservation.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_BLSPERR{13, 1, RW1C};

        /**
         * Description: Stack Bus Fault
         * 
         * Value Description
         * 0_____No bus fault has occurred on stacking for exception entry.
         * 
         * 1_____Stacking for an exception entry has caused one or more bus
         * ______faults.
         * 
         * When this bit is set, the SP is still adjusted but the values in the 
         * context area on the stack might be incorrect. A fault address is not 
         * written to the FAULTADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_BSTKE{12, 1, RW1C};

        /**
         * Description: Unstack Bus Fault
         * 
         * Value Description
         * 0_____No bus fault has occurred on unstacking for a return from
         * ______exception.
         * 
         * 1_____Unstacking for a return from exception has caused one or more
         * ______bus faults.
         * 
         * This fault is chained to the handler. Thus, when this bit is set, the 
         * original return stack is still present. The SP is not adjusted from 
         * the failing return, a new save is not performed, and a fault address 
         * is not written to the FAULTADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_BUSTKE{11, 1, RW1C};

        /**
         * Description: Imprecise Data Bus Error
         * 
         * Value Description
         * 0_____An imprecise data bus error has not occurred.
         * 
         * 1_____A data bus error has occurred, but the return address in the
         * ______stack frame is not related to the instruction that caused the error.
         * 
         * When this bit is set, a fault address is not written to the FAULTADDR 
         * register.
         * 
         * This fault is asynchronous. Therefore, if the fault is detected when 
         * the priority of the current process is higher than the bus fault 
         * priority, the bus fault becomes pending and becomes active only when 
         * the processor returns from all higher-priority processes. If a 
         * precise fault occurs before the processor enters the handler for the 
         * imprecise bus fault, the handler detects that both the IMPRE bit is 
         * set and one of the precise fault status bits is set.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_IMPRE{10, 1, RW1C};

        /**
         * Description: Precise Data Bus Error
         * 
         * Value Description
         * 0_____A precise data bus error has not occurred.
         * 
         * 1_____A data bus error has occurred, and the PC value stacked for
         * the exception return points to the instruction that caused the fault.
         * 
         * When this bit is set, the fault address is written to the FAULTADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_PRECISE{9, 1, RW1C};

        /**
         * Description: Instruction Bus Error
         * 
         * Value Description
         * 0_____An instruction bus error has not occurred.
         * 
         * 1_____An instruction bus error has occurred.
         * 
         * The processor detects the instruction bus error on prefetching an
         * instruction, but sets this bit only if it attempts to issue the 
         * faulting instruction.
         * 
         * When this bit is set, a fault address is not written to the FAULTADDR
         * register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_IBUS{8, 1, RW1C};

        /**
         * Description: Memory Management Fault Address Register Valid
         * 
         * Value Description
         * 0_____The value in the Memory Management Fault Address
         * ______(MMADDR) register is not a valid fault address.
         * 
         * 1_____The MMADDR register is holding a valid fault address.
         * 
         * If a memory management fault occurs and is escalated to a hard fault
         * because of priority, the hard fault handler must clear this bit. 
         * This action prevents problems if returning to a stacked active memory 
         * management fault handler whose MMADDR register value has been 
         * overwritten.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_MMARV{7, 1, RW1C};

        /**
         * Description: Memory Management Fault on Floating-Point Lazy State Preservation
         * 
         * Value Description
         * 0_____No memory management fault has occurred during floating-point
         * ______lazy state preservation.
         * 
         * 1_____No memory management fault has occurred during floating-point
         * ______lazy state preservation.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_MLSPERR{5, 1, RW1C};

        /**
         * Description: Stack Access Violation
         * 
         * Value Description
         * 0_____No memory management fault has occurred on stacking for 
         * ______exception entry.
         * 
         * 1_____Stacking for an exception entry has caused one or more access
         * ______violations.
         * 
         * When this bit is set, the SP is still adjusted but the values in the 
         * context area on the stack might be incorrect. A fault address is not 
         * written to the MMADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_MSTKE{4, 1, RW1C};
        
        /**
         * Description: Unstack Access Violation
         * 
         * Value Description
         * 0_____No memory management fault has occurred on unstacking for a 
         * ______return from exception.
         * 
         * 1_____Unstacking for a return from exception has caused one or more
         * ______access violations.
         * 
         * This fault is chained to the handler. Thus, when this bit is set, the 
         * original return stack is still present. The SP is not adjusted from 
         * the failing return, a new save is not performed, and a fault address 
         * is not written to the MMADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_MUSTKE{3, 1, RW1C};

        /**
         * Description: Data Access Violation
         * 
         * Value Description
         * 0_____A data access violation has not occurred.
         * 
         * 1_____The processor attempted a load or store at a location that does
         * ______not permit the operation.
         * 
         * When this bit is set, the PC value stacked for the exception return 
         * points to the faulting instruction and the address of the attempted 
         * access is written to the MMADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_DERR{1, 1, RW1C};

        /**
         * Description: Instruction Access Violation
         * 
         * Value Description
         * 0_____An instruction access violation has not occurred.
         * 1_____The processor attempted an instruction fetch from a location
         * ______that does not permit execution.
         * 
         * This fault occurs on any access to an XN region, even when the MPU is 
         * disabled or not present.
         * 
         * When this bit is set, the PC value stacked for the exception return 
         * points to the faulting instruction and the address of the attempted 
         * access is not written to the MMADDR register.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField FAULTSTAT_IERR{0, 1, RW1C};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Debug Event
         * 
         * This bit is reserved for Debug use. This bit must be written as a 0,
         * otherwise behavior is unpredictable.
         */
        // bitField HFAULTSTAT_DBG{31, 1, RW1C};

        /**
         * Description: Forced Hard Fault
         * 
         * Value Description
         * 0_____No forced hard fault has occurred.
         * 
         * 1_____A forced hard fault has been generated by escalation of a fault
         * ______with configurable priority that cannot be handled, either because
         * ______of priority or because it is disabled.
         * 
         * When this bit is set, the hard fault handler must read the other 
         * fault status registers to find the cause of the fault.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField HFAULTSTAT_FORCED{30, 1, RW1C};

        /**
         * Description: Vector Table Read Fault
         * 
         * Value Description
         * 0_____No bus fault has occurred on a vector table read.
         * 
         * 1_____A bus fault occurred on a vector table read.
         * 
         * This error is always handled by the hard fault handler.
         * 
         * When this bit is set, the PC value stacked for the exception return 
         * points to the instruction that was preempted by the exception.
         * 
         * This bit is cleared by writing a 1 to it.
         */
        // bitField HFAULTSTAT_VECT{1, 1, RW1C};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Fault Address
         * 
         * When the MMARV bit of MFAULTSTAT is set, this field holds the address
         * of the location that generated the memory management fault.
         */
        // bitField MMADDR_ADDR{0, 32, RW};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Fault Address
         * 
         * When the FAULTADDRV bit of BFAULTSTAT is set, this field holds the
         * address of the location that generated the bus fault.
         */
        // bitField FAULTADDR_ADDR{0, 32, RW};

};

#endif //SBC
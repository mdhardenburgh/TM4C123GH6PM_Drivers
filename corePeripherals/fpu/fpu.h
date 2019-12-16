/**
 * @file fpu.h
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
 * Class header for the floating point unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * Floating-Point Unit (FPU) Register Descriptions
 * 
 * This section lists and describes the Floating-Point Unit (FPU) registers,
 * in numerical order by address offset.
 */

#ifndef FPU_H
#define FPU_H

#include "../../register.h"

class Fpu
{
    public:
        Fpu();
        ~Fpu();
    
    private:
        /**
         * Cortex-M4 Peripheral SysTick, NVIC, MPU, FPU and SCB registers.
         * These register definitions begin on page 134 of the TM4C123GH6PM Datasheet.
         */
        long corePeripheralBase = 0xE000E000;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         * Register 91: Coprocessor Access Control (CPAC), offset 0xD88
         * 
         * The CPAC register specifies the access privileges for coprocessors.
         */
        Register CPAC{(volatile uint32_t*)(corePeripheralBase + 0xD88)};

        /**
         * Description: CP11 Coprocessor Access Privilege
         * 
         * Value Description
         * 0x0___Access Denied
         * ______Any attempted access generates a NOCP Usage Fault.
         * 
         * 0x1____Privileged Access Only
         * _______An unprivileged access generates a NOCP fault.
         * 
         * 0x2____Reserved
         * _______The result of any access is unpredictable.
         * 
         * 0x3____Full Access
         */
        bitField CPAC_CP11{22, 2, (char*)"RW"};

        /**
         * Description: CP10 Coprocessor Access Privilege
         * 
         * Value Description
         * 0x0___Access Denied
         * ______Any attempted access generates a NOCP Usage Fault.
         * 
         * 0x1____Privileged Access Only
         * _______An unprivileged access generates a NOCP fault.
         * 
         * 0x2____Reserved
         * _______The result of any access is unpredictable.
         * 
         * 0x3____Full Access
         */
        bitField CPAC_CP10{20, 2, (char*)"RW"};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         * Register 92: Floating-Point Context Control (FPCC), offset 0xF34
         * 
         * The FPCC register sets or returns FPU control data.
         */
        Register FPCC{(volatile uint32_t*)(corePeripheralBase + 0xF34)};

        /**
         * Description: Automatic State Preservation Enabl
         * 
         * When set, enables the use of the FRACTV bit in the CONTROL register
         * on execution of a floating-point instruction. This results in 
         * automatic hardware state preservation and restoration, for 
         * floating-point context, on exception entry and exit.
         * 
         * _____________________________________________________________________
         * Important:_Two bits control when FPCA can be enabled: the ASPEN bit 
         * ___________in the Floating-Point Context Control (FPCC) register and 
         * ___________the DISFPCA bit in the Auxiliary Control
         * ___________(ACTLR) register.
         * _____________________________________________________________________
         * 
         */
        bitField FPCC_ASPEN{31, 1, (char*)"RW"};

        /**
         * Description: Lazy State Preservation Enable
         * 
         * When set, enables automatic lazy state preservation for 
         * floating-point context.
         */
        bitField FPCC_LSPEN{30, 1, (char*)"RW"};

        /**
         * Description: Monitor Ready
         * 
         * When set, DebugMonitor is enabled and priority permits setting
         * MON_PEND when the floating-point stack frame was allocated.
         */
        bitField FPCC_MONRDY{8, 1, (char*)"RW"};

        /**
         * Description: Bus Fault Ready
         * 
         * When set, BusFault is enabled and priority permitted setting the 
         * BusFault handler to the pending state when the floating-point stack 
         * frame was allocated.
         */
        bitField FPCC_BFRDY{6, 1, (char*)"RW"};

        /**
         * Description: Memory Management Fault Ready
         * 
         * When set, MemManage is enabled and priority permitted setting the
         * MemManage handler to the pending state when the floating-point stack
         * frame was allocated.
         */
        bitField FPCC_MMRDY{5, 1, (char*)"RW"};

        /**
         * Description: Hard Fault Ready
         * 
         * When set, priority permitted setting the HardFault handler to the 
         * pending state when the floating-point stack frame was allocated.
         */
        bitField FPCC_HFRDY{4, 1, (char*)"RW"};

        /**
         * Description: Thread Mode
         * 
         * When set, mode was Thread Mode when the floating-point stack frame
         * was allocated.
         */
        bitField FPCC_THREAD{3, 1, (char*)"RW"};

        /**
         * Description: User Privilege Level
         * 
         * When set, privilege level was user when the floating-point stack 
         * frame was allocated.
         */
        bitField FPCC_USER{1, 1, (char*)"RW"};

        /**
         * Description: Lazy State Preservation Active
         * 
         * When set, Lazy State preservation is active. Floating-point stack 
         * frame has been allocated but saving state to it has been deferred.
         */
        bitField FPCC_LSPACT{0, 1, (char*)"RW"};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         * Register 93: Floating-Point Context Address (FPCA), offset 0xF38
         * 
         * The FPCA register holds the location of the unpopulated floating-point 
         * register space allocated on an exception stack frame.
         */
        Register FPCA{(volatile uint32_t*)(corePeripheralBase + 0xF38)};

        /**
         * Description: Address
         * 
         * The location of the unpopulated floating-point register space 
         * allocated on an exception stack frame.
         */
        bitField FPCA_ADDRESS{3, 29, (char*)"RW"};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /**
         * Register 94: Floating-Point Default Status Control (FPDSC), offset 0xF3C
         * 
         * The FPDSC register holds the default values for the Floating-Point Status 
         * Control (FPSC) register.
         */
        Register FPDSC{(volatile uint32_t*)(corePeripheralBase + 0xF3C)};

        /**
         * Description: AHP Bit Default
         * 
         * This bit holds the default value for the AHP bit in the FPSC register.
         */
        bitField FPDSC_AHP{26, 1, (char*)"RW"};

        /**
         * Description: DN Bit Default
         * 
         * This bit holds the default value for the DN bit in the FPSC register.
         */
        bitField FPDSC_DN{25, 1, (char*)"RW"};

        /**
         * Description: FZ Bit Default
         * 
         * This bit holds the default value for the FZ bit in the FPSC register.
         */
        bitField FPDSC_FZ{24, 1, (char*)"RW"};

        /**
         * Description: RMODE Bit Default
         * 
         * This bit holds the default value for the RMODE bit field in the FPSC
         * register.
         * 
         * Value Description
         * 0x0___Round to Nearest (RN) mode
         * 
         * 0x1___Round towards Plus Infinity (RP) mode
         * 
         * 0x2___Round towards Minus Infinity (RM) mode
         * 
         * 0x3___Round towards Zero (RZ) mode
         */
        bitField FPDSC_RMODE{22, 2, (char*)"RW"};
                
};





#endif //FPU
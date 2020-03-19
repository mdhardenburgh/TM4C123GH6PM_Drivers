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

#include "../../register/register.h"

const uint32_t CPAC_OFFSET = 0xD88;
const uint32_t FPCC_OFFSET = 0xF34;
const uint32_t FPCA_OFFSET = 0xF38;
const uint32_t FPDSC_OFFSET = 0xF3C;

class Fpu
{
    public:
        Fpu();
        ~Fpu();
    
    private:


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
        // bitField CPAC_CP11{22, 2, RW};

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
        // bitField CPAC_CP10{20, 2, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Automatic State Preservation Enable
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
        // bitField FPCC_ASPEN{31, 1, RW};

        /**
         * Description: Lazy State Preservation Enable
         * 
         * When set, enables automatic lazy state preservation for 
         * floating-point context.
         */
        // bitField FPCC_LSPEN{30, 1, RW};

        /**
         * Description: Monitor Ready
         * 
         * When set, DebugMonitor is enabled and priority permits setting
         * MON_PEND when the floating-point stack frame was allocated.
         */
        // bitField FPCC_MONRDY{8, 1, RW};

        /**
         * Description: Bus Fault Ready
         * 
         * When set, BusFault is enabled and priority permitted setting the 
         * BusFault handler to the pending state when the floating-point stack 
         * frame was allocated.
         */
        // bitField FPCC_BFRDY{6, 1, RW};

        /**
         * Description: Memory Management Fault Ready
         * 
         * When set, MemManage is enabled and priority permitted setting the
         * MemManage handler to the pending state when the floating-point stack
         * frame was allocated.
         */
        // bitField FPCC_MMRDY{5, 1, RW};

        /**
         * Description: Hard Fault Ready
         * 
         * When set, priority permitted setting the HardFault handler to the 
         * pending state when the floating-point stack frame was allocated.
         */
        // bitField FPCC_HFRDY{4, 1, RW};

        /**
         * Description: Thread Mode
         * 
         * When set, mode was Thread Mode when the floating-point stack frame
         * was allocated.
         */
        // bitField FPCC_THREAD{3, 1, RW};

        /**
         * Description: User Privilege Level
         * 
         * When set, privilege level was user when the floating-point stack 
         * frame was allocated.
         */
        // bitField FPCC_USER{1, 1, RW};

        /**
         * Description: Lazy State Preservation Active
         * 
         * When set, Lazy State preservation is active. Floating-point stack 
         * frame has been allocated but saving state to it has been deferred.
         */
        // bitField FPCC_LSPACT{0, 1, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: Address
         * 
         * The location of the unpopulated floating-point register space 
         * allocated on an exception stack frame.
         */
        // bitField FPCA_ADDRESS{3, 29, RW};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        

        /**
         * Description: AHP Bit Default
         * 
         * This bit holds the default value for the AHP bit in the FPSC register.
         */
        // bitField FPDSC_AHP{26, 1, RW};

        /**
         * Description: DN Bit Default
         * 
         * This bit holds the default value for the DN bit in the FPSC register.
         */
        // bitField FPDSC_DN{25, 1, RW};

        /**
         * Description: FZ Bit Default
         * 
         * This bit holds the default value for the FZ bit in the FPSC register.
         */
        // bitField FPDSC_FZ{24, 1, RW};

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
        // bitField FPDSC_RMODE{22, 2, RW};
                
};





#endif //FPU
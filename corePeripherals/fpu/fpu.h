/**
 * @file fpu.h
 * @brief TM4C123GH6PM FPU Driver Declaration
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
 * @class Fpu
 * @brief TM4C123GH6PM FPU Driver
 * 
 * @section fpuDescription FPU Description
 * 
 * The TM4C123GH6PM microcontroller supports a floating point unit (FPU). The 
 * FPU fully supports single-precision add, subtract, multiply, divide, 
 * multiply and accumulate, and square root operations. It also provides 
 * conversions between fixed-point and floating-point data formats, and 
 * floating-point constant instructions. The FPU provides floating-point
 * computation functionality that is compliant with the ANSI/IEEE Std 754-2008, 
 * IEEE Standard for Binary Floating-Point Arithmetic, referred to as the IEEE 
 * 754 standard. The FPU's single-precision extension registers can also be 
 * accessed as 16 doubleword registers for load, store, and move operations.
 * The FPU provides:
 *      - 32-bit instructions for single-precision (C float) data-processing operations
 *      - Combined multiply and accumulate instructions for increased precision (Fused MAC)
 *      - Hardware support for conversion, addition, subtraction, multiplication with optional accumulate, division, and square-root
 *      - Hardware support for denormals and all IEEE rounding modes
 *      - 32 dedicated 32-bit single-precision registers, also addressable as 16 double-word registers
 *      - Decoupled three stage pipeline
 * 
 * For more detailed information on the FPU please see page 130 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection fpuRegisterDescription FPU Register Description
 * 
 * The FPU class contains a list of FPU registers listed as an offset relative
 * to the hexadecimal base address of Core Peripherals 0xE000E000.
 */

#ifndef FPU_H
#define FPU_H

#include "../../register/register.h"



class Fpu
{
    public:
        Fpu();
        ~Fpu();
    
    private:

        static const uint32_t CPAC_OFFSET = 0xD88; // 0xD88 CPAC RW 0x0000.0000 Coprocessor Access Control 195
        static const uint32_t FPCC_OFFSET = 0xF34; // 0xF34 FPCC RW 0xC000.0000 Floating-Point Context Control 196
        static const uint32_t FPCA_OFFSET = 0xF38; // 0xF38 FPCA RW - Floating-Point Context Address 198
        static const uint32_t FPDSC_OFFSET = 0xF3C; // 0xF3C FPDSC RW 0x0000.0000 Floating-Point Default Status Control 199
    
};
#endif //FPU
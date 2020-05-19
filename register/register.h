/**
 * @file register.h
 * @brief Register Class Declaration
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
 * @class Register
 * @brief Class used to unify the access to registers
 * 
 * @section registerDescription Register Class Description
 * 
 * This helper class is used to unify and abstract away accessing the registers. 
 * This makes the code easier to read and more maintainable. The class's static
 * functions take care of clearing the bitfield before writing to it, to ensure
 * that the correct value is alway written.
 * 
 * Additionally, new and delete is redefined in the .cpp file for this class to
 * eliminate exception handling, which is not needed in an embedded enviroment.
 * 
 */

#ifndef REGISTER_H
#define REGISTER_H

#include <stddef.h>
#include <cstdint>
#include <new>
#include <stdlib.h>

using std::uint32_t;

/**
 * Set or Clear a register bit
 */
enum class setORClear : uint32_t {clear, set};

/**
 * The permission of the bitfield
 */
enum bitFieldPermission
{
    RW, RO, WO, RW1C
};

/**
 * Base address of the core peripherals
 */
const uint32_t corePeripheralBase = 0xE000E000;

class Register
{
    public:
        Register();
        ~Register();

        static uint32_t getRegisterBitFieldStatus(volatile uint32_t* address, uint32_t bit, uint32_t bitWidth, bitFieldPermission permission);
        static void setRegisterBitFieldStatus(volatile uint32_t* address, uint32_t value, uint32_t bit, uint32_t bitWidth, bitFieldPermission permission);
    
    private:
};

#endif //REGISTER_H
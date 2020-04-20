/**
 * @file register.cpp
 * @brief Register Class Definition
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

#include "register.h"

/**
 * @brief empty constructor placeholder
 */
Register::Register()
{
    
}

/**
 * @brief empty deconstructor placeholder
 */
Register::~Register()
{

}

/**
 * @param address of the register
 * @param bit to be retrieved or the first bit of the bitfield to be retrieved
 * @param width of the bitfield
 * @param permission of the bitfield, read-only, write-only, etc...
 * 
 * @return retrieved information in the bitfield
 */
uint32_t Register::getRegisterBitFieldStatus(volatile uint32_t* address, uint32_t bit, uint32_t bitWidth, bitFieldPermission permission)
{
    if((permission == RW) || (permission == RO) || (permission == RW1C))
    {
        uint32_t select = ((((0xFFFFFFFF >> (32 - bitWidth)))) << bit);
        return(((*address) & select) >> bit);
    }

    else
    {
        return(UINT32_MAX);
    }
}

/**
 * @param address of the register
 * @param value to be written to the bitfield
 * @param bit to be set or the first bit of the bitfield to be set
 * @param width of the bitfield
 * @param permission of the bitfield, read-only, write-only, etc...
 */
void Register::setRegisterBitFieldStatus(volatile uint32_t* address, uint32_t value, uint32_t bit, uint32_t bitWidth, bitFieldPermission permission)
{
    if((permission == RW1C) && (value != 1))
    {
        return;
    }
    
    else if((permission == RW) || (permission == WO) || (permission == RW1C))
    {
        uint32_t maxValue = (0xFFFFFFFF >> (32 - bitWidth));

        if((value <= maxValue))
        {
            uint32_t clear = (~(maxValue << bit));
            value = value << bit;
    
            (*address) &= clear;
            (*address) |= value;
        }

        else
        {
            return;
        }
        
    }

    else
    {
        return;
    }
}


void* operator new(size_t size) noexcept 
{ 
    return malloc(size); 
} 

void operator delete(void *p) noexcept 
{ 
    free(p); 
} 

void* operator new[](size_t size) noexcept 
{ 
    return operator new(size); // Same as regular new
} 

void operator delete[](void *p) noexcept 
{ 
    operator delete(p); // Same as regular delete
} 

void* operator new(size_t size, std::nothrow_t) noexcept 
{ 
    return operator new(size); // Same as regular new 
} 

void operator delete(void *p,  std::nothrow_t) noexcept 
{ 
    operator delete(p); // Same as regular delete
} 

void* operator new[](size_t size, std::nothrow_t) noexcept 
{ 
    return operator new(size); // Same as regular new
} 

void operator delete[](void *p,  std::nothrow_t) noexcept 
{ 
    operator delete(p); // Same as regular delete
}

#include "register.h"

Register::Register()
{
    
}

Register::~Register()
{

}

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

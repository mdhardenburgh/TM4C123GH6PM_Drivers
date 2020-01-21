#include "register.h"

Register::Register()
{
    
}

Register::Register(volatile uint32_t* address)
{
    (*this).address = address;
}

Register::~Register()
{

}

void Register::setRegisterAddress(volatile uint32_t* address)
{
    (*this).address = address;
}

volatile uint32_t* Register::getRegisterAddress(void)
{
    return(address);
}

// uint32_t Register::getRegisterBitFieldStatus(bitField* myBitField)
// {
//     if(((*myBitField).permission == RW) || ((*myBitField).permission == RO) || ((*myBitField).permission == RW1C))
//     {
//         uint32_t select = ((((0xFFFFFFFF >> (32 - (*myBitField).bitWidth)))) << (*myBitField).bit);
//         return(((*address) & select) >> (*myBitField).bit);
//     }

//     else
//     {
//         return(UINT32_MAX);
//     }
    
// }

// void Register::setRegisterBitFieldStatus(bitField* myBitField, uint32_t value)
// {
//     if(((*myBitField).permission == RW1C) && (value != 1))
//     {
//         return;
//     }
    
//     else if(((*myBitField).permission == RW) || ((*myBitField).permission == WO) || ((*myBitField).permission == RW1C))
//     {
//         uint32_t maxValue = (0xFFFFFFFF >> (32 - (*myBitField).bitWidth));

//         if((value <= maxValue))
//         {
//             uint32_t clear = (~(maxValue << (*myBitField).bit));
//             value = value << (*myBitField).bit;
    
//             (*address) &= clear;
//             (*address) |= value;
//         }

//         else
//         {
//             return;
//         }
        
//     }

//     else
//     {
//         return;
//     }
    
// }














uint32_t Register::getRegisterBitFieldStatus(bitField myBitField)
{
    if(((myBitField).permission == RW) || ((myBitField).permission == RO) || ((myBitField).permission == RW1C))
    {
        uint32_t select = ((((0xFFFFFFFF >> (32 - myBitField.bitWidth)))) << myBitField.bit);
        return(((*address) & select) >> myBitField.bit);
    }

    else
    {
        return(UINT32_MAX);
    }
    
}

void Register::setRegisterBitFieldStatus(bitField myBitField, uint32_t value)
{
    if((myBitField.permission == RW1C) && (value != 1))
    {
        return;
    }
    
    else if((myBitField.permission == RW) || (myBitField.permission == WO) || (myBitField.permission == RW1C))
    {
        uint32_t maxValue = (0xFFFFFFFF >> (32 - myBitField.bitWidth));

        if((value <= maxValue))
        {
            uint32_t clear = (~(maxValue << myBitField.bit));
            value = value << myBitField.bit;
    
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

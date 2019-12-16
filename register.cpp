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

uint32_t Register::getRegisterBitFieldStatus(uint32_t startBit, uint32_t size, char* permission)
{
    if((permission == (char*)"RW") || (permission == (char*)"RO") || (permission == (char*)"RW1C"))
    {
        uint32_t select = ((((0xFFFFFFFF >> (32 - size)))) << startBit);
        return(((*address) & select) >> startBit);
    }

    else
    {
        return(UINT32_MAX);
    }
    
}

void Register::setRegisterBitFieldStatus(uint32_t value, uint32_t startBit, uint32_t size, char* permission)
{
    if((permission == (char*)"RW1C") && (value != 1))
    {
        return;
    }
    
    else if((permission == (char*)"RW") || (permission == (char*)"WO") || (permission == (char*)"RW1C"))
    {
        uint32_t maxValue = (0xFFFFFFFF >> (32 - size));

        if((value <= maxValue))
        {
            uint32_t clear = (~(maxValue << startBit));
            value = value << startBit;

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

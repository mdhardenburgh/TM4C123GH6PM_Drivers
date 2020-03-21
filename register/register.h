#ifndef REGISTER_H
#define REGISTER_H

#include <stddef.h>
#include <cstdint>
#include <new>
#include <stdlib.h>

using std::uint32_t;

enum setORClear
{
    clear = 0u,
    set = 1u
};

enum bitFieldPermission
{
    RW, RO, WO, RW1C
};

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
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

class bitField
{
    public:
    
        bitField(uint32_t bit, uint32_t bitWidth, bitFieldPermission permission)
        {
            (*this).bit = bit;
            (*this).bitWidth = bitWidth;
            (*this).permission = permission;

            
        }

        ~bitField()
        {
            
        }
        
        uint32_t bit; //bit place
        uint32_t bitWidth; //field size in bit width.
        bitFieldPermission permission; //permission (RW, RO, WO) of the bit/field

};

class Register
{
    public:
        Register();
        Register(volatile uint32_t* address);
        ~Register();

        void setRegisterAddress(volatile uint32_t* address);
        volatile uint32_t* getRegisterAddress(void);
        // uint32_t getRegisterBitFieldStatus(bitField* myBitField);
        // void setRegisterBitFieldStatus(bitField* myBitField, uint32_t value);

        uint32_t getRegisterBitFieldStatus(bitField myBitField);
        void setRegisterBitFieldStatus(bitField myBitField, uint32_t value);

        static uint32_t _getRegisterBitFieldStatus(volatile uint32_t* address, uint32_t bit, uint32_t bitWidth, bitFieldPermission permission);
        static void _setRegisterBitFieldStatus(volatile uint32_t* address, uint32_t value, uint32_t bit, uint32_t bitWidth, bitFieldPermission permission);
    
    protected:
        volatile uint32_t* address;
};

#endif //REGISTER_H
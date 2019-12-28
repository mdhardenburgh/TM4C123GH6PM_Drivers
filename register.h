#ifndef REGISTER_H
#define REGISTER_H

//#include <stddef.h>
#include <cstdint>

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

typedef struct registerBitField
{
    uint32_t bit; //bit place
    uint32_t bitWidth; //field size in bit width.
    bitFieldPermission permission; //permission (RW, RO, WO) of the bit/field

} bitField;

class Register
{
    public:
        Register();
        Register(volatile uint32_t* address);
        ~Register();

        uint32_t getRegisterBitFieldStatus(bitField myBitField);

        void setRegisterBitFieldStatus(bitField myBitField, uint32_t value);
    
    protected:
        volatile uint32_t* address;
};

#endif //REGISTER_H
#ifndef REGISTER_H
#define REGISTER_H

#include <stddef.h>
#include <stdint-gcc.h>

typedef struct registerBitField
{
    uint32_t bit; //bit place
    uint32_t size; //field size in bit width.
    char* permission; //permission (RW, RO, WO) of the bit/field

} bitField;

class Register
{
    public:
        Register();
        Register(volatile uint32_t* address);
        ~Register();

        uint32_t getRegisterBitFieldStatus(uint32_t startBit, uint32_t size, char* permission);

        void setRegisterBitFieldStatus(uint32_t value, uint32_t startBit, uint32_t size, char* permission);
    

    protected:
        volatile uint32_t* address;
};

#endif //REGISTER_H
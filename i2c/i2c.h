/**
 * @file i2c.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/18/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019  Matthew Hardenburgh
 * mdhardenburgh@gmail.com
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
 * 
 * @section DESCRIPTION
 * 
 * Class header for the system control unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Registers provided for legacy software support only are listed 
 * in “System Control Legacy Register Descriptions” on page 424.
 * 
 * Inter-Integrated Circuit (I2C) Interface Register Descriptions
 * 
 */

#ifndef I2C_H
#define I2C_H

#include "../systemControl/systemControl.h"


class I2c
{
    public:
        I2c();
        ~I2c();

    private:

        static const uint32_t i2c0BaseAddress = 0x40020000;
        static const uint32_t i2c1BaseAddress = 0x40021000;
        static const uint32_t i2c2BaseAddress = 0x40022000;
        static const uint32_t i2c3BaseAddress = 0x40023000;

        static const uint32_t PPI2C_OFFSET = 0x320; //0x320 PPI2C RO 0x0000.000F Inter-Integrated Circuit Peripheral Present 299
        static const uint32_t SRI2C_OFFSET = 0x520; //0x520 SRI2C RW 0x0000.0000 Inter-Integrated Circuit Software Reset 322
        static const uint32_t RCGCI2C_OFFSET = 0x620; //0x620 RCGCI2C RW 0x0000.0000 Inter-Integrated Circuit Run Mode Clock Gating Control 348
        static const uint32_t SCGCI2C_OFFSET = 0x720; //0x720 SCGCI2C RW 0x0000.0000 Inter-Integrated Circuit Sleep Mode Clock Gating Control 370
        static const uint32_t DCGCI2C_OFFSET = 0x820; //0x820 DCGCI2C RW 0x0000.0000 Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control 392
        static const uint32_t PRI2C_OFFSET = 0xA20; //0xA20 PRI2C RO 0x0000.0000 Inter-Integrated Circuit Peripheral Ready 414

};

#endif //I2C_H
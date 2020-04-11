/**
 * @file i2c.h
 * @brief TM4C123GH6PM I2C Driver Declaration
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
 * @class I2c
 * @brief TM4C123GH6PM I2c Driver
 * 
 * @section i2cDescription I2C Description
 * 
 * I2c is a common master-slave type bi-directional serial communication 
 * interface used for communication with external devices (such as an ADC, RAM, 
 * ROM, LCDs, etc...). The TM4C123GH6PM microcontroller has 4 I2C modules. Each 
 * module has the following features:
 *      - Devices on the I2C bus can be designated as either a master or a slave
 *          - Supports both transmitting and receiving data as either a master or a slave
 *          - Supports simultaneous master and slave operation
 *      - Four I2C modes
 *          - Master Transmit
 *          - Master Receive
 *          - Slave Transmit
 *          - Slave Recieve
 *      - Four transmission speeds:
 *          - Standard 100Kbps
 *          - Fast-mode 400Kbps
 *          - Fast-mode plus 1Mbps
 *          - High-speed mode 3.33Mbps
 *      - Clock low timeout interrupt
 *      - Dual slave address capability
 *      - Glitch suppression
 *      - Master and slave interrupt generation
 *          - Master generates interrupts when a transmit or receive operation 
 *            completes (or aborts due to an error)
 *          - Slave generates interrupts when data has been transferred or 
 *            requested by a master or when a START or STOP condition is detected
 *      - Master with arbitration and clock synchronization, multimaster support, 
 *        and 7-bit addressing mode
 * 
 * For more detailed information on the ADC please see page 997 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection i2cSignalDescription I2C Signal Description
 * 
 * The following table list the external signals of the I2C interace. The GPIOs
 * must be configured for the I2C alternate function and default to GPIO at 
 * reset. The number parenthesis in the table below in the column Pin Mux/Pin 
 * Assignment is what should be programmed into the \c PMCn field of the GPIO
 * Port Control register to use the pin for I2C. The serial data pin \c I2CSDA 
 * should be set to an open drain using the GPIO Open Drain Select (GPIOODR)
 * register.
 * 
 * @image html i2cSignalPins.png
 * @image latex i2cSignalPins.png
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

        /*
         * I2C Master
         */

        static const uint32_t I2CMSA_OFFSET = 0x000; // 0x000 I2CMSA RW 0x0000.0000 I2C Master Slave Address 1019
        static const uint32_t I2CMCS_OFFSET = 0x004; // 0x004 I2CMCS RW 0x0000.0020 I2C Master Control/Status 1020
        static const uint32_t I2CMDR_OFFSET = 0x008; // 0x008 I2CMDR RW 0x0000.0000 I2C Master Data 1025
        static const uint32_t I2CMTPR_OFFSET = 0x00C; // 0x00C I2CMTPR RW 0x0000.0001 I2C Master Timer Period 1026
        static const uint32_t I2CMIMR_OFFSET = 0x010; // 0x010 I2CMIMR RW 0x0000.0000 I2C Master Interrupt Mask 1027
        static const uint32_t I2CMRIS_OFFSET = 0x014; // 0x014 I2CMRIS RO 0x0000.0000 I2C Master Raw Interrupt Status 1028
        static const uint32_t I2CMMIS_OFFSET = 0x018; // 0x018 I2CMMIS RO 0x0000.0000 I2C Master Masked Interrupt Status 1029
        static const uint32_t I2CMICR_OFFSET = 0x01C; // 0x01C I2CMICR WO 0x0000.0000 I2C Master Interrupt Clear 1030
        static const uint32_t I2CMCR_OFFSET = 0x020; // 0x020 I2CMCR RW 0x0000.0000 I2C Master Configuration 1031
        static const uint32_t I2CMCLKOCNT_OFFSET = 0x024; // 0x024 I2CMCLKOCNT RW 0x0000.0000 I2C Master Clock Low Timeout Count 1033
        static const uint32_t I2CMBMON_OFFSET = 0x02C; // 0x02C I2CMBMON RO 0x0000.0003 I2C Master Bus Monitor 1034
        static const uint32_t I2CMCR2_OFFSET = 0x038; // 0x038 I2CMCR2 RW 0x0000.0000 I2C Master Configuration 2 1035

        /*
         * I2C Slave
         */

        static const uint32_t I2CSOAR_OFFSET = 0x800; // 0x800 I2CSOAR RW 0x0000.0000 I2C Slave Own Address 1036
        static const uint32_t I2CSCSR_OFFSET = 0x804; // 0x804 I2CSCSR RO 0x0000.0000 I2C Slave Control/Status 1037
        static const uint32_t I2CSDR_OFFSET = 0x808; // 0x808 I2CSDR RW 0x0000.0000 I2C Slave Data 1039
        static const uint32_t I2CSIMR_OFFSET = 0x80C; // 0x80C I2CSIMR RW 0x0000.0000 I2C Slave Interrupt Mask 1040
        static const uint32_t I2CSRIS_OFFSET = 0x810; // 0x810 I2CSRIS RO 0x0000.0000 I2C Slave Raw Interrupt Status 1041
        static const uint32_t I2CSMIS_OFFSET = 0x814; // 0x814 I2CSMIS RO 0x0000.0000 I2C Slave Masked Interrupt Status 1042
        static const uint32_t I2CSICR_OFFSET = 0x818; // 0x818 I2CSICR WO 0x0000.0000 I2C Slave Interrupt Clear 1043
        static const uint32_t I2CSOAR2_OFFSET = 0x81C; // 0x81C I2CSOAR2 RW 0x0000.0000 I2C Slave Own Address 2 1044
        static const uint32_t I2CSACKCTL_OFFSET = 0x820; // 0x820 I2CSACKCTL RW 0x0000.0000 I2C Slave ACK Control 1045

        /*
         * I2C Slave
         */

        static const uint32_t I2CPP_OFFSET = 0xFC0; // 0xFC0 I2CPP RO 0x0000.0001 I2C Peripheral Properties 1046
        static const uint32_t I2CPC_OFFSET = 0xFC4; // 0xFC4 I2CPC RO 0x0000.0001 I2C Peripheral Configuration 1047
};

#endif //I2C_H
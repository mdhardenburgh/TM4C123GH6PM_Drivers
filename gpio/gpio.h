/**
 * @file gpio.h
 * @brief TM4C123GH6PM Gpio Driver Declaration
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
 * @class Gpio
 * @brief TM4C123GH6PM GPIO Driver
 * 
 * @section gpioDescription GPIO Module Description
 * 
 * The GPIO module has six physical GPIO blocks, A-F, and each block supports
 * upto 8 pins (with some exceptions noted in the GPIO_Port_Pins enum). There 
 * are 43 programmable GPIOs. 
 * 
 * The GPIOs can be configured for alternate 
 * functions that connect peripherals such as the ADC, USB or SPI to external 
 * physical pins. The peripherals that use external pins each have a list of 
 * Signal Descriptions. 
 * 
 * Below is a list of the features of the GPIO module copied here from the 
 * TM4C123GH6PM datasheet for convienience.
 *      - 5-V-tolerant in input configuration
 *      - Fast toggle capable of a change every clock cycle for ports on AHB, 
 *        every two clock cycles for ports on APB
 *      - Programmable control for GPIO interrupts
 *          - Interrupt generation masking
 *          - Edge-triggered on rising, falling, or both
 *          - Level-sensitive on High or Low values
 *      - Bit masking in both read and write operations through address lines
 *      - Can be used to initiate an ADC sample sequence or a μDMA transfer
 *      - Pin state can be retained during Hibernation mode
 *      - Pins configured as digital inputs are Schmitt-triggered
 *      - Programmable control for GPIO pad configuration
 *          - Weak pull-up or pull-down resistors
 *          - 2-mA, 4-mA, and 8-mA pad drive for digital communication; up to 
 *            four pads can sink 18-mA for high-current applications
 *          - Slew rate control for 8-mA pad drive
 *          - Open drain enables
 *          - Digital input enables
 * 
 * These drivers I have written support only the GPIO AHB, not APB.
 * 
 * For more detailed information on the GPIO please see page 649 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection gpioSignalDescription GPIO Signal Description
 * 
 * The GPIO ports can be to be used by the analog and digital peripherals as 
 * inputs or outputs connecting physical pins to the peripheral. The GPIOs are 
 * 5V tolerant except \c PD4 , \c PD5 , \c PB0 , and \c PB1 which are 3.3V. 
 * Analog signals are all 5V tolerant, but analog performance specs are only
 * guarenteed if the input signal swing at the pad is kept inside range. Pins 
 * are also programmed individually by TI's design and no group programming is
 * implied, unfortuntately. Entries on the table that are grey are default GPIO 
 * values.
 * 
 * @image html gpioSignalPins.png
 * @image latex gpioSignalPins.png
 * 
 * @image html gpioSignalPins2.png
 * @image latex gpioSignalPins2.png
 * 
 * Please note that there are special consideration pins. Most GPIO pins are 
 * configured as GPIOs and tri-stated by default, but there are some pins that
 * are important enough to be automatically configured and protected from 
 * accidental programming. Such pins would be the JTAG/SWD interface, UART and
 * others. The table below, copied from the TM4C123GH6PM datasheet, lists these 
 * pins and warnings when using them. 
 * 
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 * The JTAG/SWD pins can be PERMENTLY configured to disallow JTAG/SWD 
 * programming. Take extreme caution if using these pins!!!!!!!!!!!!!!!
 * 
 * @image html gpioSpecialPins.png
 * @image latex gpioSpecialPins.png
 * 
 * Last, but not least, the TM4C123G Launchpad evaluation kit, EK-TM4C123GXL has
 * GPIOs that are connected to on board LEDs and switches. Below is a table 
 * copied from the TI User's Guide for convenience
 * 
 * @image html gpioLaunchPadSignalPins.png
 * @image latex gpioLaunchPadSignalPins.png
 * 
 * @subsection gpioSystemControlRegisterDescription GPIO System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Legacy registers not supported.
 * 
 * @subsection gpioRegisterDescription GPIO Register Description
 * 
 * The Gpio class contains a list of registers listed as an offset of the 
 * hexadecimal base address of the Gpio AHB Port base address A - F. The
 * legacy APB aperture is not used in this driver. 
 *  
 * Note that the GPIO module clock must be enabled before the registers can be 
 * programmed (see page 340). There must be a delay of 3 system clocks after the 
 * GPIO module clock is enabled before any GPIO module registers are accessed.
 * 
 */



#ifndef GPIO_H
#define GPIO_H

#include "../systemControl/systemControl.h"

static const uint32_t gpioOffset = 100;

enum class PA0 {GPIO = 0 * gpioOffset, U0Rx = 1 + GPIO + 1, CAN1Rx = 8 + GPIO + 1};
enum class PA1 {GPIO = 1 * gpioOffset, U0Tx = 1 + GPIO + 1, CAN1Tx = 8 + GPIO + 1};
enum class PA2 {GPIO = 2 * gpioOffset, SSI0Clk = 2 + GPIO + 1};
enum class PA3 {GPIO = 3 * gpioOffset, SSI0Fss = 2 + GPIO + 1};
enum class PA4 {GPIO = 4 * gpioOffset, SSI0Rx = 2 + GPIO + 1};
enum class PA5 {GPIO = 5 * gpioOffset, SSI0Tx = 2 + GPIO + 1};
enum class PA6 {GPIO = 6 * gpioOffset, I2C1SCL = 3 + GPIO + 1, M1PWM2 = 5 + GPIO + 1};
enum class PA7 {GPIO = 7 * gpioOffset, I2C1SDA = 3 + GPIO + 1, M1PWM3 = 5 + GPIO + 1};
enum class PB0 {GPIO = 8 * gpioOffset, USB0ID = 0 + GPIO + 1, U1Rx = 1 + GPIO + 1, T2CCP0 = 7 + GPIO + 1};
enum class PB1 {GPIO = 9 * gpioOffset, USB0VBUS = 0 + GPIO + 1, U1Tx = 1 + GPIO + 1, T2CCP1 = 7 + GPIO + 1};
enum class PB2 {GPIO = 10 * gpioOffset, I2C0SCL = 3 + GPIO + 1, T3CCP0 = 7 + GPIO + 1};
enum class PB3 {GPIO = 11 * gpioOffset, I2C0SDA = 3 + GPIO + 1, T3CCP1 = 7 + GPIO + 1};
enum class PB4 {GPIO = 12 * gpioOffset, AIN10 = 0 + GPIO + 1, SSI2Clk = 2 + GPIO + 1, M0PWM2 = 4 + GPIO + 1, T1CCP0 = 7 + GPIO + 1, CAN0Rx = 8 + GPIO + 1};
enum class PB5 {GPIO = 13 * gpioOffset, AIN11 = 0 + GPIO + 1, SSI2Fss = 2 + GPIO + 1, M0PWM3 = 4 + GPIO + 1, T1CCP1 = 7 + GPIO + 1, CAN0Tx = 8 + GPIO + 1};
enum class PB6 {GPIO = 14 * gpioOffset, SSI2Rx = 2 + GPIO + 1, M0PWM0 = 4 + GPIO + 1, T0CCP0 = 7 + GPIO + 1};
enum class PB7 {GPIO = 15 * gpioOffset, SSI2Tx = 2 + GPIO + 1, M0PWM1 = 4 + GPIO + 1, T0CCP1 = 7 + GPIO + 1};

/** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 * The JTAG/SWD pins can be PERMENTLY configured to disallow JTAG/SWD 
 * programming. Take extreme caution if using these pins!!!!!!!!!!!!!!!
 * 
 */

// enum class PC0 {GPIO = 16 * gpioOffset, TCK_SWCLK = 1 + GPIO + 1, T4CCP0 = 7 + GPIO + 1};
// enum class PC1 {GPIO = 17 * gpioOffset, TMS_SWDIO = 1 + GPIO + 1, T4CCP1 = 7 + GPIO + 1};
// enum class PC2 {GPIO = 18 * gpioOffset, TDI = 1 + GPIO + 1, T5CCP0 = 7 + GPIO + 1};
// enum class PC3 {GPIO = 19 * gpioOffset, TDO_SWO = 1 + GPIO + 1, T5CCP1 = 7 + GPIO + 1};

enum class PC4 {GPIO = 20 * gpioOffset, C1_MINUS = 0 + GPIO + 1, U4Rx = 1 + GPIO + 1, U1Rx = 2 + GPIO + 1, M0PWM6 = 4 + GPIO + 1, IDX1 = 6 + GPIO + 1, WT0CCP0 = 7 + GPIO + 1, U1RTS = 8 + GPIO + 1};
enum class PC5 {GPIO = 21 * gpioOffset, C1_PLUS = 0 + GPIO + 1, U4Tx = 1 + GPIO + 1, U1Tx = 2 + GPIO + 1, M0PWM7 = 4 + GPIO + 1, PhA1 = 6 + GPIO + 1, WT0CCP1 = 7 + GPIO + 1, U1CTS = 8 + GPIO + 1};
enum class PC6 {GPIO = 22 * gpioOffset, C0_PLUS = 0  + GPIO + 1, U3Rx = 1 + GPIO + 1, PhB1 = 6 + GPIO + 1, WT1CCP0 = 7 + GPIO + 1, USB0EPEN = 8 + GPIO + 1};
enum class PC7 {GPIO = 23 * gpioOffset, C0_MINUS = 0 + GPIO + 1, U3Tx = 1 + GPIO + 1, WT1CCP1 = 7 + GPIO + 1, USB0PFLT = 8 + GPIO + 1};
enum class PD0 {GPIO = 24 * gpioOffset, AIN7 = 0 + GPIO + 1, SSI3Clk = 1 + GPIO + 1, SSI1Clk = 2 + GPIO + 1, I2C3SCL = 3 + GPIO + 1, M0PWM6 = 4 + GPIO + 1, M1PWM0 = 5 + GPIO + 1, WT2CCP0 = 7 + GPIO + 1};
enum class PD1 {GPIO = 25 * gpioOffset, AIN6 = 0 + GPIO + 1, SSI3Fss = 1 + GPIO + 1, SSI1Fss = 2 + GPIO + 1, I2C3SDA = 3 + GPIO + 1, M0PWM7 = 4 + GPIO + 1, M1PWM1 = 5 + GPIO + 1, WT2CCP1 = 7 + GPIO + 1};
enum class PD2 {GPIO = 26 * gpioOffset, AIN5 = 0 + GPIO + 1, SSI3Rx = 1 + GPIO + 1, SSI1Rx = 2 + GPIO + 1, M0FAULT0 = 4 + GPIO + 1, WT3CCP0 = 7 + GPIO + 1, USB0EPEN = 8 + GPIO + 1};
enum class PD3 {GPIO = 27 * gpioOffset, AIN4 = 0 + GPIO + 1, SSI3Tx = 1 + GPIO + 1, SSI1Tx = 2 + GPIO + 1, IDX0 = 6 + GPIO + 1, WT3CCP1 = 7 + GPIO + 1, USB0PFLT = 8 + GPIO + 1};
enum class PD4 {GPIO = 28 * gpioOffset, USB0DM = 0 + GPIO + 1, U6Rx = 1 + GPIO + 1, WT4CCP0 = 8 + GPIO + 1};
enum class PD5 {GPIO = 29 * gpioOffset, USB0DP = 0 + GPIO + 1, U6Tx = 1 + GPIO + 1, WT4CCP1 = 7 + GPIO + 1};
enum class PD6 {GPIO = 30 * gpioOffset, U2Rx = 1 + GPIO + 1, M0FAULT0 = 4 + GPIO + 1, PhA0 = 6 + GPIO + 1, WT5CCP0 = 7 + GPIO + 1};
enum class PD7 {GPIO = 31 * gpioOffset, U2Tx = 1 + GPIO + 1, PhB0 = 6 + GPIO + 1, WT5CCP1 = 7 + GPIO + 1, NMI = 8 + GPIO + 1};
enum class PE0 {GPIO = 32 * gpioOffset, AIN3 = 0 + GPIO + 1, U7Rx = 1 + GPIO + 1};
enum class PE1 {GPIO = 33 * gpioOffset, AIN2 = 0 + GPIO + 1, U7Tx = 1 + GPIO + 1};
enum class PE2 {GPIO = 34 * gpioOffset, AIN1 = 0 + GPIO + 1};
enum class PE3 {GPIO = 35 * gpioOffset, AIN0 = 0 + GPIO + 1};
enum class PE4 {GPIO = 36 * gpioOffset, AIN9 = 0 + GPIO + 1, U5Rx = 1 + GPIO + 1, I2C2SCL = 3 + GPIO + 1, M0PWM4 = 4 + GPIO + 1, M1PWM2 = 5 + GPIO + 1, CAN0Rx = 8 + GPIO + 1};
enum class PE5 {GPIO = 37 * gpioOffset, AIN8 = 0 + GPIO + 1, U5Tx = 1 + GPIO + 1, I2C2SDA = 3 + GPIO + 1, M0PWM5 = 4 + GPIO + 1, M1PWM3 = 5 + GPIO + 1, CAN0Tx = 8 + GPIO + 1};
// enum class PE6 {GPIO = 38 * gpioOffset}; // There is no PE6 on the microcontroller, only added for completeness.
// enum class PE7 {GPIO = 39 * gpioOffset}; // There is no PE7 on the microcontroller, only added for completeness.
enum class PF0 {GPIO = 40 * gpioOffset, U1RTS = 1 + GPIO + 1, SSI1Rx = 2 + GPIO + 1, CAN0Rx = 3 + GPIO + 1, M1PWM4 = 5 + GPIO + 1, PhA0 = 6 + GPIO + 1, T0CCP0 = 7 + GPIO + 1, NMI = 8 + GPIO + 1, C0o = 9 + GPIO + 1};
enum class PF1 {GPIO = 41 * gpioOffset, U1CTS = 1 + GPIO + 1, SSI1Tx = 2 + GPIO + 1, M1PWM5 = 5 + GPIO + 1, PhB0 = 6 + GPIO + 1, T0CCP1 = 7 + GPIO + 1, C1o = 9 + GPIO + 1, TRD1 = 14 + GPIO + 1};
enum class PF2 {GPIO = 42 * gpioOffset, SSI1Clk = 2 + GPIO + 1, M0FAULT0 = 4 + GPIO + 1, M1PWM6 = 5 + GPIO + 1, T1CCP0 = 7 + GPIO + 1, TRD0 = 14 + GPIO + 1};
enum class PF3 {GPIO = 43 * gpioOffset, SSI1Fss = 2 + GPIO + 1, CAN0Tx = 3 + GPIO + 1, M1PWM7 = 5 + GPIO + 1, T1CCP1 = 7 + GPIO + 1, TRCLK = 14 + GPIO + 1};
enum class PF4 {GPIO = 44 * gpioOffset, M1FAULT0 = 5 + GPIO + 1, IDX0 = 6 + GPIO + 1, T2CCP0 = 7 + GPIO + 1, USB0EPEN = 8 + GPIO + 1};
// enum class PF5 {GPIO = 45 * gpioOffset}; // There is no PF5 on the microcontroller, only added for completeness.
// enum class PF6 {GPIO = 46 * gpioOffset}; // There is no PF6 on the microcontroller, only added for completeness.
// enum class PF7 {GPIO = 47 * gpioOffset}; // There is no PF7 on the microcontroller, only added for completeness.

/**
 * Direction of the signal, i.e. if the gpio acts as an input or output.
 */
enum direction
{
    input, output
};

class Gpio
{
    public:
        Gpio();
        ~Gpio();

        void initialize(uint32_t gpio, direction dir);
        void initialize(uint32_t gpio, direction dir, uint32_t interruptPriority);
        void interruptClear();
        void write(uint32_t value);
        uint32_t read();

    private:

        uint32_t gpio;
        direction dir;
        uint32_t interruptPriority;
        int alternateFunction = -1; //This value should cause an error

        uint32_t baseAddress;
        uint32_t gpioPort;

        static const uint32_t gpioKey = 0x4C4F434B;

        static const uint32_t PPGPIO_OFFSET = 0x308; //0x308 PPGPIO RO 0x0000.003F General-Purpose Input/Output Peripheral Present 290
        static const uint32_t SRGPIO_OFFSET = 0x508; //0x508 SRGPIO RW 0x0000.0000 General-Purpose Input/Output Software Reset 314
        static const uint32_t RCGCGPIO_OFFSET = 0x608; //0x608 RCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Run Mode Clock Gating Control 340
        static const uint32_t SCGCGPIO_OFFSET = 0x708; //0x708 SCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Sleep Mode Clock Gating Control 362
        static const uint32_t DCGCGPIO_OFFSET = 0x808; //0x808 DCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control 384
        static const uint32_t PRGPIO_OFFSET = 0xA08; //0xA08 PRGPIO RO 0x0000.0000 General-Purpose Input/Output Peripheral Ready 406

        static const uint32_t GPIO_Port_AHB_BASE = 0x40058000;

        static const uint32_t GPIODATA_OFFSET = 0x3FC; // 0x000 GPIODATA RW 0x0000.0000 GPIO Data 662
        static const uint32_t GPIODIR_OFFSET = 0x400; // 0x400 GPIODIR RW 0x0000.0000 GPIO Direction 663
        static const uint32_t GPIOAFSEl_OFFSET = 0x420; // 0x420 GPIOAFSEL RW - GPIO Alternate Function Select 671
        static const uint32_t GPIOPUR_OFFSET = 0x510; // 0x510 GPIOPUR RW - GPIO Pull-Up Select 677
        static const uint32_t GPIODEN_OFFSET = 0x51C; // 0x51C GPIODEN RW - GPIO Digital Enable 682
        static const uint32_t GPIOLOCK_OFFSET = 0x520; // 0x520 GPIOLOCK RW 0x0000.0001 GPIO Lock 684
        static const uint32_t GPIOCR_OFFSET = 0x524; // 0x524 GPIOCR - - GPIO Commit 685
        static const uint32_t GPIOAMSEL_OFFSET = 0x528; // 0x528 GPIOAMSEL RW 0x0000.0000 GPIO Analog Mode Select 687
        static const uint32_t GPIOPCTL_OFFSET = 0x52C; // 0x52C GPIOPCTL RW - GPIO Port Control 688
        static const uint32_t GPIOIM_OFFSET = 0x410; // 0x410 GPIOIM RW 0x0000.0000 GPIO Interrupt Mask 667
        static const uint32_t GPIOIS_OFFSET = 0x404; // 0x404 GPIOIS RW 0x0000.0000 GPIO Interrupt Sense 664
        static const uint32_t GPIOIBE_OFFSET = 0x408; // 0x408 GPIOIBE RW 0x0000.0000 GPIO Interrupt Both Edges 665
        static const uint32_t GPIOIEV_OFFSET = 0x40C; // 0x40C GPIOIEV RW 0x0000.0000 GPIO Interrupt Event 666
        static const uint32_t GPIORIS_OFFSET = 0x414; // 0x414 GPIORIS RO 0x0000.0000 GPIO Raw Interrupt Status 668
        static const uint32_t GPIOMIS_OFFSET = 0x418; // 0x418 GPIOMIS RO 0x0000.0000 GPIO Masked Interrupt Status 669
        static const uint32_t GPIOICR_OFFSET = 0x41C; // 0x41C GPIOICR W1C 0x0000.0000 GPIO Interrupt Clear 670
        static const uint32_t GPIODR2R_OFFSET = 0x500; // 0x500 GPIODR2R RW 0x0000.00FF GPIO 2-mA Drive Select 673
        static const uint32_t GPIODR4R_OFFSET = 0x504; // 0x504 GPIODR4R RW 0x0000.0000 GPIO 4-mA Drive Select 674
        static const uint32_t GPIODR8R_OFFSET = 0x508; // 0x508 GPIODR8R RW 0x0000.0000 GPIO 8-mA Drive Select 675
        static const uint32_t GPIOODR_OFFSET = 0x50C; // 0x50C GPIOODR RW 0x0000.0000 GPIO Open Drain Select 676
        static const uint32_t GPIOPDR_OFFSET = 0x514; // 0x514 GPIOPDR RW 0x0000.0000 GPIO Pull-Down Select 679
        static const uint32_t GPIOSLR_OFFSET = 0x518; // 0x518 GPIOSLR RW 0x0000.0000 GPIO Slew Rate Control Select 681
        static const uint32_t GPIOADCCTL_OFFSET = 0x530; // 0x530 GPIOADCCTL RW 0x0000.0000 GPIO ADC Control 690
        static const uint32_t GPIODMACTL_OFFSET = 0x534; // 0x534 GPIODMACTL RW 0x0000.0000 GPIO DMA Control 691
        static const uint32_t GPIOPeriphID4_OFFSET = 0xFD0; // 0xFD0 GPIOPeriphID4 RO 0x0000.0000 GPIO Peripheral Identification 4 692
        static const uint32_t GPIOPeriphID5_OFFSET = 0xFD4; // 0xFD4 GPIOPeriphID5 RO 0x0000.0000 GPIO Peripheral Identification 5 693
        static const uint32_t GPIOPeriphID6_OFFSET = 0xFD8; // 0xFD8 GPIOPeriphID6 RO 0x0000.0000 GPIO Peripheral Identification 6 694
        static const uint32_t GPIOPeriphID7_OFFSET = 0xFDC; // 0xFDC GPIOPeriphID7 RO 0x0000.0000 GPIO Peripheral Identification 7 695
        static const uint32_t GPIOPeriphID0_OFFSET = 0xFE0; // 0xFE0 GPIOPeriphID0 RO 0x0000.0061 GPIO Peripheral Identification 0 696
        static const uint32_t GPIOPeriphID1_OFFSET = 0xFE4; // 0xFE4 GPIOPeriphID1 RO 0x0000.0000 GPIO Peripheral Identification 1 697
        static const uint32_t GPIOPeriphID2_OFFSET = 0xFE8; // 0xFE8 GPIOPeriphID2 RO 0x0000.0018 GPIO Peripheral Identification 2 698
        static const uint32_t GPIOPeriphID3_OFFSET = 0xFEC; // 0xFEC GPIOPeriphID3 RO 0x0000.0001 GPIO Peripheral Identification 3 699
        static const uint32_t GPIOPCellID0_OFFSET = 0xFF0; // 0xFF0 GPIOPCellID0 RO 0x0000.000D GPIO PrimeCell Identification 0 700
        static const uint32_t GPIOPCellID1_OFFSET = 0xFF4; // 0xFF4 GPIOPCellID1 RO 0x0000.00F0 GPIO PrimeCell Identification 1 701
        static const uint32_t GPIOPCellID2_OFFSET = 0xFF8; // 0xFF8 GPIOPCellID2 RO 0x0000.0005 GPIO PrimeCell Identification 2 702
        static const uint32_t GPIOPCellID3_OFFSET = 0xFFC; // 0xFFC GPIOPCellID3 RO 0x0000.00B1 GPIO PrimeCell Identification 3 703

};

#endif //GPIO_H
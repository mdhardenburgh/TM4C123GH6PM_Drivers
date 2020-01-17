/**
 * @file gpio.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/24/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019 Matthew Hardenburgh
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
 * Class header of the GPIO for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM.
 * 
 * The standard Tiva C devboard has the following pins connect to the switches
 * and LEDs
 * _____________________________________________
 * | GPIO Pin | Pin Function |     Device      |
 * |----------|--------------|-----------------|
 * |   PF4    |     GPIO     |       SW1       |
 * |----------|--------------|-----------------|
 * |   PF0    |     GPIO     |       SW2       |
 * |----------|--------------|-----------------|
 * |   PF1    |     GPIO     |  RGB LED (Red)  |
 * |----------|--------------|-----------------|
 * |   PF2    |     GPIO     |  RGB LED (Blue) |
 * |----------|--------------|-----------------|
 * |   PF3    |     GPIO     | RGB LED (Green) |
 * |----------|--------------|-----------------|
 * 
 * The table below shows special consideration GPIO pins. Most GPIO pins are 
 * configured as GPIOs and tri-stated by default (GPIOAFSEL=0, GPIODEN=0, 
 * GPIOPDR=0, GPIOPUR=0, and GPIOPCTL=0). Special consideration pins may be 
 * programed to a non-GPIO function or may have special commit controls out of 
 * reset. In addition, a Power-On-Reset (POR) or asserting RST returns these 
 * GPIO to their original special consideration state.
 * 
 * ____________________________
 * | GPIO Pin | Default Reset |
 * |          |     State     |
 * |----------|---------------|
 * |  PA[1:0] |     UART0     |
 * |----------|---------------|
 * |  PA[5:2] |     SSI0      |
 * |----------|---------------|
 * |  PB[3:2] |     I2C0      |
 * |----------|---------------|
 * |  PC[3:0] |    JTAG/SWD   |
 * |----------|---------------|
 * |   PD[7]  |     GPIO      |
 * |----------|---------------|
 * |   PF[0]  |     GPIO      |
 * |----------|---------------|
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include "../systemControl/systemControl.h"

enum direction
{
    input, output
};

enum GPIO_Port_Pins
{
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
    PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
    PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7,
    PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, //There is no PE6 or PE7
    PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7  //There is no PF5, PF6, or PF7
};

class Gpio
{
    public:
        Gpio();
        Gpio(GPIO_Port_Pins gpio, direction dir);
        Gpio(GPIO_Port_Pins gpio, direction dir, uint32_t interruptPriority);
        ~Gpio();

        void interruptClear(void);

        void gpioWrite(setORClear value);
        uint32_t gpioRead(void);

    private:

        GPIO_Port_Pins gpio = PA0;
        uint32_t gpioBaseAddress;
        uint32_t gpioPin;

        uint32_t gpioKey = 0x4C4F434B;

        const uint32_t PPGPIO_OFFSET = 0x308; //0x308 PPGPIO RO 0x0000.003F General-Purpose Input/Output Peripheral Present 290
        const uint32_t SRGPIO_OFFSET = 0x508; //0x508 SRGPIO RW 0x0000.0000 General-Purpose Input/Output Software Reset 314
        const uint32_t RCGCGPIO_OFFSET = 0x608; //0x608 RCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Run Mode Clock Gating Control 340
        const uint32_t SCGCGPIO_OFFSET = 0x708; //0x708 SCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Sleep Mode Clock Gating Control 362
        const uint32_t DCGCGPIO_OFFSET = 0x808; //0x808 DCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control 384
        const uint32_t PRGPIO_OFFSET = 0xA08; //0xA08 PRGPIO RO 0x0000.0000 General-Purpose Input/Output Peripheral Ready 406

        const uint32_t GPIO_Port_AHB_BASE = 0x40058000;

        const uint32_t GPIODATA_OFFSET = 0x3FC; // 0x000 GPIODATA RW 0x0000.0000 GPIO Data 662
        const uint32_t GPIODIR_OFFSET = 0x400; // 0x400 GPIODIR RW 0x0000.0000 GPIO Direction 663
        const uint32_t GPIOAFSEl_OFFSET = 0x420; // 0x420 GPIOAFSEL RW - GPIO Alternate Function Select 671
        const uint32_t GPIOPUR_OFFSET = 0x510; // 0x510 GPIOPUR RW - GPIO Pull-Up Select 677
        const uint32_t GPIODEN_OFFSET = 0x51C; // 0x51C GPIODEN RW - GPIO Digital Enable 682
        const uint32_t GPIOLOCK_OFFSET = 0x520; // 0x520 GPIOLOCK RW 0x0000.0001 GPIO Lock 684
        const uint32_t GPIOCR_OFFSET = 0x524; // 0x524 GPIOCR - - GPIO Commit 685
        const uint32_t GPIOAMSEL_OFFSET = 0x528; // 0x528 GPIOAMSEL RW 0x0000.0000 GPIO Analog Mode Select 687
        const uint32_t GPIOPCTL_OFFSET = 0x52C; // 0x52C GPIOPCTL RW - GPIO Port Control 688
        const uint32_t GPIOIM_OFFSET = 0x410; // 0x410 GPIOIM RW 0x0000.0000 GPIO Interrupt Mask 667
        const uint32_t GPIOIS_OFFSET = 0x404; // 0x404 GPIOIS RW 0x0000.0000 GPIO Interrupt Sense 664
        const uint32_t GPIOIBE_OFFSET = 0x408; // 0x408 GPIOIBE RW 0x0000.0000 GPIO Interrupt Both Edges 665
        const uint32_t GPIOIEV_OFFSET = 0x40C; // 0x40C GPIOIEV RW 0x0000.0000 GPIO Interrupt Event 666
        const uint32_t GPIORIS_OFFSET = 0x414; // 0x414 GPIORIS RO 0x0000.0000 GPIO Raw Interrupt Status 668
        const uint32_t GPIOMIS_OFFSET = 0x418; // 0x418 GPIOMIS RO 0x0000.0000 GPIO Masked Interrupt Status 669
        const uint32_t GPIOICR_OFFSET = 0x41C; // 0x41C GPIOICR W1C 0x0000.0000 GPIO Interrupt Clear 670
        const uint32_t GPIODR2R = 0x500;
        const uint32_t GPIODR4R = 0x504;
        const uint32_t GPIODR8R = 0x508;
        const uint32_t GPIOODR = 0x50C;
        const uint32_t GPIOPDR = 0x514;
        const uint32_t GPIOSLR = 0x518;
        const uint32_t GPIOADCCTL = 0x530;
        const uint32_t GPIODMACTL = 0x534;
        const uint32_t GPIOPeriphID4 = 0xFD0;
        const uint32_t GPIOPeriphID5 = 0xFD4;
        const uint32_t GPIOPeriphID6 = 0xFD8;
        const uint32_t GPIOPeriphID7 = 0xFDC;
        const uint32_t GPIOPeriphID0 = 0xFE0;
        const uint32_t GPIOPeriphID1 = 0xFE4;
        const uint32_t GPIOPeriphID2 = 0xFE8;
        const uint32_t GPIOPeriphID3 = 0xFEC;
        const uint32_t GPIOPCellID0 = 0xFF0;
        const uint32_t GPIOPCellID1 = 0xFF4;
        const uint32_t GPIOPCellID2 = 0xFF8;
        const uint32_t GPIOPCellID3 = 0xFFC;
        

        Register* RCGCGPIO; //0x608 RCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Run Mode Clock Gating Control 340
        Register* PRGPIO; //0xA08 PRGPIO RO 0x0000.0000 General-Purpose Input/Output Peripheral Ready 406

        Register* GPIOAFSEL; // 0x420 GPIOAFSEL RW - GPIO Alternate Function Select 671
        Register* GPIOPUR; // 0x510 GPIOPUR RW - GPIO Pull-Up Select 677
        Register* GPIODEN; // 0x51C GPIODEN RW - GPIO Digital Enable 682
        Register* GPIOLOCK; // 0x520 GPIOLOCK RW 0x0000.0001 GPIO Lock 684
        Register* GPIOCR; // 0x524 GPIOCR - - GPIO Commit 685
        Register* GPIOAMSEL; // 0x528 GPIOAMSEL RW 0x0000.0000 GPIO Analog Mode Select 687
        Register* GPIOPCTL; // 0x52C GPIOPCTL RW - GPIO Port Control 688
        Register* GPIODIR; // 0x400 GPIODIR RW 0x0000.0000 GPIO Direction 663

        Register* GPIOICR; // 0x41C GPIOICR W1C 0x0000.0000 GPIO Interrupt Clear 670
        Register* GPIO_Port_GPIODATA; // 0x000 GPIODATA RW 0x0000.0000 GPIO Data 662

        Register* GPIOIM; // 0x410 GPIOIM RW 0x0000.0000 GPIO Interrupt Mask 667
        Register* GPIOIS; // 0x404 GPIOIS RW 0x0000.0000 GPIO Interrupt Sense 664
        Register* GPIOIBE; // 0x408 GPIOIBE RW 0x0000.0000 GPIO Interrupt Both Edges 665
        Register* GPIOIEV; // 0x40C GPIOIEV RW 0x0000.0000 GPIO Interrupt Event 666
        Register* GPIORIS; // 0x414 GPIORIS RO 0x0000.0000 GPIO Raw Interrupt Status 668

        Register* GPIO_Port_GPIODR2R; // 0x500 GPIODR2R RW 0x0000.00FF GPIO 2-mA Drive Select 673
        Register* GPIO_Port_GPIODR4R; // 0x504 GPIODR4R RW 0x0000.0000 GPIO 4-mA Drive Select 674
        Register* GPIO_Port_GPIODR8R; // 0x508 GPIODR8R RW 0x0000.0000 GPIO 8-mA Drive Select 675
        Register* GPIO_Port_GPIOODR; // 0x50C GPIOODR RW 0x0000.0000 GPIO Open Drain Select 676
        Register* GPIO_Port_GPIOPDR; // 0x514 GPIOPDR RW 0x0000.0000 GPIO Pull-Down Select 679
        Register* GPIO_Port_GPIOSLR; // 0x518 GPIOSLR RW 0x0000.0000 GPIO Slew Rate Control Select 681
        Register* GPIO_Port_GPIOADCCTL ;// 0x530 GPIOADCCTL RW 0x0000.0000 GPIO ADC Control 690
        Register* GPIO_Port_GPIODMACTL; // 0x534 GPIODMACTL RW 0x0000.0000 GPIO DMA Control 691
        Register* GPIO_Port_GPIOPeriphID4; // 0xFD0 GPIOPeriphID4 RO 0x0000.0000 GPIO Peripheral Identification 4 692
        Register* GPIO_Port_GPIOPeriphID5; // 0xFD4 GPIOPeriphID5 RO 0x0000.0000 GPIO Peripheral Identification 5 693
        Register* GPIO_Port_GPIOPeriphID6; // 0xFD8 GPIOPeriphID6 RO 0x0000.0000 GPIO Peripheral Identification 6 694
        Register* GPIO_Port_GPIOPeriphID7; // 0xFDC GPIOPeriphID7 RO 0x0000.0000 GPIO Peripheral Identification 7 695
        Register* GPIO_Port_GPIOPeriphID0; // 0xFE0 GPIOPeriphID0 RO 0x0000.0061 GPIO Peripheral Identification 0 696
        Register* GPIO_Port_GPIOPeriphID1; // 0xFE4 GPIOPeriphID1 RO 0x0000.0000 GPIO Peripheral Identification 1 697
        Register* GPIO_Port_GPIOPeriphID2; // 0xFE8 GPIOPeriphID2 RO 0x0000.0018 GPIO Peripheral Identification 2 698
        Register* GPIO_Port_GPIOPeriphID3; // 0xFEC GPIOPeriphID3 RO 0x0000.0001 GPIO Peripheral Identification 3 699    
        Register* GPIO_Port_GPIOPCellID0; // 0xFF0 GPIOPCellID0 RO 0x0000.000D GPIO PrimeCell Identification 0 700
        Register* GPIO_Port_GPIOPCellID1; // 0xFF4 GPIOPCellID1 RO 0x0000.00F0 GPIO PrimeCell Identification 1 701
        Register* GPIO_Port_GPIOPCellID2; // 0xFF8 GPIOPCellID2 RO 0x0000.0005 GPIO PrimeCell Identification 2 702
        Register* GPIO_Port_GPIOPCellID3; // 0xFFC GPIOPCellID3 RO 0x0000.00B1 GPIO PrimeCell Identification 3 703

        bitField GPIODATA_DATA{0, 1, RW}; //GPIO Data. 

        bitField GPIODIR_DIR{0, 1, RW}; //GPIO Data Direction. 

        bitField PPGPIO_Pn{0, 1, RO}; //GPIO Port n Present

        bitField SRGPIO_Rn{0, 1, RW}; //GPIO Port n Software Reset

        bitField RCGCGPIO_Rn{0, 1, RW}; //GPIO Port n Run Mode Clock Gating Control

        bitField SCGCGPIO_Sn{0, 1, RW}; //GPIO Port n Sleep Mode Clock Gating Control

        bitField DCGCGPIO_Dn{0, 1, RW}; //GPIO Port n Deep-Sleep Mode Clock Gating Control

        bitField PRGPIO_Rn{0, 1, RO}; //GPIO Port n Peripheral Ready

        bitField GPIOAFSEL_AFSEL{0, 1, RW}; //GPIO Alternate Function Select

        bitField GPIOLOCK_LOCK{0, 32, RW}; //GPIO Lock. A write of the value 0x4C4F.434B unlocks the GPIO Commit (GPIOCR) register for write access.

        bitField GPIOCR_CR{0, 1, RW}; //GPIO Commit

        bitField GPIODEN_DEN{0, 1, RW}; //Digital Enable

        bitField GPIOAMSEL_GPIOAMSEL{0, 1, RW}; //GPIO Analog Mode Select

        bitField GPIOPUR_PUE{0, 1, RW}; //Pad Weak Pull-Up Enable

        bitField GPIOIS_IS{0, 1, RW}; //GPIO Interrupt Sense. 

        bitField GPIOIBE_IBE{0, 1, RW}; //GPIO Interrupt Both Edges. 

        bitField GPIOIEV_IEV{0, 1, RW}; //GPIO Interrupt Event.

        bitField GPIOIM_IME{0, 1, RW}; //GPIO Interrupt Mask Enable

        bitField GPIORIS_RIS{0, 1, RW}; //GPIO Interrupt Raw Status

        bitField GPIOMIS_MIS{0, 1, RW}; //GPIO Masked Interrupt Status

        bitField GPIOICR_IC{0, 1, RW}; //GPIO Interrupt Clear

        bitField GPIODR2R_DRV2{0, 1, RW}; //Output Pad 2-mA Drive Enable

        bitField GPIODR4R_DRV4{0, 1, RW}; //Output Pad 4-mA Drive Enable

        bitField GPIODR8R_DRV8{0, 1, RW}; //Output Pad 8-mA Drive Enable

        bitField GPIOODR_ODE{0, 1, RW}; //Output Pad Open Drain Enable


        bitField GPIOPDR_PDE{0, 1, RW}; //Pad Weak Pull-Down Enable

        bitField GPIOSLR_SRL{0, 1, RW}; //Slew Rate Limit Enable (8-mA drive only)

        bitField GPIOPCTL_PMC7{28, 4, RW}; //Port Mux Control 7. This field controls the configuration for GPIO pin 7.
        bitField GPIOPCTL_PMC6{24, 4, RW}; //Port Mux Control 6. This field controls the configuration for GPIO pin 6.
        bitField GPIOPCTL_PMC5{20, 4, RW}; //Port Mux Control 5. This field controls the configuration for GPIO pin 5.
        bitField GPIOPCTL_PMC4{16, 4, RW}; //Port Mux Control 4. This field controls the configuration for GPIO pin 4.
        bitField GPIOPCTL_PMC3{12, 4, RW}; //Port Mux Control 3. This field controls the configuration for GPIO pin 3.
        bitField GPIOPCTL_PMC2{8, 4, RW}; //Port Mux Control 2. This field controls the configuration for GPIO pin 2.
        bitField GPIOPCTL_PMC1{4, 4, RW}; //Port Mux Control 1. This field controls the configuration for GPIO pin 1.
        bitField GPIOPCTL_PMC0{0, 4, RW}; //Port Mux Control 0. This field controls the configuration for GPIO pin 0.

        bitField GPIOADCCTL_ADCEN{0, 1, RW}; //ADC Trigger Enable

        bitField GPIODMACTL_DMAEN{0, 1, RW}; //μDMA Trigger Enable

        bitField GPIOPeriphID4_PID4{0, 8, RO}; //GPIO Peripheral ID Register [7:0]
        bitField GPIOPeriphID5_PID5{0, 8, RO}; //GPIO Peripheral ID Register [15:8]
        bitField GPIOPeriphID6_PID6{0, 8, RO}; //GPIO Peripheral ID Register [23:16]
        bitField GPIOPeriphID7_PID7{0, 8, RO}; //GPIO Peripheral ID Register [31:24]

        bitField GPIOPeriphID0_PID0{0, 8, RO}; //GPIO Peripheral ID Register [7:0]. Can be used by software to identify the presence of this peripheral.
        bitField GPIOPeriphID1_PID1{0, 8, RO}; //GPIO Peripheral ID Register [15:8]
        bitField GPIOPeriphID2_PID2{0, 8, RO}; //GPIO Peripheral ID Register [23:16]
        bitField GPIOPeriphID3_PID3{0, 8, RO}; //GPIO Peripheral ID Register [31:24]

        bitField GPIOPCellID0_CID0{0, 8, RO}; //GPIO PrimeCell ID Register [7:0]
        bitField GPIOPCellID1_CID1{0, 8, RO}; //GPIO PrimeCell ID Register [15:8]
        bitField GPIOPCellID2_CID2{0, 8, RO}; //GPIO PrimeCell ID Register [23:16]
        bitField GPIOPCellID3_CID3{0, 8, RO}; //GPIO PrimeCell ID Register [31:24]

        Nvic* myNvic;

};

#endif //GPIO_H
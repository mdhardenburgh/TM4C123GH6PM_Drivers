/**
 * @file gpioControl.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/17/2019
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
 * Class header of the GPIO module for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Register Descriptions
 * 
 * All system control register addresses given are relative to the base address of 
 * 0x400F.E000. Registers provided for legacy software support only are listed 
 * in “System Control Legacy Register Descriptions” on pag0x4000.4000e 424.
 * 
 * GPIO Register Descriptions
 * 
 * The remainder of this section lists and describes the GPIO registers, address
 * offset.
 * 
 */

#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include "../systemControl/systemControl.h"

enum GPIO_Port_Pins
{
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
    PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
    PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7,
    PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, //There is no PE6 or PE7
    PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7  //There is no PF5, PF6, or PF7
};


class GpioControl
{
    public: 
        GpioControl();
        ~GpioControl();

    protected:


        //const uint32_t GPIO_Port_A_APB = 0x40004000;
        const uint32_t GPIO_Port_A_AHB = 0x40058000; 
        //const uint32_t GPIO_Port_B_APB = 0x40005000;
        const uint32_t GPIO_Port_B_AHB = 0x40059000;
        //const uint32_t GPIO_Port_C_APB = 0x40006000;
        const uint32_t GPIO_Port_C_AHB = 0x4005A000;
        //const uint32_t GPIO_Port_D_APB = 0x40007000;
        const uint32_t GPIO_Port_D_AHB = 0x4005B000;
        //const uint32_t GPIO_Port_E_APB = 0x40024000;
        const uint32_t GPIO_Port_E_AHB = 0x4005C000;
        //const uint32_t GPIO_Port_F_APB = 0x40025000;
        const uint32_t GPIO_Port_F_AHB = 0x4005D000;
        const uint32_t GPIO_PORT_AHB[6] = {GPIO_Port_A_AHB, GPIO_Port_B_AHB, GPIO_Port_C_AHB, GPIO_Port_D_AHB, GPIO_Port_E_AHB, GPIO_Port_F_AHB};

        const uint32_t GPIOAFSEl = 0x420;
        const uint32_t GPIOPUR = 0x510;
        const uint32_t GPIODEN = 0x51C;
        const uint32_t GPIOLOCK = 0x520;
        const uint32_t GPIOCR = 0x524;
        const uint32_t GPIOAMSEL = 0x528;
        const uint32_t GPIOPCTL = 0x52C;
        

        Register PPGPIO{(volatile uint32_t*)(systemControlBase + 0x308)}; //0x308 PPGPIO RO 0x0000.003F General-Purpose Input/Output Peripheral Present 290
        Register SRGPIO{(volatile uint32_t*)(systemControlBase + 0x508)};//0x508 SRGPIO RW 0x0000.0000 General-Purpose Input/Output Software Reset 314
        Register RCGCGPIO{(volatile uint32_t*)(systemControlBase + 0x608)}; //0x608 RCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Run Mode Clock Gating Control 340
        Register SCGCGPIO{(volatile uint32_t*)(systemControlBase + 0x708)}; //0x708 SCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Sleep Mode Clock Gating Control 362
        Register DCGCGPIO{(volatile uint32_t*)(systemControlBase + 0x808)}; //0x808 DCGCGPIO RW 0x0000.0000 General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control 384
        Register PRGPIO{(volatile uint32_t*)(systemControlBase + 0xA08)}; //0xA08 PRGPIO RO 0x0000.0000 General-Purpose Input/Output Peripheral Ready 406


        //alternate function register here
        Register GPIO_Port_GPIOAFSEL{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOAFSEl)}; // 0x420 GPIOAFSEL RW - GPIO Alternate Function Select 671
        Register GPIO_Port_GPIOPUR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPUR)}; // 0x510 GPIOPUR RW - GPIO Pull-Up Select 677
        Register GPIO_Port_GPIODEN{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODEN)}; // 0x51C GPIODEN RW - GPIO Digital Enable 682
        Register GPIO_Port_GPIOLOCK{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOLOCK)}; // 0x520 GPIOLOCK RW 0x0000.0001 GPIO Lock 684
        Register GPIO_Port_GPIOCR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOCR)}; // 0x524 GPIOCR - - GPIO Commit 685
        Register GPIO_Port_GPIOAMSEL{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOAMSEL)}; // 0x528 GPIOAMSEL RW 0x0000.0000 GPIO Analog Mode Select 687
        Register GPIO_Port_GPIOPCTL{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPCTL)}; // 0x52C GPIOPCTL RW - GPIO Port Control 688

   
        /**************************System Control BitFields****************************/

        // bitField PPGPIO_P14{14, 1, RO}; //GPIO Port Q Present
        // bitField PPGPIO_P13{13, 1, RO}; //GPIO Port P Present
        // bitField PPGPIO_P12{12, 1, RO}; //GPIO Port N Present
        // bitField PPGPIO_P11{11, 1, RO}; //GPIO Port M Present
        // bitField PPGPIO_P10{10, 1, RO}; //GPIO Port L Present
        // bitField PPGPIO_P9{9, 1, RO}; //GPIO Port K Present
        // bitField PPGPIO_P8{8, 1, RO}; //GPIO Port J Present
        // bitField PPGPIO_P7{7, 1, RO}; //GPIO Port H Present
        // bitField PPGPIO_P6{6, 1, RO}; //GPIO Port G Present
        bitField PPGPIO_P5{5, 1, RO}; //GPIO Port F Present
        bitField PPGPIO_P4{4, 1, RO}; //GPIO Port E Present
        bitField PPGPIO_P3{3, 1, RO}; //GPIO Port D Present
        bitField PPGPIO_P2{2, 1, RO}; //GPIO Port C Present
        bitField PPGPIO_P1{1, 1, RO}; //GPIO Port B Present
        bitField PPGPIO_P0{0, 1, RO}; //GPIO Port A Present
        bitField PPGPIO_PRESENT[6] = {PPGPIO_P0, PPGPIO_P1, PPGPIO_P2, PPGPIO_P3, PPGPIO_P4, PPGPIO_P5};

        bitField SRGPIO_R5{5, 1, RW}; //GPIO Port F Software Reset
        bitField SRGPIO_R4{4, 1, RW}; //GPIO Port E Software Reset
        bitField SRGPIO_R3{3, 1, RW}; //GPIO Port D Software Reset
        bitField SRGPIO_R2{2, 1, RW}; //GPIO Port C Software Reset
        bitField SRGPIO_R1{1, 1, RW}; //GPIO Port B Software Reset
        bitField SRGPIO_R0{0, 1, RW}; //GPIO Port A Software Reset
        bitField SRGPIO_REG[6]= {SRGPIO_R0, SRGPIO_R1, SRGPIO_R2, SRGPIO_R3, SRGPIO_R4, SRGPIO_R5};

        bitField RCGCGPIO_R5{5, 1, RW}; //GPIO Port F Run Mode Clock Gating Control
        bitField RCGCGPIO_R4{4, 1, RW}; //GPIO Port E Run Mode Clock Gating Control
        bitField RCGCGPIO_R3{3, 1, RW}; //GPIO Port D Run Mode Clock Gating Control
        bitField RCGCGPIO_R2{2, 1, RW}; //GPIO Port C Run Mode Clock Gating Control
        bitField RCGCGPIO_R1{1, 1, RW}; //GPIO Port B Run Mode Clock Gating Control
        bitField RCGCGPIO_R0{0, 1, RW}; //GPIO Port A Run Mode Clock Gating Control
        bitField RCGCGPIO_REG[6] = {RCGCGPIO_R0, RCGCGPIO_R1, RCGCGPIO_R2, RCGCGPIO_R3, RCGCGPIO_R4, RCGCGPIO_R5};

        bitField SCGCGPIO_S5{5, 1, RW}; //GPIO Port F Sleep Mode Clock Gating Control
        bitField SCGCGPIO_S4{4, 1, RW}; //GPIO Port E Sleep Mode Clock Gating Control
        bitField SCGCGPIO_S3{3, 1, RW}; //GPIO Port D Sleep Mode Clock Gating Control
        bitField SCGCGPIO_S2{2, 1, RW}; //GPIO Port C Sleep Mode Clock Gating Control
        bitField SCGCGPIO_S1{1, 1, RW}; //GPIO Port B Sleep Mode Clock Gating Control
        bitField SCGCGPIO_S0{0, 1, RW}; //GPIO Port A Sleep Mode Clock Gating Control
        bitField SCGCGPIO_SLP[6] = {SCGCGPIO_S0, SCGCGPIO_S1, SCGCGPIO_S2, SCGCGPIO_S3, SCGCGPIO_S4, SCGCGPIO_S5};

        bitField DCGCGPIO_D5{5, 1, RW}; //GPIO Port F Deep-Sleep Mode Clock Gating Control
        bitField DCGCGPIO_D4{4, 1, RW}; //GPIO Port E Deep-Sleep Mode Clock Gating Control
        bitField DCGCGPIO_D3{3, 1, RW}; //GPIO Port D Deep-Sleep Mode Clock Gating Control
        bitField DCGCGPIO_D2{2, 1, RW}; //GPIO Port C Deep-Sleep Mode Clock Gating Control
        bitField DCGCGPIO_D1{1, 1, RW}; //GPIO Port B Deep-Sleep Mode Clock Gating Control
        bitField DCGCGPIO_D0{0, 1, RW}; //GPIO Port A Deep-Sleep Mode Clock Gating Control
        bitField DCGCGPIO_DPSLP[6] = {DCGCGPIO_D0, DCGCGPIO_D1, DCGCGPIO_D2, DCGCGPIO_D3, DCGCGPIO_D4, DCGCGPIO_D5};

        bitField PRGPIO_R5{5, 1, RO}; //GPIO Port F Peripheral Ready
        bitField PRGPIO_R4{4, 1, RO}; //GPIO Port E Peripheral Ready
        bitField PRGPIO_R3{3, 1, RO}; //GPIO Port D Peripheral Ready
        bitField PRGPIO_R2{2, 1, RO}; //GPIO Port C Peripheral Ready
        bitField PRGPIO_R1{1, 1, RO}; //GPIO Port B Peripheral Ready
        bitField PRGPIO_R0{0, 1, RO}; //GPIO Port A Peripheral Ready
        bitField PRGPIO_REG[6] = {PRGPIO_R0, PRGPIO_R1, PRGPIO_R2, PRGPIO_R3, PRGPIO_R4, PRGPIO_R5};



        bitField GPIOAFSEL_AFSEL{0, 1, RW}; //GPIO Alternate Function Select

        bitField GPIOLOCK_LOCK{0, 32, RW}; //GPIO Lock. A write of the value 0x4C4F.434B unlocks the GPIO Commit (GPIOCR) register for write access.

        bitField GPIOCR_CR{0, 1, RW}; //GPIO Commit

        bitField GPIODEN_DEN{0, 1, RW}; //Digital Enable

        bitField GPIOAMSEL_GPIOAMSEL{0, 1, RW}; //GPIO Analog Mode Select

        bitField GPIOPUR_PUE{0, 1, RW}; //Pad Weak Pull-Up Enable


    private:
        /**
         * Each GPIO port can be accessed through one of two bus apertures. The 
         * legacy aperture, the Advanced Peripheral Bus (APB), is 
         * backwards-compatible with previous devices. The other aperture, the 
         * Advanced High-Performance Bus (AHB), offers the same register map but 
         * provides better back-to-back access performance than the APB bus.
         */

        const uint32_t GPIOIS = 0x404;
        const uint32_t GPIOIBE = 0x408;
        const uint32_t GPIOIEV = 0x40C;
        const uint32_t GPIOIM = 0x410;
        const uint32_t GPIORIS = 0x414;
        const uint32_t GPIOMIS = 0x418;
        const uint32_t GPIOICR = 0x41C;
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

        Register GPIOHBCTL{(volatile uint32_t*)(systemControlBase + 0x06C)}; 

        Register GPIO_Port_GPIOIS{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOIS)}; // 0x404 GPIOIS RW 0x0000.0000 GPIO Interrupt Sense 664
        Register GPIO_Port_GPIOIBE{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOIBE)}; // 0x408 GPIOIBE RW 0x0000.0000 GPIO Interrupt Both Edges 665
        Register GPIO_Port_GPIOIEV{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOIEV)}; // 0x40C GPIOIEV RW 0x0000.0000 GPIO Interrupt Event 666
        Register GPIO_Port_GPIOIM{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOIM)}; // 0x410 GPIOIM RW 0x0000.0000 GPIO Interrupt Mask 667
        Register GPIO_Port_GPIORIS{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIORIS)}; // 0x414 GPIORIS RO 0x0000.0000 GPIO Raw Interrupt Status 668
        Register GPIO_Port_GPIOMIS{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOMIS)}; // 0x418 GPIOMIS RO 0x0000.0000 GPIO Masked Interrupt Status 669
        Register GPIO_Port_GPIOICR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOICR)}; // 0x41C GPIOICR W1C 0x0000.0000 GPIO Interrupt Clear 670
        Register GPIO_Port_GPIODR2R{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODR2R)}; // 0x500 GPIODR2R RW 0x0000.00FF GPIO 2-mA Drive Select 673
        Register GPIO_Port_GPIODR4R{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODR4R)}; // 0x504 GPIODR4R RW 0x0000.0000 GPIO 4-mA Drive Select 674
        Register GPIO_Port_GPIODR48R{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODR8R)}; // 0x508 GPIODR8R RW 0x0000.0000 GPIO 8-mA Drive Select 675
        Register GPIO_Port_GPIOODR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOODR)}; // 0x50C GPIOODR RW 0x0000.0000 GPIO Open Drain Select 676
        Register GPIO_Port_GPIOPDR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPDR)}; // 0x514 GPIOPDR RW 0x0000.0000 GPIO Pull-Down Select 679
        Register GPIO_Port_GPIOSLR{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOSLR)}; // 0x518 GPIOSLR RW 0x0000.0000 GPIO Slew Rate Control Select 681
        Register GPIO_Port_GPIOADCCTL{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOADCCTL)}; // 0x530 GPIOADCCTL RW 0x0000.0000 GPIO ADC Control 690
        Register GPIO_Port_GPIODMACTL{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIODMACTL)}; // 0x534 GPIODMACTL RW 0x0000.0000 GPIO DMA Control 691
        Register GPIO_Port_GPIOPeriphID4{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID4)}; // 0xFD0 GPIOPeriphID4 RO 0x0000.0000 GPIO Peripheral Identification 4 692
        Register GPIO_Port_GPIOPeriphID5{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID5)}; // 0xFD4 GPIOPeriphID5 RO 0x0000.0000 GPIO Peripheral Identification 5 693
        Register GPIO_Port_GPIOPeriphID6{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID6)}; // 0xFD8 GPIOPeriphID6 RO 0x0000.0000 GPIO Peripheral Identification 6 694
        Register GPIO_Port_GPIOPeriphID7{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID7)}; // 0xFDC GPIOPeriphID7 RO 0x0000.0000 GPIO Peripheral Identification 7 695
        Register GPIO_Port_GPIOPeriphID0{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID0)}; // 0xFE0 GPIOPeriphID0 RO 0x0000.0061 GPIO Peripheral Identification 0 696
        Register GPIO_Port_GPIOPeriphID1{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID1)}; // 0xFE4 GPIOPeriphID1 RO 0x0000.0000 GPIO Peripheral Identification 1 697
        Register GPIO_Port_GPIOPeriphID2{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID2)}; // 0xFE8 GPIOPeriphID2 RO 0x0000.0018 GPIO Peripheral Identification 2 698
        Register GPIO_Port_GPIOPeriphID3{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPeriphID3)}; // 0xFEC GPIOPeriphID3 RO 0x0000.0001 GPIO Peripheral Identification 3 699    
        Register GPIO_Port_GPIOPCellID0{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPCellID0)}; // 0xFF0 GPIOPCellID0 RO 0x0000.000D GPIO PrimeCell Identification 0 700
        Register GPIO_Port_GPIOPCellID1{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPCellID1)}; // 0xFF4 GPIOPCellID1 RO 0x0000.00F0 GPIO PrimeCell Identification 1 701
        Register GPIO_Port_GPIOPCellID2{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPCellID2)}; // 0xFF8 GPIOPCellID2 RO 0x0000.0005 GPIO PrimeCell Identification 2 702
        Register GPIO_Port_GPIOPCellID3{(volatile uint32_t*)(GPIO_Port_A_AHB + GPIOPCellID2)}; // 0xFFC GPIOPCellID3 RO 0x0000.00B1 GPIO PrimeCell Identification 3 703

        bitField GPIOHBCTL_PORTF{5, 1, RW}; //Port F Advanced High-Performance Bus
        bitField GPIOHBCTL_PORTE{4, 1, RW}; //Port E Advanced High-Performance Bus
        bitField GPIOHBCTL_PORTD{3, 1, RW}; //Port D Advanced High-Performance Bus
        bitField GPIOHBCTL_PORTC{2, 1, RW}; //Port C Advanced High-Performance Bus
        bitField GPIOHBCTL_PORTB{1, 1, RW}; //Port B Advanced High-Performance Bus
        bitField GPIOHBCTL_PORTA{0, 1, RW}; //Port A Advanced High-Performance Bus
        
        bitField GPIODIR_DIR{0, 1, RW}; //GPIO Data Direction. 

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


/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC4_GPIOJ{8, 1, RO}; //GPIO Port J Present. When set, indicates that GPIO Port J is present.
        bitField DC4_GPIOH{7, 1, RO}; //GPIO Port H Present. When set, indicates that GPIO Port H is present.
        bitField DC4_GPIOG{6, 1, RO}; //GPIO Port G Present. When set, indicates that GPIO Port G is present.
        bitField DC4_GPIOF{5, 1, RO}; //GPIO Port F Present. When set, indicates that GPIO Port F is present.
        bitField DC4_GPIOE{4, 1, RO}; //GPIO Port E Present. When set, indicates that GPIO Port E is present.
        bitField DC4_GPIOD{3, 1, RO}; //GPIO Port D Present. When set, indicates that GPIO Port D is present.
        bitField DC4_GPIOC{2, 1, RO}; //GPIO Port C Present. When set, indicates that GPIO Port C is present.
        bitField DC4_GPIOB{1, 1, RO}; //GPIO Port B Present. When set, indicates that GPIO Port B is present.
        bitField DC4_GPIOA{0, 1, RO}; //GPIO Port A Present. When set, indicates that GPIO Port A is present.

        bitField SRCR2_GPIOF{5, 1, RO}; //Port F Reset Control
        bitField SRCR2_GPIOE{4, 1, RO}; //Port E Reset Control
        bitField SRCR2_GPIOD{3, 1, RO}; //Port D Reset Control
        bitField SRCR2_GPIOC{2, 1, RO}; //Port C Reset Control
        bitField SRCR2_GPIOB{1, 1, RO}; //Port B Reset Control
        bitField SRCR2_GPIOA{0, 1, RO}; //Port A Reset Control

        bitField RCGC2_GPIOF{5, 1, RO}; //Port F Clock Gating Control
        bitField RCGC2_GPIOE{4, 1, RO}; //Port E Clock Gating Control
        bitField RCGC2_GPIOD{3, 1, RO}; //Port D Clock Gating Control
        bitField RCGC2_GPIOC{2, 1, RO}; //Port C Clock Gating Control
        bitField RCGC2_GPIOB{1, 1, RO}; //Port B Clock Gating Control
        bitField RCGC2_GPIOA{0, 1, RO}; //Port A Clock Gating Control

        bitField SCGC2_GPIOF{5, 1, RO}; //Port F Sleep Clock Gating Control
        bitField SCGC2_GPIOE{4, 1, RO}; //Port E Sleep Clock Gating Control
        bitField SCGC2_GPIOD{3, 1, RO}; //Port D Sleep Clock Gating Control
        bitField SCGC2_GPIOC{2, 1, RO}; //Port C Sleep Clock Gating Control
        bitField SCGC2_GPIOB{1, 1, RO}; //Port B Sleep Clock Gating Control
        bitField SCGC2_GPIOA{0, 1, RO}; //Port A Sleep Clock Gating Control

        bitField DCGC2_GPIOF{5, 1, RO}; //Port F Deep-Sleep Clock Gating Control
        bitField DCGC2_GPIOE{4, 1, RO}; //Port E Deep-Sleep Clock Gating Control
        bitField DCGC2_GPIOD{3, 1, RO}; //Port D Deep-Sleep Clock Gating Control
        bitField DCGC2_GPIOC{2, 1, RO}; //Port C Deep-Sleep Clock Gating Control
        bitField DCGC2_GPIOB{1, 1, RO}; //Port B Deep-Sleep Clock Gating Control
        bitField DCGC2_GPIOA{0, 1, RO}; //Port A Deep-Sleep Clock Gating Control

};


#endif //GPIO_H
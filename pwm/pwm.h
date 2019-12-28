/**
 * @file pwm.h
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
 * Pulse Width Modulator (PWM) Register Descriptions
 * 
 * The remainder of this section lists and describes the PWM registers, 
 * in numerical order by address offset.
 */

#ifndef PWM_H
#define PWM_H

#include "../systemControl/systemControl.h"

class Pwm : SystemControl
{
    public:
        Pwm();
        ~Pwm();

    private:
        const uint32_t pwm0BaseAddress = 0x40028000;
        const uint32_t pwm1BaseAddress = 0x40029000;

/**********************System Control Register Descriptions********************/

        Register PPPWM{(volatile uint32_t*)(systemControlBase + 0x340)}; //0x340 PPPWM RO 0x0000.0003 Pulse Width Modulator Peripheral Present 305
        Register SRPWM{(volatile uint32_t*)(systemControlBase + 0x540)}; //0x540 SRPWM RW 0x0000.0000 Pulse Width Modulator Software Reset 330
        Register RCGCPWM{(volatile uint32_t*)(systemControlBase + 0x640)}; //0x640 RCGCPWM RW 0x0000.0000 Pulse Width Modulator Run Mode Clock Gating Control 354
        Register SCGCPWM{(volatile uint32_t*)(systemControlBase + 0x740)}; //0x740 SCGCPWM RW 0x0000.0000 Pulse Width Modulator Sleep Mode Clock Gating Control 376
        Register DCGCPWM{(volatile uint32_t*)(systemControlBase + 0x840)}; //0x840 DCGCPWM RW 0x0000.0000 Pulse Width Modulator Deep-Sleep Mode Clock Gating Control 398
        Register PRPWM{(volatile uint32_t*)(systemControlBase + 0xA40)}; //0xA40 PRPWM RO 0x0000.0000 Pulse Width Modulator Peripheral Ready 420

/**************************System Control BitFields****************************/

        bitField RCC_USEPWMDIV{20, 1, RW}; //Enable PWM Clock Divisor
        bitField RCC_PWMDIV{17, 3, RW}; //PWM Unit Clock Divisor

        bitField PPPWM_P1{1, 1, RO}; //PWM Module 1 Present
        bitField PPPWM_P0{0, 1, RO}; //PWM Module 0 Present

        bitField SRPWM_R1{1, 1, RW}; //PWM Module 1 Software Reset
        bitField SRPWM_R0{0, 1, RW}; //PWM Module 0 Software Reset

        bitField RCGCPWM_R1{1, 1, RW}; //PWM Module 1 Run Mode Clock Gating Control
        bitField RCGCPWM_R0{0, 1, RW}; //PWM Module 0 Run Mode Clock Gating Control

        bitField SCGCPWM_S1{1, 1, RW}; //PWM Module 1 Sleep Mode Clock Gating Control
        bitField SCGCPWM_S0{0, 1, RW}; //PWM Module 0 Sleep Mode Clock Gating Control

        bitField DCGCPWM_D1{1, 1, RW}; //PWM Module 1 Deep-Sleep Mode Clock Gating Control
        bitField DCGCPWM_D0{0, 1, RW}; //PWM Module 0 Deep-Sleep Mode Clock Gating Control

        bitField PRPWM_R1{1, 1, RO}; //PWM Module 1 Peripheral Ready
        bitField PRPWM_R0{0, 1, RO}; //PWM Module 0 Peripheral Ready

/********************System Control Legacy BitField Descriptions***************/
        /**
         * Important: Register in this section are provided for legacy software 
         * support only; registers in “System Control Register Descriptions” on 
         * page 237 should be used instead.
         */

        bitField DC1_PWM1{21, 1, RO}; //PWM Module 1 Present. When set, indicates that the PWM module is present.
        bitField DC1_PWM0{20, 1, RO}; //PWM Module 0 Present. When set, indicates that the PWM module is present.

        bitField DC3_CCP5{29, 1, RO}; //T2CCP1 Pin Present. When set, indicates that Capture/Compare/PWM pin T2CCP1 is present.
        bitField DC3_CCP4{28, 1, RO}; //T2CCP0 Pin Present. When set, indicates that Capture/Compare/PWM pin T2CCP0 is present.
        bitField DC3_CCP3{27, 1, RO}; //T1CCP1 Pin Present. When set, indicates that Capture/Compare/PWM pin T1CCP1 is present.
        bitField DC3_CCP2{26, 1, RO}; //T1CCP0 Pin Present. When set, indicates that Capture/Compare/PWM pin T1CCP0 is present.
        bitField DC3_CCP1{25, 1, RO}; //T0CCP1 Pin Present. When set, indicates that Capture/Compare/PWM pin T0CCP1 is present.
        bitField DC3_CCP0{24, 1, RO}; //T0CCP0 Pin Present. When set, indicates that Capture/Compare/PWM pin T0CCP0 is present.
        bitField DC3_PWMFAULT{15, 1, RO}; //PWM Fault Pin Present. When set, indicates that a PWM Fault pin is present. See DC5 for specific Fault pins on this device.
        bitField DC3_PWM5{5, 1, RO}; //PWM5 Pin Present. When set, indicates that the PWM pin 5 is present.
        bitField DC3_PWM4{4, 1, RO}; //PWM4 Pin Present. When set, indicates that the PWM pin 4 is present.
        bitField DC3_PWM3{3, 1, RO}; //PWM3 Pin Present. When set, indicates that the PWM pin 3 is present.
        bitField DC3_PWM2{2, 1, RO}; //PWM2 Pin Present. When set, indicates that the PWM pin 2 is present.
        bitField DC3_PWM1{1, 1, RO}; //PWM1 Pin Present. When set, indicates that the PWM pin 1 is present.
        bitField DC3_PWM0{0, 1, RO}; //PWM0 Pin Present. When set, indicates that the PWM pin 0 is present.

        bitField DC4_CCP7{15, 1, RO}; //T3CCP1 Pin Present. When set, indicates that Capture/Compare/PWM pin T3CCP1 is present.
        bitField DC4_CCP6{14, 1, RO}; //T3CCP0 Pin Present. When set, indicates that Capture/Compare/PWM pin T3CCP0 is present.

        bitField DC5_PWMFAULT3{27, 1, RO}; //PWM Fault 3 Pin Present. When set, indicates that the PWM Fault 3 pin is present.
        bitField DC5_PWMFAULT2{26, 1, RO}; //PWM Fault 2 Pin Present. When set, indicates that the PWM Fault 2 pin is present.
        bitField DC5_PWMFAULT1{25, 1, RO}; //PWM Fault 1 Pin Present. When set, indicates that the PWM Fault 1 pin is present.
        bitField DC5_PWMFAULT0{24, 1, RO}; //PWM Fault 0 Pin Present. When set, indicates that the PWM Fault 0 pin is present.
        bitField DC5_PWMEFLT{21, 1, RO}; //PWM Extended Fault Active. When set, indicates that the PWM Extended Fault feature is active.
        bitField DC5_PWMESYNC{20, 1, RO}; //PWM Extended SYNC Active. When set, indicates that the PWM Extended SYNC feature is active.
        bitField DC5_PWM7{7, 1, RO}; //PWM7 Pin Present. When set, indicates that the PWM pin 7 is present.
        bitField DC5_PWM6{6, 1, RO}; //PWM6 Pin Present. When set, indicates that the PWM pin 6 is present.
        bitField DC5_PWM5{5, 1, RO}; //PWM5 Pin Present. When set, indicates that the PWM pin 5 is present.
        bitField DC5_PWM4{4, 1, RO}; //PWM4 Pin Present. When set, indicates that the PWM pin 4 is present.
        bitField DC5_PWM3{3, 1, RO}; //PWM3 Pin Present. When set, indicates that the PWM pin 3 is present.
        bitField DC5_PWM2{2, 1, RO}; //PWM2 Pin Present. When set, indicates that the PWM pin 2 is present.
        bitField DC5_PWM1{1, 1, RO}; //PWM1 Pin Present. When set, indicates that the PWM pin 1 is present.
        bitField DC5_PWM0{0, 1, RO}; //PWM0 Pin Present. When set, indicates that the PWM pin 0 is present.

        bitField SRCR0_PWM0{20, 1, RO}; //PWM Reset Control

        bitField RCGC0_PWM0{20, 1, RO}; //PWM Clock Gating Control

        bitField SCGC0_PWM0{20, 1, RO}; //PWM Clock Gating Control
        
        bitField DCGC0_PWM0{20, 1, RO}; //PWM Clock Gating Control
};

#endif //PWM_H
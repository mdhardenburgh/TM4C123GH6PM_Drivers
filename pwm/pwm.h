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

        const uint32_t PPPWM_OFFSET = 0x340;
        const uint32_t SRPWM_OFFSET = 0x540;
        const uint32_t RCGCPWM_OFFSET = 0x640;
        const uint32_t SCGCPWM_OFFSET = 0x740;
        const uint32_t DCGCPWM_OFFSET = 0x840;
        const uint32_t PRPWM_OFFSET = 0xA40;

/**********************System Control Register Descriptions********************/

        Register* PPPWM; //0x340 PPPWM RO 0x0000.0003 Pulse Width Modulator Peripheral Present 305
        Register* SRPWM; //0x540 SRPWM RW 0x0000.0000 Pulse Width Modulator Software Reset 330
        Register* RCGCPWM; //0x640 RCGCPWM RW 0x0000.0000 Pulse Width Modulator Run Mode Clock Gating Control 354
        Register* SCGCPWM; //0x740 SCGCPWM RW 0x0000.0000 Pulse Width Modulator Sleep Mode Clock Gating Control 376
        Register* DCGCPWM; //0x840 DCGCPWM RW 0x0000.0000 Pulse Width Modulator Deep-Sleep Mode Clock Gating Control 398
        Register* PRPWM; //0xA40 PRPWM RO 0x0000.0000 Pulse Width Modulator Peripheral Ready 420

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


};

#endif //PWM_H
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

class Pwm
{
    public:
        Pwm();
        ~Pwm();

    private:
        
        static const uint32_t pwm0BaseAddress = 0x40028000;
        static const uint32_t pwm1BaseAddress = 0x40029000;

        static const uint32_t PPPWM_OFFSET = 0x340; //0x340 PPPWM RO 0x0000.0003 Pulse Width Modulator Peripheral Present 305
        static const uint32_t SRPWM_OFFSET = 0x540; //0x540 SRPWM RW 0x0000.0000 Pulse Width Modulator Software Reset 330
        static const uint32_t RCGCPWM_OFFSET = 0x640; //0x640 RCGCPWM RW 0x0000.0000 Pulse Width Modulator Run Mode Clock Gating Control 354
        static const uint32_t SCGCPWM_OFFSET = 0x740; //0x740 SCGCPWM RW 0x0000.0000 Pulse Width Modulator Sleep Mode Clock Gating Control 376
        static const uint32_t DCGCPWM_OFFSET = 0x840; //0x840 DCGCPWM RW 0x0000.0000 Pulse Width Modulator Deep-Sleep Mode Clock Gating Control 398
        static const uint32_t PRPWM_OFFSET = 0xA40; //0xA40 PRPWM RO 0x0000.0000 Pulse Width Modulator Peripheral Ready 420


};

#endif //PWM_H
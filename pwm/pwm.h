/**
 * @file pwm.h
 * @brief TM4C123GH6PM PWM Driver Declaration
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
 * @class Pwm
 * @brief TM4C123GH6PM PWM Driver
 * 
 * @section pwmDescription PWM Description
 * 
 * The TM4C123GH6PM microcontroller has two PWM modules. Each module has 4 PWM
 * generator blocks and each generator block produces 2 PWM signals that share
 * the same PWM timer and frequency. The 2 PWM signals can be programmed to 
 * operate independently or as a pair of complementary signals and a dead-band
 * delay can be inserted. The two output signals \c pwmA and \c pwmB of the 
 * device generation are managed by an output control block before they reach
 * the device pins as \c MnPWM0 , \c MnPWM1 , \c MnPWM2 etc...
 * 
 * Each PWM generator block has the following features:
 *      - One fault-condition handling inputs to quickly provide low-latency 
 *        shutdown and prevent damage to the motor being controlled, for a total 
 *        of two inputs
 *      - One 16-bit counter
 *          - Runs in Down or Up/Down mode
 *          - Output frequency controlled by a 16-bit load value
 *          - Load value updates can be synchronized
 *          - Produces output signals at zero and load value
 *      - Two PWM comparators
 *          - Comparator value updates can be synchronized
 *          - Produces output signals on match
 *      - PWM signal generator
 *          - Output PWM signal is constructed based on actions taken as a 
 *            result of  the counter and PWM comparator output signals
 *          - Produces two independent PWM signals
 *      - Dead-band generator
 *          - Produces two PWM signals with programmable dead-band delays 
 *            suitable for driving a half-H bridge
 *          - Can be bypassed, leaving input PWM signals unmodified
 *      - Can initiate an ADC sample sequence
 * 
 * The PWM control block determines the polarity of the PWM signals that are
 * passed through to the external microcontroller pins. The PWM control block 
 * has the following options:
 *      - PWM output enable of each PWM signal
 *      - Optional output inversion of each PWM signal (polarity control)
 *      - Optional fault handling for each PWM signal
 *      - Synchronization of timers in the PWM generator blocks
 *      - Synchronization of timer/comparator updates across the PWM generator blocks
 *      - Extended PWM synchronization of timer/comparator updates across the 
 *        PWM generator blocks
 *      - Interrupt status summary of the PWM generator blocks
 *      - Extended PWM fault handling, with multiple fault signals, programmable 
 *        polarities, and filtering
 *      - PWM generators can be operated independently or synchronized with 
 *        other generators
 * 
 * For more detailed information on the PWM please see page 1230 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection pwmSignalDescription PWM Signal Description
 * 
 * The following table lists the external signals and thier associtated pins 
 * for the PWM module. The GPIO needs to be configured for the PWM alternate
 * function using the \c AFSEL bit in the GPIO Alternate Function Register 
 * (GPIOAFSEL). The number in parenthesis in the Pin Mux / Pin Assignment 
 * column of the table below is what is programmed into the \c PMCn field in
 * the GPIO Port Control (GPIOPCTL) register to assign a PWM signal to a GPIO. 
 * 
 * @image html pwmSignalPins.png
 * @image latex pwmSignalPins.png
 * 
 */


#ifndef PWM_H
#define PWM_H

#include "../systemControl/systemControl.h"


/**
 * Action for Comparator B Down
 * 
 * This field specifies the action to be taken when the counter matches
 * comparator B while counting down.
 */
enum class ACTCMPBD{doNothing = 0x0<<10, invertPwm = 0x1<<10, drivePwmLow = 0x2<<10, drivPwmHigh = 0x3<<10};

/**
 * Action for Comparator B Up.
 * 
 * This field specifies the action to be taken when the counter matches
 * comparator B while counting up. This action can only occur when the
 * \c MODE bit in the PWMnCTL register is set.
 */
enum class ACTCMPBU{doNothing = 0x0<<8, invertPwm = 0x1<<8, drivePwmLow = 0x2<<8, drivPwmHigh = 0x3<<8};

/**
 * Action for Comparator A Down.
 * 
 * This field specifies the action to be taken when the counter matches
 * comparator A while counting down.
 */
enum class ACTCMPAD{doNothing = 0x0<<6, invertPwm = 0x1<<6, drivePwmLow = 0x2<<6, drivPwmHigh = 0x3<<6};

/**
 * Action for Comparator A Up.
 * 
 * This field specifies the action to be taken when the counter matches
 * comparator A while counting up. This action can only occur when the
 * \c MODE bit in the PWMnCTL register is set.
 */
enum class ACTCMPAU{doNothing = 0x0<<4, invertPwm = 0x1<<4, drivePwmLow = 0x2<<4, drivPwmHigh = 0x3<<4};

/**
 * Action for Counter=LOAD.
 * 
 * This field specifies the action to be taken when the counter matches the 
 * load value.
 */
enum class ACTLOAD{doNothing = 0x0<<2, invertPwm = 0x1<<2, drivePwmLow = 0x2<<2, drivPwmHigh = 0x3<<2};

/**
 * Action for Counter=0.
 * 
 * This field specifies the action to be taken when the counter is 0.
 */
enum class ACTZERO{doNothing, invertPwm, drivePwmLow, drivPwmHigh};

enum class countDirectionPwm{down, upAndDown};

/**
 * From the TM4C123GH6PM Datasheet p. 255:
 * 
 * "This field specifies the binary divisor used to predivide the system clock
 * down for use as the timing reference for the PWM module. The rising edge of 
 * this clock is synchronous with the system clock."
 */
enum class pwmUnitClockDivisor{_2, _4, _8, _16, _32, _64};

/**
 * Which PWM generator to use
 */
enum pwmGenerator
{
    pwmGen0, pwmGen1, pwmGen2, pwmGen3
};

/**
 * Which module is being used
 */
enum pwmModule
{
    module0, module1
};

enum class pwmOutput{pwmA = 0x000, pwmB = 0x004};


class Pwm
{
    public:
        Pwm();
        ~Pwm();

        void initializeSingle(uint32_t pwmPin, pwmModule module, uint32_t period, uint32_t compA, uint32_t compB, countDirectionPwm countDir, uint32_t genOptions, bool enablePwmDiv, uint32_t divisor);
        void initializePair(uint32_t pwmPin, pwmModule module, uint32_t period, uint32_t dutyCycleA, uint32_t dutyCycleB, countDirectionPwm countDir, uint32_t genAOptions, uint32_t genBOptions, bool enablePwmDiv, uint32_t divisor);
    
    private:
        
        void initialize(uint32_t pwmPin, pwmModule module, uint32_t period, countDirectionPwm countDir, bool enablePwmDiv, uint32_t divisor);

        uint32_t baseAddress;
        uint32_t myPwmGen;

        static const uint32_t pwm0BaseAddress = 0x40028000;
        // static const uint32_t pwm1BaseAddress = 0x40029000;

        static const uint32_t RCC_OFFSET = 0x060; //RCC RW 0x078E.3AD1 Run-Mode Clock Configuration 254

        static const uint32_t PPPWM_OFFSET = 0x340; //0x340 PPPWM RO 0x0000.0003 Pulse Width Modulator Peripheral Present 305
        static const uint32_t SRPWM_OFFSET = 0x540; //0x540 SRPWM RW 0x0000.0000 Pulse Width Modulator Software Reset 330
        static const uint32_t RCGCPWM_OFFSET = 0x640; //0x640 RCGCPWM RW 0x0000.0000 Pulse Width Modulator Run Mode Clock Gating Control 354
        static const uint32_t SCGCPWM_OFFSET = 0x740; //0x740 SCGCPWM RW 0x0000.0000 Pulse Width Modulator Sleep Mode Clock Gating Control 376
        static const uint32_t DCGCPWM_OFFSET = 0x840; //0x840 DCGCPWM RW 0x0000.0000 Pulse Width Modulator Deep-Sleep Mode Clock Gating Control 398
        static const uint32_t PRPWM_OFFSET = 0xA40; //0xA40 PRPWM RO 0x0000.0000 Pulse Width Modulator Peripheral Ready 420

        static const uint32_t PWMCTL_OFFSET = 0x000; // 0x000 PWMCTL RW 0x0000.0000 PWM Master Control 1244
        static const uint32_t PWMSYNC_OFFSET = 0x004; // 0x004 PWMSYNC RW 0x0000.0000 PWM Time Base Sync 1246
        static const uint32_t PWMENABLE_OFFSET = 0x008; // 0x008 PWMENABLE RW 0x0000.0000 PWM Output Enable 1247
        static const uint32_t PWMINVERT_OFFSET = 0x00C; // 0x00C PWMINVERT RW 0x0000.0000 PWM Output Inversion 1249
        static const uint32_t PWMFAULT_OFFSET = 0x010; // 0x010 PWMFAULT RW 0x0000.0000 PWM Output Fault 1251
        static const uint32_t PWMINTEN_OFFSET = 0x014; // 0x014 PWMINTEN RW 0x0000.0000 PWM Interrupt Enable 1253
        static const uint32_t PWMRIS_OFFSET = 0x018; // 0x018 PWMRIS RO 0x0000.0000 PWM Raw Interrupt Status 1255
        static const uint32_t PWMISC_OFFSET = 0x01C; // 0x01C PWMISC RW1C 0x0000.0000 PWM Interrupt Status and Clear 1257
        static const uint32_t PWMSTATUS_OFFSET = 0x020; // 0x020 PWMSTATUS RO 0x0000.0000 PWM Status 1259
        static const uint32_t PWMFAULTVAL_OFFSET = 0x024; // 0x024 PWMFAULTVAL RW 0x0000.0000 PWM Fault Condition Value 1260
        static const uint32_t PWMENUPD_OFFSET = 0x028; // 0x028 PWMENUPD RW 0x0000.0000 PWM Enable Update 1262
        static const uint32_t PWM0CTL_OFFSET = 0x040; // 0x040 PWM0CTL RW 0x0000.0000 PWM0 Control 1266
        static const uint32_t PWM0INTEN_OFFSET = 0x044; // 0x044 PWM0INTEN RW 0x0000.0000 PWM0 Interrupt and Trigger Enable 1271
        static const uint32_t PWM0RIS_OFFSET = 0x048; // 0x048 PWM0RIS RO 0x0000.0000 PWM0 Raw Interrupt Status 1274
        static const uint32_t PWM0ISC_OFFSET = 0x04C; // 0x04C PWM0ISC RW1C 0x0000.0000 PWM0 Interrupt Status and Clear 1276
        static const uint32_t PWM0LOAD_OFFSET = 0x050; // 0x050 PWM0LOAD RW 0x0000.0000 PWM0 Load 1278
        static const uint32_t PWM0COUNT_OFFSET = 0x054; // 0x054 PWM0COUNT RO 0x0000.0000 PWM0 Counter 1279
        static const uint32_t PWM0CMPA_OFFSET = 0x058; // 0x058 PWM0CMPA RW 0x0000.0000 PWM0 Compare A 1280
        static const uint32_t PWM0CMPB_OFFSET = 0x05C; // 0x05C PWM0CMPB RW 0x0000.0000 PWM0 Compare B 1281
        static const uint32_t PWM0GENA_OFFSET = 0x060; // 0x060 PWM0GENA RW 0x0000.0000 PWM0 Generator A Control 1282
        static const uint32_t PWM0GENB_OFFSET = 0x064; // 0x064 PWM0GENB RW 0x0000.0000 PWM0 Generator B Control 1285
        static const uint32_t PWM0DBCTL_OFFSET = 0x068; // 0x068 PWM0DBCTL RW 0x0000.0000 PWM0 Dead-Band Control 1288
        static const uint32_t PWM0DBRISE_OFFSET = 0x06C; // 0x06C PWM0DBRISE RW 0x0000.0000 PWM0 Dead-Band Rising-Edge Delay 1289
        static const uint32_t PWM0DBFALL_OFFSET = 0x070; // 0x070 PWM0DBFALL RW 0x0000.0000 PWM0 Dead-Band Falling-Edge-Delay 1290
        static const uint32_t PWM0FLTSRC0_OFFSET = 0x074; // 0x074 PWM0FLTSRC0 RW 0x0000.0000 PWM0 Fault Source 0 1291
        static const uint32_t PWM0FLTSRC1_OFFSET = 0x078; // 0x078 PWM0FLTSRC1 RW 0x0000.0000 PWM0 Fault Source 1 1293
        static const uint32_t PWM0MINFLTPER_OFFSET = 0x07C; // 0x07C PWM0MINFLTPER RW 0x0000.0000 PWM0 Minimum Fault Period 1296
        static const uint32_t PWM1CTL_OFFSET = 0x080; // 0x080 PWM1CTL RW 0x0000.0000 PWM1 Control 1266
        static const uint32_t PWM1INTEN_OFFSET = 0x084; // 0x084 PWM1INTEN RW 0x0000.0000 PWM1 Interrupt and Trigger Enable 1271
        static const uint32_t PWM1RIS_OFFSET = 0x088; // 0x088 PWM1RIS RO 0x0000.0000 PWM1 Raw Interrupt Status 1274
        static const uint32_t PWM1ISC_OFFSET = 0x08C; // 0x08C PWM1ISC RW1C 0x0000.0000 PWM1 Interrupt Status and Clear 1276
        static const uint32_t PWM1LOAD_OFFSET = 0x090; // 0x090 PWM1LOAD RW 0x0000.0000 PWM1 Load 1278
        static const uint32_t PWM1COUNT_OFFSET = 0x094; // 0x094 PWM1COUNT RO 0x0000.0000 PWM1 Counter 1279
        static const uint32_t PWM1CMPA_OFFSET = 0x098; // 0x098 PWM1CMPA RW 0x0000.0000 PWM1 Compare A 1280
        static const uint32_t PWM1CMPB_OFFSET = 0x09C; // 0x09C PWM1CMPB RW 0x0000.0000 PWM1 Compare B 1281
        static const uint32_t PWM1GENA_OFFSET = 0x0A0; // 0x0A0 PWM1GENA RW 0x0000.0000 PWM1 Generator A Control 1282
        static const uint32_t PWM1GENB_OFFSET = 0x0A4; // 0x0A4 PWM1GENB RW 0x0000.0000 PWM1 Generator B Control 1285
        static const uint32_t PWM1DBCTL_OFFSET = 0x0A8; // 0x0A8 PWM1DBCTL RW 0x0000.0000 PWM1 Dead-Band Control 1288
        static const uint32_t PWM1DBRISE_OFFSET = 0x0AC; // 0x0AC PWM1DBRISE RW 0x0000.0000 PWM1 Dead-Band Rising-Edge Delay 1289
        static const uint32_t PWM1DBFALL_OFFSET = 0x0B0; // 0x0B0 PWM1DBFALL RW 0x0000.0000 PWM1 Dead-Band Falling-Edge-Delay 1290
        static const uint32_t PWM1FLTSRC0_OFFSET = 0x0B4; // 0x0B4 PWM1FLTSRC0 RW 0x0000.0000 PWM1 Fault Source 0 1291
        static const uint32_t PWM1FLTSRC1_OFFSET = 0x0B8; // 0x0B8 PWM1FLTSRC1 RW 0x0000.0000 PWM1 Fault Source 1 1293
        static const uint32_t PWM1MINFLTPER_OFFSET = 0x0BC; // 0x0BC PWM1MINFLTPER RW 0x0000.0000 PWM1 Minimum Fault Period 1296
        static const uint32_t PWM2CTL_OFFSET = 0x0C0; // 0x0C0 PWM2CTL RW 0x0000.0000 PWM2 Control 1266
        static const uint32_t PWM2INTEN_OFFSET = 0x0C4; // 0x0C4 PWM2INTEN RW 0x0000.0000 PWM2 Interrupt and Trigger Enable 1271
        static const uint32_t PWM2RIS_OFFSET = 0x0C8; // 0x0C8 PWM2RIS RO 0x0000.0000 PWM2 Raw Interrupt Status 1274
        static const uint32_t PWM2ISC_OFFSET = 0x0CC; // 0x0CC PWM2ISC RW1C 0x0000.0000 PWM2 Interrupt Status and Clear 1276
        static const uint32_t PWM2LOAD_OFFSET = 0x0D0; // 0x0D0 PWM2LOAD RW 0x0000.0000 PWM2 Load 1278
        static const uint32_t PWM2COUNT_OFFSET = 0x0D4; // 0x0D4 PWM2COUNT RO 0x0000.0000 PWM2 Counter 1279
        static const uint32_t PWM2CMPA_OFFSET = 0x0D8; // 0x0D8 PWM2CMPA RW 0x0000.0000 PWM2 Compare A 1280
        static const uint32_t PWM2CMPB_OFFSET = 0x0DC; // 0x0DC PWM2CMPB RW 0x0000.0000 PWM2 Compare B 1281
        static const uint32_t PWM2GENA_OFFSET = 0x0E0; // 0x0E0 PWM2GENA RW 0x0000.0000 PWM2 Generator A Control 1282
        static const uint32_t PWM2GENB_OFFSET = 0x0E4; // 0x0E4 PWM2GENB RW 0x0000.0000 PWM2 Generator B Control 1285
        static const uint32_t PWM2DBCTL_OFFSET = 0x0E8; // 0x0E8 PWM2DBCTL RW 0x0000.0000 PWM2 Dead-Band Control 1288
        static const uint32_t PWM2DBRISE_OFFSET = 0x0EC; // 0x0EC PWM2DBRISE RW 0x0000.0000 PWM2 Dead-Band Rising-Edge Delay 1289
        static const uint32_t PWM2DBFALL_OFFSET = 0x0F0; // 0x0F0 PWM2DBFALL RW 0x0000.0000 PWM2 Dead-Band Falling-Edge-Delay 1290
        static const uint32_t PWM2FLTSRC0_OFFSET = 0x0F4; // 0x0F4 PWM2FLTSRC0 RW 0x0000.0000 PWM2 Fault Source 0 1291
        static const uint32_t PWM2FLTSRC1_OFFSET = 0x0F8; // 0x0F8 PWM2FLTSRC1 RW 0x0000.0000 PWM2 Fault Source 1 1293
        static const uint32_t PWM2MINFLTPER_OFFSET = 0x0FC; // 0x0FC PWM2MINFLTPER RW 0x0000.0000 PWM2 Minimum Fault Period 1296
        static const uint32_t PWM3CTL_OFFSET = 0x100; // 0x100 PWM3CTL RW 0x0000.0000 PWM3 Control 1266
        static const uint32_t PWM3INTEN_OFFSET = 0x104; // 0x104 PWM3INTEN RW 0x0000.0000 PWM3 Interrupt and Trigger Enable 1271
        static const uint32_t PWM3RIS_OFFSET = 0x108; // 0x108 PWM3RIS RO 0x0000.0000 PWM3 Raw Interrupt Status 1274
        static const uint32_t PWM3ISC_OFFSET = 0x10C; // 0x10C PWM3ISC RW1C 0x0000.0000 PWM3 Interrupt Status and Clear 1276
        static const uint32_t PWM3LOAD_OFFSET = 0x110; // 0x110 PWM3LOAD RW 0x0000.0000 PWM3 Load 1278
        static const uint32_t PWM3COUNT_OFFSET = 0x114; // 0x114 PWM3COUNT RO 0x0000.0000 PWM3 Counter 1279
        static const uint32_t PWM3CMPA_OFFSET = 0x118; // 0x118 PWM3CMPA RW 0x0000.0000 PWM3 Compare A 1280
        static const uint32_t PWM3CMPB_OFFSET = 0x11C; // 0x11C PWM3CMPB RW 0x0000.0000 PWM3 Compare B 1281
        static const uint32_t PWM3GENA_OFFSET = 0x120; // 0x120 PWM3GENA RW 0x0000.0000 PWM3 Generator A Control 1282
        static const uint32_t PWM3GENB_OFFSET = 0x124; // 0x124 PWM3GENB RW 0x0000.0000 PWM3 Generator B Control 1285
        static const uint32_t PWM3DBCTL_OFFSET = 0x128; // 0x128 PWM3DBCTL RW 0x0000.0000 PWM3 Dead-Band Control 1288
        static const uint32_t PWM3DBRISE_OFFSET = 0x12C; // 0x12C PWM3DBRISE RW 0x0000.0000 PWM3 Dead-Band Rising-Edge Delay 1289
        static const uint32_t PWM3DBFALL_OFFSET = 0x130; // 0x130 PWM3DBFALL RW 0x0000.0000 PWM3 Dead-Band Falling-Edge-Delay 1290
        static const uint32_t PWM3FLTSRC0_OFFSET = 0x134; // 0x134 PWM3FLTSRC0 RW 0x0000.0000 PWM3 Fault Source 0 1291
        static const uint32_t PWM3FLTSRC1_OFFSET = 0x138; // 0x138 PWM3FLTSRC1 RW 0x0000.0000 PWM3 Fault Source 1 1293
        static const uint32_t PWM3MINFLTPER_OFFSET = 0x13C; // 0x13C PWM3MINFLTPER RW 0x0000.0000 PWM3 Minimum Fault Period 1296
        static const uint32_t PWM0FLTSEN_OFFSET = 0x800; // 0x800 PWM0FLTSEN RW 0x0000.0000 PWM0 Fault Pin Logic Sense 1297
        static const uint32_t PWM0FLTSTAT0_OFFSET = 0x804; // 0x804 PWM0FLTSTAT0 - 0x0000.0000 PWM0 Fault Status 0 1298
        static const uint32_t PWM0FLTSTAT1_OFFSET = 0x808; // 0x808 PWM0FLTSTAT1 - 0x0000.0000 PWM0 Fault Status 1 1300
        static const uint32_t PWM1FLTSEN_OFFSET = 0x880; // 0x880 PWM1FLTSEN RW 0x0000.0000 PWM1 Fault Pin Logic Sense 1297
        static const uint32_t PWM1FLTSTAT0_OFFSET = 0x884; // 0x884 PWM1FLTSTAT0 - 0x0000.0000 PWM1 Fault Status 0 1298
        static const uint32_t PWM1FLTSTAT1_OFFSET = 0x888; // 0x888 PWM1FLTSTAT1 - 0x0000.0000 PWM1 Fault Status 1 1300
        static const uint32_t PWM2FLTSTAT0_OFFSET = 0x904; // 0x904 PWM2FLTSTAT0 - 0x0000.0000 PWM2 Fault Status 0 1298
        static const uint32_t PWM2FLTSTAT1_OFFSET = 0x908; // 0x908 PWM2FLTSTAT1 - 0x0000.0000 PWM2 Fault Status 1 1300
        static const uint32_t PWM3FLTSTAT0_OFFSET = 0x984; // 0x984 PWM3FLTSTAT0 - 0x0000.0000 PWM3 Fault Status 0 1298
        static const uint32_t PWM3FLTSTAT1_OFFSET = 0x988; // 0x988 PWM3FLTSTAT1 - 0x0000.0000 PWM3 Fault Status 1 1300
        static const uint32_t PWMPP_OFFSET = 0xFC0; // 0xFC0 PWMPP RO 0x0000.0314 PWM Peripheral Properties 1303
};

#endif //PWM_H
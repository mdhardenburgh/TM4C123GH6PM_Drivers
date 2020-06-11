/**
 * @file adc.h
 * @brief TM4C123GH6PM ADC Driver Declaration
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
 * @class Adc
 * @brief TM4C123GH6PM ADC Driver
 * 
 * @section adcDescription ADC Description
 * 
 * The TM4C123GH6PM microcontroller ADC has 12-bit resolution at 1Msps. There
 * are two ADC blocks and they share the 12 input channels. Other features include:
 *      - Single-ended and differential-input configurations
 *      - On-chip internal temperature sensor
 *      - Optional phase shift in sample time programmable from 22.5º to 337.5º
 *      - Four programmable sample conversion sequencers from one to eight 
 *        entries long, with corresponding conversion result FIFOs
 *      - Flexible trigger control
 *          - Controller (software)
 *          - Timers
 *          - Analog Comparators
 *          - PWM
 *          - GPIO
 *      - Hardware averaging of up to 64 samples
 *      -  Eight digital comparators
 *      - Power and ground for the analog circuitry is separate from the digital 
 *        power and ground
 *      - Efficient transfers using Micro Direct Memory Access Controller (µDMA)
 *          - Dedicated channel for each sample sequencer
 *          - ADC module uses burst requests for DMA
 * 
 * For more detailed information on the ADC please see page 799 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection adcSignalDescription ADC Signal Description
 * 
 * The following table lists the GPIO pin mux and physical pin number of the
 * pins that can be muxed for use by the ADC. To configure a pin for analog use
 * clear the coresponding GPIO's \c DEN bit in the GPIO Digital Enable (GPIODEN)
 * register and set the coresponding \c AMSEL bit in the GPIO Analog Mode Select 
 * (GPIOAMSEL) register. 
 * 
 * @image html adcSignalPins.PNG
 * @image latex adcSignalPins.PNG
 * 
 * @subsection adcSystemControlRegisterDescription ADC System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Legacy registers not supported.
 * 
 * @subsection adcRegisterDescription ADC Register Description
 * 
 * The Adc class contains a list of ADC registers listed as an offset relative 
 * to the hexadecimal base address of the ADC module block, ADC0 or ADC1. 
 * Note that the ADC module clock must be enabled before the registers can be 
 * programmed (see page 352). There must be a delay of 3 system clocks after the 
 * ADC module clock is enabled before any ADC module registers are accessed.
 * 
 */

#ifndef ADC_H
#define ADC_H

#include "../systemControl/systemControl.h"

enum class adcModule : uint32_t{module0, module1};

enum class ssPriority0 : uint32_t{zeroth, first, second, third};
enum class ssPriority1 : uint32_t{zeroth = 0 << 4, first = 1 << 4, second = 2 << 4, third = 3 << 4};
enum class ssPriority2 : uint32_t{zeroth = 0 << (2 * 4), first = 1 << (2 * 4), second = 2 << (2 * 4), third = 3 << (2 * 4)};
enum class ssPriority3 : uint32_t{zeroth = 0 << (3 * 4), first = 1 << (3 * 4), second = 2 << (3 * 4), third = 3 << (3 * 4)};

/**
 * Samples and FIFO Depth
 * SS0 = 8, SS1 = 4, SS2 = 4, SS3 = 1
 */
enum class sampleSequencer : uint32_t{SS0, SS1, SS2, SS3};

enum class ssTriggerSource : uint32_t{processor = 0x0, analogComparator0 = 0x1, analogComparator1 = 0x2, gpio = 0x4, timer = 0x5, pwmGen0 = 0x6, pwmGen1 = 0x7, pwmGen2 = 0x8, pwmGen3 = 0x9, continousSampling = 0xF};
// enum class ssTriggerSource1 : uint32_t{processor = 0x0 << 4, analogComparator0 = 0x1 << 4, analogComparator1 = 0x2 << 4, gpio = 0x4 << 4, timer = 0x5 << 4, pwmGen0 = 0x6 << 4, pwmGen1 = 0x7 << 4, pwmGen2 = 0x8 << 4, pwmGen3 = 0x9 << 4, continousSampling = 0xF << 4};
// enum class ssTriggerSource2 : uint32_t{processor = 0x0 << (4*2), analogComparator0 = 0x1 << (4*2), analogComparator1 = 0x2 << (4*2), gpio = 0x4 << (4*2), timer = 0x5 << (4*2), pwmGen0 = 0x6 << (4*2), pwmGen1 = 0x7 << (4*2), pwmGen2 = 0x8 << (4*2), pwmGen3 = 0x9 << (4*2), continousSampling = 0xF << (4*2)};
// enum class ssTriggerSource3 : uint32_t{processor = 0x0 << (4*3), analogComparator0 = 0x1 << (4*3), analogComparator1 = 0x2 << (4*3), gpio = 0x4 << (4*3), timer = 0x5 << (4*3), pwmGen0 = 0x6 << (4*3), pwmGen1 = 0x7 << (4*3), pwmGen2 = 0x8 << (4*3), pwmGen3 = 0x9 << (4*3), continousSampling = 0xF << (4*3)};

enum class ssInputSrc0 : uint32_t{AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN8, AIN9, AIN10, AIN11};
enum class ssInputSrc1 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << 4, AIN1 = (uint32_t)ssInputSrc0::AIN1 << 4, AIN2 = (uint32_t)ssInputSrc0::AIN2 << 4, AIN3 = (uint32_t)ssInputSrc0::AIN3 << 4, AIN4 = (uint32_t)ssInputSrc0::AIN4 << 4, AIN5 = (uint32_t)ssInputSrc0::AIN5 << 4, AIN6 = (uint32_t)ssInputSrc0::AIN6 << 4, AIN7 = (uint32_t)ssInputSrc0::AIN7 << 4, AIN8 = (uint32_t)ssInputSrc0::AIN8 << 4, AIN9 = (uint32_t)ssInputSrc0::AIN9 << 4, AIN10 = (uint32_t)ssInputSrc0::AIN10 << 4, AIN11 = (uint32_t)ssInputSrc0::AIN11 << 4};
enum class ssInputSrc2 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << (4*2), AIN1 = (uint32_t)ssInputSrc0::AIN1 << (4*2), AIN2 = (uint32_t)ssInputSrc0::AIN2 << (4*2), AIN3 = (uint32_t)ssInputSrc0::AIN3 << (4*2), AIN4 = (uint32_t)ssInputSrc0::AIN4 << (4*2), AIN5 = (uint32_t)ssInputSrc0::AIN5 << (4*2), AIN6 = (uint32_t)ssInputSrc0::AIN6 << (4*2), AIN7 = (uint32_t)ssInputSrc0::AIN7 << (4*2), AIN8 = (uint32_t)ssInputSrc0::AIN8 << (4*2), AIN9 = (uint32_t)ssInputSrc0::AIN9 << (4*2), AIN10 = (uint32_t)ssInputSrc0::AIN10 << (4*2), AIN11 = (uint32_t)ssInputSrc0::AIN11 << (4*2)};
enum class ssInputSrc3 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << (4*3), AIN1 = (uint32_t)ssInputSrc0::AIN1 << (4*3), AIN2 = (uint32_t)ssInputSrc0::AIN2 << (4*3), AIN3 = (uint32_t)ssInputSrc0::AIN3 << (4*3), AIN4 = (uint32_t)ssInputSrc0::AIN4 << (4*3), AIN5 = (uint32_t)ssInputSrc0::AIN5 << (4*3), AIN6 = (uint32_t)ssInputSrc0::AIN6 << (4*3), AIN7 = (uint32_t)ssInputSrc0::AIN7 << (4*3), AIN8 = (uint32_t)ssInputSrc0::AIN8 << (4*3), AIN9 = (uint32_t)ssInputSrc0::AIN9 << (4*3), AIN10 = (uint32_t)ssInputSrc0::AIN10 << (4*3), AIN11 = (uint32_t)ssInputSrc0::AIN11 << (4*3)};
enum class ssInputSrc4 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << (4*4), AIN1 = (uint32_t)ssInputSrc0::AIN1 << (4*4), AIN2 = (uint32_t)ssInputSrc0::AIN2 << (4*4), AIN3 = (uint32_t)ssInputSrc0::AIN3 << (4*4), AIN4 = (uint32_t)ssInputSrc0::AIN4 << (4*4), AIN5 = (uint32_t)ssInputSrc0::AIN5 << (4*4), AIN6 = (uint32_t)ssInputSrc0::AIN6 << (4*4), AIN7 = (uint32_t)ssInputSrc0::AIN7 << (4*4), AIN8 = (uint32_t)ssInputSrc0::AIN8 << (4*4), AIN9 = (uint32_t)ssInputSrc0::AIN9 << (4*4), AIN10 = (uint32_t)ssInputSrc0::AIN10 << (4*4), AIN11 = (uint32_t)ssInputSrc0::AIN11 << (4*4)};
enum class ssInputSrc5 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << (4*5), AIN1 = (uint32_t)ssInputSrc0::AIN1 << (4*5), AIN2 = (uint32_t)ssInputSrc0::AIN2 << (4*5), AIN3 = (uint32_t)ssInputSrc0::AIN3 << (4*5), AIN4 = (uint32_t)ssInputSrc0::AIN4 << (4*5), AIN5 = (uint32_t)ssInputSrc0::AIN5 << (4*5), AIN6 = (uint32_t)ssInputSrc0::AIN6 << (4*5), AIN7 = (uint32_t)ssInputSrc0::AIN7 << (4*5), AIN8 = (uint32_t)ssInputSrc0::AIN8 << (4*5), AIN9 = (uint32_t)ssInputSrc0::AIN9 << (4*5), AIN10 = (uint32_t)ssInputSrc0::AIN10 << (4*5), AIN11 = (uint32_t)ssInputSrc0::AIN11 << (4*5)};
enum class ssInputSrc6 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << (4*6), AIN1 = (uint32_t)ssInputSrc0::AIN1 << (4*6), AIN2 = (uint32_t)ssInputSrc0::AIN2 << (4*6), AIN3 = (uint32_t)ssInputSrc0::AIN3 << (4*6), AIN4 = (uint32_t)ssInputSrc0::AIN4 << (4*6), AIN5 = (uint32_t)ssInputSrc0::AIN5 << (4*6), AIN6 = (uint32_t)ssInputSrc0::AIN6 << (4*6), AIN7 = (uint32_t)ssInputSrc0::AIN7 << (4*6), AIN8 = (uint32_t)ssInputSrc0::AIN8 << (4*6), AIN9 = (uint32_t)ssInputSrc0::AIN9 << (4*6), AIN10 = (uint32_t)ssInputSrc0::AIN10 << (4*6), AIN11 = (uint32_t)ssInputSrc0::AIN11 << (4*6)};
enum class ssInputSrc7 : uint32_t{AIN0 = (uint32_t)ssInputSrc0::AIN0 << (4*7), AIN1 = (uint32_t)ssInputSrc0::AIN1 << (4*7), AIN2 = (uint32_t)ssInputSrc0::AIN2 << (4*7), AIN3 = (uint32_t)ssInputSrc0::AIN3 << (4*7), AIN4 = (uint32_t)ssInputSrc0::AIN4 << (4*7), AIN5 = (uint32_t)ssInputSrc0::AIN5 << (4*7), AIN6 = (uint32_t)ssInputSrc0::AIN6 << (4*7), AIN7 = (uint32_t)ssInputSrc0::AIN7 << (4*7), AIN8 = (uint32_t)ssInputSrc0::AIN8 << (4*7), AIN9 = (uint32_t)ssInputSrc0::AIN9 << (4*7), AIN10 = (uint32_t)ssInputSrc0::AIN10 << (4*7), AIN11 = (uint32_t)ssInputSrc0::AIN11 << (4*7)};

enum class ssControl0 : uint32_t{D0 = (uint32_t)setORClear::set, END0 = (uint32_t)setORClear::set << 1, IE0 = (uint32_t)setORClear::set << 2, TS0 = (uint32_t)setORClear::set << 3};
enum class ssControl1 : uint32_t{D1 = (uint32_t)ssControl0::D0 << 4, END1 = (uint32_t)ssControl0::END0 << 4, IE1 = (uint32_t)ssControl0::IE0 << 4, TS1 = (uint32_t)ssControl0::TS0 << 4};
enum class ssControl2 : uint32_t{D2 = (uint32_t)ssControl0::D0 << (4*2), END2 = (uint32_t)ssControl0::END0 << (4*2), IE2 = (uint32_t)ssControl0::IE0 << (4*2), TS2 = (uint32_t)ssControl0::TS0 << (4*2)};
enum class ssControl3 : uint32_t{D3 = (uint32_t)ssControl0::D0 << (4*3), END3 = (uint32_t)ssControl0::END0 << (4*3), IE3 = (uint32_t)ssControl0::IE0 << (4*3), TS3 = (uint32_t)ssControl0::TS0 << (4*3)};
enum class ssControl4 : uint32_t{D4 = (uint32_t)ssControl0::D0 << (4*4), END4 = (uint32_t)ssControl0::END0 << (4*4), IE4 = (uint32_t)ssControl0::IE0 << (4*4), TS4 = (uint32_t)ssControl0::TS0 << (4*4)};
enum class ssControl5 : uint32_t{D5 = (uint32_t)ssControl0::D0 << (4*5), END5 = (uint32_t)ssControl0::END0 << (4*5), IE5 = (uint32_t)ssControl0::IE0 << (4*5), TS5 = (uint32_t)ssControl0::TS0 << (4*5)};
enum class ssControl6 : uint32_t{D6 = (uint32_t)ssControl0::D0 << (4*6), END6 = (uint32_t)ssControl0::END0 << (4*6), IE6 = (uint32_t)ssControl0::IE0 << (4*6), TS6 = (uint32_t)ssControl0::TS0 << (4*6)};
enum class ssControl7 : uint32_t{D7 = (uint32_t)ssControl0::D0 << (4*7), END7 = (uint32_t)ssControl0::END0 << (4*7), IE7 = (uint32_t)ssControl0::IE0 << (4*7), TS7 = (uint32_t)ssControl0::TS0 << (4*7)};

enum class hardwareAvg : uint32_t{none = (uint32_t)0x0, times2 = (uint32_t)0x1, times4 = (uint32_t)0x2, times8 = (uint32_t)0x3, times16 = (uint32_t)0x4, times32 = (uint32_t)0x5, times64 = (uint32_t)0x6};
enum class phaseDelay : uint32_t{ _0_0, _22_5, _45, _67_5, _90, _112_5, _135, _157_5, _180, _202_5, _225, _247_5, _270, _292_5, _315, _337_5};

enum class ssDcOperation : uint32_t{S0DCOP = (uint32_t)setORClear::set, S1DCOP = ((uint32_t)ssDcOperation::S0DCOP) << 4, S2DCOP = ((uint32_t)ssDcOperation::S0DCOP << (4*2)), S3DCOP = ((uint32_t)ssDcOperation::S0DCOP << (4*3)), S4DCOP = ((uint32_t)ssDcOperation::S0DCOP << (4*4)), S5DCOP = ((uint32_t)ssDcOperation::S0DCOP << (4*5)), S6DCOP = ((uint32_t)ssDcOperation::S0DCOP << (4*6)), S7DCOP = ((uint32_t)ssDcOperation::S0DCOP << (4*7))};

enum class ssDcSelect0 : uint32_t{dc0, dc1, dc2, dc3, dc4, dc5, dc6, dc7};
enum class ssDcSelect1 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << 4, dc1 = (uint32_t)ssDcSelect0::dc1 << 4, dc2 = (uint32_t)ssDcSelect0::dc2 << 4, dc3 = (uint32_t)ssDcSelect0::dc3 << 4, dc4 = (uint32_t)ssDcSelect0::dc4 << 4, dc5 = (uint32_t)ssDcSelect0::dc5 << 4, dc6 = (uint32_t)ssDcSelect0::dc6 << 4, dc7 = (uint32_t)ssDcSelect0::dc7 << 4};
enum class ssDcSelect2 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << (4*2), dc1 = (uint32_t)ssDcSelect0::dc1 << (4*2), dc2 = (uint32_t)ssDcSelect0::dc2 << (4*2), dc3 = (uint32_t)ssDcSelect0::dc3 << (4*2), dc4 = (uint32_t)ssDcSelect0::dc4 << (4*2), dc5 = (uint32_t)ssDcSelect0::dc5 << (4*2), dc6 = (uint32_t)ssDcSelect0::dc6 << (4*2), dc7 = (uint32_t)ssDcSelect0::dc7 << (4*2)};
enum class ssDcSelect3 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << (4*3), dc1 = (uint32_t)ssDcSelect0::dc1 << (4*3), dc2 = (uint32_t)ssDcSelect0::dc2 << (4*3), dc3 = (uint32_t)ssDcSelect0::dc3 << (4*3), dc4 = (uint32_t)ssDcSelect0::dc4 << (4*3), dc5 = (uint32_t)ssDcSelect0::dc5 << (4*3), dc6 = (uint32_t)ssDcSelect0::dc6 << (4*3), dc7 = (uint32_t)ssDcSelect0::dc7 << (4*3)};
enum class ssDcSelect4 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << (4*4), dc1 = (uint32_t)ssDcSelect0::dc1 << (4*4), dc2 = (uint32_t)ssDcSelect0::dc2 << (4*4), dc3 = (uint32_t)ssDcSelect0::dc3 << (4*4), dc4 = (uint32_t)ssDcSelect0::dc4 << (4*4), dc5 = (uint32_t)ssDcSelect0::dc5 << (4*4), dc6 = (uint32_t)ssDcSelect0::dc6 << (4*4), dc7 = (uint32_t)ssDcSelect0::dc7 << (4*4)};
enum class ssDcSelect5 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << (4*5), dc1 = (uint32_t)ssDcSelect0::dc1 << (4*5), dc2 = (uint32_t)ssDcSelect0::dc2 << (4*5), dc3 = (uint32_t)ssDcSelect0::dc3 << (4*5), dc4 = (uint32_t)ssDcSelect0::dc4 << (4*5), dc5 = (uint32_t)ssDcSelect0::dc5 << (4*5), dc6 = (uint32_t)ssDcSelect0::dc6 << (4*5), dc7 = (uint32_t)ssDcSelect0::dc7 << (4*5)};
enum class ssDcSelect6 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << (4*6), dc1 = (uint32_t)ssDcSelect0::dc1 << (4*6), dc2 = (uint32_t)ssDcSelect0::dc2 << (4*6), dc3 = (uint32_t)ssDcSelect0::dc3 << (4*6), dc4 = (uint32_t)ssDcSelect0::dc4 << (4*6), dc5 = (uint32_t)ssDcSelect0::dc5 << (4*6), dc6 = (uint32_t)ssDcSelect0::dc6 << (4*6), dc7 = (uint32_t)ssDcSelect0::dc7 << (4*6)};
enum class ssDcSelect7 : uint32_t{dc0 = (uint32_t)ssDcSelect0::dc0 << (4*7), dc1 = (uint32_t)ssDcSelect0::dc1 << (4*7), dc2 = (uint32_t)ssDcSelect0::dc2 << (4*7), dc3 = (uint32_t)ssDcSelect0::dc3 << (4*7), dc4 = (uint32_t)ssDcSelect0::dc4 << (4*7), dc5 = (uint32_t)ssDcSelect0::dc5 << (4*7), dc6 = (uint32_t)ssDcSelect0::dc6 << (4*7), dc7 = (uint32_t)ssDcSelect0::dc7 << (4*7)};

enum class dcControl_CIM : uint32_t{always, once, hysteresisAlways, hysteresisOnce};
enum class dcControl_CIC : uint32_t{lowBand = 0x0 << 2, midBand = 0x1 << 2, highBand = 0x3 << 2};
enum class dcControl_CIE : uint32_t{disable = ((uint32_t)setORClear::clear) << 4, enable = ((uint32_t)setORClear::set) << 4};
enum class dcControl_CTM : uint32_t{always = 0x0 << 8, once = 0x1 << 8, hysteresisAlways = 0x2 << 8, hysteresisOnce = 0x3 << 8};
enum class dcControl_CTC : uint32_t{owBand = 0x0 << 10, midBand = 0x1 << 10, highBand = 0x3 << 10};
enum class dcControl_CTE : uint32_t{disable = ((uint32_t)setORClear::clear) << 12, enable = ((uint32_t)setORClear::set) << 12};


class Adc
{
    public:
        Adc();
        ~Adc();

        void initializeModule(uint32_t adcModule, uint32_t sequencerPriority, uint32_t hardwareAveraging, uint32_t phaseDelay);

        void initializeForPolling(uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, void (*action)(void));
        void initializeForInterrupt(uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, uint32_t interruptPriority);
        void enableSampleSequencer(void);
        void enableSampleSequencerDc(uint32_t dcOperation, uint32_t dcSelect);

        static void initializeDc(uint32_t adcModule, uint32_t dc, uint32_t bitField, uint32_t highBand, uint32_t lowBand);

        void pollStatus(void);
        void pollDigitalComparator(void);
        // void initializeDmaOperation(void);

        void initiateSampling(void);

        uint32_t getAdcSample(void);
        void clearInterrupt(void);

        static uint32_t getDcInterruptStatus(uint32_t adcModule, uint32_t digitalComparator);
        static void clearDcInterrupt(uint32_t adcModule, uint32_t digitalComparator);

        static uint32_t getAdcResolution();

    private:

        void initialization(void);

        void (*action)(void);

        uint32_t baseAddress;
        uint32_t adcModule;
        uint32_t sampleSequencer;
        uint32_t sequencerPriority;
        uint32_t sequencerTrigSrc;
        uint32_t inputSource;
        uint32_t sequencerControl;

        static const uint32_t ssOffset = 0x20;

        static const uint32_t adc0BaseAddress = 0x40038000; // ADC block 0 base address
        static const uint32_t adc1BaseAddress = 0x40039000; // ADC block 1 base address

        static const uint32_t PPADC_OFFSET = 0x338; // 0x338 PPADC RO 0x0000.0003 Analog-to-Digital Converter Peripheral Present 303
        static const uint32_t SRADC_OFFSET = 0x538; // 0x538 SRADC RW 0x0000.0000 Analog-to-Digital Converter Software Reset 327 
        static const uint32_t RCGCADC_OFFSET = 0x638; // 0x638 RCGCADC RW 0x0000.0000 Analog-to-Digital Converter Run Mode Clock Gating Control 352
        static const uint32_t SCGCADC_OFFSET = 0x738; // 0x738 SCGCADC RW 0x0000.0000 Analog-to-Digital Converter Sleep Mode Clock Gating Control 374
        static const uint32_t DCGCADC_OFFSET = 0x838; // 0x838 DCGCADC RW 0x0000.0000 Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control 396
        static const uint32_t PRADC_OFFSET = 0xA38; // 0xA38 PRADC RO 0x0000.0000 Analog-to-Digital Converter Peripheral Ready 418

        static const uint32_t ADCACTSS_OFFSET = 0x000; // 0x000 ADCACTSS RW 0x0000.0000 ADC Active Sample Sequencer 821
        static const uint32_t ADCRIS_OFFSET = 0x004; // 0x004 ADCRIS RO 0x0000.0000 ADC Raw Interrupt Status 823
        static const uint32_t ADCIM_OFFSET = 0x008; // 0x008 ADCIM RW 0x0000.0000 ADC Interrupt Mask 825
        static const uint32_t ADCISC_OFFSET = 0x00C; // 0x00C ADCISC RW1C 0x0000.0000 ADC Interrupt Status and Clear 828
        static const uint32_t ADCOSTAT_OFFSET = 0x010; // 0x010 ADCOSTAT RW1C 0x0000.0000 ADC Overflow Status 831
        static const uint32_t ADCEMUX_OFFSET = 0x014; // 0x014 ADCEMUX RW 0x0000.0000 ADC Event Multiplexer Select 833
        static const uint32_t ADCUSTAT_OFFSET = 0x018; // 0x018 ADCUSTAT RW1C 0x0000.0000 ADC Underflow Status 838
        static const uint32_t ADCTSSEL_OFFSET = 0x01C; // 0x01C ADCTSSEL RW 0x0000.0000 ADC Trigger Source Select 839
        static const uint32_t ADCSSPRI_OFFSET = 0x020; // 0x020 ADCSSPRI RW 0x0000.3210 ADC Sample Sequencer Priority 841
        static const uint32_t ADCSPC_OFFSET = 0x024; // 0x024 ADCSPC RW 0x0000.0000 ADC Sample Phase Control 843
        static const uint32_t ADCPSSI_OFFSET = 0x028; // 0x028 ADCPSSI RW - ADC Processor Sample Sequence Initiate 845
        static const uint32_t ADCSAC_OFFSET = 0x030; // 0x030 ADCSAC RW 0x0000.0000 ADC Sample Averaging Control 847
        static const uint32_t ADCDCISC_OFFSET = 0x034; // 0x034 ADCDCISC RW1C 0x0000.0000 ADC Digital Comparator Interrupt Status and Clear 848
        static const uint32_t ADCCTL_OFFSET = 0x038; // 0x038 ADCCTL RW 0x0000.0000 ADC Control 850
        static const uint32_t ADCSSMUX0_OFFSET = 0x040; // 0x040 ADCSSMUX0 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 0 851
        static const uint32_t ADCSSCTL0_OFFSET = 0x044; // 0x044 ADCSSCTL0 RW 0x0000.0000 ADC Sample Sequence Control 0 853
        static const uint32_t ADCSSFIFO0_OFFSET = 0x048; // 0x048 ADCSSFIFO0 RO - ADC Sample Sequence Result FIFO 0 860
        static const uint32_t ADCSSFSTAT0_OFFSET = 0x04C; // 0x04C ADCSSFSTAT0 RO 0x0000.0100 ADC Sample Sequence FIFO 0 Status 861
        static const uint32_t ADCSSOP0_OFFSET = 0x050; // 0x050 ADCSSOP0 RW 0x0000.0000 ADC Sample Sequence 0 Operation 863
        static const uint32_t ADCSSDC0_OFFSET = 0x054; // 0x054 ADCSSDC0 RW 0x0000.0000 ADC Sample Sequence 0 Digital Comparator Select 865
        static const uint32_t ADCSSMUX1_OFFFSET = 0x060; // 0x060 ADCSSMUX1 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 1 867
        static const uint32_t ADCSSCTL1_OFFSET = 0x064; // 0x064 ADCSSCTL1 RW 0x0000.0000 ADC Sample Sequence Control 1 868
        static const uint32_t ADCSSFIFO1_OFFSET = 0x068; // 0x068 ADCSSFIFO1 RO - ADC Sample Sequence Result FIFO 1 860
        static const uint32_t ADCSSFSTAT1_OFFSET = 0x06C; // 0x06C ADCSSFSTAT1 RO 0x0000.0100 ADC Sample Sequence FIFO 1 Status 861
        static const uint32_t ADCSSOP1_OFFSET = 0x070; // 0x070 ADCSSOP1 RW 0x0000.0000 ADC Sample Sequence 1 Operation 872
        static const uint32_t ADCSSDC1_OFFSET = 0x074; // 0x074 ADCSSDC1 RW 0x0000.0000 ADC Sample Sequence 1 Digital Comparator Select 873
        static const uint32_t ADCSSMUX2_OFFSET = 0x080; // 0x080 ADCSSMUX2 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 2 867
        static const uint32_t ADCSSCTL2_OFFSET = 0x084; // 0x084 ADCSSCTL2 RW 0x0000.0000 ADC Sample Sequence Control 2 868
        static const uint32_t ADCSSFIFO2_OFFSET = 0x088; // 0x088 ADCSSFIFO2 RO - ADC Sample Sequence Result FIFO 2 860
        static const uint32_t ADCSSFSTAT2_OFFSET = 0x08C; // 0x08C ADCSSFSTAT2 RO 0x0000.0100 ADC Sample Sequence FIFO 2 Status 861
        static const uint32_t ADCSSOP2_OFFSET = 0x090; // 0x090 ADCSSOP2 RW 0x0000.0000 ADC Sample Sequence 2 Operation 872
        static const uint32_t ADCSSDC2_OFFSET = 0x094; // 0x094 ADCSSDC2 RW 0x0000.0000 ADC Sample Sequence 2 Digital Comparator Select 873
        static const uint32_t ADCSSMUX3_OFFSET = 0x0A0; // 0x0A0 ADCSSMUX3 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 3 875
        static const uint32_t ADCSSCTL3_OFFSET = 0x0A4; // 0x0A4 ADCSSCTL3 RW 0x0000.0000 ADC Sample Sequence Control 3 876
        static const uint32_t ADCSSFIFO3_OFFSET = 0x0A8; // 0x0A8 ADCSSFIFO3 RO - ADC Sample Sequence Result FIFO 3 860
        static const uint32_t ADCSSFSTAT3_OFFSET = 0x0AC; // 0x0AC ADCSSFSTAT3 RO 0x0000.0100 ADC Sample Sequence FIFO 3 Status 861
        static const uint32_t ADCSSOP3_OFFSET = 0x0B0; // 0x0B0 ADCSSOP3 RW 0x0000.0000 ADC Sample Sequence 3 Operation 878
        static const uint32_t ADCSSDC3_OFFSET = 0x0B4; // 0x0B4 ADCSSDC3 RW 0x0000.0000 ADC Sample Sequence 3 Digital Comparator Select 879
        static const uint32_t ADCDCRIC_OFFSET = 0xD00; // 0xD00 ADCDCRIC WO 0x0000.0000 ADC Digital Comparator Reset Initial Conditions 880
        static const uint32_t ADCDCCTL0_OFFSET = 0xE00; // 0xE00 ADCDCCTL0 RW 0x0000.0000 ADC Digital Comparator Control 0 885
        static const uint32_t ADCDCCTL1_OFFSET = 0xE04; // 0xE04 ADCDCCTL1 RW 0x0000.0000 ADC Digital Comparator Control 1 885
        static const uint32_t ADCDCCTL2_OFFSET = 0xE08; // 0xE08 ADCDCCTL2 RW 0x0000.0000 ADC Digital Comparator Control 2 885
        static const uint32_t ADCDCCTL3_OFFSET = 0xE0C; // 0xE0C ADCDCCTL3 RW 0x0000.0000 ADC Digital Comparator Control 3 885
        static const uint32_t ADCDCCTL4_OFFSET = 0xE10; // 0xE10 ADCDCCTL4 RW 0x0000.0000 ADC Digital Comparator Control 4 885
        static const uint32_t ADCDCCTL5_OFFSET = 0xE14; // 0xE14 ADCDCCTL5 RW 0x0000.0000 ADC Digital Comparator Control 5 885
        static const uint32_t ADCDCCTL6_OFFSET = 0xE18; // 0xE18 ADCDCCTL6 RW 0x0000.0000 ADC Digital Comparator Control 6 885
        static const uint32_t ADCDCCTL7_OFFSET = 0xE1C; // 0xE1C ADCDCCTL7 RW 0x0000.0000 ADC Digital Comparator Control 7 885
        static const uint32_t ADCDCCMP0_OFFSET = 0xE40; // 0xE40 ADCDCCMP0 RW 0x0000.0000 ADC Digital Comparator Range 0 888
        static const uint32_t ADCDCCMP1_OFFSET = 0xE44; // 0xE44 ADCDCCMP1 RW 0x0000.0000 ADC Digital Comparator Range 1 888
        static const uint32_t ADCDCCMP2_OFFSET = 0xE48; // 0xE48 ADCDCCMP2 RW 0x0000.0000 ADC Digital Comparator Range 2 888
        static const uint32_t ADCDCCMP3_OFFSET = 0xE4C; // 0xE4C ADCDCCMP3 RW 0x0000.0000 ADC Digital Comparator Range 3 888
        static const uint32_t ADCDCCMP4_OFFSET = 0xE50; // 0xE50 ADCDCCMP4 RW 0x0000.0000 ADC Digital Comparator Range 4 888
        static const uint32_t ADCDCCMP5_OFFSET = 0xE54; // 0xE54 ADCDCCMP5 RW 0x0000.0000 ADC Digital Comparator Range 5 888
        static const uint32_t ADCDCCMP6_OFFSET = 0xE58; // 0xE58 ADCDCCMP6 RW 0x0000.0000 ADC Digital Comparator Range 6 888
        static const uint32_t ADCDCCMP7_OFFSET = 0xE5C; // 0xE5C ADCDCCMP7 RW 0x0000.0000 ADC Digital Comparator Range 7 888
        static const uint32_t ADCPP_OFFSET = 0xFC0; // 0xFC0 ADCPP RO 0x00B0.20C7 ADC Peripheral Properties 889
        static const uint32_t ADCPC_OFFSET = 0xFC4; // 0xFC4 ADCPC RW 0x0000.0007 ADC Peripheral Configuration 891
        static const uint32_t ADCCC_OFFSET = 0xFC8; // 0xFC8 ADCCC RW 0x0000.0000 ADC Clock Configuration 892

};

#endif //ADC_H
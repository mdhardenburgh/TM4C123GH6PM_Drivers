/**
 * @file adc.cpp
 * @brief TM4C123GH6PM ADC Driver Definition
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
 * 
 */
#include "adc.h"

/**
 * @brief empty constructor placeholder
 */
Adc::Adc()
{

}

/**
 * @brief empty deconstructor placeholder
 */
Adc::~Adc()
{

}

void Adc::initializeModule(uint32_t adcModule, uint32_t sequencerPriority, uint32_t hardwareAveraging, uint32_t phaseDelay)
{
    (*this).adcModule = adcModule;
    baseAddress = adc0BaseAddress + (adcModule * 0x1000);

    //0. Enable ADC module clock
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCADC_OFFSET)), set, adcModule, 1, RW);
    while(Register::getRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + PRADC_OFFSET), adcModule, 1, RO) == 0)
    {
        //Ready??
    }

    /*
     * 0.A If required by the application, reconfigure the sample sequencer 
     * priorities in the ADCSSPRI register. The default configuration has 
     * Sample Sequencer 0 with the highest priority and Sample Sequencer 3 as 
     * the lowest priority.
     */
    for(int i = 0; i < 4; i++)
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCSSPRI_OFFSET)), sequencerPriority >> (4 * i), i * 4, 1 + 1, RW);
    }

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCSAC_OFFSET)), hardwareAveraging, 0, 2 + 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCSPC_OFFSET)), phaseDelay, 0, 3 + 1, RW);
    
}

/**
 * @brief Initialization for a particular sample sequencer and polls Raw interrupt status
 * 
 * @param adcModule Clock to be intialized for the ADC module
 * @param action when polling the adc, the action to be taken when RIS is activate
 */
void Adc::initializeForPolling(uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, void (*action)(void))
{
    (*this).sampleSequencer = sampleSequencer;
    (*this).sequencerTrigSrc = sequencerTrigSrc;
    (*this).inputSource = inputSource;
    (*this).sequencerControl = sequencerControl;
    initialization();
    (*this).action = action;

}

void Adc::initializeForInterrupt(uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, uint32_t interruptPriority)
{
    (*this).sampleSequencer = sampleSequencer;
    (*this).sequencerTrigSrc = sequencerTrigSrc;
    (*this).inputSource = inputSource;
    (*this).sequencerControl = sequencerControl;
    initialization();
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCIM_OFFSET)), set, sampleSequencer, 1, RW);

    if(adcModule == (uint32_t)adcModule::module0)
    {
        switch (sampleSequencer)
        {
            case (uint32_t)sampleSequencer::SS0:
                Nvic::activateInterrupt(ADC_0_Sequence_0_Interrupt, interruptPriority);
                break;

            case (uint32_t)sampleSequencer::SS1:
                Nvic::activateInterrupt(ADC_0_Sequence_1_Interrupt, interruptPriority);
                break;

            case (uint32_t)sampleSequencer::SS2:
                Nvic::activateInterrupt(ADC_0_Sequence_2_Interrupt, interruptPriority);
                break;

            case (uint32_t)sampleSequencer::SS3:
                Nvic::activateInterrupt(ADC_0_Sequence_3_Interrupt, interruptPriority);
                break;
            
            default:
                break;
        }
    }

    else
    {
        switch (sampleSequencer)
        {
            case (uint32_t)sampleSequencer::SS0:
                Nvic::activateInterrupt(ADC_1_Sequence_0_Interrupt, interruptPriority);
                break;

            case (uint32_t)sampleSequencer::SS1:
                Nvic::activateInterrupt(ADC_1_Sequence_1_Interrupt, interruptPriority);
                break;

            case (uint32_t)sampleSequencer::SS2:
                Nvic::activateInterrupt(ADC_1_Sequence_2_Interrupt, interruptPriority);
                break;

            case (uint32_t)sampleSequencer::SS3:
                Nvic::activateInterrupt(ADC_1_Sequence_3_Interrupt, interruptPriority);
                break;
            
            default:
                break;
        }
    }
    
}


void Adc::enableSampleSequencer(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCACTSS_OFFSET)), set, sampleSequencer, 1, RW);
}

void Adc::pollStatus(void)
{
    if(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCRIS_OFFSET)), sampleSequencer, 1, RO) == set)
    {
        action();
    }
}

void Adc::softwareTriger(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCPSSI_OFFSET)), set, sampleSequencer, 1, RW);
}

uint32_t Adc::getAdcSample(void)
{
    return(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSFIFO0_OFFSET + (ssOffset * sampleSequencer)))), 0, 11 + 1, RO));
}

void Adc::clearInterrupt(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCISC_OFFSET)), set, sampleSequencer, 1, RW1C);
}

/**
 * @brief initialize the Sample Sequencer
 * @details Sample Sequencer Configuration:
 * 
 *          Configuration of the sample sequencers is slightly more complex 
 *          than the module initialization because each sample sequencer is 
 *          completely programmable.
 */
void Adc::initialization(void)
{    

    /*
     * Sample Sequencer Configuration:
     * 
     * Configuration of the sample sequencers is slightly more complex than the 
     * module initialization because each sample sequencer is completely 
     * programmable. 
     * 
     * The configuration for each sample sequencer should be as follows:
     */

    /*
     * 1. Ensure that the sample sequencer is disabled by clearing the 
     * corresponding ASENn bit in the ADCACTSS register. Programming of the 
     * sample sequencers is allowed without having them enabled. Disabling the 
     * sequencer during programming prevents erroneous execution if a trigger
     * event were to occur during the configuration process.
     */
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCACTSS_OFFSET)), clear, sampleSequencer, 1, RW);

    /*
     * 1.A When using a PWM generator as the trigger source, use the ADC 
     * Trigger Source Select (ADCTSSEL) register to specify in which PWM module 
     * the generator is located. The default register reset selects PWM module 
     * 0 for all generators.
     */


    //2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + ADCEMUX_OFFSET)), sequencerTrigSrc, sampleSequencer * 4, 3 + 1, RW);

    //3. For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register.
    if(sampleSequencer == (uint32_t)sampleSequencer::SS0)
    {
        for(int i = 0; i < 8; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS1)
    {
        for(int i = 0; i < 4; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS2)
    {
        for(int i = 0; i < 4; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS3)
    {
        for(int i = 0; i < 1; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        }
    }

    /*
     * 4. For each sample in the sample sequence, configure the sample control 
     * bits in the corresponding nibble in the ADCSSCTLn register. When 
     * programming the last nibble, ensure that the END bit is set. Failure to 
     * set the END bit causes unpredictable behavior.
     */
    if(sampleSequencer == (uint32_t)sampleSequencer::SS0)
    {
        for(int i = 0; i < 32; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS1)
    {
        for(int i = 0; i < 16; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS2)
    {
        for(int i = 0; i < 16; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS3)
    {
        for(int i = 0; i < 4; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
        }
    }

}
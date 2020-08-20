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
AdcModule::AdcModule()
{

}

/**
 * @brief empty deconstructor placeholder
 */
AdcModule::~AdcModule()
{

}

/**
 * @brief initialize an ADC module.
 * 
 * @param adcModule to be initialized, module 0 or 1.
 * @param hardwareAveraging averages 2<SUP>n</SUP> samples before being sent to the FIFO
 * @param phaseDelay of the ADC module. Phase delay can be used to increase the
 *                   overal sample rate of the ADC module. See the datasheet for 
 *                   more details.
 * 
 */
void AdcModule::initializeModule(uint32_t adcModule, uint32_t hardwareAveraging, uint32_t phaseDelay)
{
    //0. Enable ADC module clock
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(systemControlBase + RCGCADC_OFFSET)), (uint32_t)setORClear::set, (adcModule == (uint32_t)adcModules::module0 ? 0 : 1), 1, RW);
    while(Register::getRegisterBitFieldStatus((volatile uint32_t*)(systemControlBase + PRADC_OFFSET), (adcModule == (uint32_t)adcModules::module0 ? 0 : 1), 1, RO) == 0)
    {
        //Ready??
    }

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSAC_OFFSET)), hardwareAveraging, 0, 2 + 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCCTL_OFFSET)), hardwareAveraging == 0 ? 0x0 : 0x1, 6, 1, RW);
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSPC_OFFSET)), phaseDelay, 0, 3 + 1, RW);
}

/**
 * @brief initialize an ADC module.
 * 
 * @param adcModule to be initialized, module 0 or 1.
 * @param sequencerPriority sets the priority of the sample sequencer.
 * @param hardwareAveraging averages 2<SUP>n</SUP> samples before being sent to the FIFO
 * @param phaseDelay of the ADC module. Phase delay can be used to increase the
 *                   overal sample rate of the ADC module. See the datasheet for 
 *                   more details.
 * @param sequencerPriority sets the priority of the sample sequencer.
 * 
 * @return the base address of the adc module
 */
void AdcModule::initializeModule(uint32_t adcModule, uint32_t hardwareAveraging, uint32_t phaseDelay, uint32_t sequencerPriority)
{
    
    initializeModule(adcModule, hardwareAveraging, phaseDelay);

    /*
     * 0.A If required by the application, reconfigure the sample sequencer 
     * priorities in the ADCSSPRI register. The default configuration has 
     * Sample Sequencer 0 with the highest priority and Sample Sequencer 3 as 
     * the lowest priority.
     */
    for(int i = 0; i < 4; i++)
    {
        Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSPRI_OFFSET)), sequencerPriority >> (4 * i), i * 4, 1 + 1, RW);
    }
}

uint32_t AdcModule::getAdcResolution()
{
    return(Register::getRegisterBitFieldStatus(((volatile uint32_t*)((uint32_t)adcModules::module0 + ADCPP_OFFSET)), 18, 22 - 18 + 1, RO));
}

/******************************************************************************/

/**
 * @brief empty constructor placeholder
 */
AdcSampleSequencer::AdcSampleSequencer()
{

}

/**
 * @brief empty deconstructor placeholder
 */
AdcSampleSequencer::~AdcSampleSequencer()
{

}

/**
 * @brief Initialization of a sample sequence and polls it for
 *        new samples.
 * 
 * @details ADC samples are automatically taken when there is an available
 *          spot in the sample sequencer FIFO. Therefore the samples read from
 *          the ADC module sample sequencer are not raw samples from the input,
 *          but delayed by n spots in the FIFO. Samples can only be read in 
 *          sample sequencer order.
 * 
 * @param sampleSequencer to be used.
 * @param sequencerTrigSrc sets the source that starts the particular sample sequencer
 * @param inputSource sets the input source of a particular sample in the sample sequencer
 * @param sequencerControl set the configuration of a particular sample in the sample sequncer
 * @param action taken when the RIS is set.
 */
void AdcSampleSequencer::initializeForPolling(uint32_t adcModule, uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, void (*action)(void))
{
    
    (*this).sampleSequencer = sampleSequencer;
    (*this).sequencerTrigSrc = sequencerTrigSrc;
    (*this).inputSource = inputSource;
    (*this).sequencerControl = sequencerControl;
    (*this).action = action;
    (*this).adcModule = adcModule;
    initialization();
    // (*this).action = action;

}

/**
 * @brief Initialization of a particular sample sequencer to either send the 
 *       sample to the FIFO or Digital Comparator. 
 * 
 * @details ADC samples are automatically taken when there is an available
 *          spot in the sample sequencer FIFO. In the case of a sample 
 *          sequencer spot being used by a digital comparator, I am assuming
 *          FIFO spot is empty and ignored. The samples read from
 *          the ADC module sample sequencer are not raw samples from the input,
 *          but delayed by n spots in the FIFO. Samples can only be read in 
 *          sample sequencer order. 
 * 
 * @param sampleSequencer to be used.
 * @param sequencerTrigSrc sets the source that starts the particular sample sequencer
 * @param inputSource sets the input source of a particular sample in the sample sequencer
 * @param sequencerControl set the configuration of a particular sample in the sample sequncer
 * @param action taken when the RIS is set.
 * @param sampleDcOperation sets if the sample is sent to the SS FIFO or DC
 * @param sampleDcSelect encodes which DC the sample is sent to
 * 
 * SPECIAL STUFF HERE FOR DC
 * For polling, the RIS INRDC bit is polled. When this bit is set, at least
 * one bit in the ADCDCISC register is set, meaning that a digital comparator 
 * interrupt has occurred. 
 *
 * The DC generates an interrupt on ADCDCISC and that is promoted to the ADCRIS INRDC bit.
 * The ADCIM register bit DCONSSn determines which ss interrupt line the DC interrupt is
 * sent on.
 */
void AdcSampleSequencer::initializeForPolling(uint32_t adcModule, uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, void (*action)(void), uint32_t sampleDcOperation, uint32_t sampleDcSelect)
{
    (*this).sampleDcOperation = sampleDcOperation;
    (*this).sampleDcSelect = sampleDcSelect;
    initializeForPolling(adcModule, sampleSequencer, sequencerTrigSrc, inputSource, sequencerControl, action);

}

/**
 * @brief Initialization of a particular sample sequencer with interupt functionality
 * 
 * @details ADC samples are automatically taken when there is an available
 *          spot in the sample sequencer FIFO. Therefore the samples read from
 *          the ADC module sample sequencer are not raw samples from the input,
 *          but delayed by n spots in the FIFO. Samples can only be read in 
 *          sample sequencer order. 
 * 
 *          This function enables the interrupt on a particular sample sequencer
 *          by enabling the interrupt mask, setting the interrupt priority and 
 *          enabling the interrupt in NVIC. Setting the interrupt mask promotes
 *          the RIS to the interrupt controller.
 * 
 * @param sampleSequencer to be used.
 * @param sequencerTrigSrc sets the source that starts the particular sample sequencer
 * @param inputSource sets the input source of a particular sample in the sample sequencer
 * @param sequencerControl set the configuration of a particular sample in the sample sequncer
 * @param interruptPriority of the interrupt. 0 is the highest and 7 is the lowest
 */
void AdcSampleSequencer::initializeForInterrupt(uint32_t adcModule, uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, uint32_t interruptPriority)
{
    (*this).sampleSequencer = sampleSequencer;
    (*this).sequencerTrigSrc = sequencerTrigSrc;
    (*this).inputSource = inputSource;
    (*this).sequencerControl = sequencerControl;
    (*this).adcModule = adcModule;
    initialization();
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCIM_OFFSET)), (uint32_t)setORClear::set, sampleSequencer, 1, RW);

    if(adcModule == (uint32_t)adcModules::module0) //ADC block 0 base address
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

/**
 * @brief Initialization of a particular sample sequencer and polls it for
 *        new samples.
 * 
 * @details ADC samples are automatically taken when there is an available
 *          spot in the sample sequencer FIFO. Therefore the samples read from
 *          the ADC module sample sequencer are not raw samples from the input,
 *          but delayed by n spots in the FIFO. Samples can only be read in 
 *          sample sequencer order. 
 * 
 * @param sampleSequencer to be used.
 * @param sequencerTrigSrc sets the source that starts the particular sample sequencer
 * @param inputSource sets the input source of a particular sample in the sample sequencer
 * @param sequencerControl set the configuration of a particular sample in the sample sequncer
 * @param interruptPriority of the interrupt. 0 is the highest and 7 is the lowest
 * @param sampleDcOperation sets if the sample is sent to the SS FIFO or DC
 * @param sampleDcSelect encodes which DC the sample is sent to
 * 
 * SPECIAL STUFF HERE FOR DC
 * The DC generates an interrupt on ADCDCISC and that is promoted to the ADCRIS INRDC bit.
 * The ADCIM register bit DCONSSn determines which ss interrupt line the DC interrupt is
 * sent on.
 * 
 */
void AdcSampleSequencer::initializeForInterrupt(uint32_t adcModule, uint32_t sampleSequencer, uint32_t sequencerTrigSrc, uint32_t inputSource, uint32_t sequencerControl, uint32_t interruptPriority, uint32_t sampleDcOperation, uint32_t sampleDcSelect)
{
    (*this).sampleDcOperation = sampleDcOperation;
    (*this).sampleDcSelect = sampleDcSelect;
    initializeForInterrupt(adcModule, sampleSequencer, sequencerTrigSrc, inputSource, sequencerControl, interruptPriority);
}

/**
 * @brief Enables the sample sequncer associated with the adc object
 */
void AdcSampleSequencer::enableSampleSequencer(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCACTSS_OFFSET)), (uint32_t)setORClear::set, sampleSequencer, 1, RW);
}


void AdcSampleSequencer::pollStatus(void)
{
    if(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCRIS_OFFSET)), sampleSequencer, 1, RO) == (uint32_t)setORClear::set)
    {
        action();
    }
}

//Interrupt cleared by writing to the ADCDCISC to the right ADC module
//Should this be moved the digital comparator with a getDConSS function with ADCISC?
//This needs to be merged into the regular one above this because there can be only polling function?
void AdcSampleSequencer::pollDigitalComparator(void)
{
    if(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCRIS_OFFSET)), 16, 1, RO) == (uint32_t)setORClear::set)
    {
        action();
    }
}


void AdcSampleSequencer::initiateSampling(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCPSSI_OFFSET)), (uint32_t)setORClear::set, sampleSequencer, 1, RW);
}

/**
 * @details The way the ADC works is that when the ADC FIFO is read, a new 
 *          sample is taken. Therefore, data read from the FIFO is n sample(s) 
 *          behind (FIFO depth depends on the sample sequencer) To get a 
 *          current value of the signal read n+1 times from the FIFO. In the 
 *          case of SS3, you read from the FIFO twice.
 */
uint32_t AdcSampleSequencer::getAdcSample(void)
{
    return(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSFIFO0_OFFSET + (ssOffset * sampleSequencer)))), 0, 11 + 1, RO));
}

void AdcSampleSequencer::clearInterrupt(void)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCISC_OFFSET)), (uint32_t)setORClear::set, sampleSequencer, 1, RW1C);
}


/**
 * @brief initialize the Sample Sequencer
 * @details Sample Sequencer Configuration:
 * 
 *          Configuration of the sample sequencers is slightly more complex 
 *          than the module initialization because each sample sequencer is 
 *          completely programmable.
 */
void AdcSampleSequencer::initialization(void)
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
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCACTSS_OFFSET)), (uint32_t)setORClear::clear, sampleSequencer, 1, RW);

    /*
     * 1.A When using a PWM generator as the trigger source, use the ADC 
     * Trigger Source Select (ADCTSSEL) register to specify in which PWM module 
     * the generator is located. The default register reset selects PWM module 
     * 0 for all generators.
     */


    //2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCEMUX_OFFSET)), sequencerTrigSrc, sampleSequencer * 4, 3 + 1, RW);

    //3. For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register.
    if(sampleSequencer == (uint32_t)sampleSequencer::SS0)
    {
        //3. For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register.
        for(int i = 0; i < 8; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
            
            /*
            * 4. For each sample in the sample sequence, configure the sample control 
            * bits in the corresponding nibble in the ADCSSCTLn register. When 
            * programming the last nibble, ensure that the END bit is set. Failure to 
            * set the END bit causes unpredictable behavior.
            */
            for(int j = 0; j < 4; j++)
            {
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> ((i * 4) + j), (i * 4) + j, 1, RW);
            }

            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSOP0_OFFSET)), sampleDcOperation >> (4*i), 4*i, 1, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSDC0_OFFSET)), sampleDcSelect >> (4*i), 4*i, 4, RW);
        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS1)
    {
        //3. For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register.
        for(int i = 0; i < 4; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        
            /*
            * 4. For each sample in the sample sequence, configure the sample control 
            * bits in the corresponding nibble in the ADCSSCTLn register. When 
            * programming the last nibble, ensure that the END bit is set. Failure to 
            * set the END bit causes unpredictable behavior.
            */
            for(int j = 0; j < 4; j++)
            {
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> ((i * 4) + j), (i * 4) + j, 1, RW);
            }

            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSOP1_OFFSET)), sampleDcOperation >> (4*i), 4*i, 1, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSDC1_OFFSET)), sampleDcSelect >> (4*i), 4*i, 4, RW);
        }
        
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS2)
    {
        
        //3. For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register.
        for(int i = 0; i < 4; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        
            /*
            * 4. For each sample in the sample sequence, configure the sample control 
            * bits in the corresponding nibble in the ADCSSCTLn register. When 
            * programming the last nibble, ensure that the END bit is set. Failure to 
            * set the END bit causes unpredictable behavior.
            */
            for(int j = 0; j < 4; j++)
            {
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> ((i * 4) + j), (i * 4) + j, 1, RW);
            }

            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSOP2_OFFSET)), sampleDcOperation >> (4*i), 4*i, 1, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSDC2_OFFSET)), sampleDcSelect >> (4*i), 4*i, 4, RW);

        }
    }

    else if(sampleSequencer == (uint32_t)sampleSequencer::SS3)
    {
        //3. For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register.
        for(int i = 0; i < 1; i++)
        {
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSMUX0_OFFSET + (ssOffset * sampleSequencer)))), inputSource >> (i * 4), i * 4, 3 + 1, RW);
        
            /*
            * 4. For each sample in the sample sequence, configure the sample control 
            * bits in the corresponding nibble in the ADCSSCTLn register. When 
            * programming the last nibble, ensure that the END bit is set. Failure to
            * set the END bit causes unpredictable behavior.
            */
            for(int j = 0; j < 4; j++)
            {
                Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> ((i * 4) + j), (i * 4) + j, 1, RW);
            }

            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSOP3_OFFSET)), sampleDcOperation, 0, 1, RW);
            Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCSSDC3_OFFSET)), sampleDcSelect, 0, 4, RW);
        
        }
    }

    // /*
    //  * 4. For each sample in the sample sequence, configure the sample control 
    //  * bits in the corresponding nibble in the ADCSSCTLn register. When 
    //  * programming the last nibble, ensure that the END bit is set. Failure to 
    //  * set the END bit causes unpredictable behavior.
    //  */
    // if(sampleSequencer == (uint32_t)sampleSequencer::SS0)
    // {
    //     for(int i = 0; i < 32; i++)
    //     {
    //         Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
    //     }
    // }

    // else if(sampleSequencer == (uint32_t)sampleSequencer::SS1)
    // {
    //     for(int i = 0; i < 16; i++)
    //     {
    //         Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
    //     }
    // }

    // else if(sampleSequencer == (uint32_t)sampleSequencer::SS2)
    // {
    //     for(int i = 0; i < 16; i++)
    //     {
    //         Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
    //     }
    // }

    // else if(sampleSequencer == (uint32_t)sampleSequencer::SS3)
    // {
    //     for(int i = 0; i < 4; i++)
    //     {
    //         Register::setRegisterBitFieldStatus(((volatile uint32_t*)(baseAddress + (ADCSSCTL0_OFFSET + (ssOffset * sampleSequencer)))), sequencerControl >> i, i, 1, RW);
    //     }
    // }

}

/******************************************************************************/

/**
 * @brief Initializes the digital comparator
 * 
 * @param adcModule to init the DC for
 * @param dc to be initialized
 * @param dcControlBits settings to initialize the digital comparator
 * @param highBand 
 * @param lowBand
 * 
 */
void AdcDigitalComparator::initializeDc(uint32_t adcModule, uint32_t dc, uint32_t dcControlBits, uint32_t highBand, uint32_t lowBand)
{
    this->adcModule = adcModule;

    uint32_t CIM = 0; // Comparison Interrupt Mode bit
    uint32_t CIC = 2; // Comparison Interrupt Condition bit
    uint32_t CIE = 4; // Comparison Interrupt Enable bit
    uint32_t CTM = 8; // Comparison Trigger Mode bit
    uint32_t CTC = 10; // Comparison Trigger Condition bit
    uint32_t CTE = 12; // Comparison Trigger Enable bit

    
    uint32_t dcCtlAddress = (this->adcModule + (ADCDCCTL0_OFFSET + dc*0x4));
    uint32_t dcCmpAddress = (this->adcModule + (ADCDCCMP0_OFFSET + dc*0x4));

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCtlAddress), dcControlBits, CIM, 2, RW); // now setting Comparison Interrupt Mode
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCtlAddress), dcControlBits >> CIC, CIC, 2, RW); // now setting the Comparison Interrupt Condition
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCtlAddress), dcControlBits >> CIE, CIE, 1, RW); // now setting Comparison Interrupt Enable bit
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCtlAddress), dcControlBits >> CTM, CTM, 2, RW); // now setting Comparison Trigger Mode bit
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCtlAddress), dcControlBits >> CTC, CTC, 2, RW); // now setting the Comparison Trigger Condition
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCtlAddress), dcControlBits >> 12, 12, 1, RW); // now setting the Comparison Trigger Enable bit

    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCmpAddress), lowBand, 0, 11 + 1, RW); // sets the low band value. 12 bit number max
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)dcCmpAddress), highBand, 16, 27 - 16 + 1, RW); //sets the high band value. 12 bit number max

}


uint32_t AdcDigitalComparator::getDcInterruptStatus(uint32_t digitalComparator)
{
    return(Register::getRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCDCISC_OFFSET)), digitalComparator, 1, RW1C));
}

void AdcDigitalComparator::clearDcInterrupt(uint32_t digitalComparator)
{
    Register::setRegisterBitFieldStatus(((volatile uint32_t*)(adcModule + ADCDCISC_OFFSET)), (uint32_t)setORClear::set , digitalComparator, 1, RW1C);
}

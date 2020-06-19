/*
 * ad.c
 *
 *  Created on: 16/01/2018
 *      Author: fabio
 */

#include "ad.h"

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_adc16.h"

#include "pin_mux.h"
#include "clock_config.h"

/*
	{PTC2,  ADC0_SE4b, 0},
    {PTC8,  ADC1_SE4b, 0},
    {PTC9,  ADC1_SE5b, 0},
    {PTD1,  ADC0_SE5b, 0},
    {PTC10, ADC1_SE6b, 0},
    {PTD5,  ADC0_SE6b, 0},
    {PTC11, ADC1_SE7b, 0},
    {PTD6,  ADC0_SE7b, 0},
    {PTB0 , ADC0_SE8 , 0},
    {PTB1 , ADC0_SE9 , 0},
    {PTB2 , ADC0_SE12, 0},
    {PTB3 , ADC0_SE13, 0},
    {PTC0 , ADC0_SE14, 0},
    {PTB10, ADC1_SE14, 0},
    {PTB11, ADC1_SE15, 0},
    {PTC1 , ADC0_SE15, 0},
    {PTA17, ADC1_SE17, 0},
    //{PTE24, ADC0_SE17, 0}, //I2C pull up
    //{PTE25, ADC0_SE18, 0}, //I2C pull up
    {NC   , NC       , 0}
*/

#define	TEMP_ADC16_BASE	ADC0
#define	TEMP_ADC16_CHANNEL_GROUP 0U
#define TEMP_ADC16_USER_CHANNEL 12U

#define	LDR_ADC16_BASE	ADC0
#define	LDR_ADC16_CHANNEL_GROUP 0U
#define LDR_ADC16_USER_CHANNEL 13U

#define	POT_ADC16_BASE	ADC1
#define	POT_ADC16_CHANNEL_GROUP 0U
#define POT_ADC16_USER_CHANNEL 14U

adc16_config_t TEMPConfigStruct;
adc16_channel_config_t TEMPChannelConfigStruct;

adc16_config_t LDRConfigStruct;
adc16_channel_config_t LDRChannelConfigStruct;

adc16_config_t POTConfigStruct;
adc16_channel_config_t POTChannelConfigStruct;

void adInit(void) {

    /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */

	ADC16_GetDefaultConfig(&TEMPConfigStruct);
	ADC16_Init(TEMP_ADC16_BASE, &TEMPConfigStruct);
	ADC16_EnableHardwareTrigger(TEMP_ADC16_BASE, false); /*conferir se o trigger de software está sendo usado*/
	ADC16_DoAutoCalibration(TEMP_ADC16_BASE);
	TEMPChannelConfigStruct.channelNumber = TEMP_ADC16_USER_CHANNEL;
	TEMPChannelConfigStruct.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	TEMPChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

	ADC16_GetDefaultConfig(&LDRConfigStruct);
	ADC16_Init(LDR_ADC16_BASE, &LDRConfigStruct);
	ADC16_EnableHardwareTrigger(LDR_ADC16_BASE, false); /*conferir se o trigger de software está sendo usado*/
	ADC16_DoAutoCalibration(LDR_ADC16_BASE);
	LDRChannelConfigStruct.channelNumber = LDR_ADC16_USER_CHANNEL;
	LDRChannelConfigStruct.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	LDRChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

	ADC16_GetDefaultConfig(&POTConfigStruct);
	ADC16_Init(POT_ADC16_BASE, &POTConfigStruct);
	ADC16_EnableHardwareTrigger(POT_ADC16_BASE, false); /*conferir se o trigger de software está sendo usado*/
	ADC16_DoAutoCalibration(POT_ADC16_BASE);
	POTChannelConfigStruct.channelNumber = POT_ADC16_USER_CHANNEL;
	POTChannelConfigStruct.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	POTChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

int adRead(int channel){
	switch(channel){
		case 0:
			ADC16_SetChannelConfig(TEMP_ADC16_BASE, TEMP_ADC16_CHANNEL_GROUP, &TEMPChannelConfigStruct);
			while(0U == (kADC16_ChannelConversionDoneFlag &
						 ADC16_GetChannelStatusFlags(TEMP_ADC16_BASE, TEMP_ADC16_CHANNEL_GROUP)))
			{
			}
			return (int) ADC16_GetChannelConversionValue(TEMP_ADC16_BASE, TEMP_ADC16_CHANNEL_GROUP);
		case 1:
			ADC16_SetChannelConfig(LDR_ADC16_BASE, LDR_ADC16_CHANNEL_GROUP, &LDRChannelConfigStruct);
			while(0U == (kADC16_ChannelConversionDoneFlag &
						 ADC16_GetChannelStatusFlags(LDR_ADC16_BASE, LDR_ADC16_CHANNEL_GROUP)))
			{
			}
			return (int) ADC16_GetChannelConversionValue(LDR_ADC16_BASE, LDR_ADC16_CHANNEL_GROUP);
		case 2:
			ADC16_SetChannelConfig(POT_ADC16_BASE, POT_ADC16_CHANNEL_GROUP, &POTChannelConfigStruct);
			while(0U == (kADC16_ChannelConversionDoneFlag &
						 ADC16_GetChannelStatusFlags(POT_ADC16_BASE, POT_ADC16_CHANNEL_GROUP)))
			{
			}
			return (int) ADC16_GetChannelConversionValue(POT_ADC16_BASE, POT_ADC16_CHANNEL_GROUP);
	}
}



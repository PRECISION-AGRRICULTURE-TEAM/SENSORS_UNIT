/** @file SOIL_TEMP.c
 *  @brief This file contains the Source Code of the SOIL_TEMP Driver
 *  @author  
 */

#include "SOIL_TEMP_LOCAL.h"


void SOIL_TEMP_vidInit (void)
{
	ADC_vidInit();
	GPIO_u8SetPinDir(SOIL_TEMP_PIN,ANALOG);

}


void SOIL_TEMP_vidStartReading(void)
{
	ADC_vidSelect(SOIL_TEMP_PIN);
		ADC_vidStartConversion();
}

uint8_t SOIL_TEMP_u8ReadingStatus(void)
{
	return ADC_u8ConversionStatus();
}

uint16_t SOIL_TEMP_u16GetData(void)
{
	return ((ADC_u16GetData())*(330/0xfff));
}

uint16_t SOIL_TEMP_u16Read(void)
{
	return( ADC_u16Read(SOIL_TEMP_PIN)*(330/0xfff));
}


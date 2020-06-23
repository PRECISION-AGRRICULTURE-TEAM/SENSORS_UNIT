/** @file MOISTURE.c
 *  @brief This file contains the Source Code of the MOISTURE Driver
 *  @author  
 */

#include "MOISTURE_LOCAL.h"


void MOISTURE_vidInit (void)
{
	GPIO_u8SetPinDir(MOISTURE_PIN,ANALOG);
	ADC_vidInit();
}

uint8_t MOISTURE_u16Read(void)
{
	return (~((ADC_u16Read(MOISTURE_PIN)>>4)&0xff));
}

void MOISTURE_vidStartReading(void)
{
	ADC_vidSelect(MOISTURE_PIN);
	ADC_vidStartConversion();
}

uint8_t MOISTURE_u8ReadingStatus(void)
{
	return ADC_u8ConversionStatus();
}

uint8_t MOISTURE_u16GetData(void)
{
	return (~( ( ADC_u16GetData() >> 4 ) &0xff ) ) ;
}

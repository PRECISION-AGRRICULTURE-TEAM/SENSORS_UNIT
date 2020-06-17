/** @file ADC.c
 *  @brief This file contains the Source Code of the ADC Driver
 *  @author 
 */

//#include "stm32f10x.h"

#include "ADC_LOCAL.h"







void ADC_vidInit()
{


	RCC_APB2ENR|=1<<ADC1_EN;

//	RCC_APB2ENR|=1<<ADC2_EN;
//
//	RCC_APB2ENR|=1<<ADC3_EN;

	RCC_CFGR |=(Prescalar<<ADC_PRE);
	ADC->ADC_CR2 |=ADC_Alignement<<ALIGN    | (Continous_MODE<<ADC_CONT );
/*this for scan or multichannel mode */
	ADC->ADC_SQR1 |=  SCAN_MODE &(Total_Convertion<<L) ;
	ADC->ADC_SMPR2 |=0X00000000;

	/* need to e completed by sampling for each channel and channel sequences*/

}
uint16_t ADC_u16Read(uint8_t u8ADCNum)
{
		ADC_vidSelect(u8ADCNum);
		ADC_vidStartConversion();
		while(!ADC_u8ConversionStatus());
		return (ADC_u16GetData());
}
void ADC_vidStartConversion(void)
{
	ADC->ADC_CR2 |=  (1<< ADC_ON);
}	

void ADC_vidSelect(uint8_t CHNUM )

{
	ADC->ADC_CR2 |=  (1<< ADC_ON);
	//ADC->ADC_SQR1= 0x00000000; // Regular channel single conversion
	ADC->ADC_SQR2 = 0x00000000; //
	ADC->ADC_SQR3= (CHNUM<<0); //single mode

}
uint8_t ADC_u8ConversionStatus(void)
{
 // return 1  if conversion ended

	return Get_Bit(ADC->ADC_SR,EOC);
}

uint16_t ADC_u16GetData(void)
{
	//if (ADC_u8ConversionStatus())
		return (ADC1->ADC_DR)>>(4 &ADC_Alignement );

}
	
	
	
	
	






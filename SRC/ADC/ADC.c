/** @file ADC.c
 *  @brief This file contains the Source Code of the ADC Driver
 *  @author 
 */

#include "stm32f10x.h"
#include "ADC.h"
#include "GPIO_Driver.h"



uint32_t SAMPOS[10]={
	(0x00),//postion of pin 0 at samp register
	(0x03),//postion of pin 1 at samp register
	(0x06),//postion of pin 2 at samp register
	(0x09),//postion of pin 3 at samp register
	(0x0C),//postion of pin 4 at samp register
	(0x0F),//postion of pin 5 at samp register
	(0x12),//postion of pin 6 at samp register
	(0x15),//postion of pin 7 at samp register
	(0x18),//postion of pin 8 at samp register
	(0x1B) //postion of pin 9 at samp register
};

int msticks=0;
void SysTick_Handler (void)
{
	msticks++;
}
void delayMs(int ms)
{
	msticks=0;
	while(msticks<ms);
}

void ADC_Init()
{
	RCC->CFGR|=ADC_PRES_DIV6;
	GPIO_CLOCK_EN_ALT_FUN;
	ADC_CLOCK_EN;
	ADC1->CR1=ADC_CR1_EOCIE;
	//NVIC ENABLE INTERRUPT
	NVIC_EnableIRQ(ADC1_2_IRQn);

}
void ADC_vidSelect(uint16_t MYGPIO.pin)
{
	
	if (MYGPIO.pin>9)
		ADC1->SMPR1|= SAMPOS_BIT0 | SAMPOS_BIT1 | SAMPOS_BIT2;
	else 
		ADC1->SMPR2|= SAMPOS_BIT0 | SAMPOS_BIT1 | SAMPOS_BIT2;
	
	ADC1->SQR3|=(MYGPIO.pin<<0);
}
void ADC_vidStartConversion(void)
{
	ADC1->CR2|= ADC_ON | ADC_CONT;
	delayMs(1);
	ADC1->CR2|= ADC_ON;
	delayMs(1);
	ADC1->CR2|=	ADC_CAL;
	delayMs(2);
}	
uint8_t ADC_u8ConversionStatus(void)
{
	while( !(ADC1->SR&END_CONV) );
		return ADC_DONE; 
}

uint16_t ADC_u16GetData(void)
{
	uint16_t ADC_VAL=0;
	uint16_t ADC_END_FLAG=0;
	ADC_END_FLAG=ADC_u8ConversionStatus();
	if (ADC_END_FLAG)
		ADC_VAL=ADC1->DR;
	return ADC_VAL;
}
	
	
	
	
	






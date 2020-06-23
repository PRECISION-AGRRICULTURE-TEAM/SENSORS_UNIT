#include "TIMER_Local.h"

static uint32_t count_3 ;

void SLEEP_MODE(void)
{
	/* NOTE
	 * if you put PINA 0 -> high
	 * (STM will restart cause we are in standby mode)
	 */


	//enable the PWR control clock
	Set_Bit(RCC_APB1ENR,28);

	//set sleep deep bit of CORTEX system control register (that in program manual not in data sheet)
	Set_Bit(SCB_SCR,2);

	/*
	 * SLEEPEXIT -> in program manual
	 * (if APP has empty main -> all code is interrupts so, if finish interrupt back to sleep mode )
	 */

	//select standby mode if go in deep sleep
	Set_Bit(PWR_CR,PDDS);

	//clear wake up flag
	Set_Bit(PWR_CR,CWUP);

	//force enable wake up pin for RTC  (not necessary)
	Set_Bit(PWR_CSR,EWUP);

	//Request wait for interrupt
	//_WFI();


}

uint8_t count_set=0;

void TIMER_vidInit()
{
	/*used TIM_4 , channel 4  -> portB9
	 *
	 */


	//Reset timer 4
	Set_Bit(RCC_APB1ENR,2);

	//Reset timer 3
	Set_Bit(RCC_APB1ENR,1);

	//prescaler value
	TIM_4->PSC = MAIN_PRESCALER;
	TIM_3->PSC = PRESCALER;

	// ARR value
	TIM_4->ARR =MAIN_ARR_value;
	TIM_3->ARR =ARR_value;

	// URS enable up/down flow
	TIM_4->CR1 |= (1<<2);
	TIM_3->CR1 |= (1<<2);

	//enable update interrupt (UIE)
	TIM_4->DIER |=(1<<0);
	TIM_3->DIER |=(1<<0);

	//enable UG
	TIM_4->EGR |=(1<<0);
	TIM_3->EGR |=(1<<0);

	//enable timer ISR
	NVIC_ISER0 = (1<<TIM4_IRQn);

	//enable counter
	TIM_4->CR1 |= (1<<0);
	TIM_3->CR1 |= (1<<0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void dummy(void){}
static void (*CallBack_Ptr)(void)=dummy;  //Global variable pointer to function
uint16_t i=0;
void TIM4_IRQHandler(void)
{
	TIM_4->SR &= ~(1<<0);    //clear flag
	(*CallBack_Ptr)();  //Global variable pointer to function
	i++;
	if(i == 10000)
	{
		i=0;
	}
}



uint16_t TIMER_Get_us ()
{
	return (uint16_t) TIM_3->CNT;
}
void TIMER_Reset ()
{
	TIM_3->CNT=0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void TIM3_IRQHandler(void)
//{
//	TIM_3->SR |= (0<<0);    //clear flag
//	void (*CallBack_Ptr)(void);
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t millis()
{
	return count_set;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Delay_US(uint32_t US)
{
	TIM_3->CR1 |= (1<<0);  //CEN Enable
	count_3 =0;
	while(count_3 <US);
	TIM_3->CR1 |= (0<<0);  //CEN Disable

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Delay_MS(uint32_t MS)
{
	TIM_3->CR1 |= (1<<0);  //CEN Enable
	count_3 =0;
	while(count_3 < (MS*1000));
	TIM_3->CR1 |= (0<<0);  //CEN Disable
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void TIMER_vidSetISRCallback(void (*CallBack)(void) )
{
	CallBack_Ptr=CallBack;
}


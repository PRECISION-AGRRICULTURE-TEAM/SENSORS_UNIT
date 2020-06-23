/*
 * GPIO.C
 *
 * This file contains the Source Code of the GPIO Driver
 *
 *  Created on: Apr 28, 2020
 *      Author: Ahmed Rashad
 */



#include "GPIO_LOCAL.h"

void GPIO_vidInit (void)
{
	//GPIO Initialization function


	EXTI->IMR=(EXTI0_MASK <<0)|(EXTI1_MASK <<1)|(EXTI2_MASK <<2)|(EXTI3_MASK <<3)|(EXTI4_MASK <<4);
	EXTI->RTSR=(EXTI0_RISING <<0)|(EXTI1_RISING <<1)|(EXTI2_RISING <<2)|(EXTI3_RISING <<3)|(EXTI4_RISING <<4);
	EXTI->FTSR=(EXTI0_FALLING <<0)|(EXTI1_FALLING <<1)|(EXTI2_FALLING <<2)|(EXTI3_FALLING <<3)|(EXTI4_FALLING <<4);
	AFIO->EXTICR1=(EXTI0_LINE <<0)|(EXTI1_LINE <<4)|(EXTI2_LINE <<8)|(EXTI3_LINE <<12);
	AFIO->EXTICR2=(EXTI4_LINE <<0);
}

uint8_t GPIO_u8SetPinDir (uint8_t u8PinNum , uint8_t u8Dir)
{
	// initializing the status of the functions
	uint8_t u8Status=ERROR;
	// checking the inputs of the functions
	if ((u8PinNum<GPIO_PINS_MAX)&&(u8Dir<GPIO_PIN_DIR_MAX))
	{
		u8Status = SUCCESS;
		// calculating the port no.
		switch(u8PinNum/16)
		{
		case PORTA : //PORTA
			Set_Bit (RCC_APB2ENR , 2);
			if(u8PinNum % 16 <=7)
			{
				GPIOA->CRL &= ~(( 0x0000000f ) << (4 *  (u8PinNum % 16) ));
				GPIOA->CRL |= (((uint32_t)(u8Dir&0x0f)) << (4 *  (u8PinNum % 16)    ));
			}
			else
			{
				GPIOA->CRH &= ~(( 0x0000000f ) << (4 *  ((u8PinNum % 16)-8) ));
				GPIOA->CRH |= (((uint32_t)(u8Dir&0x0f)) << (4 * ((u8PinNum % 16)-8) ));
			}
			if(u8Dir==INPUT_PULLUP)
			{
				GPIOA->ODR|=(1<<u8PinNum%16);
			}
			break;
		case PORTB : //PORTB
			Set_Bit (RCC_APB2ENR , 3);
			if(u8PinNum % 16 <=7)
			{
				GPIOB->CRL &= ~(( 0x0000000f ) << (4 *  (u8PinNum % 16) ));
				GPIOB->CRL |= (((uint32_t)(u8Dir&0x0f)) << (4 *  (u8PinNum % 16)    ));
			}
			else
			{
				GPIOB->CRH &= ~(( 0x0000000f ) << (4 *  ((u8PinNum % 16)-8) ));
				GPIOB->CRH |= (((uint32_t)(u8Dir&0x0f)) << (4 * ((u8PinNum % 16)-8) ));
			}
			if(u8Dir==INPUT_PULLUP)
			{
				GPIOB->ODR|=(1<<u8PinNum%16);
			}
			break;
		case PORTC : //PORTC
			Set_Bit (RCC_APB2ENR , 4);
			if(u8PinNum % 16 <=7)
			{
				GPIOC->CRL &= ~(( 0x0000000f ) << (4 *  (u8PinNum % 16) ));
				GPIOC->CRL |= (((uint32_t)(u8Dir&0x0f)) << (4 *  (u8PinNum % 16)    ));
			}
			else
			{
				GPIOC->CRH &= ~(( 0x0000000f ) << (4 *  ((u8PinNum % 16)-8) ));
				GPIOC->CRH |= (((uint32_t)(u8Dir&0x0f)) << (4 * ((u8PinNum % 16)-8) ));
			}
			if(u8Dir==INPUT_PULLUP)
			{
				GPIOC->ODR|=(1<<u8PinNum%16);
			}
			break;
		case PORTD : //PORTD
			Set_Bit (RCC_APB2ENR , 5);
			if(u8PinNum % 16 <=7)
			{
				GPIOD->CRL &= ~(( 0x0000000f ) << (4 *  (u8PinNum % 16) ));
				GPIOD->CRL |= (((uint32_t)(u8Dir&0x0f)) << (4 *  (u8PinNum % 16)    ));
			}
			else
			{
				GPIOD->CRH &= ~(( 0x0000000f ) << (4 *  ((u8PinNum % 16)-8) ));
				GPIOD->CRH |= (((uint32_t)(u8Dir&0x0f)) << (4 * ((u8PinNum % 16)-8) ));
			}
			if(u8Dir==INPUT_PULLUP)
			{
				GPIOD->ODR|=(1<<u8PinNum%16);
			}
			break;
		default:
			u8Status=ERROR;
			break;
		}

	}
	return u8Status;

}

uint8_t GPIO_u8WritePin (uint8_t u8PinNum , uint8_t u8Data)
{
	/*
	 * Writing to pin
	 *        Pin number    :    PORTx_n      n=     0:7        x=    A:D
	 *        Pin Data      :    HIGH    /    LOW
	 *
	 */
	// initializing the status of the functions
	uint8_t u8Status=ERROR;
	// checking the inputs of the functions
	if ((u8PinNum<GPIO_PINS_MAX)&&(u8Data<GPIO_DATA_ERROR))
	{
		u8Status=SUCCESS;
		// calculating the port no.
		switch(u8PinNum/16)
		{
		case PORTA : //PORTA
			// Write pin values
			Assign_Bit(GPIOA->ODR ,u8PinNum % 16, u8Data );
			break;
		case PORTB : //PORTB
			// Write pin values
			Assign_Bit(GPIOB->ODR ,u8PinNum % 16, u8Data );
			break;
		case PORTC : //PORTC
			// Write pin values
			Assign_Bit(GPIOC->ODR ,u8PinNum % 16, u8Data );
			break;
		case PORTD : //PORTD
			// Write pin values
			Assign_Bit(GPIOD->ODR ,u8PinNum % 16, u8Data );
			break;
		default:
			u8Status=ERROR;
			break;
		}
	}
	return u8Status;
}

uint8_t GPIO_u8ReadPin (uint8_t u8PinNum )
{
	/*
	 * Reading from pin
	 *      Pin number      :   PORTx_n     n=  0:7     x=  A:D
	 */
	// initializing the status of the functions
	uint8_t u8Data=GPIO_DATA_ERROR;
	// checking the inputs of the functions
	if (u8PinNum<GPIO_PINS_MAX)
	{
		// calculating the port no.
		switch(u8PinNum/8)
		{
		case PORTA : //PORTA
			//Read from pin
			u8Data= Get_Bit(GPIOA->IDR ,u8PinNum % 16);
			break;
		case PORTB : //PORTB
			//Read from pin
			u8Data= Get_Bit(GPIOB->IDR ,u8PinNum % 16);
			break;
		case PORTC : //PORTC
			//Read from pin
			u8Data= Get_Bit(GPIOC->IDR ,u8PinNum % 16);
			break;
		case PORTD : //PORTD
			//Read from pin
			u8Data= Get_Bit(GPIOD->IDR ,u8PinNum % 16);
			break;
		default:
			u8Data= GPIO_DATA_ERROR;
			break;
		}
	}
	return u8Data;
}



void GPIO_vidEnableInt(uint8_t u8IntNum)
{
	if (u8IntNum<5)
	{
		NVIC_ISER0 = (1<<(6+u8IntNum));
	}
}
void GPIO_vidDisableInt(uint8_t u8IntNum)
{
	if (u8IntNum<5)
	{
		NVIC_ICER0 = (1<<(6+u8IntNum));
	}

}

static void dummy (){}


static void (*pfun_rise[5])(void)= {dummy,dummy,dummy,dummy,dummy};
static void (*pfun_fall[5])(void)= {dummy,dummy,dummy,dummy,dummy};
static void (*pfun[5])(void)= {dummy,dummy,dummy,dummy,dummy};



void GPIO_vidSetCallback_Rising(uint8_t u8IntNum , void  (*fun)(void))
{
	pfun_rise [u8IntNum] = fun;
}
void GPIO_vidSetCallback_Falling(uint8_t u8IntNum , void  (*fun)(void))
{
	pfun_fall [u8IntNum] = fun;
}
void GPIO_vidSetCallback_AnyChange(uint8_t u8IntNum , void  (*fun)(void))
{
	pfun [u8IntNum] = fun;
}



void EXTI0_IRQHandler (void)
{
	static uint8_t state;
	EXTI->PR|=1;
#if EXTI0_LINE == 0
	state  = Get_Bit(GPIOA->IDR ,0);
#elif EXTI0_LINE == 1
	state  = Get_Bit(GPIOB->IDR ,0);
#elif EXTI0_LINE == 2
	state  = Get_Bit(GPIOC->IDR ,0);
#elif EXTI0_LINE == 3
	state  = Get_Bit(GPIOD->IDR ,0);
#else
#	error "EXTI0_LINE wrong value"
#endif

	pfun[0]();
	if(state)
	{

		pfun_rise[0]();
	}
	else
	{

		pfun_fall[0]();
	}

}
void EXTI1_IRQHandler (void)
{

	static uint8_t state;
	EXTI->PR|=2;
#if EXTI1_LINE == 0
	state  = Get_Bit(GPIOA->IDR ,1);
#elif EXTI1_LINE == 1
	state  = Get_Bit(GPIOB->IDR ,1);
#elif EXTI1_LINE == 2
	state  = Get_Bit(GPIOC->IDR ,1);
#elif EXTI1_LINE == 3
	state  = Get_Bit(GPIOD->IDR ,1);
#else
#	error "EXTI1_LINE wrong value"
#endif

	pfun[1]();
	if(state)
	{

		pfun_rise[1]();
	}
	else
	{

		pfun_fall[1]();
	}


}
void EXTI2_IRQHandler (void)
{

	static uint8_t state;
	EXTI->PR|=4;
#if EXTI2_LINE == 0
	state  = Get_Bit(GPIOA->IDR ,2);
#elif EXTI2_LINE == 1
	state  = Get_Bit(GPIOB->IDR ,2);
#elif EXTI2_LINE == 2
	state  = Get_Bit(GPIOC->IDR ,2);
#elif EXTI2_LINE == 3
	state  = Get_Bit(GPIOD->IDR ,2);
#else
#	error "EXTI2_LINE wrong value"
#endif

	pfun[2]();
	if(state)
	{

		pfun_rise[2]();
	}
	else
	{

		pfun_fall[2]();
	}


}
void EXTI3_IRQHandler (void)
{

	static uint8_t state;
	EXTI->PR|=8;
#if EXTI3_LINE == 0
	state  = Get_Bit(GPIOA->IDR ,3);
#elif EXTI3_LINE == 1
	state  = Get_Bit(GPIOB->IDR ,3);
#elif EXTI3_LINE == 2
	state  = Get_Bit(GPIOC->IDR ,3);
#elif EXTI3_LINE == 3
	state  = Get_Bit(GPIOD->IDR ,3);
#else
#	error "EXTI3_LINE wrong value"
#endif

	pfun[3]();
	if(state)
	{

		pfun_rise[3]();
	}
	else
	{

		pfun_fall[3]();
	}


}
void EXTI4_IRQHandler (void)
{

	static uint8_t state;
	EXTI->PR|=16;
#if EXTI4_LINE == 0
	state  = Get_Bit(GPIOA->IDR ,4);
#elif EXTI4_LINE == 1
	state  = Get_Bit(GPIOB->IDR ,4);
#elif EXTI4_LINE == 2
	state  = Get_Bit(GPIOC->IDR ,4);
#elif EXTI4_LINE == 3
	state  = Get_Bit(GPIOD->IDR ,4);
#else
#	error "EXTI4_LINE wrong value"
#endif

	pfun[4]();
	if(state)
	{

		pfun_rise[4]();
	}
	else
	{

		pfun_fall[4]();
	}


}


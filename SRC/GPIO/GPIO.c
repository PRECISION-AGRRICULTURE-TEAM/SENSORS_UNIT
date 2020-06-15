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

<<<<<<< HEAD
=======

	EXTI->IMR=(EXTI0_MASK <<0)|(EXTI1_MASK <<1)|(EXTI2_MASK <<2)|(EXTI3_MASK <<3)|(EXTI4_MASK <<4);
	EXTI->RTSR=(EXTI0_RISING <<0)|(EXTI1_RISING <<1)|(EXTI2_RISING <<2)|(EXTI3_RISING <<3)|(EXTI4_RISING <<4);
	EXTI->FTSR=(EXTI0_FALLING <<0)|(EXTI1_FALLING <<1)|(EXTI2_FALLING <<2)|(EXTI3_FALLING <<3)|(EXTI4_FALLING <<4);
	AFIO->EXTICR1=(EXTI0_LINE <<0)|(EXTI1_LINE <<4)|(EXTI2_LINE <<8)|(EXTI3_LINE <<12);
	AFIO->EXTICR2=(EXTI4_LINE <<0);
>>>>>>> GPIO
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
<<<<<<< HEAD
    case PORT_A : //PORTA   
=======
    case PORTA : //PORTA
>>>>>>> GPIO
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
<<<<<<< HEAD
    case PORT_B : //PORTB
=======
    case PORTB : //PORTB
>>>>>>> GPIO
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
<<<<<<< HEAD
    case PORT_C : //PORTC
=======
    case PORTC : //PORTC
>>>>>>> GPIO
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
<<<<<<< HEAD
    case PORT_D : //PORTD
=======
    case PORTD : //PORTD
>>>>>>> GPIO
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
<<<<<<< HEAD
    case PORT_A : //PORTA
      // Write pin values
      Assign_Bit(GPIOA->ODR ,u8PinNum % 16, u8Data );
      break;
    case PORT_B : //PORTB
      // Write pin values
      Assign_Bit(GPIOB->ODR ,u8PinNum % 16, u8Data );
      break;
    case PORT_C : //PORTC
      // Write pin values
      Assign_Bit(GPIOC->ODR ,u8PinNum % 16, u8Data );
      break;
    case PORT_D : //PORTD
=======
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
>>>>>>> GPIO
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
<<<<<<< HEAD
    case PORT_A : //PORTA
      //Read from pin
      u8Data= Get_Bit(GPIOA->IDR ,u8PinNum % 16);
      break;
    case PORT_B : //PORTB
      //Read from pin
      u8Data= Get_Bit(GPIOB->IDR ,u8PinNum % 16);
      break;
    case PORT_C : //PORTC
      //Read from pin
      u8Data= Get_Bit(GPIOC->IDR ,u8PinNum % 16);
      break;
    case PORT_D : //PORTD
=======
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
>>>>>>> GPIO
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
<<<<<<< HEAD
=======



void GPIO_vidEnableInt(uint8_t u8IntNum)
{
	if (u8IntNum<5)
	{
		NVIC_ISER0 = (1<<6+u8IntNum);
	}
}
void GPIO_vidDisableInt(uint8_t u8IntNum)
{
	if (u8IntNum<5)
	{
		NVIC_ICER0 = (1<<6+u8IntNum);
	}
//	switch (u8IntNum)
//	{
//	case 0:
//		NVIC_ICER0 = (1<<6);
//		break;
//	case 1:
//		NVIC_ICER0 = (1<<7);
//		break;
//	case 2:
//		NVIC_ICER0 = (1<<8);
//		break;
//	case 3:
//		NVIC_ICER0 = (1<<9);
//		break;
//	case 4:
//		NVIC_ICER0 = (1<<10);
//		break;
//	default:
//		break;
//	}

}




void EXTI0_IRQHandler (void)
{
	EXTI->PR=1;

}
void EXTI1_IRQHandler (void)
{
	EXTI->PR=2;

}
void EXTI2_IRQHandler (void)
{
	EXTI->PR=4;

}
void EXTI3_IRQHandler (void)
{
	EXTI->PR=8;

}
void EXTI4_IRQHandler (void)
{
	EXTI->PR=16;

}

>>>>>>> GPIO

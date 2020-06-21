/*
 * GPIO.C
 *
 * This file contains the Source Code of the GPIO Driver
 *
 *  Created on: Apr 28, 2020
 *      Author: Ahmed Rashad
 */



#include "GPIO_LOCAL.h"
#include "GPIO.h"

void GPIO_vidInit (void)
{
    //GPIO Initialization function

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
    case PORT_A : //PORTA   
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
    case PORT_B : //PORTB
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
    case PORT_C : //PORTC
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
    case PORT_D : //PORTD
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

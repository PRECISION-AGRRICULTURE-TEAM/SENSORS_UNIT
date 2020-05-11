#include "GPIO.h"
#include "stm32f10x.h"

void GPIO_vidInit(){}
//////////////////////////////
void GPIO_vidConfigPin(PIN_CONF * PinConfig )
{
	
	
	
	uint8 pin = (PinConfig->pinNumber) % PIN_P_PORT; // Get Pin Number
	switch( (PinConfig->pinNumber) / PIN_P_PORT) // Get Port Number
	{
	case PORT0 :
		
	   // Macro -- cane be enhanced !!
		 GPIOA_CLK_ENABLE;
		 if ( pin <8)
		 {                
			 GPIOA->CRL |=( ((uint32) (PinConfig->config) )<< ((pin*4)+2) ); 
			 GPIOA->CRL |=( ((uint32) (PinConfig->mode) )<< ((pin*4)) ); 
		 }
		 else
		 {
		 GPIOA->CRH |=( ((uint32) (PinConfig->config)) << (((pin-16)*4)+2) ); 
		 GPIOA->CRH |=( ((uint32) (PinConfig->mode) )<< (((pin-16)*4)) ); 
		 }

		break;
		 //////////////////////
		 /////////////////////
	case PORT1 :
		
	 GPIOB_CLK_ENABLE;
	 if ( pin <8)
		 {                
			 GPIOB->CRL |=( ((uint32) (PinConfig->config)) << ((pin*4)+2) ); 
			 GPIOB->CRL |=( ((uint32) (PinConfig->mode) )<< ((pin*4)) ); 
		 }
		 else
		 {
		   GPIOB->CRH |=( ((uint32) (PinConfig->config) )<< (((pin-16)*4)+2) ); 
		   GPIOB->CRH |=( ((uint32) (PinConfig->mode) )<< (((pin-16)*4)) ); 
		 }
			break;
		 //////////////////
		 //////////////////
	case PORT2 :
		GPIOC_CLK_ENABLE;
		 if ( pin <8)
		 {                
			 GPIOC->CRL |=( ((uint32) (PinConfig->config)) << ((pin*4)+2) ); 
			 GPIOC->CRL |=( ((uint32) (PinConfig->mode)) << ((pin*4)) ); 
		 }
		 else
		 {
		  GPIOC->CRH |=( ((uint32) (PinConfig->config) )<< (((pin-16)*4)+2) ); 
		  GPIOC->CRH |=( ((uint32) (PinConfig->mode) )<< (((pin-16)*4)) ); 
		 }
			break;
		 //////////////////////
		 ////////////////////////
	case PORT3 :
		GPIOD_CLK_ENABLE;
		 if ( pin <8)
		 {                
			 GPIOD->CRL |=( ((uint32) (PinConfig->config) ) << ((pin*4)+2) ); 
			 GPIOD->CRL |=( ((uint32) (PinConfig->mode) )<< ((pin*4)) ); 
		 }
		 else
		 {
		 GPIOD->CRH |=( ((uint32) (PinConfig->config) )<< (((pin-16)*4)+2) ); 
		 GPIOD->CRH |=( ((uint32) (PinConfig->mode) )<< (((pin-16)*4)) ); 
		 }
			break;
		 
		 ///////////////////////////////////
		 /////////////////////////////////
		 case PORT4 :
			 GPIOE_CLK_ENABLE;
		 if ( pin <8)
		 {                
			 GPIOE->CRL |=( ((uint32) (PinConfig->config)) << ((pin*4)+2) ); 
			 GPIOE->CRL |=( ((uint32) (PinConfig->mode) )<< ((pin*4)) ); 
		 }
		 else
		 {
		 GPIOE->CRH |=( ( (uint32) (PinConfig->config)  )<< (((pin-16)*4)+2) ); 
		 GPIOE->CRH |=( ( (uint32) (PinConfig->mode)   )<< (((pin-16)*4)) ); 
		 }
			break;
	}
}

//////////////////////////////
void GPIO_vidAssignPin(uint8 pinNum , uint8 value)
{
	
	
	
	uint8 pin = pinNum % PIN_P_PORT; // Get Pin Number
	switch( pinNum / PIN_P_PORT) // Get Port Number
	{
	case PORT0 :
		
		 if ( value == 0)
		 {                
			 GPIOA->BSRR =( (uint32)1 << (pin+16) ); 
			 
		 }
		 else
		 {
		  GPIOA->BSRR =( (uint32)1 << pin ); 
		 }

		break;
		 //////////////////////
		 /////////////////////
	case PORT1 :
	  if ( value == 0)
		 {                
			 GPIOB->BSRR =( (uint32)1 << (pin+16) ); 
			 
		 }
		 else
		 {
		  GPIOB->BSRR =( (uint32)1 << pin ); 
		 }

			break;
		 //////////////////
		 //////////////////
	case PORT2 :
		  if ( value == 0)
		 {                
			 GPIOC->BSRR =( (uint32)1 << (pin+16) ); 
			 
		 }
		 else
		 {
		  GPIOC->BSRR =( (uint32)1 << pin ); 
		 }

			break;
		 //////////////////////
		 ////////////////////////
	case PORT3 :
		  if ( value == 0)
		 {                
			 GPIOD->BSRR =( (uint32)1 << (pin+16) ); 
			 
		 }
		 else
		 {
		  GPIOD->BSRR =( (uint32)1 << pin ); 
		 }

			break;
		 
		 ///////////////////////////////////
		 /////////////////////////////////
		 case PORT4 :
		  if ( value == 0)
		 {                
			 GPIOE->BSRR =( (uint32)1 << (pin+16) ); 
			 
		 }
		 else
		 {
		  GPIOE->BSRR =( (uint32)1 << pin ); 
		 }

			break;
	}
}

///////////////////////////////////////////
///////////////////////////////////////////
uint8 GPIO_vidReadPin(uint8 pinNum )
{
	
	
	uint8 value;
	uint8 pin = pinNum % PIN_P_PORT; // Get Pin Number
	switch( pinNum / PIN_P_PORT) // Get Port Number
	{
	case PORT0 :
		
			 value = ( (uint16)GPIOA->IDR >> (pin) ); 

		break;
		 //////////////////////
		 /////////////////////
	case PORT1 :
	  
			 value = ( (uint16)GPIOB->IDR >> (pin) ); 

			break;
		 //////////////////
		 //////////////////
	case PORT2 :
		
		 value = ( (uint16)GPIOC->IDR >> (pin) ); 

			break;
		 //////////////////////
		 ////////////////////////
	case PORT3 :
		
		  value = ( (uint16)GPIOD->IDR >> (pin) ); 

			break;
		 
		 ///////////////////////////////////
		 /////////////////////////////////
		 case PORT4 :
			 
		  value = ( (uint16)GPIOE->IDR >> (pin) ); 

			break;
	}
	
	return value;
}



///////////////////////////////////////////
///////////////////////////////////////////
void GPIO_vidTogglePin(uint8 pinNum )
{
	
	

	uint8 pin = pinNum % PIN_P_PORT; // Get Pin Number
	switch( pinNum / PIN_P_PORT) // Get Port Number
	{
	case PORT0 :
		
			 
			      GPIOA->ODR ^=( (uint32)1 << pin );
     
				    
		break;
		 //////////////////////
		 /////////////////////
	case PORT1 :
	  
			  GPIOB->ODR ^=( (uint32)1 << pin );

			break;
		 //////////////////
		 //////////////////
	case PORT2 :
		
		 GPIOC->ODR ^=( (uint32)1 << pin );
	
			break;
		 //////////////////////
		 ////////////////////////
	case PORT3 :
		
		   GPIOD->ODR ^=( (uint32)1 << pin );
		 
		 ///////////////////////////////////
		 /////////////////////////////////
	case PORT4 :
			 
		  GPIOE->ODR ^=( (uint32)1 << pin );
	
			break;
	}
	
	
}




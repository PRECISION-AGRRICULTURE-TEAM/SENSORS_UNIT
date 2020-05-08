#include "_HAL_GPIO.h"
#include <stdint.h>

/*
this function to define the pin in GPIO configuration register LOW or high
to acess the correct pin in register. 
each pin has 4 access bits.
*/
static uint32_t PIN_POS[16] = { // takes me to the 1st BIT in MODE
  (0x00), // pin 0 position state at 0  low pins
  (0x04), // pin 1 position state at 4
	(0x08), // pin 2
  (0x0c), // pin 3
	(0x10), // pin 4
	(0x14), // pin 5
	(0x18), // pin 6
	(0x1c), // pin 7
	(0x00), // pin 8   HIGH pins
  (0x04), // pin 9
	(0x08), // pin 10
  (0x0c), // pin 11
	(0x10), // pin 12
	(0x14), // pin 13
	(0x18), // pin 14
	(0x1c), // pin 15
	
};	


static void config_pin ( GPIO_TypeDef *port , uint32_t pinNumber ,uint32_t ModeType ) //ModeType -> means mode inside input | output
{
	if (pinNumber >= 8 ) // control HIGH Register
	{
		switch (ModeType)
		{
			case OUTPUT_GEN_PURPOSE | INPUT_Analog :
				port->CRH &= ((~(1UL<<CNF_POS_BIT1)) | (~(1UL<<CNF_POS_BIT2)));
			 break;
			
			case OUTPUT_OD | INPUT_Floating:
				port->CRH &= (~(1UL <<CNF_POS_BIT2));   //0
	      port->CRH |= (1UL << CNF_POS_BIT1);     //1
			break;
			
			case OUTPUT_ALT_FUN | INPUT_pull_down:
				port ->CRH |= OUTPUT_ALT_FUN<<(CNF_POS_BIT1);
			break;
			
			case OUTPUT_ALT_FUN_OD:
				port->CRH |= OUTPUT_ALT_FUN_OD <<(CNF_POS_BIT1);
      break;
		}
	}
	else  //control LOW Register
	{
		switch (ModeType)
		{
			case OUTPUT_GEN_PURPOSE | INPUT_Analog :
				port->CRL &= ((~(1UL<<CNF_POS_BIT1)) | (~(1UL<<CNF_POS_BIT2)));
			 break;
			
			case OUTPUT_OD | INPUT_Floating:
				port->CRL &= (~(1UL <<CNF_POS_BIT2));   //0
	      port->CRL |= (1UL << CNF_POS_BIT1);     //1
			break;
			
			case OUTPUT_ALT_FUN | INPUT_pull_down:
				port ->CRL |= OUTPUT_ALT_FUN<<(CNF_POS_BIT1);
			break;
			
			case OUTPUT_ALT_FUN_OD:
				port->CRL |= OUTPUT_ALT_FUN_OD <<(CNF_POS_BIT1);
      break;
		}
		
	}
}

static void config_pin_speed ( GPIO_TypeDef *port, uint32_t pinNumber ,uint32_t pinSpeed , uint32_t mode)   //mode -> input | output 
{
	if(pinNumber >= 8)
	{
		if(mode == INPUT_MODE) //set control HIGH Reg to input mode
      port->CRH &= ((~(1<<PIN_POS[pinNumber]) ) | (~(1<<(PIN_POS[pinNumber] +1))));
	  else
      port->CRH |= (pinSpeed << (PIN_POS[pinNumber]));  // set control HIGH to go output Mode at given speed		
	}
	else
		{
			if(mode == INPUT_MODE)
				port->CRL &= ((~(1<<PIN_POS[pinNumber])) | (~(1<<(PIN_POS[pinNumber] + 1) )));
			else
				port->CRL |= (pinSpeed << (pinNumber));
		}
		
}
	


void GPIO_Write(GPIO_TypeDef *port , uint32_t pinNumber , uint8_t state)
{
	if(state)
	{
		port->BSRR = (1<<pinNumber);
		
	}
	else
	{
		port->BSRR = (1<<(pinNumber +16));   
		
	}
	
}

void GPIO_Toggle(GPIO_TypeDef *port ,uint32_t pinNumber)
{
	port->ODR ^=(1<<pinNumber);
	
}


void gpio_init(GPIO_Type gpio_type)
{
	if(gpio_type.port == PORTA)
		GPIO_CLK_ENABLE_PORTA;
	
	if(gpio_type.port == PORTB)
		GPIO_CLK_ENABLE_PORTB;
	
	if(gpio_type.port == PORTC)
		GPIO_CLK_ENABLE_PORTC;
	
	if(gpio_type.port == PORTD)
		GPIO_CLK_ENABLE_PORTD;
	
	config_pin(gpio_type.port , gpio_type.pin , gpio_type.mode_type);
	config_pin_speed(gpio_type.port,gpio_type.pin,gpio_type.speed,gpio_type.mode);
}



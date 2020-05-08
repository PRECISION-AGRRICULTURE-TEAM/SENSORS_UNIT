#include "stm32f10x.h"
#include "_HAL_GPIO.h"

int main()
{
GPIO_Type myGPIO;
myGPIO.port = PORTC ;
myGPIO.pin = 13;
myGPIO.mode = OUTPUT_MODE;
myGPIO.mode_type = OUTPUT_GEN_PURPOSE;
myGPIO.speed = SPEED_50MHZ ;
	
gpio_init(myGPIO);	
	
	
	while(1)
	{
		GPIO_Toggle(PORTC , 13);
		for( int i=0 ; i<=500000 ; i++);
		
	}
}


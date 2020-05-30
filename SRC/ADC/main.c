#include "stm32f10x.h"
#include "GPIO_Driver.h"
#include "ADC.h"
int main (void)
	{
		SysTick_Config(SystemCoreClock/1000);
		GPIO_Type MYGPIO;
		MYGPIO.port=PORTC;
		MYGPIO.pin=15;
		MYGPIO.speed=SPEED_50MHZ;
		MYGPIO.mode=INPUT_MODE;
		MYGPIO.mode_type=INPUT_PU_PD;
		GPIO_INIT(MYGPIO);
		ADC_Init();
		uint8_t val=0;
		while (1)
		{
			ADC_vidStartConversion();
			val=ADC_u16GetData();
			
		}
	
	}




#include "GPIO.h"


int main ()
{

	struct PIN_CONF led1 ={ 5, OutputSpeed10,OutputGP };
	struct PIN_CONF led2 ={ 31, Input,InputPullUpD };
	struct PIN_CONF led3 ={ 33, OutputSpeed10 ,OutputGP };
	struct PIN_CONF led4 ={ 63, OutputSpeed50,OutputGP };

		
	
	GPIO_vidConfigPin( &led1 );
	GPIO_vidConfigPin( &led2 );
	GPIO_vidConfigPin( &led3 );
	GPIO_vidConfigPin( &led4 );

	
	uint8 val;
while (1)
{
	GPIO_vidAssignPin(5,1);
	val = GPIO_vidReadPin(31);
	if (val ==1)
		GPIO_vidAssignPin(63,1);
	else
		GPIO_vidAssignPin(72,1);
}

}
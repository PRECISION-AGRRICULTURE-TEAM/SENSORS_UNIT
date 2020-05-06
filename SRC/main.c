#include "COMMON/Std_Types.h"
#include "COMMON/Utils.h"
#include "GPIO/GPIO.h"
void SystemInit(){}
  
int main (void)
{
  int i;
  for ( i = 1 ; i <64 ; i+=2)
  {
    GPIO_u8SetPinDir(i-1,INPUT_PULLDOWN);
    GPIO_u8SetPinDir(i,OUTPUT_PUSHPULL);
  }
  
  while (1)
  {
    for (i = 1 ; i <64 ; i+=2)
    {
      GPIO_u8WritePin(i-1,!GPIO_u8ReadPin(i));
      
    }
  }
}

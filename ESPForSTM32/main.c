/*
 * main.c
 *
 *  Created on: Jun 8, 2020
 *      Author: Shourouk
 */
 #include "SRC/COMMON/Std_Types.h"
#include "SRC/SCHEDULER/SCHEDULER.h"
#include "SRC/GPIO/GPIO.h"
void SystemInit(){}
int main ()
{




SCHEDULER_vidInit();

SCHEDULER_vidStart();

	
}

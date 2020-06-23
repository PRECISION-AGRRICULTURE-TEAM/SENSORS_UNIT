/*
 * SCHEDULER.c
 *
 *  Created on: Mar 17, 2020
 *      Author: Ahmed Rashad
 */
// 9b504cbde08e.ngrok.io

#include "SCHEDULER_LOCAL.h"
#include "../GPIO/GPIO.h"
#include "../UART/UART.h"
#include "../ESP8266/ESP8266.h"

#define Task_Count 	2

static task_t Tasks[Task_Count]={

	
		{1,00,APP_vidTask},
		{1,1,DHT11_vidMainfunc}
	
};

static uint8_t scheduler=0;
void SCHEDULER_vidStart ()
{

	uint8_t u8index;
	while(1)
	{
		if(scheduler)
		{

			for(u8index=0;u8index<Task_Count;u8index++)
			{

				if(Tasks[u8index].u16Offset==0)
				{
					Tasks[u8index].u16Offset=Tasks[u8index].u16Periodicity-1;
					Tasks[u8index].TaskFunPtr();
				}
				else
				{
					Tasks[u8index].u16Offset--;
				}
			}
			scheduler=0;
		}
	}

}

static void SCHEDULER_vidTask ()
{
	scheduler=1;

}

void SCHEDULER_vidInit ()
{
	GPIO_u8SetPinDir(PORTA_9,AF_PUSHPULL);
	GPIO_u8SetPinDir(PORTA_10,INPUT);
	GPIO_vidInit();
	UART_vidInit();
	USART1_vidEnavble();
	APP_vidInit();
	TIMER_vidSetISRCallback(SCHEDULER_vidTask);
	TIMER_vidInit();


}

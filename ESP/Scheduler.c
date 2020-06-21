/*
 * Scheduler.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Alaa Abdah
 */


#include "Scheduler.h"

#include "GPIO.h"
#define TASK_NO 1

typedef struct
{
	uint16_t u16Periodicity;
	uint16_t u16Offset;
	void (* Task_Ptr) (void);
}TaskType;

uint32_t u32TickCount =0;
uint8_t u8Scheduler =0;

 TaskType  TaskArray[] ={{100,0,ESP8266_Example}} ;
//tTaskType  TaskArray={2,0,LCD_MainFunction};

void Sch_Start(void)
{
	
	while(1)
	{
		
		if ( u8Scheduler == 1)
		{
			///////////////////////////////
			GPIO_u8SetPinDir(0,OUTPUT_PUSHPULL);
			GPIO_u8WritePin(0,1);
			/////////////////////////////////
			
			uint8_t index;
			for (index=0 ; index < TASK_NO ; index++)
			{
				if (TaskArray[index].u16Offset == 0)
				{
					TaskArray[index].Task_Ptr();
					TaskArray[index].u16Offset = TaskArray[index].u16Periodicity -1;
				}
				else
				{
					TaskArray[index].u16Offset--;
				}
			}
			u8Scheduler = 0;
		}
	}
}

void Sch_UpdateTick (void)
{

	
	u32TickCount++;
	
	
	
		if (u32TickCount %1000 == 0)
		{
			u32TickCount = 0;
			u8Scheduler= 1;
		
		}

}
void Sch_Init(void)
{
	u8Scheduler = 0;
	u32TickCount = 0;
}


/** @file SCHEDUELER.c
 *  @brief This file contains the Source Code of the SCHEDUELER Driver
 *  @author Ahmed Rashad
 */

#include "../APP/APP.h"
#include "../SCHEDULER/SCHEDULER_LOCAL.h"
#include "../TIMER/TIMER.h"

typedef struct {
    uint16_t u16Periodicity;
    uint16_t u16Offset;
    void (*TaskFunPtr)(void);

}task_t;


#define Task_Count 	1

static void TASK1()
{
	APP_vidInit();
}


static task_t Tasks[Task_Count]={
		{1,0,TASK1}
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
	APP_vidInit();
//	TIMER_vidInit();
//	TIMER_vidSetISRCallback(SCHEDULER_vidTask);
//	Enable_Global_Interrupt();
}

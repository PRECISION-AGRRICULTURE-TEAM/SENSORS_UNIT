#include "SCHEDULER/SCHEDULER.h"
void SystemInit(){}
int main()
{
	SCHEDULER_vidInit();
	SCHEDULER_vidStart();
	return 0;
}

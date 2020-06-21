/*
 * Scheduler.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Alaa Abdah
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Std_Types.h"
#include "Utils.h"
#include "ESP8266.h"
#include "TIMER.h"
void Sch_Init(void);
void Sch_Start(void);
void Sch_UpdateTick (void);


#endif /* SCHEDULER_H_ */

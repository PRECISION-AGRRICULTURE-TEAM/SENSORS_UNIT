/*
 * SCHEDULER_LOCAL.h
 *
 *  Created on: Mar 17, 2020
 *      Author: Ahmed Rashad
 */

#ifndef SCHEDULER_LOCAL_H_
#define SCHEDULER_LOCAL_H_

#include "../COMMON/Std_Types.h"
#include "../COMMON/Utils.h"
#include "../TIMER/TIMER.h"
#include "../APP/APP.h"
#include "../DHT11/DHT11.h"
typedef struct {
    uint16_t u16Periodicity;
    uint16_t u16Offset;
    void (*TaskFunPtr)(void);

}task_t;

#endif /* SCHEDULER_LOCAL_H_ */

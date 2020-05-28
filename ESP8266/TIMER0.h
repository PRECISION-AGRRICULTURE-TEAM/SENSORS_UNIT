/*
 * TIMER0.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Alaa Abdah
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "Std_Types.h"
#include "Utils.h"
#include "TIMER0_local.h"
#include "DIO_local.h"

//#define F_CPU (8000000UL)
#define GLOPAL_INT 7
#define PRESCALLER 0x07
#define MODE 0x48;



///////////////////
void Timer0_vidSetCallBack( void (*CallBack)(void) );
void timer0_vidInit(uint8 clkValue ,uint8 mode,uint8 compValue );
void timer0_vidDelayMs( uint16 msTime);
void timer0_vidIntMs();
//////////////////
typedef enum {
	normal = 0x00,
	pwm    = 0x40,
	ctc    = 0x08,
	fastPwm= 0x48
}TimerModes;

typedef enum  {
	noClock = 0x00,
	noPrescaller,
	presc8,
	presc64,
	presc256,
	presc1024,
	exFallEdg,
	exRisEdg
}clock;

 enum
{
	noOvFlComInt = 0x00,
	overflowIntEn  ,
	compareInterEn

}interEn;
 enum
{
	normalMode,
	toggleOncomMatch,
	clearOnComMatch,
	setOnComMatch
}oc0CompMod;

typedef enum
{
	pmwNormalMode,
	pmwClearOnComMatch = 0x02,
	pmwSetOnComMatch
}oc0PwmMod;


#endif /* TIMER0_H_ */

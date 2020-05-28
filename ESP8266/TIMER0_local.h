/*
 * TIMER0_local.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Alaa Abdah
 */

#ifndef TIMER0_LOCAL_H_
#define TIMER0_LOCAL_H_


//////////////////////////
//////Timer0//////////////

#define TCCR0 *(uint8 *)(0x53)
#define SREG  *(uint8 *)(0x5f)
#define TIMSK *(uint8 *)(0x59)
#define TCNT0	*(uint8 *)(0x52)
#define OCR0	*(uint8 *)(0x5c)
#define TIFR	*(uint8 *)(0x58)
///////////////////////////



#endif /* TIMER0_LOCAL_H_ */

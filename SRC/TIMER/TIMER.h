/** @file TIMER.h
 *  @brief This file contains the Prototypes of the TIMER Driver
 *  @author 
 */
#ifndef TIMER_H_
#define TIMER_H_

#include "TIMER_CFG.h"


/** @brief  Timer initialization function.
 *
 *
 *  @param 
 *  @return Void
 */
void TIMER_vidInit();

/** @brief  Timer passed from begining of run
 *
 *
 *  @param 
 *  @return Time in milliseconds
 */
uint32_t millis();

/** @brief set the fuction to be called by ISR
 *
 *  @param CallbackPtr pointer to the function that want to be called by ISR
 */
void TIMER_vidSetISRCallback(void (* CallbackPtr)(void) );


#endif /* TIMER_H_ */

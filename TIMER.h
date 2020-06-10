#ifndef TIMER_H_
#define TIMER_H_

#include "TIMER_CNFG.h"
#include "Std_Types.h"

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
 *  @return Time_4 in milliseconds
 */
uint32_t millis();

/** @brief set the fuction to be called by ISR
 *
 *  @param CallbackPtr pointer to the function that want to be called by ISR
 */
void TIMER_vidSetISRCallback(void (*CallBack)(void) );

void SLEEP_MODE(void);

void (*CallBack_Ptr)(void);

/** @brief  Timer passed from begining of calling to make delay
 *
 *
 *  @param 
 *  @return Time_3 in microseconds
 */
void Delay_US(uint32_t US);

/** @brief  Timer passed from begining of calling to make delay
 *
 *
 *  @param 
 *  @return Time_3 in milliseconds
 */
void Delay_MS(uint32_t MS);

#endif /* TIMER_H_ */


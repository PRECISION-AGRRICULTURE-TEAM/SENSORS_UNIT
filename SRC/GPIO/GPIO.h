/*
 * GPIO.h
 *
 *  This file contains the Prototypes of the GPIO Driver
 *
 *  Created on: Apr 28, 2020
 *      Author: Ahmed Rashad
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "../COMMON/Std_Types.h"
#include "GPIO_CFG.h"
/** @brief  GPIO Initialization function
 *
 *
 *  @param 
 *  @return Void
 */
void    GPIO_vidInit     (void);

/** @brief  Set the direction/mode of GPIO pin
 *
 *
 *  @param  u8PinNum the GPIO Pin num to set direction
 *  @param  u8PinDir the direction/mode
 *  @return status of the operation Success or Error
 */
uint8_t GPIO_u8SetPinDir (uint8_t U8PinNum , uint8_t U8Dir);

/** @brief  Write to GPIO pin
 *
 *
 *  @param  u8PinNum the GPIO Pin num to set write to
 *  @param  u8PinData the data to be written
 *  @return status of the operation Success or Error
 */
uint8_t GPIO_u8WritePin  (uint8_t U8PinNum , uint8_t U8Data);

/** @brief  Read from GPIO pin
 *
 *
 *  @param  u8PinNum the GPIO Pin num to read from
 *  @return Value on the GPIO pin
 */
uint8_t GPIO_u8ReadPin   (uint8_t U8PinNum);

#endif /* GPIO_H_ */

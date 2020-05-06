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

#include "GPIO_CFG.h"
extern void    GPIO_vidInit     (void);
extern uint8_t GPIO_u8SetPinDir (uint8_t U8PinNum , uint8_t U8Dir);
extern uint8_t GPIO_u8WritePin  (uint8_t U8PinNum , uint8_t U8Data);
extern uint8_t GPIO_u8ReadPin   (uint8_t U8PinNum);

#endif /* GPIO_H_ */

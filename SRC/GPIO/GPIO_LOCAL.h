/*
 * GPIO_LOCAL.h
 *
 *  This file contains the Locals of the GPIO Driver
 *
 *  Created on: Apr 28, 2020
 *      Author: Ahmed Rashad
 */

#ifndef GPIO_LOCAL_H_
#define GPIO_LOCAL_H_

#include "../COMMON/Std_Types.h"
#include "../COMMON/Utils.h"

#include "GPIO_CFG.h"

typedef struct{
  uint32_t CRL ;
  uint32_t CRH ;
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t BRR;
  uint32_t LCKR;
}GPIO_t;


#define RCC_APB2ENR (*((volatile uint32_t *)(0x40021018)))

#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000
#define GPIOD_BASE 0x40011400


#define GPIOA (((volatile GPIO_t * ) GPIOA_BASE ))
#define GPIOB (((volatile GPIO_t * ) GPIOB_BASE ))
#define GPIOC (((volatile GPIO_t * ) GPIOC_BASE ))
#define GPIOD (((volatile GPIO_t * ) GPIOD_BASE ))



#endif /* GPIO_LOCAL_H_ */

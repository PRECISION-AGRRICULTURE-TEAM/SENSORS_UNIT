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



typedef struct{
  uint32_t EVCR;
  uint32_t MAPR;
  uint32_t EXTICR1;
  uint32_t EXTICR2;
  uint32_t EXTICR3;
  uint32_t EXTICR4;
  uint32_t MAPR2;
}AFIO_t;
#define AFIO_BASE 0x40010000
#define AFIO (((volatile AFIO_t * ) AFIO_BASE ))

typedef struct{
  uint32_t IMR;
  uint32_t EMR;
  uint32_t RTSR;
  uint32_t FTSR;
  uint32_t SWIER;
  uint32_t PR;
}EXTI_t;
#define EXTI_BASE 0x40010400
#define EXTI (((volatile EXTI_t * ) EXTI_BASE ))



#define NVIC_BASE 0xE000E100
#define NVIC_ISER0 *(((volatile uint32_t * ) (NVIC_BASE + 0x000 )))
#define NVIC_ICER0 *(((volatile uint32_t * ) (NVIC_BASE + 0x080 )))




#endif /* GPIO_LOCAL_H_ */

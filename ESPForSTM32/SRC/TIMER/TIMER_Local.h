#ifndef TIMER_LOCAL_H_
#define TIMER_LOCAL_H_

#include "../COMMON/Std_Types.h"
#include "../COMMON/utils.h"
#include "TIMER_CFG.h"

typedef struct{
  uint32_t CRL ;
  uint32_t CRH ;
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t BRR;
  uint32_t LCKR;
}GPIO_t;
//_____________________________________  GPIO  _______________________________//

#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000
#define GPIOD_BASE 0x40011400


#define GPIOA (((volatile GPIO_t * ) GPIOA_BASE ))
#define GPIOB (((volatile GPIO_t * ) GPIOB_BASE ))
#define GPIOC (((volatile GPIO_t * ) GPIOC_BASE ))
#define GPIOD (((volatile GPIO_t * ) GPIOD_BASE ))

//____________________________________________________________________________________//

#define RRC           (*((volatile uint32_t *)(0x40021000)))
#define RCC_APB2ENR   (*((volatile uint32_t *)(0x40021018)))
#define RCC_APB1ENR   (*((volatile uint32_t *)(0x4002101C)))

//  __________________ Timers base unit for timer 2:5  _______________________//

typedef struct {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;       // value from 1:65536
	uint32_t ARR;       //value divide counter to can count more than 16 bit
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t DCR;
	uint32_t DMAR;

}TIMER_t;

//   ________________________  Address for Timers  _______________________   //

#define TIM_1         (((volatile TIMER_t  *)(0x40012C00)))
#define TIM_2         (((volatile TIMER_t  *)(0x40000000)))
#define TIM_3         (((volatile TIMER_t  *)(0x40000400)))
#define TIM_4         (((volatile TIMER_t *)(0x40000800)))
#define TIM_5         (((volatile TIMER_t  *)(0x40000C00)))
#define TIM_6         (((volatile TIMER_t  *)(0x40001000)))
#define TIM_7         (((volatile TIMER_t  *)(0x40001400)))
#define TIM_8         (((volatile TIMER_t  *)(0x40013400)))
#define TIM_9         (((volatile TIMER_t  *)(0x40014C00)))
#define TIM_10        (((volatile TIMER_t  *)(0x40015000)))
#define TIM_11        (((volatile TIMER_t  *)(0x40015400)))
#define TIM_12        (((volatile TIMER_t  *)(0x40001800)))
#define TIM_13        (((volatile TIMER_t  *)(0x40001C00)))
#define TIM_14        (((volatile TIMER_t  *)(0x40002000)))

//______________________________________________________________________________________________________________//

#define SCB_SCR       (*((volatile uint32_t *)(0xE000ED10)))    //need to check //

#define PWR_CR        (*((volatile uint32_t *)(0x40007000)))
#define PWR_CSR       (*((volatile uint32_t *)(0x40007004)))

#define PDDS  1   //power down deep sleep
#define CWUP  2   //clear wake up pin
#define EWUP  8   //enable wake up pin

 //  __________________________________________________________________________________________________________ //

#define NVIC_BASE 0xE000E100
#define NVIC_ISER0 *(((volatile uint32_t * ) (NVIC_BASE + 0x000 )))





#endif /* TIMER_LOCAL_H_ */


/** @file ADC_LOCAL.h
 *  @brief This file contains the Locals of the ADC Driver
 *  @author 
 */

#ifndef ADC_LOCAL_H_
#define ADC_LOCAL_H_

#include "../COMMON/Std_Types.h"
#include "../COMMON/Utils.h"
#include "ADC_CFG.h"
#include "ADC.h"
#define RCC_APB2ENR (*((volatile uint32_t *)(0x40021018)))
typedef struct{
uint32_t ADC_SR;
uint32_t ADC_CR1;
uint32_t ADC_CR2 ;
uint32_t ADC_SMPR1;
uint32_t ADC_SMPR2;
uint32_t ADC_JOFR1;
uint32_t ADC_JOFR2;
uint32_t ADC_JOFR3;
uint32_t ADC_JOFR4;
uint32_t ADC_HTR;
uint32_t ADC_LTR;
uint32_t ADC_SQR1;
uint32_t ADC_SQR2;
uint32_t ADC_SQR3;
uint32_t ADC_JSQR;
uint32_t ADC_JDR1;
uint32_t ADC_JDR2;
uint32_t ADC_JDR3;
uint32_t ADC_JDR4;
uint32_t ADC_DR;
}ADC_t;


#define ADC1_Base 0x40012400
#define ADC2_Base 0x40012800
#define ADC3_Base 0x40013C00

#define ADC1 (((volatile ADC_t * ) ADC1_Base ))
#define ADC2 (((volatile ADC_t * ) ADC2_Base ))
#define ADC3 (((volatile ADC_t * ) ADC3_Base))
/*prescalar*/
#define RCC_CFGR *(((volatile uint32_t * )0x40021000 +0x04 ))




/*rcc*/
 #define ADC1_EN 9
#define ADC2_EN 10
#define ADC3_EN 15

/*end of flag*/
#define EOC 1


//The GPIO configuration of the ADC inputs should be analog.
#define  PCLK2_By2  0
#define  PCLK2_By4  1
#define  PCLK2_By6  2
#define  PCLK2_by8  3


#define ADC_PRE 14

typedef enum
{
	ADC_CH0=0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7,
}PORTA_CH;

typedef enum
{
	ADC_CH8=16,
	ADC_CH9,

}PORTB_CH;

typedef enum
{
	ADC_CH10=32,
	ADC_CH11,
	ADC_CH12,
	ADC_CH13,
	ADC_CH14,
	ADC_CH15,
}PORTC_CH;


#define ALIGN 11
#define RIGHT 0
#define LEFT 1

/*ADC_SRQ1*/
#define L 20
#endif /* ADC_LOCAL_H_ */

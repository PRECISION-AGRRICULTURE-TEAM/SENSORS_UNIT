/*
 * GPIO_CFG.h
 *
 *  This file contains the constants of the GPIO Driver
 *
 *  Created on: Apr 28, 2020
 *      Author: Ahmed Rashad
 */

#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_

/**@brief the return values of function */
enum GPIO_STATUS{
  /** Error state*/    	ERROR = 0,
  /** Success state*/  	SUCCESS=1
};

/**@brief the values of pins in reading and writing */
enum GPIO_DATA{
  /** Low Voltage */ 	LOW    =0,
  /** High Voltage */ 	HIGH   =1,
  GPIO_DATA_ERROR
};

/**@brief the values of pins' directions/mode*/
enum GPIO_PIN_DIR{
  /** Analog pin */
  ANALOG=0X00,
  /** Output pin with push-pull */
  OUTPUT_PUSHPULL=0X01,
  /** input  pin open drain*/
  INPUT=0X04,
  /** ouput  pin open drain*/
  OUTPUT=0X05,
  /** input  pin with pulldown*/
  INPUT_PULLDOWN=0X08,
  /** Alternative function pin with push-pull*/
  AF_PUSHPULL=0X09,
  /** Alternative function pin open drain*/
  AF=0X0D,
  /** input  pin with pullup*/
  INPUT_PULLUP=0X18,
  GPIO_PIN_DIR_MAX
};

/**@brief the port names*/
enum GPIO_PORT_NAMES{
  /** PORT A */
  PORTA = 0,
  /** PORT B */
  PORTB = 1,
  /** PORT C */
  PORTC = 2,
  /** PORT D */
  PORTD = 3,
  PORT_MAX
};

/**@brief the values of pins' names*/
enum GPIO_PINS {
  PORTA_0 = 0,PORTA_1 = 1,PORTA_2 = 2,PORTA_3 = 3,PORTA_4 = 4,PORTA_5 = 5,PORTA_6 = 6,PORTA_7 = 7,
  PORTA_8 = 8,PORTA_9 = 9,PORTA_10=10,PORTA_11=11,PORTA_12=12,PORTA_13=13,PORTA_14=14,PORTA_15=15,
  PORTB_0 =16,PORTB_1 =17,PORTB_2 =18,PORTB_3 =19,PORTB_4 =20,PORTB_5 =21,PORTB_6 =22,PORTB_7 =23,
  PORTB_8 =24,PORTB_9 =25,PORTB_10=26,PORTB_11=27,PORTB_12=28,PORTB_13=29,PORTB_14=30,PORTB_15=31,
  PORTC_0 =32,PORTC_1 =33,PORTC_2 =34,PORTC_3 =35,PORTC_4 =36,PORTC_5 =37,PORTC_6 =38,PORTC_7 =39,
  PORTC_8 =40,PORTC_9 =41,PORTC_10=42,PORTC_11=43,PORTC_12=44,PORTC_13=45,PORTC_14=46,PORTC_15=47,
  PORTD_0 =48,PORTD_1 =49,PORTD_2 =50,PORTD_3 =51,PORTD_4 =52,PORTD_5 =53,PORTD_6 =54,PORTD_7 =55,
  PORTD_8 =56,PORTD_9 =57,PORTD_10=58,PORTD_11=59,PORTD_12=60,PORTD_13=61,PORTD_14=62,PORTD_15=63,
  GPIO_PINS_MAX
};


#define EXTI0_MASK		1
#define EXTI0_LINE		PORTA
#define EXTI0_RISING	1
#define EXTI0_FALLING	1

#define EXTI1_MASK		1
#define EXTI1_LINE		PORTA
#define EXTI1_RISING	1
#define EXTI1_FALLING	1

#define EXTI2_MASK		1
#define EXTI2_LINE		PORTA
#define EXTI2_RISING	1
#define EXTI2_FALLING	1

#define EXTI3_MASK		1
#define EXTI3_LINE		PORTA
#define EXTI3_RISING	1
#define EXTI3_FALLING	1

#define EXTI4_MASK		1
#define EXTI4_LINE		PORTA
#define EXTI4_RISING	1
#define EXTI4_FALLING	1

#endif /* GPIO_CFG_H_ */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f10x.h"

#define LOW  0
#define HIGH 1

//PORT names
#define PORTA   GPIOA
#define PORTB   GPIOB
#define PORTC   GPIOC
#define PORTD   GPIOD
#define PORTE   GPIOE
#define PORTF   GPIOF
#define PORTG   GPIOG

//PIN names
#define OUTPUT_MODE  ((uint32_t)0x01)  // write in speed mode 0x00
#define INPUT_MODE   ((uint32_t)0x02)

// output MODE 
#define OUTPUT_GEN_PURPOSE          ((uint32_t)0x00)  //general purpose output
#define OUTPUT_OD                   ((uint32_t)0x01)  //output open drain
#define OUTPUT_ALT_FUN   ((uint32_t)0x02)  //alternative function  push pull
#define OUTPUT_ALT_FUN_OD           ((uint32_t)0x03)  // alternative function open drain


// input MODE bits 
#define INPUT_Analog    ((uint32_t)0x00)
#define INPUT_Floating  ((uint32_t)0x01)
#define INPUT_pull_down ((uint32_t)0x02)
#define INPUT_REVERSE   ((uint32_t)0x03)

//PIN speeds
#define SPEED_2MHZ   ((uint32_t)0x02)
#define SPEED_10MHZ  ((uint32_t)0x01)
#define SPEED_50MHZ  ((uint32_t)0x03)

// clock enable
#define GPIO_CLK_ENABLE_ALT_FUN  (RCC->APB2ENR |= (1<<0))  //to handeling interrupt pins
#define GPIO_CLK_ENABLE_PORTA    (RCC->APB2ENR |= (1<<2))
#define GPIO_CLK_ENABLE_PORTB    (RCC->APB2ENR |= (1<<3))
#define GPIO_CLK_ENABLE_PORTC    (RCC->APB2ENR |= (1<<4))
#define GPIO_CLK_ENABLE_PORTD    (RCC->APB2ENR |= (1<<5))
#define GPIO_CLK_ENABLE_PORTE    (RCC->APB2ENR |= (1<<6))



//HIGH BIT Positions for CRH Register CNFYG and MODE
#define CNF_POS_BIT1  (PIN_POS[pinNumber] +2)
#define CNF_POS_BIT2  (PIN_POS[pinNumber] +3)


//configration structure
typedef struct
	{
		GPIO_TypeDef *port;
		
		uint32_t pin;
		
		uint32_t mode;
		
		uint32_t mode_type;
		
		uint32_t pull;  //direction that will use in interrupt
		
		uint32_t speed;
		
		uint32_t alt_fun;  //will use in interrupt
		
		
	}GPIO_Type ;

	
// function proto type
//********************************************************************************************************************//
//                GPIO Configuration                    //
static void config_pin(GPIO_TypeDef *port , uint32_t pinNumber ,uint32_t ModeType );
static void config_pin_speed(GPIO_TypeDef *port, uint32_t pinNumber ,uint32_t pinSpeed , uint32_t mode);

// ******************************************************************************************************************//
//                GPIO PIN Functions                     //
void GPIO_Write(GPIO_TypeDef *port , uint32_t pinNumber , uint8_t state);
void GPIO_Toggle(GPIO_TypeDef *port ,uint32_t pinNumber);
void gpio_init(GPIO_Type gpio_type);





#endif
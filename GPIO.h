
#ifndef GPIO_H_
#define GPIO_H_


#include "Std_Types.h"


#define PIN_P_PORT 16


#define HIGH 1
#define LOW  0
//////////////////
#define NIBBLE_HIGH 1
#define NIBBLE_LOW 0
///////////////////////
#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3
#define PORT4 4


// INPUT PIN MODES
#define I_ANALOG ( (uint32) x00 )
#define I_FLOATING ( (uint32) x01) //(reset state)
#define I_PULL_UP ( (uint32) x10)// pull-down

// PUTPUT PIN MODES
#define O_GP ( (uint32) x00)
#define O_OPEN_DRAIN ( (uint32) x01)
#define O_ALTER_FUNC_PUSH_PULL ( (uint32) x10)
#define O_ALTER_FUNC_OP_DRAIN ( (uint32) x11)

// Clock Configuration
#define GPIO_ALT_FUNC_CLK_ENABLE (RCC->APB2ENR |=((uint32)1<<0))
#define GPIOA_CLK_ENABLE (RCC->APB2ENR |=((uint32)1<<2))
#define GPIOB_CLK_ENABLE (RCC->APB2ENR |=((uint32)1<<3))
#define GPIOC_CLK_ENABLE (RCC->APB2ENR |=((uint32)1<<4))
#define GPIOD_CLK_ENABLE (RCC->APB2ENR |=((uint32)1<<5))
#define GPIOE_CLK_ENABLE (RCC->APB2ENR |=((uint32)1<<6))


typedef enum
{
	AnalogMode = 0,
	FloatingInput =1,
	InputPullUpD =2,
  OutputGP = 0,
	outputOpenDrain =1,
	OAlterFuncPushPull =2,
	OAlterFuncOpenDrain=3

}PINMODE;

typedef enum
{
	Input = 0,
	OutputSpeed10 =1,
	OutputSpeed2 =2,
  OutputSpeed50 = 3
	

}PINCONFIG;

// CONFIG
typedef struct PIN_CONF
{
	uint32 pinNumber;
	uint32 config;
	uint32 mode;
	
}PIN_CONF;


void GPIO_vidConfigPin(PIN_CONF * PinConfig );
void GPIO_vidAssignPin(uint8 pinNum , uint8 value);
uint8 GPIO_vidReadPin(uint8 pinNum );
void GPIO_vidTogglePin(uint8 pinNum );


#endif

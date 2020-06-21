/*
 * main.c
 *
 *  Created on: Apr 5, 2020
 *      Author: Alaa Abdah
 */

#include "Std_Types.h"
#include "Utils.h"
//#include "DIO.h"
#include "TIMER.h"
#include "UART.h"
#include "Scheduler.h"
#include "GPIO.h"
#include "ESP8266.h"


uint8_t LCD_MainFlag =0;
uint8_t Traffic_MainFlag =0;



int main()
{

//	//////////
//	DIO_vidSetPortDir(0,0xff);
//	DIO_vidSetPortDir(3,0xff);
//
//	SET_BIT(DDRA,0);
//	SET_BIT(DDRB,3);
//	SET_BIT(DDRB,2);
//	//SET_BIT(SREG,7);

//	timer0_vidInit(presc8,ctc,125);
//	timer0_vidIntMs();


//	LED_vidInit();
//	LED_vidToggle();

	///////GLOPAL TIMER /////
	
  Sch_Init();
	//TIMER_vidSetISRCallback(Sch_UpdateTick );
	//TIMER_vidInit();

	//Timer0_vidSetCallBack(Sch_UpdateTick);

//	UART_vidInit(TxRxOn,UnormalMode,stop1size8,DataRegEmpInter,risingTXfallingRX,parityDisapled);
	//lcd_vidWriteData('A');
	//DIO_vidSetPinDir(1,HIGH);
	GPIO_u8SetPinDir(USART1_TX,AF_PUSHPULL);
	GPIO_u8SetPinDir(USART1_RX,INPUT);
	USART1_vidEnavble();
	UART_vidInit();
 
	uint32_t counter =0;
	
	setSensorData("80.6" ,"61.4","9.2","14.7");
 
	while (1)
	{
		counter ++;
		 if ( (counter >=10000) )
		 {
			 
			 counter=0;
		ESP8266_Example();
			 
		 }
	
		//Sch_Start();
		 //UART_vidSendString("TEST", 4);
	}
return 0;
}




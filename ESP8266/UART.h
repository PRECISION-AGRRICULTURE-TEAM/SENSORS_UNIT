/*
 * UART.h
 *
 *  Created on: Feb 7, 2020
 *      Author: Alaa Abdah
 */

#ifndef UART_H_
#define UART_H_


#include "UART_cfg.h"
#include "UART_local.h"
#include "Utils.h"
#include "Std_Types.h"
#include "DIO.h"


//////////////////
//////////////////
extern uint8 URxArray [URxArrayLen];
extern uint8 URxArrayIndex ;
extern uint8 URxArraySize;
extern uint8 URxFlag ;
extern uint8 UMatchCase[UMatchLen] ;
extern uint8 UMatchSize ;
/////////////////
/////////////////
extern uint8 UTxArray [UTxArrayLen];
extern uint8 UTxArrayIndex ;
extern uint8 UTxArraySize;
extern uint8 UTxFlag ;
extern uint8 URxFlag;
////////////////////
/////////////////////






void UART_vidInit( uint8 RxTxMode,uint8 speedMode,uint8 framFormat,uint8 uInterrupt,uint8 polarity ,uint8 parity  );
/////////
void UART_vidPollTrans( uint16 pollData);
void UART_vidPollTransString ( char * data );
void UART_vidTrans( uint16 data);
/////////
uint16  UART_U16Receive( void);
uint16  UART_U16PollReceive( void);

/////////
void UART_vidSetTxArr (char * data ,uint8 enter);
void UART_vidSetRxArr (uint8 size, uint8 * matchString);
////////////
void UART_vidSetMode ( uint8 RxTxMode);
enum
{
	 U2X=1,
	 PE,
	 DOR,
	 FE,
	 UDRE,
	 TXC,
	 RXC
};

enum
{
	TXB8 =0,
	RXB8,
	UCSZ2,
	TXEN,
	RXEN,
	UDRIE,
	TXCIE,
	RXCIE
};

enum
{
	UCPOL =0,
	UCSZ0 ,
	UCSZ1 ,
	USBS  ,
	UPM0  ,
	UPM1  ,
	UMSEL ,
	URSEL
};

enum parityMode
{
	parityDisapled =0,
	parityEven     =0x20,
	parityOdd      = 0x30
};

enum framFormate
{
	stop1size5 =0,
	stop2size5 =0x04,
	stop1size6 =0x02,
	stop2size6 =0x0A,
	stop1size7 =0x04,
	stop2size7 =0x0C,
	stop1size8 =0x06,
	stop2size8 =0x0E,
	stop1size9 =0x06,
	stop2size9 =0x0E,
	};
enum uPol
{
	risingTXfallingRX = 0,
	fallingTXRisingRX = 1
};

enum UInterrupt
{
	NoInter = 0x00,
	RxOnlyInter = 0x80,
	TxOnlyInter = 0x40,
	DataRegEmpInter = 0x20,
	RxDataEmpInte = 0xA0,
	RxTxInter = 0xC0,
	TxDataEmpInter = 0x60,
	RxTxDataEmpInter = 0xE0

};

enum TxRxMode
{
	RxTxoff = 0x00,
	RxOn    =0x10,
	TxOn    = 0x08,
	TxRxOn  =0x18
	};

enum speedMode
{
	UnormalMode = 0x00,
	UdoubleMode =0x02
};

#endif /* UART_H_ */

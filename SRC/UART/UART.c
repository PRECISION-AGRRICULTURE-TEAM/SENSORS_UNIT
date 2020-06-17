/** @file UART.c
 *  @brief This file contains the Source Code of the UART Driver
 *  @author  
 */

#include "UART_LOCAL.h"

#include "UART.h"


void   UART_vidInit(void)
{
	//BRR
	UART->USART_BRR |=(((FREQUENCY/(Prescalar*16*BaudRate))&(0xfff))<<4);
	//	(UART->USART_BRR) |=(uint8_t)1+(     ( (FREQUENCY/(16*BaudRate*Prescalar))  -  (uint8_t)((FREQUENCY/Prescalar)/(16*BaudRate)))*16);
	UART->USART_BRR	|=(((FREQUENCY%(Prescalar*16*BaudRate))/(Prescalar*BaudRate))%0xf);
	//CR1
	UART->USART_CR1 |=( UART_SEL			<<UE )
					  | ( Character_Size	<<Word_Length )
					  | ((Parity_Check&0x3)	<<PS)
					  | ( RX_EN				<<RE)
					  | ( TX_EN				<<TE);
	//CR2
	UART->USART_CR2 |=StopBit<<STOP;
	UART->USART_GTRP|=Prescalar;
	//SR
	RCC_APB2ENR 	|=  (UART_SEL <<  (USART1EN)) ;

}


/*
uint8_t UART_u8DataReady()
{
	return Get_Bit(UART->USART_SR,RXNE);
}
uint8_t UART_u8GetData()
{
	return ( UART->USART_DR);
}
 */


#if UART_PERIODIC == 1

static uint8_t UART_RX_BUFFER[ UART_BUFFERSIZE ];
static uint8_t UART_LAST_RECEIVED =-1;
static uint8_t UART_LAST_READ =-1;
static uint8_t UART_TX_BUFFER[ UART_BUFFERSIZE ];
static uint8_t UART_LAST_SEND =-1;
static uint8_t UART_LAST_WRITTEN =-1;
void UART_vidTask (void)
{
	if (Get_Bit(UART->USART_SR,RXNE))
	{
		UART_RX_BUFFER [++UART_LAST_RECEIVED]=UART->USART_DR;
	}
	else
	{
		if (UART_LAST_SEND != UART_LAST_WRITTEN)
		{
			if (Get_Bit( UART->USART_SR,TXE))
			{
				UART->USART_DR=UART_TX_BUFFER [++UART_LAST_SEND];
			}
		}
	}
}

void UART_vidSendChar(uint8_t u8Data) //need to ba array
{
	UART_TX_BUFFER [++UART_LAST_WRITTEN]=u8Data;
}

uint8_t UART_u8RecieveChar(void)
{
	uint8_t u8Data=0;
	if (UART_LAST_READ != UART_LAST_RECEIVED)
	{
		u8Data=UART_RX_BUFFER[++UART_LAST_READ];
	}
	return u8Data;
}

#else
void UART_vidSendChar(uint8_t u8Data) //need to ba array
{
	while(Get_Bit( UART->USART_SR,TXE)==0);
	( UART->USART_DR)=u8Data;

}

uint8_t UART_u8RecieveChar(void)
{
	while (Get_Bit(UART->USART_SR,RXNE)==0 );
	return ( UART->USART_DR);
}
#endif



void    UART_vidSendString(uint8_t u8Data[], uint8_t u8Length)
{
	uint8_t i=0;
	while ((u8Data[i]) && (i<u8Length))
	{
		UART_vidSendChar(u8Data[i++]);
	}
}
void    UART_vidRecieveString(uint8_t u8Data[], uint8_t * u8Length)
{


	*u8Length=0;
	do
	{
		u8Data[(*u8Length)++]=UART_u8RecieveChar();
	}
	while(u8Data[(*u8Length)-1]&&u8Data[(*u8Length)-1]!='\r');
	u8Data[(*u8Length)]=0;

}



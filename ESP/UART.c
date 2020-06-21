/** @file UART.c
 *  @brief This file contains the Source Code of the UART Driver
 *  @author  
 */

#include "UART_LOCAL.h"
#include  "GPIO.h"
#include "UART.h"

//////////////////
//////////////////
// Received Array by Interrupt
uint8_t URxArray [URxArrayLen];
// Index of Received Array
volatile uint8_t URxArrayIndex =0;
// Size of Received Array
uint8_t URxArraySize;
// Reception ended Flag
volatile uint8_t URxFlag =0;
// Array to check matching in Reception
uint8_t UMatchCase[UMatchLen] ;
// Size of Match Array
uint8_t UMatchSize ;
/////////////////
/////////////////
// Transmission Array
uint8_t UTxArray [UTxArrayLen];
// Transimssion Array Index
volatile uint8_t UTxArrayIndex =0;
// Transmission Array size
uint8_t UTxArraySize;
//Transmission ended Flag
volatile uint8_t UTxFlag =0;
////////////////////
/////////////////////






void   UART_vidInit(void)
{
	RCC_APB2ENR 	|=  (UART_SEL <<  (USART1EN)) ;
	//BRR
//	
//	UART->USART_BRR |=(((FREQUENCY/(Prescalar*16*BaudRate))&(0xfff))<<4);
//	//	(UART->USART_BRR) |=(uint8_t)1+(     ( (FREQUENCY/(16*BaudRate*Prescalar))  -  (uint8_t)((FREQUENCY/Prescalar)/(16*BaudRate)))*16);
//	UART->USART_BRR	|=(((FREQUENCY%(Prescalar*16*BaudRate))/(Prescalar*BaudRate))%0xf);
//	//CR1
//	
	
	UART->USART_BRR = 625;
	
	
	
	UART->USART_CR1 |=( UART_SEL			<<UE )
					  | ( Character_Size	<<Word_Length )
					  | ((Parity_Check&0x3)	<<PS)
					  | ( RX_EN				<<RE)
					  | ( TX_EN				<<TE)
					  |(  (1)<<RXNEIE ) ;
	//CR
	UART->USART_CR2 |=StopBit<<STOP;
	UART->USART_GTRP|=Prescalar;
	//SR
	

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
void USART1_vidEnavble()
{
	NVIC_ISER1 |=(1<<(USART1_IRQn   %32)    );

}

void USART1_vidDisable()
{
	//NNVIC_ICER1 |=(1<<(USART1_IRQn   %32)    );
	UART1->USART_CR1 |=0<<RXNEIE ;
}


#if UART_PERIODIC == 0

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













void UART_vidEndReciption()
{
	// If true --> disable Receive complete Interrupt and set URxFlag to 1 to announce the the end of the reception
//			CLEAR_BIT(UCSRB,RXCIE );
			CLEAR_BIT ( UART->USART_CR1	,RXNEIE) ;//DISABLE Rx Interrupt
			URxFlag =0;
			URxArrayIndex =0;

}

void UART_vidSetRxArr (uint8_t size, uint8_t * matchString)
{
	// -- The function get the length of the string wanted to be received with an OPTIONAL match string to
	// match the received string with it.
	// --EX ---------
	// UART_vidSetRxArr (8, "ALAA")
	// The function will open the reception window until the string ALAA
	// is received then terminates the reception window.
	// -- If there is no wanted match case the matchString shall be empty --""-- .
	//--EX ----------
	// UART_vidSetRxArr (8, "")
	// The function will open the reception window until 8 characters string is received.

	// -------------------------------------------------------------------
	if ( URxFlag == 0)
	{

		// Set the URxArraySize with size parameter
		URxArraySize = size;
		// Set the URxArrayIndex (reception array index) to zero 0
		URxArrayIndex =0;
		// Set the URxFlag ( reception done flag ) to zero 0
		URxFlag=1;
		uint8_t i;
		// Copy the match string if any to the UMatchCase ( string to compare the received string with)
		for (i=0;( matchString[i]!='\0' );i++)
		{
		UMatchCase[i] = matchString[i];

		}
		// Put a null operator at the end of the UMatchCase
		UMatchCase[i] = '\0';
		// Get the UMatch Size
		UMatchSize = i;

		// Enable Receive Complete interrupt to begin Reception of the RxArray
		SET_BIT( UART->USART_CR1	,RXNEIE) ;//Enable Rx Interrupt
	}
}

void UART_vidSetTxArr (uint8_t * data )
{
	// the function load the UTXArray with data string characters, get the size of the data string,
	// terminate the string with null terminator and enable UDR empty interrupt to send UTxArray character
	// by character when UDR is empty using the UDR empty interrupt
	// In case of AT Command the function uses parameter (enter) to check if AT Command,
	// terminate the string with Enter.
	if ( UTxFlag ==0)
	{
		uint8_t i;

		for (i=0;(data[i]!='\0')&& (i<(UTxArrayLen-1));i++)
		{
			// copy the data string into UTxArray
			UTxArray[i] = data[i];
		}
				UTxArray[i] = '\0';

		// get the size of the string
		UTxArraySize = i;
		// Enable UDR Empty interrupt to begin transmission of the TxArray
		UTxFlag=1;
		
		UART->USART_CR1	|= 0x80; // TX Interrupt
//		SET_BIT(UCSRB , UDRIE);
	}

}

void USART1_IRQHandler(void)
{
		

	if ( Get_Bit(UART->USART_SR,RXNE) )
		{
			
		// Receive the URxArray character by character
		URxArray[URxArrayIndex] =UART->USART_DR;
		// Check if there is a UMatchCase with size >0 to compare the received stream with
			// and check if the received matching stream doesn't exceed the UMatchCase Array size.
			if ( (UMatchSize >0 ) && (URxArrayIndex < UMatchSize))
			{
			
				// If the received stream is not matching the UMatchCase array  then reset the Index of URxArray
				if (URxArray[URxArrayIndex] != UMatchCase[URxArrayIndex])
				{

					
					URxArrayIndex =0;
				}
				else
				{
					// Else -- > go to the next character

					URxArrayIndex++;
				}
			}
			else
			{
				// If there is no matchCase Array then increase index and receive character by character into the URxReceiveArray
				URxArrayIndex++;
			}
			// Check if the received stream size is equal to the URxArraySize
			if ( URxArraySize <= URxArrayIndex)
			{
				// If true --> disable Receive complete Interrupt and set URxFlag to 1 to announce the the end of the reception
				//CLEAR_BIT(UCSRB,RXCIE);
				CLEAR_BIT ( UART->USART_CR1	,RXNEIE) ;//DISABLE Rx Interrupt
				URxFlag =0;
				URxArrayIndex =0;
			}

		}
		else
		{
			if ( (Get_Bit( UART->USART_SR,TXE)) )
			{
				// Transmit the UTxArray assigned by UART_vidSetTxArr (char * data)
					// character by character
					UART->USART_DR = UTxArray[UTxArrayIndex];
					UTxArrayIndex++;
					///////////////////////////
					// check if the transmitted characters reached the size ot the UTxArray (UTxArraySize)
					if ( UTxArraySize < UTxArrayIndex)
					{
						// if condition is true -- disable the UDR empty interrupt and set the transmission done flag (UTxFlag =1)
					//	CLEAR_BIT(UCSRB,UDRIE); // disable Interrupt
						UTxFlag =0;
						UTxArrayIndex=0;
						
						CLEAR_BIT ( UART->USART_CR1	,7) ;//|= 0x80; // Disable TX Interrupt
					}

//				if (Get_Bit( UART->USART_SR,TXE))
//				{
//				//	UART->USART_DR=UART_TX_BUFFER [++UART_LAST_SEND];
//				}

			}
		}








	// Receive the URxArray character by character
//		URxArray[URxArrayIndex] =UDR;
	//	/////////// DEBUG////////
	//	iDebug++ ;
	//		///////// DEBUG /////////

}


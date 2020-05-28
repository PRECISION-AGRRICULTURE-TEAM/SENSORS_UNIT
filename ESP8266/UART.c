/*
 * UART.c
 *
 *  Created on: Feb 7, 2020
 *      Author: Alaa Abdah
 */

#include "UART.h"
#include <math.h>
//////////////////
//////////////////
// Received Array by Interrupt
uint8 URxArray [URxArrayLen];
// Index of Received Array
uint8 URxArrayIndex =0;
// Size of Received Array
uint8 URxArraySize;
// Reception ended Flag
uint8 URxFlag =0;
// Array to check matching in Reception
uint8 UMatchCase[UMatchLen] ;
// Size of Match Array
uint8 UMatchSize ;
/////////////////
/////////////////
// Transmission Array
uint8 UTxArray [UTxArrayLen];
// Transimssion Array Index
uint8 UTxArrayIndex =0;
// Transmission Array size
uint8 UTxArraySize;
//Transmission ended Flag
uint8 UTxFlag =0;
////////////////////
/////////////////////

void UART_vidInit( uint8 RxTxMode,uint8 speedMode,uint8 framFormat,uint8 uInterrupt,uint8 polarity ,uint8 parity  )
{

		// UBR value according to baud rate and CPU frequency and speed mode
		//uint16 UBRValue =4;
		uint16 UBRValue =round((F_CPU*1.0/SPEED_FACTOR/UART_BAUD_RATE) -1);
		// upper value in upper register
		UBRRH = (unsigned char)(UBRValue >>8);
		// lower value in lower register
		UBRRL = (unsigned char)UBRValue;

		// URSEL >>1 for UCSRC Register
		// framFormat for frame size  and stop bits
		// polarity and parity of the frame
		// choosing asynchronous UART mode
		UCSRC = (UCSRC_SEL<<URSEL) |framFormat|polarity | (ASYNC_UART<<UMSEL)| parity;
		//choosing RxTx mode
		UCSRB = RxTxMode;
		// if UART_DATA_SIZE==9 assign UCSZ2 bit to one
		if (UART_DATA_SIZE==9)
		UCSRB |= (1<<UCSZ2);
		//assign speed mode
		UCSRA =speedMode;
		
	
}

uint16 UART_uint16PollReceive( void)
{
	//wait until receive complete flag is one then return UDR value
	while ( ! (GET_BIT(UCSRA ,RXC)) );
	return UART_U16Receive() ;

}
uint16 UART_U16Receive( void)
{
	// check if data size is 9 bits to append RXB8 with UDR value else return UDR value only
	if (UART_DATA_SIZE ==9)
		return ( (GET_BIT(UCSRB,RXB8)<<8)| UDR) ;
	else
		return (UDR) ;
}

void UART_vidPollTrans( uint16 pollData)
{
	// wait until UDR empty flag is one to load UDR register with pollData value
	while ( !GET_BIT(UCSRA,UDRE) );
	UART_vidTrans(pollData);
}

void UART_vidPollTransString ( char * data  )
{
	uint8 i;
	// loop over the string characters and send them one by one
	for (i=0; data[i]!='\0' ; i++)
	UART_vidPollTrans(data[i]);
}


void UART_vidTrans( uint16 data)
{
	// the function puts in mind the 9 bits mode
	///////////////
	// clear TXB8 by default
	CLEAR_BIT( UCSRB , TXB8);
	// if data value has one in 8 bit then set TXB8 to one
	if ( (UART_DATA_SIZE ==9) & (data & (1<<8) ) )
	{
		SET_BIT ( UCSRB , TXB8);
	}
	UDR =  data;

}


void UART_vidSetTxArr (char * data ,uint8 enter)
{
	// the function load the UTXArray with data string characters, get the size of the data string,
	// terminate the string with null terminator and enable UDR empty interrupt to send UTxArray character
	// by character when UDR is empty using the UDR empty interrupt
	// In case of AT Command the function uses parameter (enter) to check if AT Command,
	// terminate the string with Enter.
	if ( UTxFlag ==0)
	{
		uint8 i;
		for (i=0;(data[i]!='\0')&& (i<(UTxArrayLen-1));i++)
		{
			// copy the data string into UTxArray
			UTxArray[i] = data[i];
		}

		if ( enter ==1 )
			{
				UTxArray[i] = 0x0d;

			}
			else
			{
				UTxArray[i] = '\0';
			}

		// get the size of the string
		UTxArraySize = i;
		// Enable UDR Empty interrupt to begin transmission of the TxArray
		UTxFlag=1;
		SET_BIT(UCSRB , UDRIE);
	}

}


void UART_vidSetRxArr (uint8 size, uint8 * matchString)
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
		uint8 i;
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
		SET_BIT(UCSRB , RXCIE);
	}
}

void UART_vidSetMode ( uint8 RxTxMode)
{
	// Clear current Tx Rx mode
	CLEAR_BIT(UCSRB ,RXEN);
	CLEAR_BIT(UCSRB , TXEN);
	// Set new Tx Rx Mode
	UCSRB |= RxTxMode;
}


//----------------------------------------------------
// UDR empty interrupt
void __vector_14(void) __attribute__((signal,__INTR_ATTRS));
void __vector_14(void)
{

	// Transmit the UTxArray assigned by UART_vidSetTxArr (char * data)
	// character by character
	//UART_vidTrans((uint16) UTxArray[UTxArrayIndex]);
	UDR = UTxArray[UTxArrayIndex];
	UTxArrayIndex++;
	// check if the transmitted characters reached the size ot the UTxArray (UTxArraySize)
	if ( UTxArraySize < UTxArrayIndex)
	{
		// if condition is true -- disaple the UDR empty interrupt and set the transmission done flag (UTxFlag =1)
		CLEAR_BIT(UCSRB,UDRIE); // disable Interrupt
		UTxFlag =0;
		UTxArrayIndex=0;
	}

}


///////////// DEBUG////////
//	uint8 iDebug = 0;
//	///////// DEBUG /////////

///////// Recive Complete Interrupt
void __vector_13(void) __attribute__((signal,__INTR_ATTRS));
void __vector_13(void)
{
	// Receive the URxArray character by character
	URxArray[URxArrayIndex] =UDR;
//	/////////// DEBUG////////
//	iDebug++ ;
//		///////// DEBUG /////////
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
			///////// DEBUG ///////////
//			DIO_vidSetPinDir(8+URxArrayIndex,1);
//			DIO_vidWritePin(8+URxArrayIndex,1);
//			/////////// DEBUG //////////
			URxArrayIndex++;


		}
	}
	else
	{
		// If there is no matchCase Array then increase index and receive character by character into the URxReceiveArray

//		///////// DEBUG ///////////
//		DIO_vidSetPinDir(8+URxArrayIndex,1);
//		DIO_vidWritePin(8+URxArrayIndex,1);
//		/////////// DEBUG //////////
		URxArrayIndex++;

	}
	
	// Check if the received stream size is equal to the URxArraySize
	if ( URxArraySize <= URxArrayIndex)
	{
		// If true --> disable Receive complete Interrupt and set URxFlag to 1 to announce the the end of the reception
		CLEAR_BIT(UCSRB,RXCIE);
		URxFlag =0;
		URxArrayIndex =0;


	}


}


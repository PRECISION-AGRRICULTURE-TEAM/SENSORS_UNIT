
/** @file ESP8266.c
 *  @brief ESP8266 Driver V 1.0
 *
 *  Created on: May 26, 2020
 *  Handles sending to a Local server with only one connection.
 *
 * @author Alaa AbdAlrhman
 * @bug no known bugs
 */

#include "ESP8266.h"
#include <stdio.h>

// ESP Initialization parameters --> Change base on your configurations
struct ESP_INIT_PARAM param = {1,"AbdAlrhmanAbdah","01157227548"};

void ESP8266_vidSendCommand(uint8 * command,uint8 option,uint8 query)
{
	char ATcommand[15];
	// Check if there is an option and modify the command based on it.
	if ( option != noOption )
		sprintf(ATcommand,"%s=%d\r\n",command,option);
	// Check if there is an querey and modify the command based on it.
	else if ( query == querey )
		sprintf(ATcommand,"%s=%c\r\n",command,query);
	// else .. Normal formatting of the command
	else
		sprintf(ATcommand,"%s\r\n",command);

	UART_vidSetTxArr(ATcommand,0);
}
void ESP_vidJoinNetwork ()
{
	char ATcommand[50] ;
	// format the join network command based on network parameters
	sprintf ( ATcommand ,"AT+CWJAP=\"%s\",\"%s\"\r\n",param.SSID,param.PASSWORD );
	UART_vidSetTxArr(ATcommand,0);
}
void ESP_vidCheckForIP()
{
		ESP8266_vidSendCommand("AT+CIFSR",noOption,noQuerey);
}

uint8 ESP8266_vidListen(uint8 * wordToFind)
{
	static uint8 timOutCounter=0;
	static uint8 listenStat=0;
	int i;
	switch ( listenStat )
	{
	case 0 :
		// counts number of characters to find
		for ( i=0;wordToFind[i]!='\0';i++){}
		UART_vidSetRxArr(i,wordToFind );
		listenStat++;
		break;
	case 1:
		// if word is found return 1.
		if ( URxFlag ==0 )
		{
			listenStat=0;
			return 1;
		}
		listenStat++;
		break;
	case 2:
		// if Counter reaches 10 >> timeout error
		timOutCounter++;
		if ( timOutCounter >10 )
		{	timOutCounter =0;
			listenStat=1;
			return timeout;
		}
		listenStat--;
		break;
	}
	return 0;
}



// Create Server with Port defined as parameter
uint8 ESP8266_vidCreateServer( uint8 port)
{
	static uint8 serverState =0;
	uint8 command[20];
	switch (serverState)
	{

	case 0:
		// specify the connection to be only 1
		ESP8266_vidSendCommand("AT+CIPMUX",1,noQuerey);
		serverState++;
		break;
	case 1:
		if (ESP8266_vidListen("OK")==ok)
			serverState++;
		break;
	case 2:
		// create the server with port specified as parameter
		sprintf(command , "AT+CIPSERVER=1,%d\r\n",port);
		UART_vidSetTxArr(command,0);
		serverState++;
		break;
	case 3:
		if (ESP8266_vidListen("OK")==ok)
			   serverState++;
		break;
	default:
		return 1;
		break;
	}
	return 0;
}

uint8 ESP8266_vidCheckForConnectionRequest()
{
	// if ",CONNECT is found there is a connection request
	if ( ESP8266_vidListen(",CONNECT") == 1)
	{
		return 1;
	}
	else
		return 0;
}
uint8 ESP8266_vidOpenConnection(uint16 dataSize)
{
	static uint8 connectionState =0;
	uint8 command [20];
	switch (connectionState )
		{
		case 0:
			// send dataSize Characters to connection 0.
			sprintf(command,"AT+CIPSEND=0,%d\r\n",dataSize);
			UART_vidSetTxArr(command,0);
			connectionState=1;
			break;
		case 1:
			if ( UTxFlag==0 )
			{
				connectionState=0;
				return 1;
			}
			break;
		}
	return 0;
}
uint8 ESP8266_vidSendDataToOpendConnection(uint8 * Data)
{
	static uint8 dataState =0;
	switch (dataState)
	{
	case 0:
		UART_vidSetTxArr(Data,0);
		dataState++;
		break;
	case 1:
		if ( UTxFlag == 0)
		{
			dataState =0;
			return 1;
		}
		break;
	}
	return 0;
}

uint8 ESP8266_vidCloseConnection()
{
	static uint8 sendState =0;
	uint8 command [20];
	switch (sendState)
	{
	case 0:
		// close connection 0
		sprintf(command,"AT+CIPCLOSE=0\r\n");
		UART_vidSetTxArr(command,0);
		sendState++;
		break;
	case 1:
		if ( UTxFlag ==1)
		{
			sendState=0;
			return 1;
		}
		break;
	}
	return 0;
}

uint8 ESP8266_Init()
{
	static uint8 EspInitCase = 0;
	switch( EspInitCase)
	{
	case 0 :
		// SEND AT To check ESP is active or not
		// UART_vidSetTxArr("AT\r\n",0);
		ESP8266_vidSendCommand("AT",noOption,noQuerey);
		EspInitCase++;
		break;
	case 1:
		if ( ESP8266_vidListen("OK") == 1)
		EspInitCase++;
		else
		{// Handle Error cases.
		}
		break;
	case 2:
		// Send the mode specified in ESP_INITPARAM struct
		ESP8266_vidSendCommand("AT+CWMODE", param.mode ,noQuerey);
		EspInitCase++;
		break;
	case 3:
		if (  ESP8266_vidListen("OK") == ok )
			EspInitCase++;
		else
		{// Handle Error cases.
		}
		break;
	default :
		EspInitCase=0;
		return 1;
		break;
	}
	return 0;
}


//////////////////////////////
/////// Example //////////////
uint8 ESP8266_Example()
{
	static uint8 EspExampleCase = 0;
	switch( EspExampleCase)
	{
	case 0:
		if ( ESP8266_Init() ==1)
			EspExampleCase++;
		break;
	case 1:
		ESP_vidJoinNetwork();
		EspExampleCase++;
		break;
	case 2 :
		if ( ESP8266_vidListen("OK") == ok)
			EspExampleCase++;
		else{// Handle Error cases.
			}
		break;
	case 3 :
			ESP_vidCheckForIP();
			EspExampleCase++;
			break;
	case 4:
		if ( ESP8266_vidCreateServer( 80 ) ==1)
			EspExampleCase++;
		break;
	case 5:
		if ( ESP8266_vidCheckForConnectionRequest()==1)
			EspExampleCase++;
		break;
	case 6:
		// 18 character .. number of string to be sent in next step
		if ( ESP8266_vidOpenConnection(18) ==1)
			EspExampleCase++;
		break;
	case 7:
		if ( ESP8266_vidSendDataToOpendConnection("<h1>ITI WCE 40<h1>")==1 )
			EspExampleCase++;
		break;
	case 8:
		if ( ESP8266_vidListen("OK")==ok )
			EspExampleCase++;
		break;
	case 9:
		if ( ESP8266_vidCloseConnection() )
			EspExampleCase++;
		break;
	default :
		//EspInitCase =0;
		return 1;
		break;

	}
	return 0;

}



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
struct ESP_INIT_PARAM param = {1,"AbdAlrhmanAbdah","01157227548","GET /API/insert.php?UnitId=1&SoilTemp=35.6%20&SoilMoisture=30.214&AirTemp=30.2&AirHumidity=12.7 HTTP/1.1\r\nHOST:itiprecisionagriculture.000webhostapp.com\r\nConnection: close\r\n\r\n ","itiprecisionagriculture.000webhostapp.com",80,"TCP"};

//////// DEBUG///////////////
uint8 global =0;
//////////////////////////////


enum
{
	DataSent=1
}SendData;
enum ESP_STATUS ESP8266_u8CheckStatues ()
{

    static uint8 checkStatuesState=0;
	char ATcommand[20] ;
	uint8 ListenReturn;
	switch ( checkStatuesState)
	{
	case 0:
		// SEND Command to check ESP statues
		sprintf ( ATcommand ,"AT+CIPSTATUS\r\n");
		ESP8266_vidSendCommand(ATcommand);
		checkStatuesState++;
		break;
	case 1:
		// Listen To Response of ESP8266 .. If ESP replay with STATUS check number after STATUS
		// Ex. ( STATUS:2) -> Connected TO AP
		ListenReturn = ESP8266_vidListen("STATUS:",8,500);
		switch (ListenReturn)
		{
		case Found:
			// Check Number after STATUS: >>> return value corresponding to it.
			checkStatuesState=0;
			if (URxArray[7] == '2')
				return CONNECTED_TO_AP;
			else if (URxArray[7] == '3')
				return TRANSMISSION_CONNECTED;
			else if (URxArray[7] == '4')
				return TRANSMISSION_DISCONNECTED;
			else if (URxArray[7] == '5')
				return NOT_CONNECTED_TO_AP;
			else return UNKNOWN_ERROR;
			break;
		case Timeout:
			// Case Timeout before reading STATUS: .. return NotConnected
			checkStatuesState=0;
			return NotConnected;
			break;
		}

		break;
	}
	return Wait;

}
void ESP8266_vidSendCommand(uint8 * command)
{
	UART_vidSetTxArr(command,0);
}
// Function that joins Network with SSID and Password defined in parameters structure.
uint8 ESP_vidJoinNetwork ()
{
	static joinNetworkState=0;
	char ATcommand[50] ;
	uint8 ListenReturn;
	switch ( joinNetworkState)
	{
	case 0:
		// format the join network command based on network parameters
		sprintf ( ATcommand ,"AT+CWJAP=\"%s\",\"%s\"\r\n",param.SSID,param.PASSWORD );
		ESP8266_vidSendCommand(ATcommand);
		joinNetworkState++;
		break;
	case 1:
		// Wait 5000 ticks to listen to OK
		ListenReturn =ESP8266_vidListen("OK",2,5000);
		switch (ListenReturn)
		{
		case Found:
			// If Found Return connected
			joinNetworkState=0;
			return Connected;
			break;
		case Timeout:
			// If Timeout return NotConnected
			joinNetworkState=0;
			return NotConnected;
			break;
		}
	}
	return Wait;
}

// Function To Check For IP .. Send "AT+CIFSR" .. ESP Responds with IP
uint8 ESP_vidCheckForIP()
{
	static uint8 checkForIpState =0;
	char ATCommand [10];
	switch( checkForIpState)
	{

	case 0:
		sprintf(ATCommand,"AT+CIFSR\r\n");
		ESP8266_vidSendCommand(ATCommand);
		checkForIpState++;
		break;
	case 1:
		// If ESP returned OK .. IP returned Successfully.
		if ( ESP8266_vidListen("OK",2,200) == ok )
		{
			checkForIpState=0;
			return 1;
		}

	}
	return 0;

}
// Function To listen to specific word and fetch specific size of string after it
// with timeout timer to check if time is out before finding the word
uint8 ESP8266_vidListen(uint8 * wordToFind ,uint8 sizeOfStringToFetch, uint16 timeOut )
{
	static uint16 timOutCounter=0;
	static uint8 listenStat=0;
	switch ( listenStat )
	{
	case 0 :
		// Set UART fetch the word and characters after it with specified length
		UART_vidSetRxArr(sizeOfStringToFetch,wordToFind );
		timOutCounter =0;
		listenStat++;
		break;
	case 1:
		// if word is found return 1.
		if ( URxFlag ==0 )
		{
			listenStat=0;
			return Found ;
		}
		listenStat++;
		break;
	case 2:
		// if Counter reaches timeOut >> timeout error
		timOutCounter++;
		if ( timOutCounter >timeOut )
		{
			timOutCounter =0;
			listenStat=0;
			UART_vidEndReciption();
			return Timeout;
		}
		listenStat--;
		break;
	}
	return ListenWait;
}



// Create Server with Port defined as parameter
uint8 ESP8266_u8CreateServer( void )
{
	static uint8 serverState =0;
	char ATcommand[20];
	switch (serverState)
	{
	case 0:
		// create the server with port specified in parameters Structure.
		sprintf(ATcommand ,"AT+CIPSERVER=1,%d\r\n",param.port);
		ESP8266_vidSendCommand(ATcommand);
		serverState++;
		break;
	case 1:
		if (ESP8266_vidListen("OK",2,200)==ok)
		{
			serverState=0;
			return ok;
		}
		break;
	}
	return 0;
}

uint8 ESP8266_u8CheckForConnectionRequest()
{
	// if ",CONNECT is found there is a connection request
	if ( ESP8266_vidListen(",CONNECT",7,200) == Found )
	{
		return Found;
	}
	else if ( ESP8266_vidListen(",CONNECT",7,200) == Timeout  )
		return Timeout;
	else
		return Wait;
}

uint8 ESP8266_u8SendGETDataToOpendConnection( )
{
	static uint8 dataState =0;
	uint8 command [20];
	uint8 dataSize;
	uint8 SendGETListenReturn;
	switch (dataState )
	{
	case 0:
		// send dataSize Characters to connection 0.
		for (dataSize=0;param.getRequest[dataSize]!='\0';dataSize++);
		sprintf(command,"AT+CIPSEND=%d\r\n",dataSize);
		ESP8266_vidSendCommand(command);
		dataState++;
		break;
	case 1:
		SendGETListenReturn = ESP8266_vidListen("OK",2,3000);
		switch ( SendGETListenReturn)
		{
		case Found:
			dataState++;
			break;
		case Timeout:
			dataState=0;
			return NotConnected;
			break;
		default:break;
		}
		break;
	case 2:
		ESP8266_vidSendCommand(param.getRequest);
		dataState++;
		break;
	case 3:
		if ( UTxFlag == 0)
		{
			dataState =0;
			return DataSent;
		}
		break;
	}
	return Wait;
}

uint8 ESP8266_u8NumberOfConnections(uint8 connections)
{
static uint8 numberOfConnectionsState =0;
uint8 command[20];
switch (numberOfConnectionsState)
{

case 0:
	// specify the connection to be only 1
	sprintf(command,"AT+CIPMUX=%d",connections);
	ESP8266_vidSendCommand( command );
	numberOfConnectionsState++;
	break;
case 1:
	if (ESP8266_vidListen("OK",2,200)==ok)
	{
		numberOfConnectionsState=0;
		return ok;
	}
	break;
}
	return Wait;
}

uint8 ESP8266_u8ConnectToHost( )
{
static char ATCommand [100];
static uint8 connectToHostState =0;
uint8 connectToHostListenReturn;
switch ( connectToHostState)
{
case 0:
	sprintf( ATCommand,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",param.ConnectionType, param.host, param.port);
	ESP8266_vidSendCommand(ATCommand);
	connectToHostState++;
	break;
case 1:
	connectToHostListenReturn = ESP8266_vidListen("OK",2,3000);
	switch ( connectToHostListenReturn)
	{
	case Found:
		connectToHostState=0;
		return Connected;
		break;
	case Timeout:
		connectToHostState=0;
		return NotConnected;
		break;
	default:break;
	}
}
return Wait;

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
		ESP8266_vidSendCommand(command);
		sendState++;
		break;
	case 1:
		if ( UTxFlag ==0)
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
	char command[15];
	switch( EspInitCase)
	{
	case 0 :
		// SEND AT To check ESP is active or not
		// UART_vidSetTxArr("AT\r\n",0);
		ESP8266_vidSendCommand("AT\r\n");
		EspInitCase++;
		break;
	case 1:
		if ( ESP8266_vidListen("OK",2,200) == 1)
		EspInitCase++;
		else
		{// Handle Error cases.
		}
		break;
	case 2:
		// Send the mode specified in ESP_INITPARAM struct
		sprintf(command , "AT+CWMODE=%d\r\n",param.mode);
		ESP8266_vidSendCommand(command);
		EspInitCase++;
		break;
	case 3:
		if (  ESP8266_vidListen("OK",2,200) == ok )
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

uint8 ESP8266_u8Reset()
{

	static uint8 ResetState =0;
	char ATCommand [15];
	switch ( ResetState)
	{
	case 0:

		sprintf( ATCommand, "AT+RST\r\n");
		ESP8266_vidSendCommand(ATCommand);
		ResetState++;
		break;
	case 1:
		if ( ESP8266_vidListen("Ai-Thinker",2,2000) == ok )
		{
			ResetState =0;
			return ok;
		}
		break;
	}
	return Wait;

}

void ESP8266_vidDeepSleap(uint8 ms)
{
char ATCommand [20];
sprintf	(ATCommand,"AT+GSLP=%d",ms);
ESP8266_vidSendCommand(ATCommand);
}

enum
{

ESPCheckStatus =0,
ESPJoinNetWork,
ESPConnectToHost,
ESPSendGetRequest,
ESPCheckResponce,
ESPCloseConnection,
ESPReset
};

/////// Example //////////////
uint8 ESP8266_Example()
{
	static uint8 EspExampleCase = ESPCheckStatus;
	uint8 ListenReturn;
	switch( EspExampleCase)
	{
	case ESPCheckStatus:
		ListenReturn = ESP8266_u8CheckStatues();
		switch ( ListenReturn)
		{
		case TRANSMISSION_CONNECTED:
			EspExampleCase=ESPSendGetRequest;
			break;
		case TRANSMISSION_DISCONNECTED:
			EspExampleCase = ESPConnectToHost;
			break;
		case NOT_CONNECTED_TO_AP:
			EspExampleCase = ESPJoinNetWork;
			break;
		case NotConnected:
		case UNKNOWN_ERROR:
			EspExampleCase=ESPReset;
		}
		break;
	case ESPJoinNetWork:
		if ( ESP_vidJoinNetwork() == Connected)
			EspExampleCase = ESPConnectToHost;
		break;
	case ESPConnectToHost:
		ListenReturn = ESP8266_u8ConnectToHost();
		switch ( ListenReturn)
		{
		case Connected:
			EspExampleCase = ESPSendGetRequest;
			break;
		case NotConnected:
			EspExampleCase=ESPReset;
			break;
		}

		break;
	case ESPSendGetRequest:
		ListenReturn = ESP8266_u8SendGETDataToOpendConnection();
		switch ( ListenReturn)
		{
		case DataSent:
			EspExampleCase = ESPCheckResponce;
			break;
		case NotConnected:
			EspExampleCase=0;
			break;
		default:break;
		}

		break;
	case ESPCheckResponce:

		ListenReturn = ESP8266_vidListen("{\"success\":1" ,15,200 );
		switch ( ListenReturn)
		{
		case Found:
			EspExampleCase = ESPCloseConnection;

			break;
		case Timeout:
			EspExampleCase= ESPCheckStatus;

			break;
		}

		break;
	case ESPCloseConnection:
		if ( ESP8266_vidCloseConnection() ==1)
			{

			EspExampleCase =0;
			global=1;
			}
		break;
	case ESPReset:
		if ( ESP8266_u8Reset()==1)
			EspExampleCase = ESPJoinNetWork;
		break;

	}
	return 0;

}


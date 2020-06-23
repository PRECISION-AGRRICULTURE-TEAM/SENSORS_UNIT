
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
#include "../GPIO/GPIO.h"

 //ESP Initialization parameters --> Change base on your configurations
struct ESP_INIT_PARAM param = {1,"AbdAlrhmanAbdah","01157227548","GET /API/insert.php?UnitId=1&SoilTemp=35.6%20&SoilMoisture=30.214&AirTemp=30.2&AirHumidity=12.7 HTTP/1.1\r\nHOST:192.168.1.4\r\nConnection: close\r\n\r\n ",
"192.168.1.4" ,80,"TCP"};

	
///////////////
// Change to 1 if tick in ms - Change to 1000 if tick in Micro Seconds
#define TIME_OUT 1
///////////////

void copyString ( uint8_t * string , uint8_t * stringToCopy )
{
	uint8_t i,j;
	for ( j =0; string[j] != '\0' ; j++ )
	{}
	for (  i =0; stringToCopy[i] != '\0' ;i++)
	{
		string[i+j] = stringToCopy[i];
	}
	string[i+j] = '\0';
}



void setSensorData( uint8_t * SoilMois,uint8_t * SoilTemp,uint8_t * AirTemp,uint8_t * AirHumidity)
{
	param.GETRequest[0] = '\0';
	copyString(param.GETRequest,"GET /API/insert.php?UnitId=1");
	copyString(param.GETRequest,"&SoilTemp=");
	copyString(param.GETRequest,SoilTemp);
	copyString(param.GETRequest,"%20&SoilMoisture=");
	copyString(param.GETRequest,SoilMois);
	copyString(param.GETRequest,"&AirTemp=");
	copyString(param.GETRequest,AirTemp);
	copyString(param.GETRequest,"&AirHumidity=");
	copyString(param.GETRequest,AirHumidity);
	copyString(param.GETRequest," HTTP/1.1\r\nHOST:192.168.1.4\r\nConnection: close\r\n\r\n ");
	

}
enum
{
	DataSent=1
}SendData;
enum ESP_STATUS ESP8266_u8CheckStatues ()
{

    static uint8_t checkStatuesState=0;
	uint8_t ATcommand[20] ={0};
	uint8_t ListenReturn ;
	switch ( checkStatuesState)
	{
	case 0:

	
		// SEND Command to check ESP statues
 		//	copyString ( ATcommand , ( uint8_t *) "AT+CIPSTATUS\r\n");
		ESP8266_vidSendCommand("AT+CIPSTATUS\r\n");
		checkStatuesState++;
		break;
	case 1:

		// Listen To Response of ESP8266 .. If ESP replay with STATUS check number after STATUS
		// Ex. ( STATUS:2) -> Connected TO AP
		ListenReturn = ESP8266_vidListen(( uint8_t *) "STATUS:",8,1500); // TIME out in 500 ms
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
void ESP8266_vidSendCommand(uint8_t * command)
{



	UART_vidSetTxArr(command);
}
// Function that joins Network with SSID and Password defined in parameters structure.
uint8_t ESP_vidJoinNetwork ()
{
	static uint8_t joinNetworkState=0;
	uint8_t ATcommand[50]={0} ;
	uint8_t ListenReturn;
	switch ( joinNetworkState)
	{
	case 0:
		// format the join network command based on network parameters
	//	sprintf ( ATcommand ,"AT+CWJAP=\"%s\",\"%s\"\r\n",param.SSID,param.PASSWORD );
		copyString (ATcommand,"AT+CWJAP=\"");
		copyString (ATcommand,param.SSID);
		copyString (ATcommand,"\",\"");
		copyString (ATcommand,param.PASSWORD);
		copyString (ATcommand,"\"\r\n");
		ESP8266_vidSendCommand(ATcommand);
		joinNetworkState++;
		break;
	case 1:

		// Wait 5000 ticks to listen to OK
		ListenReturn =ESP8266_vidListen("OK",2,5000); // Time out in 5 s
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
uint8_t ESP_vidCheckForIP()
{
	static uint8_t checkForIpState =0;
	uint8_t ATCommand [10] ={0};
	switch( checkForIpState)
	{

	case 0:
		copyString(ATCommand,"AT+CIFSR\r\n");
		ESP8266_vidSendCommand(ATCommand);
		checkForIpState++;
		break;
	case 1:
		// If ESP returned OK .. IP returned Successfully.
		if ( ESP8266_vidListen("OK",2,200) == ok ) // Timeout in 200 ms
		{
			checkForIpState=0;
			return 1;
		}

	}
	return 0;

}
// Function To listen to specific word and fetch specific size of string after it
// with timeout timer to check if time is out before finding the word
uint8_t ESP8266_vidListen(uint8_t * wordToFind ,uint8_t sizeOfStringToFetch, uint16_t timeOut )
{
	
	static uint32_t timOutCounter=0;
	volatile static uint8_t listenStat=0;
	switch ( listenStat )
	{
	case 0 :

		// Set UART fetch the word and characters after it with specified length
		UART_vidSetRxArr(sizeOfStringToFetch,wordToFind );
		listenStat++;

		break;
	case 1:

		// if word is found return 1.
		if ( URxFlag == 0 )
		{

			listenStat=0;
			return Found ;
		}
		listenStat++;
		break;
	case 2:
		// if Counter reaches timeOut >> timeout error
		timOutCounter++;
		if ( timOutCounter >( timeOut * TIME_OUT) )
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
uint8_t ESP8266_u8CreateServer( void )
{
	static uint8_t serverState =0;
	uint8_t ATcommand[20] ={0};
	switch (serverState)
	{
	case 0:
		// create the server with port specified in parameters Structure.
		copyString(ATcommand ,"AT+CIPSERVER=1,80\r\n");
		ESP8266_vidSendCommand(ATcommand);
		serverState++;
		break;
	case 1:
		if (ESP8266_vidListen("OK",2,200)==ok) // Time out in 200 ms
		{
			serverState=0;
			return ok;
		}
		break;
	}
	return 0;
}

uint8_t ESP8266_u8CheckForConnectionRequest()
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


uint8_t * intToString (uint8_t num)
{

	uint8_t i=100,index=0;
	static uint8_t string[4]={0};
	
	while (1)
	{
	//128
	if(num/i)
	{
					string[index] = (num/i)+48;
					index++;			
	}else
	{
	
		i =10;
		if(num/i)
		{
			string[index] = (num/i)+48;
			index++;
		}else
		{
			
				string[index] = (num%i)+48;
				string[index+1]='\0';
				return string;
		}
	}
	//////////////////////
	num = num%i;
	}

}
uint8_t ESP8266_u8SendGETDataToOpendConnection( )
{
	volatile static uint8_t dataState =0;
	uint8_t command [20] = {0};
	static uint16_t dataSize=0;
	uint8_t index;
	uint8_t * num;
	uint8_t SendGETListenReturn;
	switch (dataState )
	{
		case 0:
			for (index=0;param.GETRequest[index]!='\0';index++);
			dataSize=index;

	dataState++;
		break;
	case 1:

		// send dataSize Characters to connection 0.

	//////////////////////	
	copyString(command,"AT+CIPSEND=");
		num = intToString(dataSize);
		copyString(command,num);
		copyString(command,"\r\n");
		ESP8266_vidSendCommand(command);
		SendGETListenReturn = ESP8266_vidListen("OK",2,3000);
		dataSize=0;
		dataState++;
		break;
	case 2:
		if ( UTxFlag ==0 ) 	dataState++;
	break;
	case 3:

		SendGETListenReturn = ESP8266_vidListen("OK",2,3000);// Timeout 1 s
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
	case 4:
		ESP8266_vidSendCommand(param.GETRequest);
		dataState++;
		break;
	case 5:
		if ( UTxFlag == 0)
		{
		//	dataState++;
			dataState =0;
		return DataSent;
		}
		break;

	
	}
	return Wait;
}

uint8_t ESP8266_u8NumberOfConnections(uint8_t connections)
{
static uint8_t numberOfConnectionsState =0;
uint8_t command[20]={0};
switch (numberOfConnectionsState)
{

case 0:
	// specify the connection to be only 1
		copyString(command,"AT+CIPMUX=");
		copyString(command,intToString(connections));
		copyString(command,"\r\n");
	//sprintf(command,"AT+CIPMUX=%d",connections);
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

uint8_t ESP8266_u8ConnectToHost( )
{
 uint8_t ATCommand [100]={0};
static uint8_t connectToHostState =0;
uint8_t connectToHostListenReturn;
switch ( connectToHostState)
{
case 0:

/////////////////////////////
	copyString(ATCommand,"AT+CIPSTART=\"");
	copyString(ATCommand,param.ConnectionType);
	copyString(ATCommand,"\",\"");
	copyString(ATCommand,param.host);
	copyString(ATCommand,"\",");
  copyString(ATCommand,intToString(param.port));
	copyString(ATCommand,"\r\n");
	ESP8266_vidSendCommand(ATCommand);
	connectToHostState++;
	break;
case 1:
	connectToHostListenReturn = ESP8266_vidListen("OK",2,4000); // TimeOut 2 seconds
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


uint8_t ESP8266_vidCloseConnection()
{
	static uint8_t sendState =0;
	uint8_t command [20] = {0};
	switch (sendState)
	{
	case 0:
		// close connection 0
		copyString(command,"AT+CIPCLOSE=0\r\n");
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

uint8_t ESP8266_Init()
{
	static uint8_t EspInitCase = 0;
	 uint8_t InitListen;
	char command[15] = {0};
	switch( EspInitCase)
	{
	case 0 :
		// SEND AT To check ESP is active or not
		// UART_vidSetTxArr("AT\r\n",0);
	
		ESP8266_vidSendCommand("AT\r\n");
		InitListen= ESP8266_vidListen("OK",2,200);			
//ESP8266_vidSendCommand(SensorData.GETHeader);
		EspInitCase++;
	break;
	case 1:
			
		InitListen= ESP8266_vidListen("OK",2,200);																									
	
		switch ( InitListen)
		{

		case Found:

			EspInitCase++;
		break;
		case Timeout:

			EspInitCase=0;
			return NotConnected;
		break;
		default:
	
			break;
		}
	break;
	case 2:
		// Send the mode specified in ESP_INITPARAM struct
		copyString(command,"AT+CWMODE=");
		copyString(command,intToString(param.mode));
		copyString(command,"\r\n");
		ESP8266_vidSendCommand(command);
		EspInitCase++;
	break;
	case 3:
		InitListen= ESP8266_vidListen("OK",2,200) ;
			
		switch ( InitListen)
		{
		case Found:
			EspInitCase=0;
			return Connected;
		break;
		case Timeout:
			EspInitCase=0;
			return NotConnected;
		break;
		}	
	break;
	}
	return 0;
}

uint8_t ESP8266_u8Reset()
{

	static uint8_t ResetState =0;
	char ATCommand [15] = {0};
	switch ( ResetState)
	{
	case 0:

		copyString( ATCommand, "AT+RST\r\n");
		ESP8266_vidSendCommand(ATCommand);
		ResetState++;
		break;
	case 1:

		if ( ESP8266_vidListen("Ai-Thinker",2,2000) == ok ) // Timeout 2 s
		{

			ResetState =0;
			return ok;
		}
		break;
	}
	return Wait;

}

void ESP8266_vidDeepSleap(uint8_t ms)
{
uint8_t ATCommand [20] = {0};
copyString(ATCommand,"AT+GSLP=");
copyString(ATCommand,intToString(ms));
copyString(ATCommand,"\r\n");
//sprintf	(ATCommand,"AT+GSLP=%d",ms);
ESP8266_vidSendCommand(ATCommand);
}

enum
{

ESPCheckStatus=0,
ESPJoinNetWork,
ESPConnectToHost,
ESPSendGetRequest,
ESPCheckResponce,
ESPCloseConnection,
ESPReset
};

/////// Example //////////////
uint8_t ESP8266_Example()
{
	
	
	volatile static uint8_t EspExampleCase = ESPCheckStatus;
	static ret =0;
	
	static uint8_t ListenReturn;
	switch( EspExampleCase)
	{
		
	case ESPCheckStatus:
		
		ListenReturn =  ESP8266_u8CheckStatues();
//	EspExampleCase=20;

		switch ( ListenReturn)
		{
		case TRANSMISSION_CONNECTED:
			EspExampleCase=ESPSendGetRequest;
			break;
		case CONNECTED_TO_AP:
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
		{
			EspExampleCase = ESPConnectToHost;
	
		}
		break;
	case ESPConnectToHost:

	/////////////////////////////////
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
			EspExampleCase=ESPCheckStatus;
			break;
		default:break;
		}

		break;
	case ESPCheckResponce:

		ListenReturn = ESP8266_vidListen("{\"success\":1" ,15,5000 );
		switch ( ListenReturn)
		{
		case Found:
			EspExampleCase = ESPCloseConnection;

			break;
		case Timeout:
			EspExampleCase=ESPCheckStatus;

			break;
		}

		break;
	case ESPCloseConnection:
		if ( ESP8266_vidCloseConnection() ==1)
			{

			EspExampleCase =ESPCheckStatus;
			ret = 1;
			}
		break;
	case ESPReset:
		if ( ESP8266_u8Reset()==1)
			EspExampleCase = ESPJoinNetWork;
		break;
		
	default : break;

	}
	return ret;

}


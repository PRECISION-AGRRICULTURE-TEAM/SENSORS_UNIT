
/** @file ESP8266.h
 *  @brief ESP8266 Driver V 1.0
 *
 *  Created on: May 26, 2020
 *  Handles sending to a Local server with only one connection.
 *
 * @author Alaa AbdAlrhman
 * @bug no known bugs
 */

#ifndef ESP8266_H_
#define ESP8266_H_
#include "Utils.h"
#include "Std_Types.h"
#include "../UART/UART.h"

/*@brief
 *
 * Mode : mode of Operation ( 1-> Station mode, 1-> Access point mode, 3-> Access Point and Station mode)
 * SSID : WiFi Network name to join
 * Pssword : Password of WiFi Network to join
 *
 * */
struct ESP_INIT_PARAM
{
uint8_t mode ; // station mode
uint8_t SSID [20] ;
uint8_t PASSWORD [20];
uint8_t GETRequest[300];
char host[60];
uint8_t port;
char ConnectionType[4];
};

/*@brief
 *
 * Mode : mode of Operation ( 1-> Station mode, 1-> Access point mode, 3-> Access Point and Station mode)
 *
 * */
enum ESP_MODS
{
	station =1,
	accessPoint =2,
	stationAccessPoint=3
};
/*@brief
 *
 * Some Used Enums for Control
 *
 * */
enum
{
	noOption =255,
	ok=1,
	error=2,
};

 enum ESPNetwork
{
	Wait = 0,
	Connected =1,
	NotConnected =7
};


 enum ESPListen
{
	ListenWait = 0,
	Found =1,
	Timeout =2
};

enum ESP_STATUS
{
	CONNECTED_TO_AP=2,
	TRANSMISSION_CONNECTED,
	TRANSMISSION_DISCONNECTED,
	NOT_CONNECTED_TO_AP,
	UNKNOWN_ERROR,
	
};

void wifiMainFunctuion ();

/*@brief
 *
 * Used to Initialize Esp and set it's Mode to
 * ( 1, Station ) , ( 2, Access point) , ( 3, Access point and Station)
 *
 *
 *@return ( 1 ,Configuration is Done) ( 0, Wait)
 * */
uint8_t ESP8266_Init();

/*@brief
 *
 * Used to check Esp Status
 * Example : STATUS = 2 >> Esp is connected to Access Point
 * Example : STATUS = 3 >> Esp is Connected to transmission channel
 * Example : STATUS = 4 >> Esp is not Connected to transmission channel
 * Example : STATUS = 5 >> Esp is not connected to Access point.
 *
 *
 *@return STATUS ( (2,CONNECTED_TO_AP) , (3,TRANSMISSION_CONNECTED) ,(4  TRANSMISSION_DISCONNECTED ),(5 ,UNKNOWN_ERROR ) ,( 7 ,NotConnected >> TimeOut Error))
 * */

enum  ESP_STATUS ESP8266_u8CheckStatues ();
/*@brief
 *
 *Used to send Commands to Esp
 *
 *@param command: Command to send Ex ( AT, AT+SIFR, AT+CIPSEND ...)
 *@param option : in case command has options Ex ( AT+CWMODE=1 )..(1 .. is Option for the command (AT+CWMODE)
 *@param  query : in case command with querey Ex ( AT+CWMODE=? )
 *@return void
 * */
void ESP8266_vidSendCommand(uint8_t * command);
/*@brief
 *
 *Used to Join to Network with Defined SSID and Password in structure "ESP_INIT_PARAM"
 *
 *@return ( 0 Wait), ( 1 Connected ), (7 NotConnected >> Timeout error)
 * */
uint8_t ESP_vidJoinNetwork ();
/*@brief
 *
 *Used to Check IP State. prints the IPs if there are any.
 *@return ( 0 Wait), ( 1 Done )

 * */
uint8_t ESP_vidCheckForIP();
/*@brief
 *
 * Used to Listen to the ESP UART bus for Specified word
 * Example ESP8266_vidListen("OK",5, 500);
 * The function will wait for "OK" to show up before 500 tick happens
 * if OK is found it will fetch it with another 3 characters after it,
 * else if 500 ticks happens before it found it will return a time out error
 *
 *@param wordToFind : word to search for at ESP UART bus
 *@param sizeOfStringToFetch : Size of string to fetch
 *@param timeOut : time in tick which after it the timeout error will show up
 *@return ( 0 Wait), ( 1 Found ), (2 Timeout >> Timeout error)
 * */
uint8_t ESP8266_vidListen(uint8_t * wordToFind,uint8_t sizeOfStringToFetch, uint16_t timeOut );
/*@brief
 *
 * Used to Create a server on the port declared in param structure
 *
 *@return ( 1 , Ok >> Server created successfully ) ,( 0 , Wait)
 *
 * */
uint8_t ESP8266_u8CreateServer( );
/*@brief
 *
 *Used to check for connection request ( usually by browsers accessing IP address of the ESP )
 *
 *@return ( 1 , Found >> Connection Request found ) ,( 0 , Wait),(2, Timeout >> timeout error)
 * */
uint8_t ESP8266_u8CheckForConnectionRequest();
/*@brief
 *
 * Used to open a connection to a host with a specified Connection type ( TCP,UDP)
 * to host on a port defined in param structure
 *
 *@param dataSize : number of data to be sent
 *
 * */
uint8_t ESP8266_u8ConnectToHost();


/*@brief
 *
 * Used to send Get Request defined in Param structure to an opened connection
 *
 *
 *
 *@return ( 1 , DataSent >> Connection created ) ,( 0 , Wait),(7,NotConnected >> Timeout error)
 * */
uint8_t ESP8266_u8SendGETDataToOpendConnection();


/*@brief
 *
 *Used to close opened connection
 *@return ( 1 , Ok >> Connection closed ) ,( 0 , Wait)
 * */
uint8_t ESP8266_vidCloseConnection();


/*@brief
 *
 *Example demonstrating using of ESP8266 driver APIs
 *
 *
 * */
uint8_t ESP8266_Example();



#endif /* ESP8266_H_ */

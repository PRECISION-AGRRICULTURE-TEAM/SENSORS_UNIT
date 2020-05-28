
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
#include "UART.h"

/*@brief
 *
 * Mode : mode of Operation ( 1-> Station mode, 1-> Access point mode, 3-> Access Point and Station mode)
 * SSID : WiFi Network name to join
 * Pssword : Password of WiFi Network to join
 *
 * */
struct ESP_INIT_PARAM
{
uint8 mode ; // station mode
uint8 SSID [20] ;
uint8 PASSWORD [20];
};
/*@brief
 *
 * Mode : mode of Operation ( 1-> Station mode, 1-> Access point mode, 3-> Access Point and Station mode)
 *
 * */
enum
{
	station =1,
	accessPoint =2,
	stationAccessPoint=3
}ESP_MODS;
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
	timeout=3,
	querey =4,
	noQuerey =5
};
/*@brief
 *
 *Used to send Commands to Esp
 *
 *@param command: Command to send Ex ( AT, AT+SIFR, AT+CIPSEND ...)
 *@param option : in case command has options Ex ( AT+CWMODE=1 )..(1 .. is Option for the command (AT+CWMODE)
 *@param  query : in case command with querey Ex ( AT+CWMODE=? )
 * */
void ESP8266_vidSendCommand(uint8 * command,uint8 option,uint8 query);
/*@brief
 *
 *Used to Join to Network with Defined SSID and Password in structure "ESP_INIT_PARAM"
 *
 * */
void ESP_vidJoinNetwork ();
/*@brief
 *
 *Used to Check IP State. prints the IPs if there are any.
 *
 * */
void ESP_vidCheckForIP();
/*@brief
 *
 *Used to Listen to the ESP UART bus for Specified word
 *
 *@param wordToFind : word to search for at ESP UART bus
 *
 * */
uint8 ESP8266_vidListen(uint8 * wordToFind);
/*@brief
 *
 *Used to Create a server
 *
 *@param port : port for the server
 *
 * */
uint8 ESP8266_vidCreateServer( uint8 port);
/*@brief
 *
 *Used to check for connection request ( usually by browsers accessing IP address of the ESP )
 *
 * */
uint8 ESP8266_vidCheckForConnectionRequest();
/*@brief
 *
 *Used to open a connection.
 *must be used after a connection request.
 *opens a window with a specified number of characters
 *
 *@param dataSize : number of data to be sent
 *
 * */
uint8 ESP8266_vidOpenConnection(uint16 dataSize);
/*@brief
 *
 *Used to send data to an opened connection with same number of characters requested before
 *
 *@param Data : string to be send through connection
 *
 * */
uint8 ESP8266_vidSendDataToOpendConnection(uint8 * Data);
/*@brief
 *
 *Used to close opend connection
 *
 * */
uint8 ESP8266_vidCloseConnection();
/*@brief
 *
 *Example demonstrating using of ESP8266 driver APIs
 *
 *
 * */
uint8 ESP8266_Example();



#endif /* ESP8266_H_ */

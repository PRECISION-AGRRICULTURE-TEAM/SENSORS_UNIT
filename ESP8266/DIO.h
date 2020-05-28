/*
 * DIO.h
 *
 *  Created on: Nov 15, 2019
 *      Author: Alaa Abdah
 */

#ifndef DIO_H_
#define DIO_H_


#include "Std_Types.h"
#include "DIO_local.h"
#include "Utils.h"

#define HIGH 1
#define LOW  0
//////////////////
#define NIBBLE_HIGH 1
#define NIBBLE_LOW 0
///////////////////////
#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3


void DIO_vidInit();

void DIO_vidSetPinDir(uint8 U8PinNum, uint8 U8Dir);
void DIO_vidSetNibbleDir(uint8 U8PortNum,uint8 U8nibbleDirection ,uint8 U8Dir);
void DIO_vidSetPortDir(uint8 U8PortNum, uint8 U8Dir);
void DIO_vidWritePin(uint8 U8PinNum, uint8 U8Value);

uint8 DIO_U8ReadPin(uint8 U8PinNum);

void DIO_vidWritePort(uint8 U8PortNum, uint8 U8Value);
void DIO_vidWriteNibble(uint8 U8PortNum,uint8 U8nibbleDirection, uint8 U8Value);
uint8 DIO_vidReadNibble(uint8 U8PortNum,uint8 U8nibbleDirection);

uint8 DIO_U8ReadPort(uint8 U8PortNum);

#endif /* DIO_H_ */

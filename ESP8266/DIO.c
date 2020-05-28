/*
 * DIO.c
 *
 *  Created on: Dec 10, 2019
 *      Author: Alaa Abdah
 */


#include "DIO.h"

void DIO_vidInit(){}
//////////////////////////////
void DIO_vidSetPinDir(uint8 U8PinNum, uint8 U8Dir)

{
	uint8 pin = U8PinNum % PIN_P_PORT;
	switch( U8PinNum / PIN_P_PORT)
	{
	case PORT0 :ASSIGN_BIT(DDRA,pin,U8Dir);
			break;
	case PORT1 :ASSIGN_BIT(DDRB,pin,U8Dir);
			break;
	case PORT2 :ASSIGN_BIT(DDRC,pin,U8Dir);
			break;
	case PORT3 :ASSIGN_BIT(DDRD,pin,U8Dir);
			break;
	}
}
void DIO_vidSetNibbleDir(uint8 U8PortNum,uint8 U8nibbleDirection ,uint8 U8Dir)
{
	switch( U8nibbleDirection )
			{
			case NIBBLE_LOW :

				switch( U8PortNum )
							{
							case PORT0 :ASSIGN_L_NIB(DDRA,U8Dir);
									break;
							case PORT1 :ASSIGN_L_NIB(DDRB,U8Dir);
									break;
							case PORT2 :ASSIGN_L_NIB(DDRC,U8Dir);
									break;
							case PORT3 :ASSIGN_L_NIB(DDRD,U8Dir);
									break;
							}
					break;

			case NIBBLE_HIGH :
				switch( U8PortNum )
				{
				case PORT0 :ASSIGN_H_NIB(DDRA,U8Dir);
						break;
				case PORT1 :ASSIGN_H_NIB(DDRB,U8Dir);
						break;
				case PORT2 :ASSIGN_H_NIB(DDRC,U8Dir);
						break;
				case PORT3 :ASSIGN_H_NIB(DDRD,U8Dir);
						break;
				}
			break;
			}
}
void DIO_vidSetPortDir(uint8 U8PortNum, uint8 U8Dir)
{
	switch( U8PortNum )
			{
			case PORT0 :ASSIGN_PORT(DDRA,U8Dir);
					break;
			case PORT1 :ASSIGN_PORT(DDRB,U8Dir);
					break;
			case PORT2 :ASSIGN_PORT(DDRC,U8Dir);
					break;
			case PORT3 :ASSIGN_PORT(DDRD,U8Dir);
					break;
			}
}
///////////////////////////////////
void DIO_vidWritePin(uint8 U8PinNum, uint8 U8Value)
{
	uint8 pin = U8PinNum % PIN_P_PORT;
	uint8 port = U8PinNum/PIN_P_PORT;
		switch( port )
		{
		case PORT0 :ASSIGN_BIT(PORTA,pin,U8Value);
				break;
		case PORT1 :ASSIGN_BIT(PORTB,pin,U8Value);
				break;
		case PORT2 :ASSIGN_BIT(PORTC,pin,U8Value);
				break;
		case PORT3 :ASSIGN_BIT(PORTD,pin,U8Value);
				break;
		}
}


void DIO_vidTogglePin(uint8 U8PinNum)
{
	uint8 pin = U8PinNum % PIN_P_PORT;
	uint8 port = U8PinNum/PIN_P_PORT;
		switch( port )
		{
		case PORT0 :TOGGLE_BIT(PORTA,pin);
				break;
		case PORT1 :TOGGLE_BIT(PORTB,pin);
				break;
		case PORT2 :TOGGLE_BIT(PORTC,pin);
				break;
		case PORT3 :TOGGLE_BIT(PORTD,pin);
				break;
		}
}
void DIO_vidWriteNibble(uint8 U8PortNum,uint8 U8nibbleDirection, uint8 U8Value)
{

	switch( U8nibbleDirection )
			{
			case NIBBLE_LOW :

				switch( U8PortNum )
							{
							case PORT0 :ASSIGN_L_NIB(PORTA,U8Value);
									break;
							case PORT1 :ASSIGN_L_NIB(PORTB,U8Value);
									break;
							case PORT2 :ASSIGN_L_NIB(PORTC,U8Value);
									break;
							case PORT3 :ASSIGN_L_NIB(PORTD,U8Value);
									break;
							}
					break;

			case NIBBLE_HIGH :
				switch( U8PortNum )
				{
						case PORT0 :ASSIGN_H_NIB(PORTA,U8Value);
								break;
						case PORT1 :ASSIGN_H_NIB(PORTB,U8Value);
								break;
						case PORT2 :ASSIGN_H_NIB(PORTC,U8Value);
								break;
						case PORT3 :ASSIGN_H_NIB(PORTD,U8Value);
								break;
						}
			break;
			}

}
void DIO_vidWritePort(uint8 U8PortNum, uint8 U8Value)
{

		switch( U8PortNum )
		{
			case PORT0 :ASSIGN_PORT(PORTA,U8Value);
					break;
			case PORT1 :ASSIGN_PORT(PORTB,U8Value);
					break;
			case PORT2 :ASSIGN_PORT(PORTC,U8Value);
					break;
			case PORT3 :ASSIGN_PORT(PORTD,U8Value);
					break;
			}
}
///////////////////////////////////////
uint8 DIO_U8ReadPin(uint8 U8PinNum)
{
	uint8 value;
	uint8 pin = U8PinNum % 8;
	switch( U8PinNum / 8)
	{
		case 0 :value = GET_BIT(PINA,pin);
				break;
		case 1 :value = GET_BIT(PINB,pin);
				break;
		case 2 :value = GET_BIT(PINC,pin);
				break;
		case 3 :value = GET_BIT(PIND,pin);
				break;
	}
	return value;
}
uint8 DIO_vidReadNibble(uint8 U8PortNum,uint8 U8nibbleDirection)
{
	uint8 value;
	switch( U8nibbleDirection )
			{
			case NIBBLE_LOW :

				switch( U8PortNum )
				{
					case PORT0 :value = GET_L_NIB(PINA);
							break;
					case PORT1 :value =GET_L_NIB(PINB);
							break;
					case PORT2 :value =GET_L_NIB(PINC);
							break;
					case PORT3 :value =GET_L_NIB(PIND);
							break;
				}
					break;

			case NIBBLE_HIGH :

				switch( U8PortNum )
				{
					case PORT0 :value = GET_H_NIB(PINA);
							break;
					case PORT1 :value = GET_H_NIB(PINB);
							break;
					case PORT2 :value = GET_H_NIB(PINC);
							break;
					case PORT3 :value = GET_H_NIB(PIND);
							break;
				}
			break;
			}
	return value;
}
uint8 DIO_U8ReadPort(uint8 U8PortNum)
{
	uint8 value;

	switch( U8PortNum )
	{
		case PORT0 :value = GET_PORT(PINA);
				break;
		case PORT1 :value = GET_PORT(PINB);
				break;
		case PORT2 :value = GET_PORT(PINC);
				break;
		case PORT3 :value = GET_PORT(PIND);
				break;
	}
	return value;
}

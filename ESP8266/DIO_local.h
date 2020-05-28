/*
 * DIO_local.h
 *
 *  Created on: Dec 10, 2019
 *      Author: Alaa Abdah
 */

#ifndef DIO_LOCAL_H_
#define DIO_LOCAL_H_


#define PIN_P_PORT 8
//////////////////////////
#define DDRA	 	*( uint8 *)(0x3A)
#define PORTA 		*( uint8 *)(0x3B)
#define PINA 		*( uint8 *)(0x39)
#define DDRB 		*( uint8 *)(0x37)
#define PORTB 		*( uint8 *)(0x38)
#define PINB 		*( uint8 *)(0x36)
#define DDRC 		*( uint8 *)(0x34)
#define PORTC 		*( uint8 *)(0x35)
#define PINC 		*( uint8 *)(0x33)
#define DDRD 		*( uint8 *)(0x31)
#define PORTD 		*( uint8 *)(0x32)
#define PIND 		*( uint8 *)(0x30)


/////////////////////////////
//ADC RIGESTERS//////////////

#define ADCSRA 		*( uint8 *)(0x26)
#define ADCH   		*( uint8 *)(0x25)
#define ADCL 		*( uint8 *)(0x24)
#define ADCMUX 		*( uint8 *)(0x27)





#endif /* DIO_LOCAL_H_ */

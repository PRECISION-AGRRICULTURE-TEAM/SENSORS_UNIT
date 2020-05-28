/*
 * UART_local.h
 *
 *  Created on: Feb 7, 2020
 *      Author: Alaa Abdah
 */

#ifndef UART_LOCAL_H_
#define UART_LOCAL_H_


#define UDR   (*(uint8 *)(0x2C))
#define UCSRA (*(uint8 *)(0x2B))
#define UCSRB (*(uint8 *)(0x2A))
#define UCSRC (*(uint8 *)(0x40))
#define UBRRL (*(uint8 *)(0x29))
#define UBRRH (*(uint8 *)(0x40))


#endif /* UART_LOCAL_H_ */

/** @file UART_CFG.h
 *  @brief This file contains the Constants of the UART Driver
 *  @author  
 */
#ifndef UART_CFG_H_
#define UART_CFG_H_


#define UART 			UART1
#define UART_SEL  		ENABLE

#define RX_EN			ENABLE
#define TX_EN			ENABLE
#define BaudRate  		115200UL /* 58.59375  for 8 mhz*/
#define StopBit			One_STOPBIT//USART_CR2 (13,12)
#define Parity_Check 	No_Parity
#define Character_Size  EIGHT_Char//usart_cr1
#define Prescalar       1  //dived by 1

#define UART_PERIODIC	1

#if UART_PERIODIC == 1
#	define UART_BUFFERSIZE 		20
#	define UART_SENDCONFIMED 	0
#endif



#endif /* UART_H_ */

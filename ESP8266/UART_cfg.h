/*
 * UART_cfg.h
 *
 *  Created on: Feb 7, 2020
 *      Author: Alaa Abdah
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

#define UART_BAUD_RATE 115200

//0>>normal speed || 1>> double speed mode
#define SPEED_MODE 0
//16 for normal speed or 8 for double speed
#define SPEED_FACTOR (16-SPEED_MODE*8)
// Transmission array length
#define UTxArrayLen 60
// Reception array length
#define URxArrayLen 60
// The Matching string length
#define UMatchLen 20
// UART data size
#define UART_DATA_SIZE 8
// Accessing UCSRC Or UBRRH register
#define UCSRC_SEL 1
#define UBRRH_SEL 0
// USART synchronous and asynchronous modes
#define SYNC_UART 1
#define ASYNC_UART 0


//#define UART_STOP_FRAME 0// 0 for 1 bit
//#define UART_PARITY 0// 0 for no parity


#endif /* UART_CFG_H_ */

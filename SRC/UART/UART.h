/** @file UART.h
 *  @brief This file contains the Prototypes of the UART Driver
 *  @author  
 */
#ifndef UART_H_
#define UART_H_

#include "UART_CFG.h"

/** @brief  UART initialization function.
 *
 *
 *  @param 
 *  @return Void
 */
void    UART_vidInit(void);

/** @brief  Send Character by UART.
 *
 *
 *  @param  u8Data Character to be send
 *  @return Void
 */
void    UART_vidSendChar(uint8_t u8Data);

/** @brief  Recieve Character From UART.
 *
 *  @param 
 *  @return The recieved charcter 
 */
uint8_t UART_u8RecieveChar(void);

/** @brief  Check if data is ready in recieve buffer.
 *
 *
 *  @param 
 *  @return Status of buffer
 */
uint8_t UART_u8DataReady();

/** @brief  read data from recieve buffer.
 *
 *
 *  @param 
 *  @return data recieved in buffer
 */
uint8_t UART_u8GetData();

/** @brief  Send string over UART.
 *  
 *  this function uses busy wait
 *
 *  @param  u8Data the string to be send
 *  @param  u8Length the length of string
 *  @return 
 */
void    UART_vidSendString(uint8_t u8Data[], uint8_t u8Length);

/** @brief  Recieve string from UART.
 *  
 *  this function uses busy wait
 *
 *  @param  u8Data the string to Recieve in
 *  @param  u8Length the length of string
 *  @return 
 */
void    UART_vidRecieveString(uint8_t u8Data[], uint8_t * u8Length);


#endif /* UART_H_ */


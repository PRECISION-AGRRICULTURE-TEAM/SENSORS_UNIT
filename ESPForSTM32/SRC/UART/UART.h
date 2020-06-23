/** @file UART.h
 *  @brief This file contains the Prototypes of the UART Driver
 *  @author  
 */
#ifndef UART_H_
#define UART_H_

#include "UART_CFG.h"
#include "../COMMON/Std_Types.h"
#include "../COMMON/Utils.h"

#define UTxArrayLen 200
// Reception array length
#define URxArrayLen 200
// The Matching string length
#define UMatchLen 20
// UART data size
//////////////////
//////////////////
extern uint8_t URxArray [URxArrayLen];
extern volatile uint8_t URxArrayIndex ;
extern uint8_t URxArraySize;
extern volatile uint8_t URxFlag ;
extern uint8_t UMatchCase[UMatchLen] ;
extern uint8_t UMatchSize ;
/////////////////
/////////////////
extern uint8_t UTxArray [UTxArrayLen];
extern volatile uint8_t UTxArrayIndex ;
extern uint8_t UTxArraySize;
extern  uint8_t UTxFlag ;

////////////////////
/////////////////////



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


void  UART_vidSendChar(uint8_t u8Data);

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
uint8_t UART_u8DataReady(void);

/** @brief  read data from recieve buffer.
 *
 *
 *  @param 
 *  @return data recieved in buffer
 */
uint8_t UART_u8GetData(void);

/** @brief  Send string over UART.
 *  
 *  this function uses busy wait
 *
 *  @param  u8Data the string to be send
 *  @param  u8Length the length of string
 *  @return 
 */
uint8_t    UART_vidSendString(uint8_t u8Data[]);

/** @brief  Recieve string from UART.
 *  
 *  this function uses busy wait
 *
 *  @param  u8Data the string to Recieve in
 *  @param  u8Length the length of string
 *  @return 
 */
void    UART_vidRecieveString(uint8_t u8Data[], uint8_t * u8Length);

void USART1_vidEnavble(void);

void USART1_vidDisable(void);


/** @brief  Set Transmision Array to String that to be transmitted
 *  
 *  
 *
 *  @param  u8Data *  >the string set Transmission Array with.
 *  
 *  @return 
 */
void UART_vidSetTxArr (uint8_t * data );


/** @brief  Set Reciption Array size with size of String that to be received and set matchString array with string to be searched for.
 *  
 *  
 *
 *  @param  u8Data the size of string to be recieved.
 *  @param  u8Data * the string to be searched for.
 
 *  @return 
 */
void UART_vidSetRxArr (uint8_t size, uint8_t * matchString);


/** @brief  End of UART reciption.
 *  
 *  
 *
 *  @return 
 */

void UART_vidEndReciption(void);

#define USART2_TX   2 //PA2 9
#define USART2_RX   3

#define USART1_TX   9 //PA9 9
#define USART1_RX  10 //PA10 10

#define USART3_TX  26   //PB10 2
#define USART3_RX  27   //PB11 3

#endif /* UART_H_ */


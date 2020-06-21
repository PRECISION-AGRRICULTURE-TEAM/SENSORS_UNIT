/** @file UART_LOCAL.h
 *  @brief This file contains the Locals of the UART Driver
 *  @author  
 */

#ifndef UART_LOCAL_H_
#define UART_LOCAL_H_

#include "Std_Types.h"
#include "Utils.h"
#include "UART_CFG.h"

//#include "../GPIO/GPIO.h"

#define USART1_BASE  (0x40013800)
#define USART2_BASE  (0x40004400)
#define USART3_BASE  (0x40004800)
#define USART4_BASE  (0x40004C00)
#define USART5_BASE  (0x40005000)

/**  offsets **/


typedef struct{

uint32_t  USART_SR  ;
uint32_t  USART_DR  ;
uint32_t  USART_BRR ;
uint32_t  USART_CR1 ;
uint32_t  USART_CR2 ;
uint32_t  USART_CR3 ;
uint32_t  USART_GTRP ;

}UARAT_t;


#define UART1 (((volatile UARAT_t * ) USART1_BASE ))
#define UART2 (((volatile UARAT_t * ) USART2_BASE ))
#define UART3 (((volatile UARAT_t * ) USART3_BASE ))
#define UART4 (((volatile UARAT_t * ) USART4_BASE ))
#define UART5 (((volatile UARAT_t * ) USART5_BASE ))


/*register (RCC_APB2ENR)*/


#define USART1EN 14
/*RCC_APB1ENR*/
#define RCC_APB1ENR *(((volatile uint32_t * )0x40021000+0x1C))
#define USART2EN 17
#define USART3EN 18
#define USART4EN 19
#define USART5EN 20

#define TXE 7
#define PS 9
#define TC 6
#define ENABLE 1
#define DISABLE 0

#define Num_USART 4



#define TWo_STOPBit 2
#define One_STOPBIT 0
#define Half_STOPBit 1
#define Oneh_STOPBIT 3

#define  Even_Pairty 2
#define  Odd_Parity 1
#define  No_Parity  0



#define EIGHT_Char 0
#define NINE_Char 1




/*
#define USART4_TX  26 //PB10
#define USART4_RX  27 //PB11

#define USART5_TX  22  //PB6 //AFPUSHPULL
#define USART5_RX  23  //PB7 //INPUT FLOATING PUSHPULL
*/

/*CR1*/
#define  Word_Length 12
#define  UE 13
#define PCE 10
#define PS 9
#define TE 3
#define RE 2
#define RXNE 5
/*CR2*/
#define STOP 12



#define RCC_APB2ENR (*((volatile uint32_t *)(0x40021018)))

#define NVIC_BASE   0xE000E100



/* interrupt */
#define USART1_IRQn                  37
#define RXNEIE 5
#define  NVIC_ISER1 (*( (volatile  uint32_t *  ) (NVIC_BASE+0x004)))
#endif /* UART_LOCAL_H_ */

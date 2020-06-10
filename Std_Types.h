#ifndef STD_TYPES_H_INCLUDED
#define STD_TYPES_H_INCLUDED

typedef unsigned char    uint8_t ;
typedef signed   char    sint8_t ;
typedef          char    int8_t  ;

typedef unsigned short   uint16_t;
typedef signed   short   sint16_t;
typedef          short   int16_t ;

typedef unsigned long    uint32_t;
typedef signed   long    sint32_t;
typedef          long    int32_t ;

typedef unsigned char    bool_t  ;

#define RCC_APB2ENR   (*((volatile uint32_t *)(0x40021018)))
#define RCC_APB1ENR   (*((volatile uint32_t *)(0x4002101C)))
	#define PDDS  1   //power down deep sleep
#define CWUP  2   //clear wake up pin
#define EWUP  8   //enable wake up pin

#endif // STD_TYPES_H_INCLUDED


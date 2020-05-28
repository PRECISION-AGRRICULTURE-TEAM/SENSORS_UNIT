#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


#define F_CPU 9000000UL

#define LOGIC1 1
#define LOGIC0 0
#define TRUE 1
#define FALSE 0
#define NULL_STR '\0'
#define INITIAL0 0

///////////////////////////
#define SET_BIT(reg,bitNum) 		(reg|=(LOGIC1<<bitNum))
#define CLEAR_BIT(reg,bitNum) 		(reg&= ~(LOGIC1<<bitNum))
#define TOGGLE_BIT(reg,bitNum) 		((reg)^=(LOGIC1<<bitNum))
#define GET_BIT(reg,bitNum) 		(1&&(reg&(LOGIC1<<bitNum) ))
#define ASSIGN_BIT(reg,bitNum,val) 	(reg =((val==LOGIC1)?reg|(LOGIC1<<bitNum):reg& ~(LOGIC1<<bitNum)))
///////////////////////////////////

#define SET_L_NIB(reg) 			(reg|=(0x0f))
#define CLEAR_L_NIB(reg) 		(reg&=(0xf0))
#define TOGGLE_L_NIB(reg) 		(reg^=(0x0f))
#define GET_L_NIB(reg) 			(reg&(0x0f))
#define ASSIGN_L_NIB(reg,val) 	(reg=((reg&(0xf0))|val))

///////////////////////////////////

#define SET_H_NIB(reg) 			(reg|=(0xf0))
#define CLEAR_H_NIB(reg) 		(reg&=(0x0f))
#define TOGGLE_H_NIB(reg) 		(reg^=(0xf0))
#define GET_H_NIB(reg) 			(reg&(0xf0))
#define ASSIGN_H_NIB(reg,val) 	(reg=((reg&(0x0f))|(val<<4)))

////////////////////////////////////

#define SET_PORT(reg) 			(reg = 0xff)
#define CLEAR_PORT(reg) 		(reg = 0x00)
#define TOGGLE_PORT(reg) 		(~reg )
#define GET_PORT(reg) 			(reg)
#define ASSIGN_PORT(reg,val) 	(reg=val)
#endif // UTILS_H_INCLUDED

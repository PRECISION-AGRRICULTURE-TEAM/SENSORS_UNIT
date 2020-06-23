#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


//#define F_CPU 9000000UL

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





/////////////////////////////////////

#define FREQUENCY                  8000000UL


#define Get_Bit(R,n)                    (            ((R)>>(n))        &1    )
#define Set_Bit(R,n)              (R) = (   (1<<(n))   |(R))
#define Clear_Bit(R,n)            (R) = ( (~(1<<(n)))  &(R))
#define Toggle_Bit(R,n)           (R) = (   (1<<(n))   ^(R))
#define Assign_Bit(R,n,val)       (R) = (((~(1<<(n)))  &(R))|(((val)&1)<<(n)))

#define Get_Low_Nibble(R)               (   (0xf)  &(R)                      )
#define Set_Low_Nibble(R)           R = (   (0xf)  |(R)                      )
#define Toggle_Low_Nibble(R)        R = (   (0xf)  ^(R)                      )
#define Clear_Low_Nibble(R)         R = ( (~(0xf)) &(R)                      )
#define Assign_Low_Nibble(R,val)    R = (((~(0xf)) &(R))    |(val &0xf)      )

#define Get_High_Nibble(R)              (  ((0xf0) &(R))    >>4              )
#define Set_High_Nibble(R)          R = (   (0xf0) |(R)                      )
#define Toggle_High_Nibble(R)       R = (   (0xf0) ^(R)                      )
#define Clear_High_Nibble(R)        R = ( (~(0xf0))&(R)                      )
#define Assign_High_Nibble(R,val)   R = (((~(0xf0))&(R))    |((val<<4) &0xf0))

#define Rot_Left(R,n)               R = ((R<<n)|(R>>((8*sizeof(R))-n+((n/(8*sizeof(R)))*(8*sizeof(R))))))
#define Rot_Right(R,n)              R = ((R>>n)|(R<<((8*sizeof(R))-n+((n/(8*sizeof(R)))*(8*sizeof(R))))))

#define REG_32(BASE,OFFSET) (*((volatile uint32_t *)((BASE) +  (OFFSET))
#define REG_16(BASE,OFFSET) (*((volatile uint16_t *)((BASE) +  (OFFSET))
	/////////////////////////////////////////////////









#endif // UTILS_H_INCLUDED

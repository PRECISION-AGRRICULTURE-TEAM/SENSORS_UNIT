#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define FREQUENCY                  16000000UL


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



#endif // UTILS_H_INCLUDED


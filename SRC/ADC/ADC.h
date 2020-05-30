/** @file ADC.h
 *  @brief This file contains the Prototypes of the ADC Driver
 *  @author 
 */
#ifndef ADC_H_
#define ADC_H_

#include "stm32f10x.h"
#include "GPIO_Driver.h"
#define freq_ADC (RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6)
#define SAMPOS_BIT0 (SAMPOS[u8ADCNum])
#define SAMPOS_BIT1 (SAMPOS[u8ADCNum]+1)
#define SAMPOS_BIT2 (SAMPOS[u8ADCNum]+2)







#define  ADC_PRES_DIV2                ((uint32_t)0x00000000)        /*!< PCLK2 divided by 2 */
#define  ADC_PRES_DIV4                ((uint32_t)0x00004000)        /*!< PCLK2 divided by 4 */
#define  ADC_PRES_DIV6                ((uint32_t)0x00008000)        /*!< PCLK2 divided by 6 */
#define  ADC_PRES_DIV8                ((uint32_t)0x0000C000)        /*!< PCLK2 divided by 8 */








#define ADC_ON  	0x01
#define ADC_CONT 	0x02
#define ADC_CAL 	0x04
#define END_CONV 	0x02
#define ADC_DONE 	0x01



/** @brief  ADC Initialization function
 *
 *
 *  @param 
 *  @return Void
 */
void ADC_vidInit (void);

/** @brief  Read analog value from ADC pin
 *
 *  called once to read from the adc pin 
 *  it uses Busy wait
 *
 *  @param  u8ADCNum the ADC num to read from
 *  @return the analog value on the pin
 */
 
//uint16_t ADC_u16Read(uint8_t u8ADCNum);


/** @brief  Select the ADC pin to be read from
 *  
 *  this function should be called before starting conversion
 *
 *  @param  u8ADCNum the ADC num to select
 *  @return Void
 */ 
void ADC_vidSelect(uint8_t u8ADCNum);

/** @brief  start conversion of the Analog value
 *  
 *  use this function to start conversion on the ADC pin
 *  selected by ADC_vidSelect()
 *
 *  @param 
 *  @return Void
 */ 
void ADC_vidStartConversion();

/** @brief  Check the status of conversion 
 *  
 *  poll  on this function to know if the conversion has ended
 *
 *  @param 
 *  @return status of the conversion
 */ 
uint8_t ADC_u8ConversionStatus();

/** @brief  Read the value of the ADC register
 *  
 *  use this function after you checked that the conversion has ended
 *
 *  @param 
 *  @return ADC Register value
 */ 
uint16_t ADC_u16GetData();





#endif /* ADC_H_ */

/** @file ADC.h
 *  @brief This file contains the Prototypes of the ADC Driver
 *  @author 
 */
#ifndef ADC_H_
#define ADC_H_

#include "ADC_CFG.h"

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
 
uint16_t ADC_u16Read(uint8_t u8ADCNum);


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
 *  @param  u8ADCNum the ADC num to select
 *  @return Void
 */ 
void ADC_vidStartConversion();

/** @brief  Check the status of conversion 
 *  
 *  poll  on this function to know if the conversion has ended
 *
 *  @param  u8ADCNum the ADC num to select
 *  @return Void
 */ 
uint8_t ADC_u8ConversionStatus();

/** @brief  Read the value of the ADC register
 *  
 *  use this function after you checked that the conversion has ended
 *
 *  @param  u8ADCNum the ADC num to select
 *  @return Void
 */ 
uint16_t ADC_u16GetData(void);





#endif /* ADC_H_ */

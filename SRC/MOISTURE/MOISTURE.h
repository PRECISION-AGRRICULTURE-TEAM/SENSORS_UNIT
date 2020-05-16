/** @file MOISTURE.h
 *  @brief This file contains the Prototypes of the MOISTURE Driver
 *  @author  
 */
#ifndef MOISTURE_H_
#define MOISTURE_H_

#include "MOISTURE_CFG.h"


/** @brief  MOISTURE Sensor initialization function.
 *
 *
 *  @param 
 *  @return Void
 */
void MOISTURE_vidInit (void){}

/** @brief  Read analog value from MOISTURE pin.
 *
 *  called once to read from the MOISTURE sensor 
 *  it uses Busy wait.
 *
 *  @param 
 *  @return the analog value on the Sensor
 */ 
uint16_t MOISTURE_u16Read(){}

/** @brief  start reading of the sensor value
 *  
 *
 *  @param 
 *  @return Void
 */ 
void MOISTURE_vidStartReading(){}

/** @brief  Check the status of the reading process
 *  
 *  poll  on this function to know if the reading has ended
 *
 *  @param 
 *  @return the reading status
 */ 
 
uint8_t MOISTURE_u8ReadingStatus(){}

/** @brief  Read the value of the last read sensor value
 *  
 *  use this function after you checked that the conversion has ended
 *
 *  @param  
 *  @return The last read sensor values
 */ 
uint16_t MOISTURE_u16GetData(void){}


#endif /* MOISTURE_H_ */

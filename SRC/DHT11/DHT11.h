/** @file DHT11.h
 *  @brief This file contains the Prototypes of the DHT11 Driver
 *  @author  
 */
#ifndef DHT11_H_
#define DHT11_H_

#include "DHT11_CFG.h"



/** @brief  DHT11 Initialization function.
 *
 *
 *  @param 
 *  @return Void
 */
void DHT11_vidInit (void);

/** @brief  Read analog value from DHT11 pin.
 *
 *  called once to read from the DHT11 sensor 
 *  it uses Busy wait.
 *
 *  @param 
 *  @return the analog value on the pin
 */
 
DHT11_Data_t DHT11_D11Read();


/** @brief  start reading of the sensor values
 *  
 *
 *  @param 
 *  @return Void
 */ 
void DHT11_vidStartReading();

/** @brief  Check the status of the reading process
 *  
 *  poll  on this function to know if the reading has ended
 *
 *  @param 
 *  @return the reading status
 */ 
 
uint8_t DHT11_u8ReadingStatus();

/** @brief  Read the value of the last read sensor values
 *  
 *  use this function after you checked that the conversion has ended
 *
 *  @param  
 *  @return The last read sensor values
 */ 
DHT11_Data_t DHT11_D11GetData(void);

/** @brief  Read the value of the last read temperature value
 *  
 *  use this function after you checked that the conversion has ended
 *
 *  @param  
 *  @return The last read temperature value
 */ 
uint16_t DHT11_u16GetTemp(void);

/** @brief  Read the value of the last read humidity value
 *  
 *  use this function after you checked that the conversion has ended
 *
 *  @param  
 *  @return The last read humidity value
 */ 
uint16_t DHT11_u16GetHumid(void);

#endif /* DHT11_H_ */

/** @file DHT11_CFG.h
 *  @brief This file contains the Constants of the DHT11 Driver
 *  @author  
 */
#ifndef DHT11_CFG_H_
#define DHT11_CFG_H_

/** @brief  A user defined data type that caries the 
 *          senser data.
 */
typedef struct {
/** @brief The relative humidity value */ 
	uint16_t Humidity;
/** @brief The temperature value */ 
	uint16_t Temperature;
/** @brief The CheckSum of the sensor readings */ 
	uint8_t  CheckSum;
/** @brief The validity of the reading */ 
	uint8_t  validity;
} DHT11_Data_t;



#endif /* DHT11_H_ */

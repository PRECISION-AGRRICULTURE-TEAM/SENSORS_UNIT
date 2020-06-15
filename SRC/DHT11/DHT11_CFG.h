/** @file DHT11_CFG.h
 *  @brief This file contains the Constants of the DHT11 Driver
 *  @author  
 */
#ifndef DHT11_CFG_H_
#define DHT11_CFG_H_

/** @brief  A user defined data type that caries the 
 *          senser data.
 */
//integral RH data + 8 bit decimal RH data + 8 bit integral T data+8 bit decimal T data + 8 bit checksum
typedef struct {
/** @brief The relative humidity value */ 
	uint8  Humidity_int;
	uint8  Humidity_float;
/** @brief The temperature value */
	uint8  Temperature_int;
	uint8  Temperature_float;
/** @brief The CheckSum of the sensor readings */
	uint8  CheckSum;
/** @brief The validity of the reading */
	uint8  validity;
} DHT11_Data_t;

#define DHT11_PORT GPIOA
#define DHT11_PIN  PORTD_2



#endif /* DHT11_H_ */

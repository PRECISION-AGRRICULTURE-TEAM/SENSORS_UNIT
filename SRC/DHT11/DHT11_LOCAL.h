/** @file DHT11_LOCAL.h
 *  @brief This file contains the Locals of the DHT11 Driver
 *  @author  
 */

#ifndef DHT11_LOCAL_H_
#define DHT11_LOCAL_H_

#include "../COMMON/Std_Types.h"
#include "../COMMON/Utils.h"
#include "DHT11_CFG.h"
#include "DHT11.h"
#include "../GPIO/DIO.h"
#include "../TIMER/TIMER.h"
typedef enum
{
	DHT11_Init,
	DHT11_Wait,
	DHT11_Request_Start,
	DHT11_Request_Wait,

}DHT11_STATES;

typedef enum{
	DHT11_Request_End,
	DHT11_Response_Start,
	DHT11_Response_End,
	Read_Low,
	Read_High,
	DHT11_EOF

}ExternalStates;

/*typedef enum {
	Read_Low,
	Read_High
}DHT11_READ_STATE_t;*/


#endif /* DHT11_LOCAL_H_ */

/** @file DHT11.c
 *  @brief This file contains the Source Code of the DHT11 Driver
 *  @author  
 */

#include "DHT11_LOCAL.h"

//GPIO_Pin_Conf DHT11_OUT={DHT11_PIN,Output_PushPull,Speed10MHz};
//GPIO_Pin_Conf DHT11_IN={DHT11_PIN,Input_Floating,Speed10MHz};





static uint8 DHT11_State=-1;
static DHT11_Data_t DHT11_Data;
static uint8 ExternalState=0;
static uint8 DHT11_ReadReq =0;
static uint8 DHT11_Data_state = 0;

void DHT11_vidInit (void)
{
	DIO_vidInit();
	DHT11_State=DHT11_Init;
}

void DHT11_vidStartReading()
{
	DHT11_ReadReq =1;
}

DHT11_Data_t DHT11_D11Read()
{
	return  DHT11_Data;
}

void DHT11_Falling()
{
	static uint8 DHT11_u8BitNum = 0;
	static uint8 * DHT11_pu8Data ;
	switch (ExternalState)
	{
	case DHT11_Request_End :
	{

		ExternalState = DHT11_Response_Start;
	}
	break;
	case DHT11_Response_End :
	{
		ExternalState=Read_Low;
	}
	break;
	case Read_High:
	{
		ExternalState = Read_Low;
		DHT11_pu8Data = ((uint8 *) & ( DHT11_Data))+(DHT11_u8BitNum /8);
		if (TIMER_Get_us()<40 )
		{
			// read 0
			Clear_Bit((*DHT11_pu8Data) ,  ((~DHT11_u8BitNum)&7) );
		}
		else
		{
			// read 1
			Set_Bit  ((*DHT11_pu8Data),   ((~DHT11_u8BitNum)&7)   );
		}
		++DHT11_u8BitNum;
		if (DHT11_u8BitNum>39)
		{
			DHT11_u8BitNum =0;
			ExternalState = DHT11_EOF;
		}
	}
	break;

	default:
		break;
	}

}


void DHT11_Rising()
{
	switch (ExternalState)
	{
	case DHT11_Response_Start:
		ExternalState = DHT11_Response_End;
		break;
	case Read_Low:
		ExternalState = Read_High;
		TIMER_Reset();
		break;
	case DHT11_EOF :

		DHT11_Data.validity =
				( DHT11_Data.Humidity_int
						+ DHT11_Data.Humidity_float
						+ DHT11_Data.Temperature_int
						+ DHT11_Data.Temperature_float)== DHT11_Data.CheckSum;


		DHT11_State = DHT11_Wait;
		DHT11_Data_state = 1;
		DIO_vidDisableInt(0);
		DIO_u8SetPinDir(DHT11_PIN,OUTPUT);
		DIO_u8WritePin(DHT11_PIN,1);
		ExternalState = -1;
		break;

	}
}

uint8 adummy = 0 ;
void DHT11_vidMainfunc(void)
{
	static uint32 DHT11Counter=0;
	DHT11Counter ++;

	switch (DHT11_State)
	{

	case DHT11_Init: // takes 80 us on 16Mhz

		DIO_u8SetPinDir(DHT11_PIN,OUTPUT);
		DIO_u8WritePin(DHT11_PIN,1);
		DHT11_State = DHT11_Wait;
		DIO_vidSetCallback_Falling(0,DHT11_Falling);
		DIO_vidSetCallback_Rising(0,DHT11_Rising);

		break;
	case DHT11_Wait :

		if(DHT11_ReadReq)
		{
			DHT11_State = DHT11_Request_Start;
			DHT11_ReadReq =0;

		}
		break;
	case DHT11_Request_Start:

		DHT11_Data_state = 0;
		DIO_u8WritePin(DHT11_PIN,0);
		DHT11_State= DHT11_Request_Wait;
		DHT11Counter=0;
		break;
	case DHT11_Request_Wait:

		if (DHT11Counter>=18)
		{
			DIO_u8SetPinDir(DHT11_PIN,INPUT_PULLUP);
			ExternalState= DHT11_Request_End;
			DHT11_State= -1;
			DHT11Counter= 0;
			DIO_vidEnableInt(0);
		}
		break;

	default:
		break;
	}
}

uint8 DHT11_u8ReadingStatus()
{
	return DHT11_Data_state;
}


/*
DHT11_Data_t DHT11_D11GetData(void)

{

	DATA1.Humidity = ((float)((Integral_RHdata << 8) +  Decimal_RHdata)/(float)10.0);

	DATA1.Temperature = ((float)((Integral_Temp<< 8) + Decimal_Temp)/(float)10.0);

	return DATA1;
}
 */


/*

uint16 DHT11_u16GetTemp(void)
{
	return DHT11_Data.Temperature;
}




uint16 DHT11_u16GetHumid(void)
{
 return DHT11_Data.Humidity;
}



*/

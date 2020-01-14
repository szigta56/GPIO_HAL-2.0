/*
 * plgpio.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#include "plgpio.h"

status_t PL_Gpio_Init (const PL_GPIO_CFG_t *const Config)
{
	status_t ret;
    uint8_t i;
    PL_PORT_REG_t* port;
    volatile uint8_t pin;
    Pl_Channel_num_t channel;
    volatile uint8_t interrupt;
    volatile uint8_t state;
    volatile uint8_t direction;

    for (i=0;i<PL_CONFIG_ELEMENTS;i++)
    {
        port = Config[i].Port;
        pin  = Config[i].Pin;
        interrupt= Config [i].Interrupt;
        state = Config[i].State;
        direction = Config[i].Direction;

		if(ASSERT_PORT(port))
		{
			ret = INCORRECT_PORT_ADDRESS;
			break;
		}
			else
			{
				if(ASSERT_PIN(pin))
				{
					ret = INCORRECT_PIN;
					break;
				}
				else
				{
					
						if(ASSERT_VALUE(state))
						{
							ret = INCORRECT_VALUE;
							break;
						}
						else
						{
							if(ASSERT_PLINTERRUPT(interrupt))
							{
								ret = INCORRECT_INTERRUPT_TYPE;
								break;
							}
							else
							{
								if (ASSERT_DIRECTION(direction))
								{
									ret = INCORRECT_DIRECTION;
									break;
								}
								else
								{
									ret = NO_ERROR;
									channel = PL_Gpio_GetChannel(port);
									port = PL_Gpio_SetAddress(port,channel);
									switch(channel)
									{
									case PL_CH1:

										if(direction == PL_INPUT) port->CH1_TRI_REG |= 1<<pin;
										else 					  port ->CH1_TRI_REG &= ~(1<<pin);

										if(state==PL_PIN_LOW)	  port->CH1_DATA_REG &= ~(1<<pin);
										else					  port->CH1_DATA_REG |= 1<<pin;
										break;

									case PL_CH2:

										if(direction == PL_INPUT) port->CH2_TRI_REG |= 1<<pin;
										else					  port ->CH2_TRI_REG &= ~(1<<pin);

										if(state==PL_PIN_LOW) 	  port->CH2_DATA_REG &= ~(1<<pin);
										else					  port->CH2_DATA_REG |= 1<<pin;
										break;
									}

									switch (interrupt)
									{
										case PL_INTR_NONE:
										PL_Gpio_InterruptDisable(port);
										break;

										case PL_INTR_LEVEL:
										PL_Gpio_GlobalInterruptEnable(port);
										PL_Gpio_InterruptEnable(port);
										break;
									}
								}
							}
						}
					
				}
        	}
    }
	return ret;
}

status_t PL_Gpio_Write(PL_PORT_REG_t *port,  uint8_t pinNum,Pl_Pin_state_t value )
{
	status_t ret;
	Pl_Channel_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
			
					if(ASSERT_VALUE(value)) ret = INCORRECT_VALUE;
					else
					{
						channel = PL_Gpio_GetChannel(port);
						port = PL_Gpio_SetAddress(port,channel);

						ret = NO_ERROR;
						switch(channel)
						{
						case PL_CH1:
							if(value==PL_PIN_HIGH) port->CH1_DATA_REG |= 1<< pinNum;
							else 				   port->CH1_DATA_REG &= ~(1<< pinNum);
							break;
						case PL_CH2:
							if(value==PL_PIN_HIGH) port->CH2_DATA_REG |= 1 << pinNum;
							else 				   port->CH2_DATA_REG &=  ~(1<< pinNum);
							break;

						}
					}
				
			}
		}
	return ret;
}

Pl_Pin_state_t PL_Gpio_Read(PL_PORT_REG_t* port,uint8_t pinNum)
{
	status_t ret;
	Pl_Channel_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
					channel = PL_Gpio_GetChannel(port);
					port = PL_Gpio_SetAddress(port,channel);
					uint32_t tempReg=0;
					uint32_t pinMask = 1<<pinNum;

					switch(channel)
					{
					case PL_CH1:
						tempReg = port->CH1_DATA_REG;
						break;
					case PL_CH2:
						tempReg = port->CH2_DATA_REG;
						break;
					}
					return ((tempReg & pinMask)? PL_PIN_HIGH:PL_PIN_LOW);
				
			}
		}
	return ret;
}

status_t PL_Gpio_SetDirection(PL_PORT_REG_t* port,uint8_t pinNum,Pl_Pin_mode_t direction)
{
	status_t ret;
	Pl_Channel_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
			
					if(ASSERT_DIRECTION(direction)) ret = INCORRECT_DIRECTION;
					else
					{
						channel = PL_Gpio_GetChannel(port);
						port = PL_Gpio_SetAddress(port,channel);
						
						ret = NO_ERROR;
						switch (direction)
						{
							case PL_INPUT:
								if(channel == PL_CH1) 	 port->CH1_TRI_REG |= 1<<pinNum;
								else if(channel==PL_CH2) port ->CH2_TRI_REG |= 1<<pinNum;
							break;
							case PL_OUTPUT:
								if(channel == PL_CH1) 	 port->CH1_TRI_REG &= ~(1<<pinNum);
								else if(channel==PL_CH2) port ->CH2_TRI_REG &= ~(1<<pinNum);
							break;
						}
					}
				
			}
		}
	return ret;
}

status_t PL_Gpio_GlobalInterruptEnable(PL_PORT_REG_t* port)
{
	status_t ret;
	Pl_Channel_num_t channel;
	static uint32_t enableMask = 0x80000000;

	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
	else
	{
		channel = PL_Gpio_GetChannel(port);
		port = PL_Gpio_SetAddress(port,channel);

		ret = NO_ERROR;
		port->GLOBAL_INTR_REG |= enableMask;
	}
	return ret;
}

status_t PL_Gpio_InterruptEnable(PL_PORT_REG_t* port)
{
	status_t ret;
	Pl_Channel_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
	else
	{
			channel = PL_Gpio_GetChannel(port);
			port = PL_Gpio_SetAddress(port,channel);
			ret = NO_ERROR;
			uint32_t enableMask = 0;
			switch(channel)
			{
			case PL_CH1:
				enableMask = 0x01;
				break;
			case PL_CH2:
				enableMask = 0x02;
				break;
			}
			port ->INTR_ENABLE_REG |= enableMask;
		

	}
	return ret;
}
status_t PL_Gpio_InterruptDisable(PL_PORT_REG_t* port)
{
	status_t ret;
	Pl_Channel_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
	else
	{
			channel = PL_Gpio_GetChannel(port);
			port = PL_Gpio_SetAddress(port,channel);
			ret = NO_ERROR;
			uint32_t enableMask = 0;
			switch(channel)
			{
			case PL_CH1:
				enableMask = ~(1<<0);
				break;
			case PL_CH2:
				enableMask = ~(1<<1);
				break;
			}
			port ->INTR_ENABLE_REG &= enableMask;
		
	}
	return ret;
}

status_t PL_Gpio_ClearInterrupt(PL_PORT_REG_t* port)
{
	status_t ret;
	Pl_Channel_num_t channel;
	if(ASSERT_PORT(port)) 
		ret = INCORRECT_PORT_ADDRESS;
	else
	{
			channel = PL_Gpio_GetChannel(port);
			port = PL_Gpio_SetAddress(port,channel);
			ret = NO_ERROR;
			uint32_t clearMask=0;
			switch(channel)
			{
			case PL_CH1:
				clearMask = 0x01;
				break;
			case PL_CH2:
				clearMask = 0x02;
				break;
			}
			port ->INTR_STATUS_REG |= clearMask;
		
	}
	return ret;
}

Pl_Channel_num_t PL_Gpio_GetChannel(PL_PORT_REG_t* port)
{	
	uint8_t digit;
	Pl_Channel_num_t channelNum;
	digit = (uint32_t)port & 0xF;
	if(digit==0x8) 
	{
		channelNum = PL_CH2;
	}
	else channelNum = PL_CH1;
	return channelNum;
}
PL_PORT_REG_t* PL_Gpio_SetAddress(PL_PORT_REG_t* port,Pl_Channel_num_t channel)
{
	uint32_t address = (uint32_t) port;

	if(channel==PL_CH2) address -= 0x08;
	return (PL_PORT_REG_t*) address;

}

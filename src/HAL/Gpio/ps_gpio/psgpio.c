/*
 * psgpio.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#include "psgpio.h"

status_t PS_Gpio_Init(const PS_GPIO_CFG_t *const Config)
{
	status_t ret;
    uint8_t i;
    PS_PORT_REG_t* port;
    volatile uint8_t pinNum;
    Ps_Bank_num_t channel;
    volatile uint8_t interrupt;
    volatile uint8_t state;
    volatile uint8_t direction;

    for (i=0;i<PS_CONFIG_ELEMENTS;i++)
    {
        port = Config[i].Port;
        pinNum  = Config[i].Pin;
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
				if(ASSERT_PIN(pinNum))
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
							if(ASSERT_PSINTERRUPT(interrupt))
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

									channel = PS_Gpio_GetBankNum(pinNum);
									pinNum = PS_Gpio_GetPinNum(pinNum);
									switch(channel)
									{
									case PS_BANK0:

										if(direction == PS_INPUT)
										{

											port->DIR_MODE_0 &= ~(1<<pinNum);
											port->OUT_ENABLE_0 &= ~(1<<pinNum);
										}
										else
										{
											port ->DIR_MODE_0 |= 1<<pinNum;
											port ->OUT_ENABLE_0 |= 1<<pinNum;
										}

										if(state==PS_PIN_LOW)		port->DATA_OUT_0 &= ~(1<<pinNum);
										else						port->DATA_OUT_0 |= 1<<pinNum;
										break;

									case PS_BANK1:

										if(direction == PS_INPUT)
										{

											port->DIR_MODE_1 &= ~(1<<pinNum);
											port->OUT_ENABLE_1 &= ~(1<<pinNum);
										}
										else
										{
											port ->OUT_ENABLE_1 |= 1<<pinNum;
											port ->DIR_MODE_1 |= 1<<pinNum;
										}

										if(state==PS_PIN_LOW)		port->DATA_OUT_1 &= ~(1<<pinNum);
										else 						port->DATA_OUT_1 |= 1<<pinNum;
										break;

									}

									switch (interrupt)
									{
										case PS_INTR_NONE:

										if(channel==PS_BANK1)
										{
											port ->INTR_DISABLE_1 |= 1<<pinNum;

										}
										else if(channel==PS_BANK0)
										{
											port ->INTR_DISABLE_0 |= 1<<pinNum;

										}

										break;

										case PS_INTR_RISING:

										if(channel==PS_BANK1)
										{
											port ->INTR_ENABLE_1 |= 1<<pinNum;
											port ->INTR_TYPE_1	|= 1<<pinNum;
											port ->INTR_POLARITY_1 |= 1<<pinNum;
										}
										else if(channel==PS_BANK0)
										{
											port ->INTR_ENABLE_0 |= 1<<pinNum;
											port ->INTR_TYPE_0	|= 1<<pinNum;
											port ->INTR_POLARITY_0 |= 1<<pinNum;
										}

										break;

										case PS_INTR_FALLING:

										if(channel==PS_BANK1)
										{
											port ->INTR_ENABLE_1 |= 1<<pinNum;
											port ->INTR_TYPE_1	|= 1<<pinNum;
											port ->INTR_POLARITY_1 &= ~(1<<pinNum);
										}
										else if(channel==PS_BANK0)
										{
											port ->INTR_ENABLE_0 |= 1<<pinNum;
											port ->INTR_TYPE_0	|= 1<<pinNum;
											port ->INTR_POLARITY_0 &= ~(1<<pinNum);
										}

										break;

										case PS_INTR_LEVEL:

											if(channel==PS_BANK1)
											{
												port ->INTR_ENABLE_1 |= 1<<pinNum;
												port ->INTR_TYPE_1	&= ~(1<<pinNum);
												port ->INTR_POLARITY_1 |= 1<<pinNum;
											}
											else if(channel==PS_BANK0)
											{
												port ->INTR_ENABLE_0 |= 1<<pinNum;
												port ->INTR_TYPE_0	&= ~(1<<pinNum);
												port ->INTR_POLARITY_0 |= 1<<pinNum;
											}

										break;

										case PS_INTR_BOTH:
											if(channel==PS_BANK1)
											{
												port ->INTR_ENABLE_1 |= 1<<pinNum;
												port ->INTR_TYPE_1	|= 1<<pinNum;
												port ->INTR_BOTH_EDGE_1 |= 1<<pinNum;
											}
											else if(channel==PS_BANK0)
											{
												port ->INTR_ENABLE_0 |= 1<<pinNum;
												port ->INTR_TYPE_0	|= 1<<pinNum;
												port ->INTR_BOTH_EDGE_0 |= 1<<pinNum;
											}

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

status_t PS_Gpio_Write(PS_PORT_REG_t *port, uint8_t pinNum,Ps_Pin_state_t value )
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
			
				
				
					if(ASSERT_VALUE(value)) ret = INCORRECT_VALUE;
					else
					{
						channel = PS_Gpio_GetBankNum( pinNum);
						pinNum = PS_Gpio_GetPinNum(pinNum);
						ret = NO_ERROR;
						switch(channel)
						{
						case PS_BANK0:
							if(value==PS_PIN_HIGH) 			port->DATA_OUT_0 |= 1 << pinNum;
							else 							port->DATA_OUT_0 &= ~(1<< pinNum) ;
						break;
						case PS_BANK1:
							if(value==PS_PIN_HIGH)			port->DATA_OUT_1 |= 1 << pinNum;
							else							port->DATA_OUT_1 &= ~(1 << pinNum);
						break;
						}
					}

				
			}

		}

	return ret;
}

Ps_Pin_state_t PS_Gpio_Read(PS_PORT_REG_t* port,uint8_t pinNum)
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
			
						channel = PS_Gpio_GetBankNum( pinNum);
						pinNum = PS_Gpio_GetPinNum(pinNum);
						uint32_t tempReg=0;
						uint32_t pinMask = 1<<pinNum;

						switch(channel)
						{
						case PS_BANK0:
							tempReg = port->DATA_IN_0;
							break;
						case PS_BANK1:
							tempReg = port->DATA_IN_1;
							break;
						}
						ret = ((tempReg & pinMask)? PS_PIN_HIGH:PS_PIN_LOW);
				
			}
		}
	return ret;
}

status_t PS_Gpio_SetDirection(PS_PORT_REG_t* port,uint8_t pinNum,Ps_Pin_mode_t direction)
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
					if(ASSERT_DIRECTION(direction)) ret = INCORRECT_DIRECTION;
					else
					{
						ret = NO_ERROR;
						channel = PS_Gpio_GetBankNum( pinNum);
						pinNum = PS_Gpio_GetPinNum(pinNum);
						switch(direction)
						{
						case PS_INPUT:

							if(channel == PS_BANK0)
							{
								port->DIR_MODE_0 &= ~(1<<pinNum);
								port->OUT_ENABLE_0 &= ~(1<<pinNum);
							}
							else if(channel == PS_BANK1)
							{
								port ->DIR_MODE_1 &= ~(1<<pinNum);
								port ->OUT_ENABLE_1 &= ~(1<<pinNum);
							}
							break;

						case PS_OUTPUT:

							if(channel == PS_BANK0)
							{
								port->DIR_MODE_0 |= 1<<pinNum;
								port->OUT_ENABLE_0 |= 1<<pinNum;
							}
							else if(channel == PS_BANK1)
							{
								port ->OUT_ENABLE_1 |= 1<<pinNum;
								port ->DIR_MODE_1 |= 1<<pinNum;
							}
							break;
						}

					}

			}

		}

	return ret;
}

status_t PS_Gpio_InterruptEnable(PS_PORT_REG_t* port,uint8_t pinNum)
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
					channel = PS_Gpio_GetBankNum( pinNum);
					pinNum = PS_Gpio_GetPinNum(pinNum);
					ret = NO_ERROR;
					if(channel==PS_BANK1) 		port ->INTR_ENABLE_1 |= 1<<pinNum;
					else if(channel==PS_BANK0) 	port ->INTR_ENABLE_0 |= 1<<pinNum;
	
			}
		}
	return ret;
}

status_t PS_Gpio_InterruptDisable(PS_PORT_REG_t* port,uint8_t pinNum)
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
				
					channel = PS_Gpio_GetBankNum( pinNum);
					pinNum = PS_Gpio_GetPinNum(pinNum);
					ret = NO_ERROR;
					if(channel==PS_BANK1) 		port ->INTR_DISABLE_1 |= 1<<pinNum;
					else if(channel==PS_BANK0) 	port ->INTR_DISABLE_0 |= 1<<pinNum;
				

			}
		}
	return ret;
}

status_t PS_Gpio_SetInterruptType(PS_PORT_REG_t* port,uint8_t pinNum,Ps_Intr_mode_t type)
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
					if(ASSERT_PSINTERRUPT(type)) ret = INCORRECT_INTERRUPT_TYPE;
					else
					{
						ret = NO_ERROR;
						channel = PS_Gpio_GetBankNum( pinNum);
						pinNum = PS_Gpio_GetPinNum(pinNum);
						switch (type)
						{
							case PS_INTR_NONE:

							if(channel==PS_BANK1) 			port ->INTR_DISABLE_1 |= 1<<pinNum;
							else if(channel==PS_BANK0) 		port ->INTR_DISABLE_0 |= 1<<pinNum;
							break;

							case PS_INTR_RISING:

								if(channel==PS_BANK1)
								{
									port ->INTR_ENABLE_1 |= 1<<pinNum;
									port ->INTR_TYPE_1	|= 1<<pinNum;
									port ->INTR_POLARITY_1 |= 1<<pinNum;
									port ->INTR_BOTH_EDGE_1 &= ~(1<<pinNum);
								}
								else if(channel==PS_BANK0)
								{
									port ->INTR_ENABLE_0 |= 1<<pinNum;
									port ->INTR_TYPE_0	|= 1<<pinNum;
									port ->INTR_POLARITY_0 |= 1<<pinNum;
									port ->INTR_BOTH_EDGE_0 &= ~(1<<pinNum);
								}

							break;

							case PS_INTR_FALLING:

								if(channel==PS_BANK1)
								{
									port ->INTR_ENABLE_1 |= 1<<pinNum;
									port ->INTR_TYPE_1	|= 1<<pinNum;
									port ->INTR_POLARITY_1 &= ~(1<<pinNum);
									port ->INTR_BOTH_EDGE_1 &= ~(1<<pinNum);
								}
								else if(channel==PS_BANK0)
								{
									port ->INTR_ENABLE_0 |= 1<<pinNum;
									port ->INTR_TYPE_0	|= 1<<pinNum;
									port ->INTR_POLARITY_0 &= ~(1<<pinNum);
									port ->INTR_BOTH_EDGE_0 &= ~(1<<pinNum);
								}

							break;

							case PS_INTR_LEVEL:

								if(channel==PS_BANK1)
								{
									port ->INTR_ENABLE_1 |= 1<<pinNum;
									port ->INTR_TYPE_1	&= ~(1<<pinNum);
									port ->INTR_POLARITY_1 |= 1<<pinNum;
								}
								else if(channel==PS_BANK0)
								{
									port ->INTR_ENABLE_0 |= 1<<pinNum;
									port ->INTR_TYPE_0	&= ~(1<<pinNum);
									port ->INTR_POLARITY_0 |= 1<<pinNum;
								}

							break;

							case PS_INTR_BOTH:
								if(channel==PS_BANK1)
								{
									port ->INTR_ENABLE_1 |= 1<<pinNum;
									port ->INTR_TYPE_1	|= 1<<pinNum;
									port ->INTR_BOTH_EDGE_1|= 1<<pinNum;
								}
								else if(channel==PS_BANK0)
								{
									port ->INTR_ENABLE_0 |= 1<<pinNum;
									port ->INTR_TYPE_0	|= 1<<pinNum;
									port ->INTR_BOTH_EDGE_0 |= 1<<pinNum;
								}
							break;
						}
					}
			}
		}
	return ret;
}

status_t PS_Gpio_ClearInterrupt(PS_PORT_REG_t* port,uint8_t pinNum)
{
	status_t ret;
	Ps_Bank_num_t channel;
	if(ASSERT_PORT(port)) ret = INCORRECT_PORT_ADDRESS;
		else
		{
			if(ASSERT_PIN(pinNum)) ret = INCORRECT_PIN;
			else
			{
				 channel = PS_Gpio_GetBankNum(pinNum);
				 pinNum = PS_Gpio_GetPinNum(pinNum);
					ret = NO_ERROR;
					switch (channel)
					{
					case PS_BANK0:
						port ->INTR_STATUS_0 |= 1<<pinNum;
					break;
					case PS_BANK1:
						port ->INTR_STATUS_1 |= 1<<pinNum;
					break;
					}
				

			}
		}
	return ret;
}

 Ps_Bank_num_t  PS_Gpio_GetBankNum(uint8_t pinNum)
{
	Ps_Bank_num_t BankNum ;
	if(ASSERT_PIN(pinNum)) BankNum = INCORRECT_PIN;
	if((pinNum >=0) &&  (pinNum<20))
	{
		BankNum = PS_BANK0;
	}
	else if((pinNum > 20) && (pinNum <=31))
	{
		BankNum = PS_BANK1;
	}
	return BankNum;
}

uint8_t PS_Gpio_GetPinNum(uint8_t pinNum)
{
	if((pinNum >=0) &&  (pinNum<20))
	{
		if(pinNum>15) pinNum += 12; 
	}
	else if((pinNum > 20) && (pinNum <=31))
	{
		if(pinNum<28) pinNum -= 21;
		else if((pinNum>=28) && (pinNum<30)) pinNum -=12;
		else if((pinNum>=30) && (pinNum<=31)) pinNum -= 10;
	}	
	return pinNum;

}

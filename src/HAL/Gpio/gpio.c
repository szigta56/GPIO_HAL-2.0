/*
 * gpio.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#include "gpio.h"

static uint32_t volatile *const PS_Ports[]=
{
    (uint32_t *)PS_GPIO
};

static uint32_t volatile *const PL_Ports[]=
{
    (uint32_t*)PL_PORT0,
    (uint32_t*)PL_PORT1,
	(uint32_t*)PL_PORT2

};


status_t Gpio_Init()
{
    status_t errorStatus,ret;

    errorStatus = PS_Gpio_Init(PS_Gpio_GetConfig());
    if(errorStatus) ret = errorStatus;
    else
    {
        errorStatus = PL_Gpio_Init(PL_Gpio_GetConfig());
        if(errorStatus) ret = errorStatus;
        else ret = NO_ERROR;
    }

    return ret;
}

status_t Gpio_Write(void *port, uint8_t pinNum, uint8_t value)
{
    status_t errorStatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
      {
          errorStatus = PL_Gpio_Write(port,pinNum,value);
          ret = errorStatus;
      }
    else if(type==PS_TYPE_GPIO)
    {
         errorStatus = PS_Gpio_Write(port,pinNum,value);
         ret = errorStatus;
    }
    else  ret = INCORRECT_PORT_ADDRESS;

    return ret;
}

uint8_t Gpio_Read(void *port, uint8_t pinNum)
{
    uint8_t ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
        ret = PL_Gpio_Read(port,pinNum);
    }
    else if(type==PS_TYPE_GPIO)
    {
        ret = PS_Gpio_Read(port,pinNum);
    }
    else ret = INCORRECT_PORT_ADDRESS;

    return ret;
}

status_t Gpio_SetDirection(void *port, uint8_t pinNum, uint8_t direction)
{
    status_t errorStatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
        errorStatus = PL_Gpio_SetDirection(port,pinNum,direction);
        ret = errorStatus;
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorStatus = PS_Gpio_SetDirection(port,pinNum,direction);
        ret = errorStatus;
    }
    else  ret = INCORRECT_PORT_ADDRESS;

    return ret;
}

status_t Gpio_InterruptEnable(void *port,uint8_t pinNum)
{
    status_t errorStatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
        errorStatus = PL_Gpio_GlobalInterruptEnable(port);
        if(errorStatus) ret = errorStatus;
        else
        {
           errorStatus =  PL_Gpio_InterruptEnable(port);
           ret = errorStatus;
        }
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorStatus = PS_Gpio_InterruptEnable(port,pinNum);
        ret = errorStatus;
    }
    return ret;
}

status_t Gpio_InterruptDisable(void *port,uint8_t pinNum)
{
    status_t errorStatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
      errorStatus = PL_Gpio_InterruptDisable(port);
      ret = errorStatus;
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorStatus = PS_Gpio_InterruptDisable(port,pinNum);
        ret = errorStatus;
    }
    return ret;
}

status_t Gpio_ClearInterrupt(void *port,uint8_t pinNum)
{
    status_t errorStatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
       errorStatus = PL_Gpio_ClearInterrupt(port);
       ret = errorStatus;
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorStatus = PS_Gpio_ClearInterrupt(port,pinNum);
        ret = errorStatus;
    }
    return ret;
}

status_t Gpio_SetInterruptType(void *port,uint8_t pinNum,Intr_type_t type)
{

    status_t errorStatus,ret;
    Gpio_type_t portType;
    portType = GetPortType(port);

    if(portType==PS_TYPE_GPIO)
    {
       errorStatus = PS_Gpio_SetInterruptType(port,pinNum,type);
       ret = errorStatus;
    }
    else
    {
        if(ASSERT_PSINTERRUPT(type)) ret = INCORRECT_PORT_ADDRESS;
        else if(type==INTR_NONE)
        {
            errorStatus = PL_Gpio_InterruptDisable(port);
            ret = errorStatus ;

        } 
        else
        {
           errorStatus = PL_Gpio_GlobalInterruptEnable(port);
           if(errorStatus) ret = errorStatus;
           else
            {

               errorStatus = PL_Gpio_InterruptEnable(port);
                ret = errorStatus;
            }
        }
    }
    return ret;
}


void Gpio_RegisterWrite(uint32_t Address, uint32_t Value)
{
   uint32_t * const RegisterPointer = (uint32_t *) Address;

   *RegisterPointer = Value;
}

uint32_t Gpio_RegisterRead(uint32_t Address)
{
   uint32_t * const RegisterPointer = (uint32_t *) Address;

   return *RegisterPointer;
}

Gpio_type_t GetPortType(void *port)
{
    uint8_t  i=0;

    for(i=0;i<PS_PORT_NUM;i++)
    {
        if(port==PS_Ports[i]) return PS_TYPE_GPIO;
    }
    for(i=0;i<PL_PORT_NUM;i++)
    {
        if(port==PL_Ports[i]) return PL_TYPE_GPIO;
    }

    return INCORRECT_PORT_ADDRESS;

}

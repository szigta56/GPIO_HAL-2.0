/*
 * mygpio.c
 *
 *  Created on: 2019. szept. 3.
 *      Author: szigta56
 */


#include "mygpio.h"

static uint32_t volatile *const PS_Ports[]=
{
    (uint32_t *)PS_GPIO
};

static uint32_t volatile *const PL_Ports[]=
{
    (uint32_t*)PL_PORT0,
    (uint32_t*)PL_PORT1
};


status_t Gpio_Init()
{
    status_t errorstatus,ret;

    errorstatus = PS_Gpio_Init(PS_Gpio_GetConfig());
    if(errorstatus) ret = errorstatus;
    else 
    {
        errorstatus = PL_Gpio_Init(PL_Gpio_GetConfig());
        if(errorstatus) ret = errorstatus;
        else ret = NO_ERROR;
    }

    return ret;
}

status_t Gpio_Write(void *port,uint8_t channel, uint8_t pinNum, uint8_t value)
{   
    status_t errorstatus_t,ret;
    Gpio_type_t type;
    type = GetPortType(port);
    
    if (type==PL_TYPE_GPIO)   
      { 
          errorstatus_t = PL_Gpio_Write(port,channel,pinNum,value);
          ret = errorstatus_t;
      }
    else if(type==PS_TYPE_GPIO)
    {
         errorstatus_t = PS_Gpio_Write(port,channel,pinNum,value);  
         ret = errorstatus_t;
    }   
    else  ret = INCORRECT_PORT_ADDRESS;

    return ret;
}

uint8_t Gpio_Read(void *port,Channel_num_t channel, uint8_t pinNum)
{
    uint8_t ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
        ret = PL_Gpio_Read(port,channel,pinNum);
    }
    else if(type==PS_TYPE_GPIO)
    {
        ret = PS_Gpio_Read(port,channel,pinNum);
    }
    else ret = INCORRECT_PORT_ADDRESS;

    return ret;
}

status_t Gpio_SetDirection(void *port,Channel_num_t channel, uint8_t pinNum, uint8_t direction)
{
    status_t errorstatus_t,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {
        errorstatus_t = PL_Gpio_SetDirection(port,channel,pinNum,direction);
        ret = errorstatus_t;
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorstatus_t = PS_Gpio_SetDirection(port,channel,pinNum,direction);
        ret = errorstatus_t;
    }
    else  ret = INCORRECT_PORT_ADDRESS;
    
    return ret;
}

status_t Gpio_InterruptEnable(void *port,Channel_num_t channel,uint8_t pinNum)
{
    status_t errorstatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {   
        errorstatus = PL_Gpio_GlobalInterruptEnable(port);
        if(errorstatus) ret = errorstatus;
        else
        {
           errorstatus =  PL_Gpio_InterruptEnable(port,channel);
           ret = errorstatus;
        }
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorstatus = PS_Gpio_InterruptEnable(port,channel,pinNum);
        ret = errorstatus;
    }
    return ret;
}

status_t Gpio_InterruptDisable(void *port,Channel_num_t channel,uint8_t pinNum)
{
    status_t errorstatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {   
      errorstatus = PL_Gpio_InterruptDisable(port,channel);
      ret = errorstatus;
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorstatus = PS_Gpio_InterruptDisable(port,channel,pinNum);
        ret = errorstatus;
    }
    return ret;
}

status_t Gpio_ClearInterrupt(void *port,Channel_num_t channel,uint8_t pinNum)
{
    status_t errorstatus,ret;
    Gpio_type_t type;
    type = GetPortType(port);

    if (type==PL_TYPE_GPIO)
    {   
       errorstatus = PL_Gpio_ClearInterrupt(port,channel);
       ret = errorstatus;
    }
    else if(type==PS_TYPE_GPIO)
    {
        errorstatus = PS_Gpio_ClearInterrupt(port,channel,pinNum);
        ret = errorstatus;
    }    
    return ret;
}

status_t Gpio_SetInterruptType(void *port,Channel_num_t channel,uint8_t pinNum,Intr_type_t type)
{
    
    status_t errorstatus,ret;
    Gpio_type_t portType;
    portType = GetPortType(port);

    if(portType==PS_TYPE_GPIO)
    {
       errorstatus = PS_Gpio_SetInterruptType(port,channel,pinNum,type);
       ret = errorstatus;
    }
    else 
    {
        if(ASSERT_PLINTERRUPT(type)) ret = INCORRECT_PORT_ADDRESS;
        else
        {
           errorstatus = PL_Gpio_GlobalInterruptEnable(port);
           if(errorstatus) ret = errorstatus;
           else
            {   
                
               errorstatus = PL_Gpio_InterruptEnable(port,channel);
                ret = errorstatus;
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

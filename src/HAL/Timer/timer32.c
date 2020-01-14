/*
 * timer32.c
 *
 *  Created on: 2019. nov. 21.
 *      Author: szigta56
 */


#include "timer32.h"

void Timer32_Init(void* timer)
{
    
        PL_Timer_Init(PL_Timer_GetConfig());
        
}
void Timer32_Enable(void* timer)
{
   
        PL_Timer_Enable(timer);
      
}
void Timer32_Disable(void* timer)
{
     
        PL_Timer_Disable(timer);
    
}

void Timer32_SetPeriod(void* timer,uint32_t period)
{
   
        PL_Timer_SetPeriod(timer,period);
      
}

uint32_t Timer32_ReadCounter(void* timer)
{
    uint32_t ret;
  
    ret = PL_Timer_ReadCounter(timer);

    return ret;
}
void Timer32_SetRunMode(void* timer,Timer32_RunMode_t runMode, Timer32_CountMode_t countMode)
{
    
        PL_Timer_SetRunMode(timer,runMode,countMode);
       
}
void Timer32_InterruptEnable(void* timer,Timer32_IntrMode_t interrupt)
{
    
        PL_Timer_InterruptEnable(timer,interrupt);
       
}
void Timer32_InterruptDisable(void* timer,Timer32_IntrMode_t interrupt)
{
    
        PL_Timer_InterruptDisable(timer,interrupt);
       
    
}
uint8_t Timer32_ClearInterrupt(void* timer)
{
    
        PL_Timer_ClearInterrupt(timer);
       
}

void Timer32_RegisterWrite(uint32_t Address, uint32_t Value)
{
    
   uint32_t * const RegisterPointer = (uint32_t *) Address;

   *RegisterPointer = Value;
}
uint32_t Timer32_RegisterRead(uint32_t Address)
{
    uint32_t * const RegisterPointer = (uint32_t *) Address;

   return *RegisterPointer;
}

/*
 * timer32.c
 *
 *  Created on: 2019. nov. 21.
 *      Author: szigta56
 */


#include "timer32.h"

void Timer32_Init(Timer32_num_t timer)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_Init(PL_Timer_GetConfig());
        break;
    default:
        break;
    }
}
void Timer32_Enable(Timer32_num_t timer)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_Enable(TIMER1);
        break;
    default:
        break;
    }
}
void Timer32_Disable(Timer32_num_t timer)
{
     switch (timer)
    {
    case TIMER1:
        PL_Timer_Disable(TIMER1);
        break;
    default:
        break;
    }
}

void Timer32_SetPeriod(Timer32_num_t timer,uint32_t period)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_SetPeriod(TIMER1,period);
        break;
    default:
        break;
    }
}

uint32_t Timer32_ReadCounter(Timer32_num_t timer)
{
    uint32_t ret;
    switch (timer)
    {
    case TIMER1:
       ret = PL_Timer_ReadCounter(TIMER1);
        break;
    default:
        break;
    }

    return ret;
}
void Timer32_SetRunMode(Timer32_num_t timer,Timer32_RunMode_t runMode, Timer32_CountMode_t countMode)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_SetRunMode(TIMER1,runMode,countMode);
        break;
    default:
        break;
    }
}
void Timer32_InterruptEnable(Timer32_num_t timer,Timer32_IntrMode_t interrupt)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_InterruptEnable(TIMER1,interrupt);
        break;
    default:
        break;
    }
}
void Timer32_InterruptDisable(Timer32_num_t timer,Timer32_IntrMode_t interrupt)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_InterruptDisable(TIMER1,interrupt);
        break;
    default:
        break;
    }
}
uint8_t Timer32_ClearInterrupt(Timer32_num_t timer)
{
    switch (timer)
    {
    case TIMER1:
        PL_Timer_ClearInterrupt(TIMER1);
        break;
    default:
        break;
    }
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

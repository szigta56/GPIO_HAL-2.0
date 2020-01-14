/*
 * timer16.c
 *
 *  Created on: 2019. nov. 21.
 *      Author: szigta56
 */

#include "timer16.h"

void Timer16_Init(Timer16_num_t timer)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_Init(PS_Timer_GetConfig());
        break;
    default:
        break;
    }
}
void Timer16_Enable(Timer16_num_t timer)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_Enable(PS_TIMER0);
        break;
    default:
        break;
    }
}
void Timer16_Disable(Timer16_num_t timer)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_Disable(PS_TIMER0);
        break;
    default:
        break;
    }
}
void Timer16_SetPeriod(Timer16_num_t timer,uint16_t period)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_SetPeriod(PS_TIMER0,period);
        break;
    default:
        break;
    }
}

void Timer16_ResetCounter(Timer16_num_t timer,uint16_t newValue)
{

	switch (timer)
	{
	case TIMER0:
		PS_Timer_ResetCounter(PS_TIMER0,newValue);
		break;
	default:
		break;
	}

}

void Timer16_SetPrescaler(Timer16_num_t timer, Timer16_Prescale_t prescale)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_SetPrescaler(PS_TIMER0,prescale);
        break;
    default:
        break;
    }
}
uint16_t Timer16_ReadCounter(Timer16_num_t timer)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_ReadCounter(PS_TIMER0);
        break;
    default:
        break;
    }
}
void Timer16_SetRunMode(Timer16_num_t timer,Timer16_RunMode_t runMode, Timer16_CountMode_t countMode)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_SetRunMode(PS_TIMER0,runMode,countMode);
        break;
    default:
        break;
    }
}
void Timer16_InterruptEnable(Timer16_num_t timer,Timer16_IntrMode_t interrupt)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_InterruptEnable(PS_TIMER0,interrupt);
        break;
    default:
        break;
    }
}

void Timer16_InterruptDisable(Timer16_num_t timer,Timer16_IntrMode_t interrupt)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_InterruptDisable(PS_TIMER0,interrupt);
        break;
    default:
        break;
    }
}

uint8_t Timer16_ClearInterrupt(Timer16_num_t timer)
{
    switch (timer)
    {
    case TIMER0:
        PS_Timer_ClearInterrupt(PS_TIMER0);
        break;
    default:
        break;
    }
}

void Timer16_RegisterWrite(uint32_t Address, uint16_t Value)
{
   uint32_t * const RegisterPointer = (uint32_t *) Address;

   *RegisterPointer = Value;
}

uint16_t Timer16_RegisterRead(uint32_t Address)
{
   uint32_t * const RegisterPointer = (uint32_t *) Address;

   return (uint16_t)*RegisterPointer;
}


/*
 * timer.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#include "pltimer.h"

void PL_Timer_Init (const PL_Timer_Cfg_t *const Config)
{
	int i;
    volatile PL_TCPWM_REG_t  *timer;
    volatile uint8_t operation;
    volatile uint8_t countMode;
    volatile uint8_t runMode;
    volatile uint32_t period;
    volatile uint8_t interrupt;

    for(i=0;i<CONFIG_ELEMENTS;i++)
    {
      timer = Config[i].Timer;
      operation = Config[i].Operation;
      runMode = Config[i].RunMode;
      countMode = Config[i].CountMode;
      period = Config[i].Period;
      interrupt = Config[i].Interrupt;

      timer->CTRL_STATUS_REG0 &= ~1 ;

      switch (runMode)
      {
        case PL_ONE_SHOT:
            timer->CTRL_STATUS_REG0 |= PL_ONE_SHOT<<4;
            break;
        case PL_CONTINUOUS :
            timer->CTRL_STATUS_REG0 |= PL_CONTINUOUS<<4;
        default:
            break;
      }
      switch (countMode)
      {
        case PL_UP_COUNT:
            timer->CTRL_STATUS_REG0 &= ~(1<<1);
            break;
        case PL_DOWN_COUNT:
            timer->CTRL_STATUS_REG0 |= PL_DOWN_COUNT<<1;
            break;
        default:
            break;
      }
        switch (interrupt)
        {
            case PLTIMER_INTR_NONE:
        timer->CTRL_STATUS_REG0 &= ~(1<<6);
        break;
            case PL_TERMINAL_COUNT:
        timer->CTRL_STATUS_REG0 |= (PL_TERMINAL_COUNT<<6);
        break;
    default:
        break;
    }
      timer->LOAD_REG0 = period;

      switch (operation)
            {
              case PL_ENABLED:
                  timer->CTRL_STATUS_REG0 |= PL_ENABLED<<7;
                  break;
              case PL_DISABLED:
                  timer->CTRL_STATUS_REG0 &= ~(1<<7);
                  break;
              default:
                  break;
            }
    }

}

void PL_Timer_Enable(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 |= PL_ENABLED<<7;
}
void PL_Timer_Disable(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 &= ~(1<<7);
}

void PL_Timer_SetPeriod(PL_TCPWM_REG_t *timer,uint32_t period)
{
    timer->LOAD_REG0 = period;
}
 void PL_Timer_ResetCounter(PL_TCPWM_REG_t *timer,uint32_t resetCountVal)
{
    PL_Timer_Disable(timer);
    PL_Timer_SetPeriod(timer,resetCountVal);
    timer->CTRL_STATUS_REG0 |= 1<<5;
    PL_Timer_Enable(timer);
}

uint32_t PL_Timer_ReadCounter(PL_TCPWM_REG_t *timer)
{
    return timer->COUNT_REG0;
}

void PL_Timer_SetRunMode(PL_TCPWM_REG_t *timer, PL_Run_mode_t runMode,PL_Count_mode_t countMode)
{
    switch (runMode)
      {
        case PL_ONE_SHOT:
            timer->CTRL_STATUS_REG0 &= ~(1<<4);
            break;
        case PL_CONTINUOUS :
            timer->CTRL_STATUS_REG0 |= PL_CONTINUOUS<<4;
        default:
            break;
      }

    switch (countMode)
      {
        case PL_UP_COUNT:
            timer->CTRL_STATUS_REG0 &= ~(1<<1);
            break;
        case PL_DOWN_COUNT:
            timer->CTRL_STATUS_REG0 |= PL_DOWN_COUNT<<1;
            break;
      }
}

void PL_Timer_InterruptEnable(PL_TCPWM_REG_t *timer,PL_Intr_mode_t interrupt)
{
    timer->CTRL_STATUS_REG0 |= (PL_TERMINAL_COUNT<<6);
}
void PL_Timer_InterruptDisable(PL_TCPWM_REG_t *timer,PL_Intr_mode_t interrupt)
{
    timer->CTRL_STATUS_REG0 &= ~(PL_TERMINAL_COUNT<<6);
}

void PL_Timer_ClearInterrupt(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 |= 1<<8;
}

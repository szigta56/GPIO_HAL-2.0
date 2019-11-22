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
        case ONE_SHOT:
            timer->CTRL_STATUS_REG0 |= ONE_SHOT<<4;
            break;
        case CONTINUOUS :
            timer->CTRL_STATUS_REG0 |= CONTINUOUS<<4;
        default:
            break;
      }
      switch (countMode)
      {
        case UP_COUNT:
            timer->CTRL_STATUS_REG0 &= ~(1<<1);
            break;
        case DOWN_COUNT:
            timer->CTRL_STATUS_REG0 |= DOWN_COUNT<<1;
            break;
        default:
            break;
      }
        switch (interrupt)
        {
            case NONE:
        timer->CTRL_STATUS_REG0 &= ~(1<<6);
        break;
            case TERMINAL_COUNT:
        timer->CTRL_STATUS_REG0 |= (TERMINAL_COUNT<<6);
        break;
    default:
        break;
    }
      timer->LOAD_REG0 = period;

      switch (operation)
            {
              case ENABLED:
                  timer->CTRL_STATUS_REG0 |= ENABLED<<7;
                  break;
              case DISABLED:
                  timer->CTRL_STATUS_REG0 &= ~(1<<7);
                  break;
              default:
                  break;
            }
    }

}

void PL_Timer_Enable(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 |= ENABLED<<7;
}
void PL_Timer_Disable(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 &= ~(1<<7);
}
void PL_Timer_Stop(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 &= ~(1<<5);
}
void PL_Timer_Start(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 |= (1<<5);
}
void PL_Timer_SetPeriod(PL_TCPWM_REG_t *timer,uint32_t period)
{
    timer->LOAD_REG0 = period;
}

uint32_t PL_Timer_ReadCounter(PL_TCPWM_REG_t *timer)
{
    return timer->COUNT_REG0;
}

void PL_Timer_SetRunMode(PL_TCPWM_REG_t *timer, PL_Run_mode_t runMode,PL_Count_mode_t countMode)
{
    switch (runMode)
      {
        case ONE_SHOT:
            timer->CTRL_STATUS_REG0 &= ~(1<<4);
            break;
        case CONTINUOUS :
            timer->CTRL_STATUS_REG0 |= CONTINUOUS<<4;
        default:
            break;
      }

    switch (countMode)
      {
        case UP_COUNT:
            timer->CTRL_STATUS_REG0 &= ~(1<<1);
            break;
        case DOWN_COUNT:
            timer->CTRL_STATUS_REG0 |= DOWN_COUNT<<1;
            break;
      }
}

void PL_Timer_InterruptEnable(PL_TCPWM_REG_t *timer,PL_Intr_mode_t interrupt)
{
    timer->CTRL_STATUS_REG0 |= (TERMINAL_COUNT<<6);
}
void PL_Timer_InterruptDisable(PL_TCPWM_REG_t *timer,PL_Intr_mode_t interrupt)
{
    timer->CTRL_STATUS_REG0 &= ~(TERMINAL_COUNT<<6);
}

void PL_Timer_ClearInterrupt(PL_TCPWM_REG_t *timer)
{
    timer->CTRL_STATUS_REG0 |= 1<<8;
}

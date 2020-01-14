/*
 * pstimer.c
 *
 *  Created on: 2019. nov. 19.
 *      Author: szigta56
 */
#include "pstimer.h"

void PS_Timer_Init (const PS_Timer_Cfg_t *const Config)
{
	int i;
    volatile PS_TCPWM_REG_t  *timer;
    volatile uint8_t operation;
    volatile uint8_t countMode;
    volatile uint8_t runMode;
    volatile uint16_t period;
    volatile uint16_t compare;
    volatile uint8_t interrupt;
    volatile uint8_t prescale;

    for(i=0;i<CONFIG_ELEMENTS;i++)
    {
      timer = Config[i].Timer;
      operation = Config[i].Operation;
      runMode = Config[i].RunMode;
      countMode = Config[i].CountMode;
      period = Config[i].Period;
      interrupt = Config[i].Interrupt;
      prescale = Config[i].Prescale;
      compare = Config[i].Compare;

      timer->CTRL_REG  |= 1 ;  //Disable Timer 
      timer->CLK_CTRL_REG &= ~(1<<5);  // CPU1x Clock Source

      switch (runMode)
      {
        case PS_OVERFLOW:
            timer->CTRL_REG &= ~(1<<1);
            break;
        case PS_INTERVAL:
            timer->CTRL_REG |= (PS_INTERVAL<<1);
            break;
        default:
            break;
      }
      switch (countMode)
      {
        case PS_UP_COUNT:
            timer->CTRL_REG &= ~(1<<2);
            break;
        case PS_DOWN_COUNT:
            timer->CTRL_REG |= PS_DOWN_COUNT<<2;
            break;
        default:
            break;
      }
        switch (interrupt)
        {

        case PS_INTR_OVERFLOW:
        	timer->INTR_ENABLE_REG &= 0;
            timer->INTR_ENABLE_REG |= 1<<4;
            break;

        case PS_INTR_INTERVAL:
        	timer->INTR_ENABLE_REG &= 0;
            timer->INTR_ENABLE_REG |=1;
            break;

        case PS_INTR_MATCH:
        	timer->INTR_ENABLE_REG &= 0;
        	timer->CTRL_REG |= 1<<3;
        	timer->INTR_ENABLE_REG |= 1<<1;
        	break;
        case PSTIMER_INTR_NONE:
        	timer->INTR_ENABLE_REG &= 0;
            break;
        default:
            break;
        }

    switch (prescale)
    {

    case PS_PRESCALE_1:
        timer->CLK_CTRL_REG &= ~1; // PRESCALING DISABLED
        break;
    case PS_PRESCALE_2:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_3:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_4:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
     case PS_PRESCALE_5:
    	 timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_6:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_7:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_8:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_9:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_10:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_11:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_12:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
     case PS_PRESCALE_13:
    	 timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_14:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_15:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PS_PRESCALE_16:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    default:
        break;
    }
      timer->PERIOD_REG = period;
      timer->MATCH1_REG = compare;
    
    /*  switch (operation)
            {
              case PS_ENABLED:
                  timer->CTRL_REG &= ~1;
                  break;
              case PS_DISABLED:
                  timer->CTRL_REG |= 1;
                  break;
              default:
                  break;
            }
      */
    }

}


void PS_Timer_Enable(PS_TCPWM_REG_t *timer)
{
    timer->CTRL_REG &= ~1;

}
void PS_Timer_Disable(PS_TCPWM_REG_t *timer)
{
    timer->CTRL_REG |= 1;

}
void PS_Timer_SetPeriod(PS_TCPWM_REG_t *timer,uint16_t period)
{
    timer->PERIOD_REG = period;
}

 void PS_Timer_ResetCounter(PS_TCPWM_REG_t *timer,uint16_t newValue)
{

    PS_Timer_SetPeriod(timer,newValue);
    timer->CTRL_REG |= 1<<4;
}


void PS_Timer_SetCompare(PS_TCPWM_REG_t *timer,uint16_t compare)
{
    timer->MATCH1_REG = compare;
}
void PS_Timer_SetPrescaler(PS_TCPWM_REG_t *timer, PS_Prescale_mode_t prescale)
{
    timer->CLK_CTRL_REG |= 1;
    timer->CLK_CTRL_REG &= ~(0x0F<<1);
    timer->CLK_CTRL_REG |= prescale<<1;

}
uint16_t PS_Timer_ReadCounter(PS_TCPWM_REG_t *timer)
{
    return timer->COUNT_REG;
}
void PS_Timer_SetRunMode(PS_TCPWM_REG_t *timer,PS_Run_mode_t runMode, PS_Count_mode_t countMode)
{
    switch (runMode)
      {
        case PS_OVERFLOW:
            timer->CTRL_REG &= ~(1<<1);
            break;
        case PS_INTERVAL:
            timer->CTRL_REG |= (1<<1);
            break;
        default:
            break;
      }
      switch (countMode)
      {
        case PS_UP_COUNT:
            timer->CTRL_REG &= ~(1<<2);
            break;
        case PS_DOWN_COUNT:
            timer->CTRL_REG |= PS_DOWN_COUNT<<2;
            break;
        default:
            break;
      }
}

void PS_Timer_InterruptEnable(PS_TCPWM_REG_t *timer,PS_Intr_mode_t interrupt)
{
    switch (interrupt)
        {
        case PS_INTR_OVERFLOW:
            timer->INTR_ENABLE_REG |= 1<<4;
            break;
        case PS_INTR_MATCH:
            timer->CTRL_REG |= (1<<3);
            timer->INTR_ENABLE_REG |= 1<<1; 
            break;
        case PS_INTR_INTERVAL:
            timer->INTR_ENABLE_REG |=1;
            break;
        case PSTIMER_INTR_NONE:
            timer->INTR_ENABLE_REG = 0;
            break;
        default:
            break;
        }
}
void PS_Timer_InterruptDisable(PS_TCPWM_REG_t *timer,PS_Intr_mode_t interrupt)
{
    switch (interrupt)
        {
        case PS_INTR_OVERFLOW:
            timer->INTR_ENABLE_REG &= ~(1<<4);
            break;
        case PS_INTR_MATCH:
            timer->CTRL_REG &= ~(1<<3);
            timer->INTR_ENABLE_REG &= ~(1<<1); 
            break;
        case PS_INTR_INTERVAL:
            timer->INTR_ENABLE_REG &= ~1;
            break;
        case PSTIMER_INTR_NONE:
            timer->INTR_ENABLE_REG = 0;
            break;
        default:
            break;
        }
}

uint8_t PS_Timer_ClearInterrupt(PS_TCPWM_REG_t *timer)
{
    return (uint8_t)timer->PS_INTR_STATUS_REG;
}

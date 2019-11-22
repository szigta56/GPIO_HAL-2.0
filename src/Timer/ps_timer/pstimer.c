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
        case OVERFLOW:
            timer->CTRL_REG &= ~(1<<1);
            break;
        case INTERVAL :
            timer->CTRL_REG |= (INTERVAL<<1);
            break;
        default:
            break;
      }
      switch (countMode)
      {
        case UP_COUNT:
            timer->CTRL_REG &= ~(1<<2);
            break;
        case DOWN_COUNT:
            timer->CTRL_REG |= DOWN_COUNT<<2;
            break;
        default:
            break;
      }
        switch (interrupt)
        {

        case INTR_OVERFLOW:
        	timer->INTR_ENABLE_REG &= 0;
            timer->INTR_ENABLE_REG |= 1<<4;
            break;

        case INTR_INTERVAL:
        	timer->INTR_ENABLE_REG &= 0;
            timer->INTR_ENABLE_REG |=1;
            break;

        case INTR_MATCH:
        	timer->INTR_ENABLE_REG &= 0;
        	timer->CTRL_REG |= 1<<3;
        	timer->INTR_ENABLE_REG |= 1<<1;
        	break;
        case NONE:
        	timer->INTR_ENABLE_REG &= 0;
            break;
        default:
            break;
        }

    switch (prescale)
    {

    case PRESCALE_1:
        timer->CLK_CTRL_REG &= ~1; // PRESCALING DISABLED
        break;
    case PRESCALE_2:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_3:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_4:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
     case PRESCALE_5:
    	 timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_6:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_7:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_8:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_9:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_10:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_11:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_12:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
     case PRESCALE_13:
    	 timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_14:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_15:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    case PRESCALE_16:
    	timer->CLK_CTRL_REG &= ~(0xF<<1);
        timer->CLK_CTRL_REG |= 1;
        timer->CLK_CTRL_REG |= prescale<<1;
        break;
    default:
        break;
    }
      timer->PERIOD_REG = period;
      timer->MATCH1_REG = compare;
      

      switch (operation)
            {
              case ENABLED:
                  timer->CTRL_REG &= ~1;
                  break;
              case DISABLED:
                  timer->CTRL_REG |= 1;
                  break;
              default:
                  break;
            }
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
        case OVERFLOW:
            timer->CTRL_REG &= ~(1<<1);
            break;
        case INTERVAL :
            timer->CTRL_REG |= (1<<1);
            break;
        default:
            break;
      }
      switch (countMode)
      {
        case UP_COUNT:
            timer->CTRL_REG &= ~(1<<2);
            break;
        case DOWN_COUNT:
            timer->CTRL_REG |= DOWN_COUNT<<2;
            break;
        default:
            break;
      }
}

void PS_Timer_InterruptEnable(PS_TCPWM_REG_t *timer,PS_Intr_mode_t interrupt)
{
    switch (interrupt)
        {
        case INTR_OVERFLOW:
            timer->INTR_ENABLE_REG |= 1<<4;
            break;
        case INTR_MATCH:
            timer->CTRL_REG |= (1<<3);
            timer->INTR_ENABLE_REG |= 1<<1; 
            break;
        case INTR_INTERVAL:
            timer->INTR_ENABLE_REG |=1;
            break;
        case NONE:
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
        case INTR_OVERFLOW:
            timer->INTR_ENABLE_REG &= ~(1<<4);
            break;
        case INTR_MATCH:
            timer->CTRL_REG &= ~(1<<3);
            timer->INTR_ENABLE_REG &= ~(1<<1); 
            break;
        case INTR_INTERVAL:
            timer->INTR_ENABLE_REG &= ~1;
            break;
        case NONE:
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

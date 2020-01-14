/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "timer16.h"
#include "project.h"

 volatile TCPWM_REG_t  *timer;
 volatile TCPWM_SHARED_t *TcpwmShared;
    

 void Timer16_Init (const Timer_Cfg_t *const Config)
 {
    uint8_t i;
   
    volatile uint8_t timerNum;
    volatile uint8_t operation; 
    volatile uint8_t prescale;
    volatile uint8_t countMode;
    volatile uint8_t runMode;
    volatile uint16_t period;
    volatile uint16_t ccValue;
    volatile uint8_t interrupt;
    
    for(i=0;i<CONFIG_ELEMENTS;i++)
    {
      timer = Config[i].Timer;
      operation = Config[i].Operation;
      prescale = Config[i].Prescaling;
      runMode = Config[i].RunMode;
      countMode = Config[i].CountMode;
      period = Config[i].Period;
      ccValue = Config[i].CapCompValue;
      interrupt = Config[i].Interrupt;
     
      timerNum = GetCounterNum(timer);
       

      TcpwmShared->CTRL_CLR_REG |= 1<<timerNum;
      timer->COUNT_CTRL_REG &= ~(TIMER_MODE_MASK<<TIMER_MODE_OFFSET);

      timer->COUNT_PERIOD = period;
      timer->COUNT_CC_REG = ccValue; 

      switch(prescale)
      { 
      case PRESCALE_1:  timer->COUNT_CTRL_REG &= ~(GENERIC_MASK<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_2:  timer->COUNT_CTRL_REG |= (PRESCALE_2<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_4:  timer->COUNT_CTRL_REG |= (PRESCALE_4<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_8:  timer->COUNT_CTRL_REG |= (PRESCALE_8<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_16: timer->COUNT_CTRL_REG |= (PRESCALE_16<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_32: timer->COUNT_CTRL_REG |= (PRESCALE_32<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_64: timer->COUNT_CTRL_REG |= (PRESCALE_64<<TIMER_PRESCALE_OFFSET);
         break;
      case PRESCALE_128:   timer->COUNT_CTRL_REG |= (PRESCALE_128<<TIMER_PRESCALE_OFFSET);
         break;
      default:
         break;
      }

      switch (countMode)
      {
      case UP_COUNT: timer->COUNT_CTRL_REG &= ~(UP_DOWN_MODE_MASK<<UP_DOWN_MODE_OFFSET);
         break;
      case DOWN_COUNT:  timer->COUNT_CTRL_REG |= (DOWN_COUNT<<UP_DOWN_MODE_OFFSET);
         break;
      case UPDOWN_COUNT1:  timer->COUNT_CTRL_REG |= (UPDOWN_COUNT1<<UP_DOWN_MODE_OFFSET);
         break;
      case UPDOWN_COUNT2:  timer->COUNT_CTRL_REG |= (UPDOWN_COUNT2<<UP_DOWN_MODE_OFFSET);
         break;
      default:
         break;
      }

      switch (runMode)
      {
      case ONE_SHOT: timer->COUNT_CTRL_REG |= (ONE_SHOT<<ONE_SHOT_OFFSET);
         break;
      case CONTINUOUS: timer->COUNT_CTRL_REG &= ~(1<<ONE_SHOT_OFFSET);
         break;
      default:
         break;
      }
      switch (interrupt)
      {
      case  TERMINAL_COUNT:   timer->INTR_MASK_REG = TERMINAL_COUNT;
         break;
      case  CC_MATCH:   timer->INTR_MASK_REG = CC_MATCH;
         break;
      default:
         break;
      }

      if(operation==DISABLED) TcpwmShared->CTRL_CLR_REG |= 1<<timerNum;
      if(operation==ENABLED)  TcpwmShared->CTRL_SET_REG |= 1<<timerNum;
     
    }

 }

 void Timer16_Enable(TCPWM_REG_t *timer)
{
   uint8_t timerNum = GetCounterNum(timer);
   
   TcpwmShared->CTRL_SET_REG |= 1<<timerNum;
}

void Timer16_Disable(TCPWM_REG_t *timer)
{
   uint8_t timerNum = GetCounterNum(timer);

   if(timerNum < 8) TcpwmShared = TCPWM0_SHARED;
   else TcpwmShared = TCPWM1_SHARED;   
    
   TcpwmShared->CTRL_CLR_REG |= 1<<timerNum;
}

void Timer16_Stop(TCPWM_REG_t *timer)
{
   uint8_t timerNum = GetCounterNum(timer);
    
   TcpwmShared->STOP_CMD_REG |= 1<<timerNum;
}

void Timer16_Start(TCPWM_REG_t *timer)
{
   uint8_t timerNum = GetCounterNum(timer);

    
   TcpwmShared->START_CMD_REG |= 1<<timerNum;
}

void Timer16_SetPeriod(TCPWM_REG_t *timer,uint16_t period)
{  
   timer->COUNT_PERIOD = period;
}

void Timer16_SetCompare(TCPWM_REG_t *timer,uint16_t compare)
{
   timer->COUNT_CC_REG = compare;
}
void Timer16_ResetCounter(TCPWM_REG_t *timer,uint16_t newPeriodVal)
{    
   
    Timer16_SetPeriod(timer,newPeriodVal);
    uint8_t timerNum = GetCounterNum(timer);
    TcpwmShared->RELOAD_CMD_REG |= 1<<timerNum;
}

uint16_t Timer16_ReadCounter(TCPWM_REG_t *timer)
{
   return timer->COUNT_REG;
}

void Timer16_SetInterruptType(TCPWM_REG_t *timer,Intr_mode_t interrupt)
{ 
   timer->INTR_MASK_REG = interrupt;
}

void Timer16_ClearInterrupt(TCPWM_REG_t *timer)
{
   timer->INTR_REQUEST_REG &= timer->INTR_MASKED_REQUEST_REG ;
}

void Timer16_SetPrescaler(TCPWM_REG_t *timer, Prescaling_mode_t prescale)
{
   timer->COUNT_CTRL_REG |= prescale<<TIMER_PRESCALE_OFFSET;
}

void Timer16_SetRunMode(TCPWM_REG_t *timer, Run_mode_t runMode,Count_mode_t countMode)
{
   if(runMode==ONE_SHOT) timer->COUNT_CTRL_REG |= runMode<<ONE_SHOT_OFFSET;
   else timer->COUNT_CTRL_REG &= ~(1<<ONE_SHOT_OFFSET); 

   switch (countMode)
      {
      case UP_COUNT: timer->COUNT_CTRL_REG &= ~(UP_DOWN_MODE_MASK<<UP_DOWN_MODE_OFFSET);
         break;
      case DOWN_COUNT:  timer->COUNT_CTRL_REG |= (DOWN_COUNT<<UP_DOWN_MODE_OFFSET);
         break;
      case UPDOWN_COUNT1:  timer->COUNT_CTRL_REG |= (UPDOWN_COUNT1<<UP_DOWN_MODE_OFFSET);
         break;
      case UPDOWN_COUNT2:  timer->COUNT_CTRL_REG |= (UPDOWN_COUNT2<<UP_DOWN_MODE_OFFSET);
         break;
      default:
         break;
      }
}

uint8_t GetCounterNum(TCPWM_REG_t *timer)
{
   uint32_t offset;
   uint8_t  timerNum;
  
   offset = (uint32_t)timer-0x40380000;
   if(offset > 0x2C0)
   {
      offset = (uint32_t)timer - 0x40390000;
      timerNum = (offset-0x100)/0x40;
        TcpwmShared = TCPWM1_SHARED;
   } 
   else
   {
       timerNum = (offset-0x100)/0x40;
        TcpwmShared = TCPWM0_SHARED;
   }
   
   return timerNum;
}

/* [] END OF FILE */

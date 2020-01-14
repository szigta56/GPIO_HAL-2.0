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
#ifndef TIMER_H
#define TIMER_H

#include "timer_cfg.h"

#define TIMER_MODE_MASK     7
#define TIMER_MODE_OFFSET   24

#define TIMER_PRESCALE_OFFSET   8

#define GENERIC_MASK 255
#define UP_DOWN_MODE_MASK 3
#define UP_DOWN_MODE_OFFSET 16

#define ONE_SHOT_OFFSET 18


void Timer16_Init (const Timer_Cfg_t *const Config);
void Timer16_Enable(TCPWM_REG_t *timer);
void Timer16_Disable(TCPWM_REG_t *timer);
void Timer16_Stop(TCPWM_REG_t *timer);
void Timer16_Start(TCPWM_REG_t *timer);
void Timer16_SetPeriod(TCPWM_REG_t *timer,uint16_t period);
void Timer16_ResetCounter(TCPWM_REG_t *timer,uint16_t newPeriodVal);
void Timer16_SetCompare(TCPWM_REG_t *timer,uint16_t compare);
uint16_t Timer16_ReadCounter(TCPWM_REG_t *timer);
void Timer16_SetPrescaler(TCPWM_REG_t *timer, Prescaling_mode_t prescale);
void Timer16_SetRunMode(TCPWM_REG_t *timer, Run_mode_t runMode,Count_mode_t countMode);
void Timer16_SetInterruptType(TCPWM_REG_t *timer,Intr_mode_t interrupt);
void Timer16_ClearInterrupt(TCPWM_REG_t *timer);

uint8_t GetCounterNum(TCPWM_REG_t *timer);


#endif


/* [] END OF FILE */

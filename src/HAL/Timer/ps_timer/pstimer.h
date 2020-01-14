/*
 * pstimer.h
 *
 *  Created on: 2019. nov. 19.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_PS_TIMER_PSTIMER_H_
#define SRC_TIMER_PS_TIMER_PSTIMER_H_

#include "pstimer_cfg.h"

void PS_Timer_Init (const PS_Timer_Cfg_t *const Config);

void PS_Timer_Enable(PS_TCPWM_REG_t *timer);
void PS_Timer_Disable(PS_TCPWM_REG_t *timer);
void PS_Timer_SetPeriod(PS_TCPWM_REG_t *timer,uint16_t period);
void PS_Timer_ResetCounter(PS_TCPWM_REG_t *timer,uint16_t resetCountVal);
void PS_Timer_SetCompare(PS_TCPWM_REG_t *timer,uint16_t compare);
void PS_Timer_SetPrescaler(PS_TCPWM_REG_t *timer, PS_Prescale_mode_t prescale);
uint16_t PS_Timer_ReadCounter(PS_TCPWM_REG_t *timer);
void PS_Timer_SetRunMode(PS_TCPWM_REG_t *timer,PS_Run_mode_t runMode, PS_Count_mode_t countMode);
void PS_Timer_InterruptEnable(PS_TCPWM_REG_t *timer,PS_Intr_mode_t interrupt);
void PS_Timer_InterruptDisable(PS_TCPWM_REG_t *timer,PS_Intr_mode_t interrupt);
uint8_t PS_Timer_ClearInterrupt(PS_TCPWM_REG_t *timer);
#endif /* SRC_TIMER_PS_TIMER_PSTIMER_H_ */

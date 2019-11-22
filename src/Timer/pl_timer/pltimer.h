/*
 * timer.h
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_PL_TIMER_TIMER_H_
#define SRC_TIMER_PL_TIMER_TIMER_H_

#include "pltimer_cfg.h"

void PL_Timer_Init (const PL_Timer_Cfg_t *const Config);
void PL_Timer_Enable(PL_TCPWM_REG_t *timer);
void PL_Timer_Disable(PL_TCPWM_REG_t *timer);
void PL_Timer_Stop(PL_TCPWM_REG_t *timer);
void PL_Timer_Start(PL_TCPWM_REG_t *timer);
void PL_Timer_SetPeriod(PL_TCPWM_REG_t *timer,uint32_t period);
uint32_t PL_Timer_ReadCounter(PL_TCPWM_REG_t *timer);
void PL_Timer_SetRunMode(PL_TCPWM_REG_t *timer, PL_Run_mode_t runMode,PL_Count_mode_t countMode);

void PL_Timer_InterruptEnable(PL_TCPWM_REG_t *timer,PL_Intr_mode_t interrupt);
void PL_Timer_InterruptDisable(PL_TCPWM_REG_t *timer,PL_Intr_mode_t interrupt);
void PL_Timer_ClearInterrupt(PL_TCPWM_REG_t *timer);

#endif /* SRC_TIMER_PL_TIMER_TIMER_H_ */

/*
 * timer32.h
 *
 *  Created on: 2019. nov. 21.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_TIMER32_H_
#define SRC_TIMER_TIMER32_H_

#include  "pl_timer/pltimer.h"

typedef enum
{
    TIMER1
}Timer32_num_t;

typedef enum
{
    TIMER1_UP_COUNT,
    TIMER1_DOWN_COUNT
}Timer32_CountMode_t;

typedef enum
{
    TIMER1_ONE_SHOT,
    TIMER1_CONTINUOUS
}Timer32_RunMode_t;

typedef enum
{
    TIMER1_INTR_NONE,
    TIMER1_INTR_INTERVAL
}Timer32_IntrMode_t;

void Timer32_Init(Timer32_num_t timer);
void Timer32_Enable(Timer32_num_t timer);
void Timer32_Disable(Timer32_num_t timer);
void Timer32_SetPeriod(Timer32_num_t timer,uint32_t period);

uint32_t Timer32_ReadCounter(Timer32_num_t timer);
void Timer32_SetRunMode(Timer32_num_t timer,Timer32_RunMode_t runMode, Timer32_CountMode_t countMode);
void Timer32_InterruptEnable(Timer32_num_t timer,Timer32_IntrMode_t interrupt);
void Timer32_InterruptDisable(Timer32_num_t timer,Timer32_IntrMode_t interrupt);
uint8_t Timer32_ClearInterrupt(Timer32_num_t timer);

void Timer32_RegisterWrite(uint32_t Address, uint32_t Value);
uint32_t Timer32_RegisterRead(uint32_t Address);

#endif /* SRC_TIMER_TIMER32_H_ */

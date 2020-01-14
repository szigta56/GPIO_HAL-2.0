/*
 * timer32.h
 *
 *  Created on: 2019. nov. 21.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_TIMER32_H_
#define SRC_TIMER_TIMER32_H_

#include  "pl_timer/pltimer.h"

#define TIMER1 AXI_TIMER

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

void Timer32_Init(void* timer);
void Timer32_Enable(void* timer);
void Timer32_Disable(void* timer);
void Timer32_SetPeriod(void* timer,uint32_t period);
void Timer32_ResetCounter(void* timer, uint32_t countVal);

uint32_t Timer32_ReadCounter(void* timer);
void Timer32_SetRunMode(void* timer,Timer32_RunMode_t runMode, Timer32_CountMode_t countMode);
void Timer32_InterruptEnable(void* timer,Timer32_IntrMode_t interrupt);
void Timer32_InterruptDisable(void* timer,Timer32_IntrMode_t interrupt);
uint8_t Timer32_ClearInterrupt(void* timer);

void Timer32_RegisterWrite(uint32_t Address, uint32_t Value);
uint32_t Timer32_RegisterRead(uint32_t Address);

#endif /* SRC_TIMER_TIMER32_H_ */

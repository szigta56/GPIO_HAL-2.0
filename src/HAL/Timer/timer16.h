/*
 * timer16.h
 *
 *  Created on: 2019. nov. 21.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_TIMER16_H_
#define SRC_TIMER_TIMER16_H_

#include "ps_timer/pstimer.h"


typedef enum 
{
    TIMER0
} Timer16_num_t;

typedef enum
{
    TIMER0_PRESCALE_1,
    TIMER0_PRESCALE_2,
    TIMER0_PRESCALE_3,
    TIMER0_PRESCALE_4,
    TIMER0_PRESCALE_5,
    TIMER0_PRESCALE_6,
    TIMER0_PRESCALE_7,
    TIMER0_PRESCALE_8,
    TIMER0_PRESCALE_9,
    TIMER0_PRESCALE_10,
    TIMER0_PRESCALE_11,
    TIMER0_PRESCALE_12,
    TIMER0_PRESCALE_13,
    TIMER0_PRESCALE_14,
    TIMER0_PRESCALE_15,
    TIMER0_PRESCALE_16,
}Timer16_Prescale_t;

typedef enum
{
   TIMER0_OVERFLOW,
   TIMER0_INTERVAL,
}Timer16_RunMode_t;

typedef enum
{
    TIMER0_INTR_NONE,
    TIMER0_INTR_INTERVAL,
    TIMER0_INTR_OVERFLOW,
    TIMER0_INTR_MATCH
}Timer16_IntrMode_t;

typedef enum
{
    TIMER0_UP_COUNT,
    TIMER0_DOWN_COUNT
}Timer16_CountMode_t;

void Timer16_Init(Timer16_num_t timer);
void Timer16_Enable(Timer16_num_t timer);
void Timer16_Disable(Timer16_num_t timer);
void Timer16_SetPeriod(Timer16_num_t timer,uint16_t period);
void Timer16_ResetCounter(Timer16_num_t timer,uint16_t countVal);

void Timer16_SetPrescaler(Timer16_num_t timer, Timer16_Prescale_t prescale);
uint16_t Timer16_ReadCounter(Timer16_num_t timer);
void Timer16_SetRunMode(Timer16_num_t timer,Timer16_RunMode_t runMode, Timer16_CountMode_t countMode);
void Timer16_InterruptEnable(Timer16_num_t timer,Timer16_IntrMode_t interrupt);
void Timer16_InterruptDisable(Timer16_num_t timer,Timer16_IntrMode_t interrupt);
uint8_t Timer16_ClearInterrupt(Timer16_num_t timer);

void Timer16_RegisterWrite(uint32_t Address, uint16_t Value);
uint16_t Timer16_RegisterRead(uint32_t Address);


#endif /* SRC_TIMER_TIMER16_H_ */

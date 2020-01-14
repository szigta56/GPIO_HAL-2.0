/*
 * pstimer_cfg.h
 *
 *  Created on: 2019. nov. 19.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_PS_TIMER_PSTIMER_CFG_H_
#define SRC_TIMER_PS_TIMER_PSTIMER_CFG_H_

#include "stdint.h"

#define PS_TIMER0 ((PS_TCPWM_REG_t*)0xF8001000)

#define CONFIG_ELEMENTS  1

typedef enum
{
    PS_UP_COUNT,
    PS_DOWN_COUNT
}PS_Count_mode_t;

typedef enum
{
    PS_OVERFLOW,
    PS_INTERVAL
}PS_Run_mode_t;

typedef enum
{
    PS_DISABLED,
    PS_ENABLED
}PS_Operation_mode_t;

typedef enum
{
    PSTIMER_INTR_NONE,
    PS_INTR_INTERVAL,
    PS_INTR_OVERFLOW,
    PS_INTR_MATCH
}PS_Intr_mode_t;

typedef enum
{   
    PS_PRESCALE_2,
    PS_PRESCALE_3,
    PS_PRESCALE_4,
    PS_PRESCALE_5,
    PS_PRESCALE_6,
    PS_PRESCALE_7,
    PS_PRESCALE_8,
    PS_PRESCALE_9,
    PS_PRESCALE_10,
    PS_PRESCALE_11,
    PS_PRESCALE_12,
    PS_PRESCALE_13,
    PS_PRESCALE_14,
    PS_PRESCALE_15,
    PS_PRESCALE_16,
    PS_PRESCALE_1
}PS_Prescale_mode_t;


typedef struct
{
                uint32_t CLK_CTRL_REG;
    uint32_t RESERVED[2];
                uint32_t CTRL_REG;
    uint32_t  RESERVED_1[2];
                uint32_t COUNT_REG;
    uint32_t RESERVED2[2];
                uint32_t PERIOD_REG;
    uint32_t RESERVED3[2];
                uint32_t MATCH1_REG;
    uint32_t RESERVED4[2]; 
                uint32_t MATCH2_REG;
    uint32_t RESERVED5[2];
                uint32_t MATCH3_REG;
    uint32_t RESERVED6[2];
                uint32_t PS_INTR_STATUS_REG;
    uint32_t RESERVED7[2];
                uint32_t INTR_ENABLE_REG;
    uint32_t RESERVED8[2];
                uint32_t EVENT_CTRL_REG;
    uint32_t RESERVED9[2];
                uint32_t EVENT_REG;
    
} PS_TCPWM_REG_t;

typedef struct
{
    PS_TCPWM_REG_t*        Timer;
    PS_Run_mode_t          RunMode;
    PS_Prescale_mode_t     Prescale;
    PS_Operation_mode_t    Operation;
    PS_Count_mode_t        CountMode;
    uint16_t               Period;
    uint16_t               Compare;
    PS_Intr_mode_t         Interrupt;
}PS_Timer_Cfg_t;

const PS_Timer_Cfg_t *const PS_Timer_GetConfig();


#endif /* SRC_TIMER_PS_TIMER_PSTIMER_CFG_H_ */

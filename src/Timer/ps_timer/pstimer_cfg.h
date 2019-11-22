/*
 * pstimer_cfg.h
 *
 *  Created on: 2019. nov. 19.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_PS_TIMER_PSTIMER_CFG_H_
#define SRC_TIMER_PS_TIMER_PSTIMER_CFG_H_

#include "stdint.h"

#define PS_TIMER ((PS_TCPWM_REG_t*)0xF8001000)

#define CONFIG_ELEMENTS  1

typedef enum
{
    UP_COUNT,
    DOWN_COUNT,
    COUNT_MODE_MAX
}PS_Count_mode_t;

typedef enum
{
    OVERFLOW,
    INTERVAL,
    RUN_MODE_MAX
}PS_Run_mode_t;

typedef enum
{
    DISABLED,
    ENABLED
}PS_Operation_mode_t;

typedef enum
{
    NONE,
    INTR_INTERVAL,
    INTR_OVERFLOW,
    INTR_MATCH
}PS_Intr_mode_t;

typedef enum
{   
    PRESCALE_2,
    PRESCALE_3,
    PRESCALE_4,
    PRESCALE_5,
    PRESCALE_6,
    PRESCALE_7,
    PRESCALE_8,
    PRESCALE_9,
    PRESCALE_10,
    PRESCALE_11,
    PRESCALE_12,
    PRESCALE_13,
    PRESCALE_14,
    PRESCALE_15,
    PRESCALE_16,
    PRESCALE_1
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

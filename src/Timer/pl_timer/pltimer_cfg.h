/*
 * timer_cfg.h
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#ifndef SRC_TIMER_PL_TIMER_PLTIMER_CFG_H_
#define SRC_TIMER_PL_TIMER_PLTIMER_CFG_H_

#include "stdint.h"

#define AXI_TIMER     ((PL_TCPWM_REG_t*)0x42800000)

#define CONFIG_ELEMENTS  1

typedef enum
{
    UP_COUNT,
    DOWN_COUNT,
    COUNT_MODE_MAX
}PL_Count_mode_t;

typedef enum
{
    ONE_SHOT,
    CONTINUOUS,
    RUN_MODE_MAX
}PL_Run_mode_t;

typedef enum
{
    DISABLED,
    ENABLED
}PL_Operation_mode_t;

typedef enum
{
    NONE,
    TERMINAL_COUNT
}PL_Intr_mode_t;

typedef struct
{
    uint32_t CTRL_STATUS_REG0;
    uint32_t LOAD_REG0;
    uint32_t COUNT_REG0;
    uint32_t RESERVED[1];
    uint32_t CTRL_STATUS_REG1;
    uint32_t LOAD_REG1;
    uint32_t COUNT_REG1;
} PL_TCPWM_REG_t;

typedef struct
{
    PL_TCPWM_REG_t*        Timer;
    PL_Run_mode_t          RunMode;
    PL_Operation_mode_t    Operation;
    PL_Count_mode_t        CountMode;
    uint32_t               Period;
    PL_Intr_mode_t         Interrupt;
}PL_Timer_Cfg_t;

const PL_Timer_Cfg_t *const PL_Timer_GetConfig();

#endif /* SRC_TIMER_PL_TIMER_PLTIMER_CFG_H_ */

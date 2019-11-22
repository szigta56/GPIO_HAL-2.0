/*
 * timer_cfg.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */


#include "pltimer_cfg.h"

const PL_Timer_Cfg_t PL_TimerConfigTable[]=
{
   { AXI_TIMER, CONTINUOUS, ENABLED, UP_COUNT, 30000000, TERMINAL_COUNT }
};

const PL_Timer_Cfg_t *const PL_Timer_GetConfig()
{
     PL_Timer_Cfg_t *CfgPtr;

    CfgPtr = (PL_Timer_Cfg_t *)&PL_TimerConfigTable;

    return CfgPtr;
}

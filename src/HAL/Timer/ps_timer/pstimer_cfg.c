/*
 * pstimer_cfg.c
 *
 *  Created on: 2019. nov. 19.
 *      Author: szigta56
 */
#include "pstimer_cfg.h"

const PS_Timer_Cfg_t PS_TimerConfigTable[]=
{
   { PS_TIMER0, PS_INTERVAL, PS_PRESCALE_10, PS_ENABLED, PS_UP_COUNT, 50000, 10000, PS_INTR_INTERVAL }
};

const PS_Timer_Cfg_t *const PS_Timer_GetConfig()
{
     PS_Timer_Cfg_t *CfgPtr;

    CfgPtr = (PS_Timer_Cfg_t *)&PS_TimerConfigTable;

    return CfgPtr;
}

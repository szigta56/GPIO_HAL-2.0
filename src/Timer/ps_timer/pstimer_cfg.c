/*
 * pstimer_cfg.c
 *
 *  Created on: 2019. nov. 19.
 *      Author: szigta56
 */
#include "pstimer_cfg.h"

const PS_Timer_Cfg_t PS_TimerConfigTable[]=
{
   { PS_TIMER, OVERFLOW, PRESCALE_10, ENABLED, UP_COUNT, 50000, 10000, INTR_MATCH }
};

const PS_Timer_Cfg_t *const PS_Timer_GetConfig()
{
     PS_Timer_Cfg_t *CfgPtr;

    CfgPtr = (PS_Timer_Cfg_t *)&PS_TimerConfigTable;

    return CfgPtr;
}

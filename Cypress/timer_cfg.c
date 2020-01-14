/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "timer_cfg.h"


const Timer_Cfg_t TimerConfigTable[]=
{
   { TIMER0, CONTINUOUS, ENABLED, PRESCALE_1, UP_COUNT, 20000, 5000, TERMINAL_COUNT }
};


const Timer_Cfg_t *const Timer_GetConfig()
{
     Timer_Cfg_t *CfgPtr;
    
    CfgPtr = (Timer_Cfg_t *)&TimerConfigTable;
    
    return CfgPtr;
}


/* [] END OF FILE */

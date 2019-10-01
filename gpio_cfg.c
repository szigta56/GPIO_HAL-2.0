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

#include "gpio_cfg.h"

const GPIO_CFG_t GpioConfigTable[]=
{
//    Port      Pin     Pin         Initital    Interrupt       Pin drive
//    number    number  direction   state       type            mode

    { PORT6,   PIN3,   OUTPUT,    PIN_LOW,      INTR_NONE,     STRONG_DRIVE   },
    { PORT0,   PIN4,   INPUT,     PIN_HIGH,     INTR_NONE,     HIGH_IMPEDANCE    },
  //  { PORT6,   PIN2,   INPUT,    PIN_HIGH,    INTR_NONE,     RES_PULL_UP   },
    { PORT7,   PIN1,   OUTPUT,     PIN_LOW,     INTR_NONE,     STRONG_DRIVE }
     
};

const GPIO_CFG_t *const Gpio_GetConfig()
{
    GPIO_CFG_t *CfgPtr;
    
    CfgPtr = (GPIO_CFG_t *)&GpioConfigTable;
    
    return CfgPtr;
}

/* [] END OF FILE */

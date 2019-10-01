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
#include <stdint.h>
#include <stdbool.h>
#include "project.h"
#include "mygpio.h"

 const cy_stc_sysint_t Switch_ISR_cfg = {
        .intrSrc = 0,
        .intrPriority = 7
}; 

int main(void)
{
    GPIO_Init (Gpio_GetConfig());
    GPIO_EnableInterrupt(PORT0,PIN4);
    GPIO_SetInterruptType(PORT0,PIN4,INTR_BOTH);
       
    Cy_SysInt_Init(&Switch_ISR_cfg,Switch_ISR);
    NVIC_ClearPendingIRQ(0);
    NVIC_EnableIRQ(0);
    __enable_irq(); /* Enable global interrupts. */
    
    for(;;)
    {
        GPIO_Write(PORT7,PIN1,!GPIO_Read(PORT7,PIN1));
        CyDelay(500);
    }
}

void Switch_ISR(void)
{   
    GPIO_Write(PORT6,PIN3,!GPIO_Read(PORT6,PIN3));
    GPIO_CLearInterrupt(PORT0,PIN4);
    NVIC_ClearPendingIRQ(0);
    CyDelayUs(1);  
}

/* [] END OF FILE */



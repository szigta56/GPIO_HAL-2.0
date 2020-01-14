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
#ifndef TIMER_CFG_H
#define TIMER_CFG_H

#include "stdint.h"

#define TCPWM0_SHARED ((TCPWM_SHARED_t*)0x40380000)
#define TCPWM1_SHARED ((TCPWM_SHARED_t*)0x40390000)
#define TIMER0     ((TCPWM_REG_t*)0x40390140)

#define CONFIG_ELEMENTS  1

typedef enum
{
    UP_COUNT,
    DOWN_COUNT,
    UPDOWN_COUNT1,
    UPDOWN_COUNT2,
    COUNT_MODE_MAX
}Count_mode_t;

typedef enum 
{
    CONTINUOUS,
    ONE_SHOT,
    RUN_MODE_MAX
}Run_mode_t;

typedef enum
{
    PRESCALE_1,
    PRESCALE_2,
    PRESCALE_4,
    PRESCALE_8,
    PRESCALE_16,
    PRESCALE_32,
    PRESCALE_64,
    PRESCALE_128,
    PRESCALE_MODE_MAX
}Prescaling_mode_t;

typedef enum
{
    ENABLED,
    DISABLED
}Operation_mode_t;

typedef enum 
{   
    TERMINAL_COUNT=1,
    CC_MATCH,
    INTR_MODE_MAX
}Intr_mode_t;

typedef struct 
{
  //each field represents a memory mapped register with the individual offsets from the baseaddress                            
    uint32_t COUNT_CTRL_REG;                    
    uint32_t COUNT_STATUS_REG;                      
    uint32_t COUNT_REG;                           
    uint32_t COUNT_CC_REG;                        
    uint32_t COUNT_BUFF_CC_REG; 
    uint32_t COUNT_PERIOD;
    uint32_t COUNT_BUFF_PERIOD_REG;
    uint32_t RESERVED2[1];
    uint32_t COUNT_TRIGG_CTRL0_REG;
    uint32_t COUNT_TRIGG_CTRL1_REG;
    uint32_t COUNT_TRIGG_CTRL2_REG;
    uint32_t RESERVED3[1];
    uint32_t INTR_REQUEST_REG;
    uint32_t INTR_SET_REQUEST_REG;
    uint32_t INTR_MASK_REG;
    uint32_t INTR_MASKED_REQUEST_REG;             
} TCPWM_REG_t;

typedef struct
{
    uint32_t CTRL_REG;                           /*!< 0x00000000 Port output data register */ 
    uint32_t CTRL_CLR_REG;                       /*!< 0x00000004 Port output data set register */
    uint32_t CTRL_SET_REG;                       /*!< 0x00000008 Port output data clear register */
    uint32_t CAPTURE_CMD_REG;                    /*!< 0x0000000C Port output data invert register */
    uint32_t RELOAD_CMD_REG;                     /*!< 0x00000010 Port input state register */
    uint32_t STOP_CMD_REG;                       /*!< 0x00000014 Port interrupt status register */
    uint32_t START_CMD_REG;                     /*!< 0x00000018 Port interrupt mask register */
    uint32_t COUNT_INTR_CAUSE_REG;
}TCPWM_SHARED_t;


typedef struct 
{   
    TCPWM_REG_t*       Timer;
    Run_mode_t          RunMode;
    Operation_mode_t    Operation;
    Prescaling_mode_t   Prescaling;
    Count_mode_t        CountMode;
    uint16_t            Period;
    uint16_t            CapCompValue;
    Intr_mode_t         Interrupt;
}Timer_Cfg_t;

const Timer_Cfg_t *const Timer_GetConfig();

#endif

/* [] END OF FILE */

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
#ifndef GPIO_CFG_H
#define GPIO_CFG_H

#include <stdint.h>

#define  CyDelay                   Cy_SysLib_Delay
#define CONFIG_ELEMENTS  3

// *****************REGISTER OFFSETS FROM GPIO BASEADDRESSES************************

#define PORT6 ((PORT_REG_t*) 0x40320300)
#define PORT7 ((PORT_REG_t*) 0x40320380)
#define PORT0 ((PORT_REG_t*) 0x40320000)

typedef enum
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN_MAX_NUM
}Pin_num_t;

typedef enum
{
    INPUT,
    OUTPUT,
    PIN_MODE_MAX
}Pin_mode_t;

typedef enum
{
    PIN_LOW,
    PIN_HIGH,
    GPIO_PIN_STATE_MAX
}Pin_state_t;

typedef enum
{
    INTR_NONE,
    INTR_RISING,
    INTR_FALLING,
    INTR_BOTH,
    INTR_MODE_MAX
}Intr_mode_t;

typedef enum
{
    HIGH_IMPEDANCE,
    RESERVED,
    RES_PULL_UP,
    RES_PULL_DOWN,
    OPN_DRAIN_LOW,
    OPN_DRAIN_HIGH,
    STRONG_DRIVE,
    RES_PULL_UPDOWN,
    DRIVE_MODE_MAX
}Drive_mode_t;

//*******************STRUCTURE OF REGISTERS*******************************************

typedef struct 
{
  //each field represents a memory mapped register with the individual offsets from the baseaddress
    uint32_t OUT_REG;                           /*!< 0x00000000 Port output data register */ 
    uint32_t OUT_CLR_REG;                       /*!< 0x00000004 Port output data set register */
    uint32_t OUT_SET_REG;                       /*!< 0x00000008 Port output data clear register */
    uint32_t OUT_INV_REG;                       /*!< 0x0000000C Port output data invert register */
    uint32_t IN_STATE_REG;                      /*!< 0x00000010 Port input state register */
    uint32_t INTR_REG;                          /*!< 0x00000014 Port interrupt status register */
    uint32_t INTR_MASK_REG;                     /*!< 0x00000018 Port interrupt mask register */
    uint32_t INTR_MASKED_REG;                   /*!< 0x0000001C Port interrupt masked status register */
    uint32_t INTR_SET_REG;                      /*!< 0x00000020 Port interrupt set register */
    uint32_t INTR_CFG_REG;                      /*!< 0x00000024 Port interrupt configuration register */
    uint32_t CFG_REG;                           /*!< 0x00000028 Port configuration register */
    uint32_t CFG_IN_REG;                        /*!< 0x0000002C Port input buffer configuration register */
    uint32_t CFG_OUT_REG; 
} PORT_REG_t;

typedef struct 
{
    PORT_REG_t*     Port;
    Pin_num_t       Pin;
    Pin_mode_t      Direction;
    Pin_state_t     State;
    Intr_mode_t     Interrupt;
    Drive_mode_t    DriveMode;
} GPIO_CFG_t;

const GPIO_CFG_t *const Gpio_GetConfig(void);

#endif
/* [] END OF FILE */

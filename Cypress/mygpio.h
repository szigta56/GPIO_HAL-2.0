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
#ifndef MYGPIO_H
#define MYGPIO_H

#include <stdint.h>
#include "gpio_cfg.h"
#include "myassert.h"

status_t GPIO_Init (const GPIO_CFG_t *const Config);
status_t GPIO_Write(PORT_REG_t* port, uint8_t pinNum, uint8_t value );
uint8_t GPIO_Read(PORT_REG_t *port, uint8_t pinNum);
status_t GPIO_SetDirection(PORT_REG_t *port,uint8_t pinNum,uint8_t direction);
status_t GPIO_SetDriveMode(PORT_REG_t *port,uint8_t pinNum,Drive_mode_t drive);

status_t GPIO_EnableInterrupt(PORT_REG_t *port,uint8_t pinNum);
status_t GPIO_DisableInterrupt(PORT_REG_t *port,uint8_t pinNum);
status_t GPIO_SetInterruptType(PORT_REG_t *port,uint8_t pinNum,Intr_mode_t type);
status_t GPIO_CLearInterrupt(PORT_REG_t *port,uint8_t pinNum);

void Switch_ISR(void);

#endif

/* [] END OF FILE */

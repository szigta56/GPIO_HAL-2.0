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
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "gpio_cfg.h"
#include "gpio_assert.h"

status_t Gpio_Init (const GPIO_CFG_t *const Config);
status_t Gpio_Write(PORT_REG_t* port, uint8_t pinNum, uint8_t value );
uint8_t Gpio_Read(PORT_REG_t *port, uint8_t pinNum);
status_t Gpio_SetDirection(PORT_REG_t *port,uint8_t pinNum,uint8_t direction);
status_t Gpio_SetDriveMode(PORT_REG_t *port,uint8_t pinNum,Drive_mode_t drive);

status_t Gpio_EnableInterrupt(PORT_REG_t *port,uint8_t pinNum);
status_t Gpio_DisableInterrupt(PORT_REG_t *port,uint8_t pinNum);
status_t Gpio_SetInterruptType(PORT_REG_t *port,uint8_t pinNum,Gpio_Intr_mode_t type);
status_t Gpio_ClearInterrupt(PORT_REG_t *port,uint8_t pinNum);

void Switch_ISR(void);

#endif
/* [] END OF FILE */

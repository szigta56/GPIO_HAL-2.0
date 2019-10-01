/*
 * ps_gpio.h
 *
 *  Created on: 2019. aug. 29.
 *      Author: szigta56
 */


#ifndef SRC_PS_LEVEL_PSGPIO_H_
#define SRC_PS_LEVEL_PSGPIO_H_

#include "../PS_LEVEL/psgpio_cfg.h"
#include "../Zynq_GPIO_HAL/myassert.h"


//*****************************PS_TYPE GPIO APIs***************************************
status_t PS_Gpio_Init(const PS_GPIO_CFG_t *const Config);
status_t PS_Gpio_Write(PS_PORT_REG_t* port,uint8_t channel, uint8_t pinNum, Ps_Pin_state_t value );
Ps_Pin_state_t PS_Gpio_Read(PS_PORT_REG_t* port,uint8_t channel,uint8_t pinNum);
status_t PS_Gpio_SetDirection(PS_PORT_REG_t* port,uint8_t channel,uint8_t pinNum,Ps_Pin_mode_t direction);

status_t PS_Gpio_InterruptEnable(PS_PORT_REG_t* port,uint8_t channel,uint8_t pinNum);
status_t PS_Gpio_SetInterruptType(PS_PORT_REG_t* port,uint8_t channel,uint8_t pinNum,Ps_Intr_mode_t type);
status_t PS_Gpio_InterruptDisable(PS_PORT_REG_t* port,uint8_t channel,uint8_t pinNum);
status_t PS_Gpio_ClearInterrupt(PS_PORT_REG_t* port,uint8_t channel,uint8_t pinNum);

Ps_Pin_num_t  PS_Gpio_GetBankPinNum(uint8_t* channel,uint8_t pinNum);

#endif /* SRC_PS_LED_HAL_PSPS_Gpio_H_ */


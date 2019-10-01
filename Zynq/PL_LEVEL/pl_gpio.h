#ifndef SRC_PL_LEVEL_PL_GPIO_H_
#define SRC_PL_LEVEL_PL_GPIO_H_


#include "../PL_LEVEL/pl_gpio_cfg.h"
#include "../Zynq_GPIO_HAL/myassert.h"



status_t PL_Gpio_Init (const PL_GPIO_CFG_t *const Config);
status_t PL_Gpio_Write(PL_PORT_REG_t* port,uint8_t channel, uint8_t pinNum, Pl_Pin_state_t value );
Pl_Pin_state_t PL_Gpio_Read(PL_PORT_REG_t* port,uint8_t channel,uint8_t pinNum);
status_t PL_Gpio_SetDirection(PL_PORT_REG_t* port,uint8_t channel,uint8_t pinNum,Pl_Pin_mode_t direction);

status_t PL_Gpio_GlobalInterruptEnable(PL_PORT_REG_t* port);
status_t PL_Gpio_InterruptEnable(PL_PORT_REG_t* port, uint8_t channel);
status_t PL_Gpio_InterruptDisable(PL_PORT_REG_t* port, uint8_t channel);
status_t PL_Gpio_ClearInterrupt(PL_PORT_REG_t* port,uint8_t channel);

#endif




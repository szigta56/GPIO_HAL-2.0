/*
 * gpio.h
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#ifndef SRC_GPIO_GPIO_H_
#define SRC_GPIO_GPIO_H_

#include "pl_gpio/plgpio.h"
#include "ps_gpio/psgpio.h"



/*
    PL_RED_LED      on PORT1, Channel : CH2 PinNum: PIN3
    PL_GREEN_LED    on PORT1, Channel : CH1 PinNum: PIN3
    PL_BUTTON       on PORT2, Channel : CH1 PinNum: PIN3

    PS_RED_LED      on PORT0, Channel : CH2 PinNum: PIN1
    PS_GREEN_LED    on PORT0, Channel : CH2 PinNum: PIN2
    PS_BUTTON       on PORT0, Channel : CH1 PinNum: PIN0

*/

#define PS_PORT_NUM  1u
#define PL_PORT_NUM  2u

#define PORT0 PS_GPIO
#define PORT1 PL_PORT0
#define PORT2 PL_PORT1

#define PIN0 PS_PIN0
#define PIN1 PS_PIN20
#define PIN2 PS_PIN21
#define PIN3 PL_PIN0

typedef enum
{
    INPUT,
    OUTPUT
}Dir_mode_t;

typedef enum
{
    PS_TYPE_GPIO,
    PL_TYPE_GPIO
}Gpio_type_t;

typedef enum
{
    CH1,
    CH2
}Channel_num_t;

typedef enum
{
    INTR_NONE,
    INTR_RISING,
    INTR_FALLING,
    INTR_BOTH,
    INTR_LEVEL,
    INTR_MODE_MAX
}Intr_type_t;

status_t Gpio_Init();
status_t Gpio_Write(void *port,Channel_num_t channel, uint8_t pinNum, uint8_t value);
uint8_t  Gpio_Read(void *port,Channel_num_t channel, uint8_t pinNum);
status_t Gpio_SetDirection(void *port,Channel_num_t channel, uint8_t pinNum, Dir_mode_t direction);

status_t Gpio_InterruptEnable(void *port,Channel_num_t channel,uint8_t pinNum);
status_t Gpio_InterruptDisable(void *port,Channel_num_t channel,uint8_t pinNum);
status_t Gpio_ClearInterrupt(void *port,Channel_num_t channel,uint8_t pinNum);
status_t Gpio_SetInterruptType(void *port,Channel_num_t channel,uint8_t pinNum,Intr_type_t type);

void Gpio_RegisterWrite(uint32_t Address, uint32_t Value);
uint32_t Gpio_RegisterRead(uint32_t Address);

Gpio_type_t GetPortType(void *port);

#endif /* SRC_GPIO_GPIO_H_ */

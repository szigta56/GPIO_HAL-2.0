/*
 * psgpio_cfg.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */
#include "psgpio_cfg.h"

const PS_GPIO_CFG_t PS_GpioConfigTable[]=

{
//    Port     Channel 		Pin     Pin         Initital    Interrupt
//    number   number 		number  direction   state       type

	{  PS_GPIO,   	31,   PS_OUTPUT,    PS_PIN_LOW,    	PS_INTR_NONE,     },
    {  PS_GPIO,   	30,   PS_OUTPUT,    PS_PIN_LOW,    	PS_INTR_NONE,     },
    {  PS_GPIO,  	0,    PS_INPUT,     PS_PIN_HIGH,    PS_INTR_RISING,   },

};
//PS l�bak v�ltoztak! 31-30 a LED 0-as a gomb, De ez a MIO l�bak ugye 52-53 �s 0

const PS_GPIO_CFG_t *const PS_Gpio_GetConfig()
{
    PS_GPIO_CFG_t *CfgPtr;

    CfgPtr = (PS_GPIO_CFG_t *)&PS_GpioConfigTable;

    return CfgPtr;
}


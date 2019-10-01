/*
 * main.c
 *
 *  Created on: 2019. szept. 4.
 *      Author: szigta56
 */

#include "xscugic.h"

#include "mygpio.h"

/* 
    PL_RED_LED      on PORT1, Channel : CH2 PinNum: PIN3
    PL_GREEN_LED    on PORT1, Channel : CH1 PinNum: PIN3
    PL_BUTTON       on PORT2, Channel : CH1 PinNum: PIN3 

    PS_RED_LED      on PORT0, Channel : CH2 PinNum: PIN1
    PS_GREEN_LED    on PORT0, Channel : CH2 PinNum: PIN2
    PS_BUTTON       on PORT0, Channel : CH1 PinNum: PIN0

	IRQ numbers:   IRQn 52 for all PS ports, 61 for axi GPIO_1 !!!!!
*/

static XScuGic ScuGic;
static XScuGic_Config *ScuGic_ConfigPointer;

void Button_ISR(void *data);

status_t statusCheck;
int i;
int main ()
{
	statusCheck = Gpio_Init();
	statusCheck = Gpio_SetDirection(PORT0,CH1,PIN0,INPUT);
	//Gpio_Write(PORT0,CH2,PIN1,1);
	Gpio_InterruptEnable(PORT2,CH1,PIN3);
	ScuGic_ConfigPointer = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

	XScuGic_CfgInitialize(&ScuGic,ScuGic_ConfigPointer,XPAR_SCUGIC_0_CPU_BASEADDR);
	XScuGic_Connect(&ScuGic,61,&Button_ISR,PORT2);
	XScuGic_Enable(&ScuGic,61);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,&ScuGic);
	Xil_ExceptionEnable();

	for (;;)
	{	
		for( i=0;i<1000000;i++) Gpio_Write(PORT0,CH2,PIN1,1);
		for( i=0;i<1000000;i++) Gpio_Write(PORT0,CH2,PIN1,0);
	}
	return 0;
}

void Button_ISR(void *data)
{
	Gpio_Write(PORT1,CH1,PIN3,!Gpio_Read(PORT1,CH1,PIN3));
	Gpio_ClearInterrupt(PORT2,CH1,PIN3);
}


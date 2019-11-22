/*
 * main.c
 *
 *  Created on: 2019. nov. 18.
 *      Author: szigta56
 */

#include "xscugic.h"
#include "Gpio/gpio.h"
#include "Timer/ps_timer/pstimer.h"
//#include "Timer/timer16.h"
//#include "Timer/timer32.h"


/*
    PL_RED_LED      on PORT1, Channel : CH2 PinNum: PIN3
    PL_GREEN_LED    on PORT1, Channel : CH1 PinNum: PIN3
    PL_BUTTON       on PORT2, Channel : CH1 PinNum: PIN3

    PS_RED_LED      on PORT0, Channel : CH2 PinNum: PIN1
    PS_GREEN_LED    on PORT0, Channel : CH2 PinNum: PIN2
    PS_BUTTON       on PORT0, Channel : CH1 PinNum: PIN0

	IRQ numbers:   IRQn 52 for all PS ports, 61 for axi GPIO_1 !!
				   IRQn 62 for AXI Timer0 and 42 for PS Timer0(TTC0/Timer0)
*/

static XScuGic ScuGic;
static XScuGic_Config *ScuGic_ConfigPointer;

void Timer_ISR(void *data);

status_t statusCheck;

int main ()
{

	ScuGic_ConfigPointer = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

	XScuGic_CfgInitialize(&ScuGic,ScuGic_ConfigPointer,XPAR_SCUGIC_0_CPU_BASEADDR);
	XScuGic_Connect(&ScuGic,42,&Timer_ISR,PS_TIMER);
	XScuGic_Enable(&ScuGic,42);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,&ScuGic);
	Xil_ExceptionEnable();

	Gpio_Init();
	Gpio_SetDirection(PORT1,CH1,PIN3,OUTPUT);

	PS_Timer_Init(PS_Timer_GetConfig());
	//PS_Timer_InterruptEnable(PS_TIMER,INTR_INTERVAL);


	for (;;)
	{

	}
	return 0;
}

void Timer_ISR(void *data)
{
	Gpio_Write(PORT1,CH1,PIN3,!Gpio_Read(PORT1,CH1,PIN3));

	PS_Timer_ClearInterrupt(PS_TIMER);
}


#include <stdint.h>
#include "../HAL/Timer/timer16.h"
#include "../HAL/Gpio/gpio.h"
#include "xscugic.h"
#include "ped_sig_logic.h"


/*IRQ numbers:   IRQn 52 for all PS ports, 61 for axi GPIO_1 !!
				 IRQn 62 for AXI Timer0 and 42 for PS Timer0(TTC0/Timer0) */


static XScuGic ScuGic;
static XScuGic_Config *ScuGic_ConfigPointer;



#define GREEN_BLINK_CYCLES  (7u)
#define GREEN_CH            (PORT1)
#define GREEN_PIN           (PIN0)
#define RED_CH              (PORT3)
#define RED_PIN             (PIN0)

typedef enum {
  RED,
  GREEN,
  GREENBLINK,
  MAX_SIG_STATES
} signalStates_t;

static void RedLedOn();
static void GreenLedOn();
static void LedsOff();
static void ToggleGreenPin();
static void SignalSetTimer(uint16_t timerPeriod);




void TimerIsrCallback(void);
void ButtonIsrCallback(void);


static signalStates_t currentState = RED;
static signalTransition_t nextTransition = initRed;
static volatile uint8_t stillBlinking = 1;
static volatile uint8_t timerIsrFlag = 0;
static volatile uint8_t stillRed = 0;
static volatile uint8_t buttonFlag = 0;


void StartApp()
{
  RedLedOn();
  SignalSetTimer(RED_LIGHT_INTERVAL);
}

static void RedLedOn()
{
  //#TODO (HW-re még ráhúzzuk)
  Gpio_Write(GREEN_CH, GREEN_PIN, PIN_LOW); 
  Gpio_Write(RED_CH, RED_PIN, PIN_HIGH); 
}

static void GreenLedOn()
{
  //#TODO (HW-re még ráhúzzuk)
  Gpio_Write(RED_CH, RED_PIN, PIN_LOW); 
  Gpio_Write(GREEN_CH, GREEN_PIN, PIN_HIGH); 
}

static void LedsOff()
{
  //#TODO (HW-re még ráhúzzuk)
  Gpio_Write(RED_CH, RED_PIN, PIN_LOW); 
  Gpio_Write(GREEN_CH, GREEN_PIN, PIN_LOW); 
}

static void ToggleGreenPin()
{
  if(Gpio_Read(GREEN_CH, GREEN_PIN))
    LedsOff();
  else
    GreenLedOn();
}

static void SignalSetTimer(uint16_t timerPeriod)
{
  //egy opció, ami futás / cnt mode függő lehet
	Timer16_ResetCounter( TIMER0, timerPeriod);
}

void HWInit()
{
  Gpio_Init();
  Timer16_Init(TIMER0);
  Timer16_SetPrescaler(TIMER0,TIMER0_PRESCALE_13);
  Timer16_Enable(TIMER0);
}

void HWInitIsr()
{
		ScuGic_ConfigPointer = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

		XScuGic_CfgInitialize(&ScuGic,ScuGic_ConfigPointer,XPAR_SCUGIC_0_CPU_BASEADDR);
		XScuGic_Connect(&ScuGic,42,TimerIsrCallback,PS_TIMER0);
		XScuGic_Connect(&ScuGic,52,ButtonIsrCallback,PORT0);

		XScuGic_Enable(&ScuGic,42);
		XScuGic_Enable(&ScuGic,52);


		Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,&ScuGic);
		Xil_ExceptionEnable();
}

uint8_t IsTimerFinished()
{
  uint8_t ret = 0;
  if(timerIsrFlag){
    timerIsrFlag = 0;
    ret = 1;
  }
  return ret;
}

void StartRed()
{
  RedLedOn();
  SignalSetTimer(RED_LIGHT_INTERVAL);
}

void StartGreen()
{
  GreenLedOn();
  SignalSetTimer(GREEN_LIGHT_INTERVAL);
}

void DoGreenBlinky()
{
  static uint8_t remainingCycles = GREEN_BLINK_CYCLES;
  
  if(remainingCycles > 0)
  {
    stillBlinking = 1;
    ToggleGreenPin();
       remainingCycles--;
  }
  else
  {
    stillBlinking = 0;
    remainingCycles = GREEN_BLINK_CYCLES;
  }
  SignalSetTimer(GREEN_BLINK_HALFPERIOD);
}

signalTransition_t ToDoAction()
{
  return nextTransition;
}

void SetWhatTransitionToDoNext()
{
  if(currentState == RED)
  {
	  nextTransition = initGreen;

  }
  else if(currentState == GREEN)
  {
    nextTransition = toggleGreenBlinky;

  }

  else if(currentState == GREENBLINK)
  {
    if(stillBlinking)
      nextTransition = toggleGreenBlinky;
    else
    {
      nextTransition = initRed;

    }
  }
}

void SetCurrentState()
{
  if(nextTransition == initGreen) {currentState = GREEN;}
  else if(nextTransition == toggleGreenBlinky) {currentState = GREENBLINK;}
  else {currentState = RED;}
}

void TimerIsrCallback(void)
{
  Timer16_ClearInterrupt(TIMER0);
  timerIsrFlag = 1;
}

void ButtonIsrCallback(void)
{
	Gpio_ClearInterrupt(PORT0,PIN0);

	uint16_t actualCount = Timer16_ReadCounter(TIMER0);
  if(currentState==RED)
  {
    if(actualCount < (RED_LIGHT_INTERVAL/2))
    	{
    		SetCurrentState();
    		SignalSetTimer(PED_SIGNAL_DELAY);
    	}
  }
	Gpio_Write(PORT0,31,!Gpio_Read(PORT0,31));
}

#include <stdint.h>
#include "timer.h"
#include "gpio.h"
#include "ped_sig_logic.h"

static void RedLedOn();
static void SignalSetTimer(RED_LIGHT_INTERVAL);

void StartSignal()
{
  RedLedOn();
  SignalSetTimer(RED_LIGHT_INTERVAL);
}

static void RedLedOn()
{
  Gpio_Write(PORT0, CH1, PIN0, ON); //ez már tuti, h melyik a HW-en (CHANNEL-t ki lehetne egyszerűsíteni)
}

static void SignalSetTimer(uint16 timerPeriod)
{
  //egy opció, ami futás / cnt mode függő lehet
  Timer16_Disable(TIMER0);
  Timer16_ClearCounter(TIMER0);
  Timer16_SetPeriod(TIMER0, timerPeriod);
  Timer16_Enable(TIMER0);
}



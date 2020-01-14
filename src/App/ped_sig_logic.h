#ifndef PED_SIG_LOGIC_H
#define PED_SIG_LOGIC_H

#define RED_LIGHT_INTERVAL		64278u
#define GREEN_LIGHT_INTERVAL    64278u
#define GREEN_BLINK_HALFPERIOD  7142u
#define PED_SIGNAL_DELAY	  	7142u


typedef enum {
  initRed,
  initGreen,
  toggleGreenBlinky,
  maxSignalStates
} signalTransition_t;

void StartApp();
void HWInit();
void HWInitIsr();
uint8_t IsTimerFinished();
void StartRed();
void StartGreen();
void DoGreenBlinky();
signalTransition_t ToDoAction();
void SetWhatTransitionToDoNext(void);
void SetCurrentState();



#endif

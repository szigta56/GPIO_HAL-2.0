#include <stdint.h>
#include "../HAL/Gpio/gpio.h"
#include "ped_sig_logic.h"


int main(void) 
{


	HWInit();
	HWInitIsr();

	StartApp();


	for(;;)
	{
		if(IsTimerFinished())
		{
			if(ToDoAction() == initRed)
			{	
				StartRed();
				SetCurrentState();
				SetWhatTransitionToDoNext();

			}
			else if (ToDoAction() == initGreen)
			{	
				StartGreen();
				SetCurrentState();
				SetWhatTransitionToDoNext();

			}
			else if (ToDoAction() == toggleGreenBlinky)
			{
				DoGreenBlinky();
				SetCurrentState();
				SetWhatTransitionToDoNext();
		    }

		}
	}

	return 0;
}




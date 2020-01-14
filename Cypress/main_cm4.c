/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
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





 
 


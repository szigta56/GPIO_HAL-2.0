#include <stdint.h>
#include "ped_sig_logic.h"
void Init();
void InitIsr();


int main(void) 
{
  Init();
  InitIsr();
  StartSignal();

  for(;;)
  {
    
  }

  return 0;
}

void Init()
{

}

void InitIsr()
{

}
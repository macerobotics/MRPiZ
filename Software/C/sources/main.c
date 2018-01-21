#include "MRPi1.h"



int main(int argc, char* argv[])
{
unsigned int prox1,prox2,prox3,prox4,prox5;

unsigned int speedFast=50;
unsigned int speedSlow=35;

  // init robot
  init();  

  while(1)
  {
    // lecture des capteurs de proximite
    prox1 = proxSensor(1);
    prox2 = proxSensor(2);
    prox3 = proxSensor(3);
    prox4 = proxSensor(4);
    prox5 = proxSensor(5);

    if( prox1>limit_obs and prox2>limit_obs and prox3>limit_obs and prox4>limit_obs and prox5>limit_obs)
    {
        back(speedSlow);
    }
	else{
		if(prox1>limit_obs and  prox2>limit_obs)
		{
			
		}
  }

  
}
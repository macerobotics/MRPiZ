#include "MRPi1.h"



int main(int argc, char* argv[])
{
unsigned int prox1,prox2,prox3,prox4,prox5,prox6;

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
    prox6 = proxSensor(6);

    if( prox1>limit_obs and prox2>limit_obs and prox3>limit_obs and prox4>limit_obs and prox5>limit_obs and prox6>limit_obs)
    {
        back(speedSlow);
    }
	else{
		if(prox1>limit_obs and  prox2>limit_obs)
		{
			
		}

	}
    elif :
      state = 2
      if (random.randint(0,1) == 1):
        turnRight(speedSlow)
      else:
       back(speedSlow)
    elif prox4>limit_obs or prox5>limit_obs or prox6>limit_obs:
      state = 3
      turnLeft(speedSlow)
    elif prox1>limit_obs or  prox2>limit_obs or  prox3>limit_obs:
      state = 4
      turnRight(speedSlow)
    else:
     r = random.randint(0,10)
     if (r == 0):
       turnLeft(speedSlow)
     elif (r == 3):
        turnRight(speedSlow)
        time.sleep(0.5)
        forward(speedFast)
        time.sleep(0.5)
     elif (r == 4):
        turnLeft(speedSlow)
     else:
      forward(speedFast)
      time.sleep(0.4)
  }

  
}
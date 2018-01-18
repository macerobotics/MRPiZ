#include "MRPi1.h"

int main(int argc, char* argv[])
{
unsigned int prox1, prox2, prox3, prox4, prox5, prox6;

  // init robot
  init();  
  
  while(1)
  {
    // read proximity sensors
    prox1 = proxSensor(1);
    prox2 = proxSensor(2);
    prox3 = proxSensor(3);
    prox4 = proxSensor(4);
    prox5 = proxSensor(5);
    prox6 = proxSensor(6);

    printf("proximity sensor = %d %d %d %d %d %d\n", prox1, prox2, prox3, prox4, prox5, prox6);

    sleep(1);
  }

  
}
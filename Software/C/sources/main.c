#include "MRPiZ.h"


int main(int argc, char* argv[])
{

  // init robot
  init();  
  
  printf("Exemple \n");
  
  forward(25);
  
  sleep(1.5);
  
  firmwareVersion();

  stop();

  
}

#include "MRPi1.h"

int main(int argc, char* argv[])
{

  // init robot
  init();  
  
  controlEnable();
  
  // forward of 150 mm
  forward_mm(10, 150);
  
  // turn 90°
  turnRight_degree(10, 90);

  
}
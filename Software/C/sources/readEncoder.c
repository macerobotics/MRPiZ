#include "MRPi1.h"

int main(int argc, char* argv[])
{
int odo_left, odo_right;


  // init robot
  init();  
  
  while(1)
  {
    // read encoder
    odo_right = encoderRight();
    odo_left = encoderLeft();

    printf("encoder = %d %d\n", odo_right, odo_left);

    sleep(1);
  }

  
}
#include <iostream>
#include "Particle.h"
#include "Manager.h"

// g++ -g -pthread memtest.cpp Manager.cpp Particle.cpp Sthread.cpp -o memtest
int main()
{

  particles::Manager m1;
  m1.initialize(1000, 93);
   

  for(int i=0; i < 100; ++i){
    //m1.sense();
    m1.orient(1);
    m1.move(1);
    //m1.get_positions();
    //m1.get_colors();
    //m1.free_positions();  
 }
  
  
  return 0;
}

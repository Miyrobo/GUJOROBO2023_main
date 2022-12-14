//便利機能等
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Arduino.h"

class TIMER{
  public:
    void reset();
    unsigned long get();
  private:
    unsigned long s_tim;
};


unsigned long TIMER::get(){
  return millis()-s_tim;
}

void TIMER::reset(){
  s_tim=millis();
}


bool anglecheck(int target,int angle,int tolerance){ //目標角度とのずれが指定値以下か
  tolerance = abs(tolerance);
  int diff = abs(angle - target) % 360;
  if(diff > 180)diff-=360;

  if(diff <= tolerance && diff >= -tolerance){
    return true;
  }
  return false;
}


#endif
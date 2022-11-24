//便利機能等
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Arduino.h"

#define BUZZER_PIN 16;   //ブザーのピン

#define length 200

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

class SOUND{
  public:
    void put(unsigned int f, unsigned int d);
    void put(unsigned int frequency);
    void play(unsigned int f, unsigned int d);
    unsigned int freq_now;

    void windowsXP();    //windowsXP起動音
    void tondemowonders();
  private:
    const int _pin = BUZZER_PIN;
    int _Hz[7]={1077,1209,1357,1438,1614,1812,2033};
}buzzer;

void SOUND::put(unsigned int f, unsigned int d){
  tone(_pin,f,d);
}

void SOUND::put(unsigned int f){
  tone(_pin,f);
  freq_now = f;
}

void SOUND::play(unsigned int f, unsigned int d){
  tone(_pin,f,d*0.8);
  delay(d);
}

void SOUND::windowsXP(){
  play(1281,300);  //ミ♭(高)
  play(640,100);    //ミ♭(低)
  play(960,200);   //シ♭
  play(855,200);    //ラ♭
  play(640,200);    //ミ♭(低)
  play(1281,200);  //ミ♭(高)
  play(960,600);   //シ♭
}

void SOUND::tondemowonders(){
  play(_Hz[6]/2,length);
  play(_Hz[4]/2,length/2);
  play(_Hz[4]/2,length/2);
  play(_Hz[6]/2,length);
  play(_Hz[4]/2,length/2);
  play(_Hz[4]/2,length/2);
  play(_Hz[2]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[2],length);
  play(_Hz[1],length*2);
  play(_Hz[6]/2,length/2);
  play(_Hz[5]/2,length/2);
  play(_Hz[4]/2,length);
  play(_Hz[5]/2,length*2);
  play(_Hz[4]/2,length);
  delay(length);
  play(_Hz[1]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[1]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[5]/2,length);
  play(_Hz[6]/2,length);
  play(_Hz[0],length);
  play(_Hz[1],length);
  play(_Hz[6]/2,length);
  play(_Hz[5]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[6]/2,length*4);
  delay(length*2);

  play(_Hz[6]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[6]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[2]/2,length);
  play(_Hz[4]/2,length);
  play(_Hz[2],length);
  play(_Hz[1],length*2);
  play(_Hz[6]/2,length/2);
  play(_Hz[5]/2,length/2);
  play(_Hz[4]/2,length);
  play(_Hz[5]/2,length);
  play(_Hz[5]/2,length);
  play(_Hz[4]/2,length);
  delay(length);
  play(_Hz[6]/2,length);
  play(_Hz[0],length);
  play(_Hz[0],length*2);
  play(_Hz[6]/2,length);
  play(_Hz[0],length);
  play(_Hz[0],length);
  play(_Hz[5]/2,length);
  play(_Hz[2],length*2);
  play(_Hz[1],length);
  play(_Hz[6]/2,length);
  play(_Hz[1],length*2);
  play(_Hz[1],length);
  play(_Hz[2],length*2);

}

#endif
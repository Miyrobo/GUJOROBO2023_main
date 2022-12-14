#include "UI.h"


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
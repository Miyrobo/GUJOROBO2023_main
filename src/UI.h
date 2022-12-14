#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define BUZZER_PIN 16;   //ブザーのピン

#define length 200

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
};



#endif
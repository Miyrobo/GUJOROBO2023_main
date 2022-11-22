#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "Adafruit_BNO055.h"
#include "SPI.h"

#define NUM_balls 16
#define NUM_lines 25

const double SIN16[16] = {0.0,   0.383,  0.707,  0.924,  1.0,    0.924,
                          0.707, 0.383,  0.0,    -0.383, -0.707, -0.924,
                          -1.0,  -0.924, -0.707, -0.383};

class BALL {
 public:
  int value[NUM_balls];
  void get();
  int dir;          //ボールの方向
  double distance;  //ボールまでの距離
  int x, y;

 private:
  int pin[NUM_balls] = {};  //ピン番号
};

class LINE {
 public:
  bool isOnline = 0;  //ライン上か
  bool isHalfout = 0; //半分以上外
  int dir;            //コートの方向
  int x,y;            //位置
  void get_state();         //状態取得
  bool state[NUM_lines];
 private:
  int _pin[NUM_lines]={};
  int _th[NUM_lines];
};

class BNO{
 public:
  double ypr[3];
  void setup();
  void get();
  void reset();
  int dir;

 private:
  int dir0;
};

class CAMERA {
 public:
  int x, y, h, w;
  int color;
  bool canSee;
  void get();
};

#endif
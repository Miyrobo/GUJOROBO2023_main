#ifndef SENSORS_H
#define SENSORS_H

#include "Adafruit_BNO055.h"
#include "Arduino.h"
#include "SPI.h"


#define NUM_balls 16
#define NUM_lines 20

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
  int num;  //見えている数
  bool isExist;   //ボールがあるか
 private:
  int pin[NUM_balls] = {A8,A10,A14,A15,A13,A11,A9,A7,A5,A3,A1,A0,A2,A4,A6};  //ピン番号
  const int _th = 700;      //反応限界
};

class LINE {
 public:
  bool isOnline = 0;   //ライン上か
  bool isHalfout = 0;  //半分以上外
  int dir;             //コートの方向
  int x, y;            //位置
  void get_state();    //状態取得
  bool state[NUM_lines];
  void LEDset(int s);   //LED操作

 private:
  bool _LED = true;
  int _pin[NUM_lines] = {32,34,36,   //前　外側から
                         46,47,48,   //右
                         33,35,37,   //後
                         44,45,49,   //左
                         38,40,50,52,39,41,51,53};  //円部分　前からCW
  int ledpin = 30;                 //LED制御ピン
  int _th[NUM_lines];
};

class BNO {
 public:
  double ypr[3];
  void setup();
  void get();
  void reset();
  int dir;

 private:
  int dir0;
};

class ULTRASONIC{
  public:
    int value[4];
    void getall(); //全部測定
    int get(int n); //1つ測定
  private:
    int echo_pin[4];
    int trig_pin[4];
};

class CAMERA {
 public:
  int x, y, h, w;
  int color;
  bool canSee;
  void get();
};

#endif
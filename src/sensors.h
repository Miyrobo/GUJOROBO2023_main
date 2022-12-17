#ifndef SENSORS_H
#define SENSORS_H

//#define ball_debug

#include "Adafruit_BNO055.h"
#include "Arduino.h"
#include "SPI.h"

#include "Pixy2.h"


#define Pin_sw1 16
#define Pin_sw2 17
#define Pin_sw3 18
#define Pin_sw4 19

#define SW1 !digitalRead(Pin_sw1)
#define SW2 !digitalRead(Pin_sw2)
#define SW3 !digitalRead(Pin_sw3)
#define SW4 !digitalRead(Pin_sw4)


#define NUM_balls 16
#define NUM_lines 22

const int SIN16_1000[16] = {0,   383,  707,  924,  1000,   924,
                          707, 383,  0, -383, -707, -924,
                          -1000, -924, -707, -383};

class BALL {
 public:
  int value[NUM_balls];
  void get();
  int dir;          //ボールの方向
  double distance;  //ボールまでの距離
  int x, y;
  int max;
  int maxn;
  int num;  //見えている数
  bool isExist;   //ボールがあるか
 private:
  const byte pin[NUM_balls] = {A0,A1,A3,A5,A7,A9,A11,A13,A15,A14,A12,A10,A8,A6,A4,A2};  //ピン番号
  //const byte pin[NUM_balls] = {A0,A2,A4,A6,A8,A10,A12,A14,A15,A13,A11,A9,A7,A5,A3,A1};  //ピン番号
  const int _th = 700;      //反応限界
};

class LINE {
 public:
  bool isOnline = 0;   //ライン上か
  bool isHalfout = 0;  //半分以上外
  int dir = 1000;             //コートの方向
  int x, y;            //位置
  void get_state();    //状態取得
  bool state[NUM_lines];
  void LEDset(int s);   //LED操作

  void begin(){
    for(int i=0;i<NUM_lines;i++){
      pinMode(_pin[i],INPUT);
    }
  }

 private:
  bool _LED = true;
  const byte _pin[NUM_lines] = {41,40,39,
                                47,48,49,
                                42,43,44,
                                32,33,34,
                                53,52,37,38,50,51,45,46,35,36};
  // const byte _pin[NUM_lines] = {53,37,39,41,40,38,
  //                               30,47,49,51,50,48,
  //                               31,42,44,46,45,43,
  //                               52,32,34,36,35,33};
  // const byte _pin[NUM_lines] = {{32,34,36,   //前　外側から
  //                               46,47,48,   //右
  //                               33,35,37,   //後
  //                               44,45,49,   //左
  //                               38,40,50,52,39,41,51,53};  //円部分　前からCW}
  const byte x_line[6] = {3,4,5,11,10,9}; //右から左
  const byte y_line[6] = {0,1,2,8,7,6};    //前から後
  const byte angel_line[8] = {12,13,14,15,16,17,18,19}; //円　前からCW
  const byte ledpin = 10;                 //LED制御ピン
  int _th[NUM_lines]; //閾値 デジタルの場合不使用
};

class BNO {
 public:
  double ypr[3];
  void setup();
  void get();
  void reset();
  double dir;

 private:
  double dir0;
};

class ULTRASONIC{
  public:
    int value[4];
    void get_all(); //全部測定
    int get(int n); //1つ測定
  private:
    const byte echo_pin[4]={23,25,27,29};  //前から時計回り
    const byte trig_pin[4]={22,24,26,28};
    unsigned long timeout = 20000;  //タイムアウト (us)
};

class CAMERA {
 public:
  int x, y, h, w;
  int color;
  bool canSee;
  void get();
};

#endif
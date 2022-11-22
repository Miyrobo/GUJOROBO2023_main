#ifndef MOVE_H
#define MOVE_H
#include <Arduino.h>

class MOTOR{
  public:
    int m_speed[4];
    void set_power(int,int,int,int);
    void cal_power(int dir,int speed);
    void stop();
    void pwm_out();
  private:
    const int _pin[8]={};
    const int _angle[4]={-45,45,135,-135};  //モーター取り付け角度
    const float _corr[4]={1,1,1,1};         //回転補正
};

#endif
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
    const int _pin[8]={3,5,8,12,2,6,7,11};
    const int _angle[4]={-45,45,135,-135};  //モーター取り付け角度
    const float _corr[4]={1,-1,-1,1};         //回転補正
};

class MOVE{
  public:
    int dir; //進む方向
    int speed; //スピード
    void carryball(int balldir);
  private:

};

#endif
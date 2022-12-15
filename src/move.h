#ifndef MOVE_H
#define MOVE_H
#include <Arduino.h>

class MOTOR {
 public:
  int m_speed[4];
  void set_power(int, int, int, int);
  void cal_power(int dir, int speed);
  void cal_power(int dir, int speed, int rot);  // 回転を加える
  void stop();
  void pwm_out();

 private:
  const int _pin[8] = {3, 5, 8, 12, 2, 6, 7, 11};
  const int _angle[4] = {-45, 45, 135, -135};  // モーター取り付け角度
  const float _corr[4] = {1, -1, -1, 1};       // 回転補正
};

class MOVE {
 public:
  int dir;    // 進む方向
  int speed;  // スピード
  int rot;    // 回転速度
  void carryball(int balldir);

 private:
};

class PID{
 public:
  int run(double a);  // 姿勢制御
 private:
  float Kp = 1.0, Ki = 1.0, Kd = 1.0;  // 比例制御係数
  double b; //前回の値
  double da;  //変化量
  double v; //時間変化率
  double stack = 0.0;  //積分量
  unsigned long t0, t1, dt;  //[us]
};

#endif
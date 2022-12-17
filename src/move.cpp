#include "move.h"

void MOTOR::cal_power(int dir, int speed) {
  for (int i = 0; i < 4; i++) {
    m_speed[i] = (int)(sin((dir - _angle[i]) / 57.3) * speed);
  }
}

void MOTOR::cal_power(int dir, int speed, int rot) {
  for (int i = 0; i < 4; i++) {
    m_speed[i] = (int)(sin((dir - _angle[i]) / 57.3) * speed) + rot;
  }
}

void MOTOR::stop() {
  for (int i = 0; i < 4; i++) {
    m_speed[i] = 0;
  }
}

void MOTOR::pwm_out() {
  int pwm;
  for (int i = 0; i < 4; i++) {
    pwm = m_speed[i] * _corr[i] * 2.55;
    if (pwm > 0) {
      if (pwm > 255) pwm = 255;
      analogWrite(_pin[i * 2], 1);
      analogWrite(_pin[i * 2 + 1], pwm);
    } else {
      pwm = -pwm;
      if (pwm > 255) pwm = 255;
      analogWrite(_pin[i * 2], pwm);
      analogWrite(_pin[i * 2 + 1], 1);
    }
  }
}

void MOTOR::set_power(int m1, int m2, int m3, int m4) {
  m_speed[0] = m1;
  m_speed[1] = m2;
  m_speed[2] = m3;
  m_speed[3] = m4;
}


void MOVE::carryball(int balldir){
  if(balldir <= 15 && balldir >= -15){
    this->dir = 0;
  }else{
    int a;
    if(balldir <= 30 && balldir >= -30){
      a=20;
      this->speed = 40;
    }else if(balldir <= 60 && balldir >= -60){
      a=30;
    }else{
      a=50;
    }
    if(balldir > 0){
      this->dir = balldir + a;
    }else{
      this->dir = balldir - a;
    }
  }
}


int PID::run(double a){
  t1 = micros();
  dt = t1 - t0;
  t0 = t1;
  da = a-b;
  b = a;  //前回の値
  v = da / (double)dt * 1000;
  stack += a * (double)dt / 1000;
  if(stack > 100)stack=100;
  else if(stack < -100)stack=-100;
  return -(Kp * a + Ki * stack + Kd * v);
}

void kicker(bool out){
  digitalWrite(9,out);
}
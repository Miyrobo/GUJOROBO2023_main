#include "move.h"

void MOTOR::cal_power(int dir, int speed) {
  for (int i = 0; i < 4; i++) {
    m_speed[i] = sin((dir - _angle[i]) / 57.3) * speed;
  }
}

void MOTOR::cal_power(int dir, int speed, int rot) {
  for (int i = 0; i < 4; i++) {
    m_speed[i] = sin((dir - _angle[i]) / 57.3) * speed + rot;
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
  if(balldir <= 5 && balldir >= -5){
    this->dir = 0;
  }else{
    this->dir = balldir * 1.5;
  }
}


int PID::run(double a){
  t1 = micros();
  dt = t1 - t0;
  t0 = t1;
  da = a-b;
  v = da / (double)dt;
  stack += a * (double)dt;
}
#include "sensors.h"

// HardwareSerial Serial_arduino(Serial2);   //サブマイコン用のUARTの番号

Adafruit_BNO055 bno055 = Adafruit_BNO055(-1, 0x28);

void BALL::get() {  //ボールの位置取得
  x = 0;
  y = 0;
  num=0;
  for (int i = 0; i < NUM_balls; i++) {
    int v=analogRead(pin[i]);
    if(v < _th){
      value[i]=_th-v;
      num++;
    }else{
      value[i]=0;
    }
    x += SIN16[i] * value[i];
    y += SIN16[(i + 4) % 16] * value[i];
  }
  dir = atan2(x, y) * 57.3;
  distance = sqrt(x * x + y * y);
  if(num>1){
    isExist=true;
  }else{
    isExist=false;
  }
}

void BNO::setup() {
  bno055.begin();
  bno055.getTemp();
  bno055.setExtCrystalUse(true);
  reset();
}

void BNO::get() {
  imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
  ypr[0] = euler.x();
  ypr[1] = euler.y();
  ypr[2] = euler.z();
  dir = ypr[0] - dir0;
  dir %= 360;
  if (dir > 180)
    dir -= 360;
  else if (dir < -179)
    dir += 360;
}

void BNO::reset() {  //攻め方向リセット
  this->get();
  dir0 = ypr[0];
}


void LINE::get_state() {
  for (int i = 0; i < NUM_lines; i++) {
    if (analogRead(_pin[i] > _th[i])) {
      state[i] = true;
    } else {
      state[i] = false;
    }
  }
}


void LINE::LEDset(int s = -1){  //ラインのLED操作
  if(s==-1){
    s=this->_LED;
  }
  digitalWrite(ledpin,s);
}
#include "sensors.h"

// HardwareSerial Serial_arduino(Serial2);   //サブマイコン用のUARTの番号

Adafruit_BNO055 bno055 = Adafruit_BNO055(-1, 0x28);
Pixy2 pixy;

void BALL::get() {  // ボールの位置取得
  x = 0;
  y = 0;
  num = 0;
  max = 0;
  maxn = -1;
  for (int i = 0; i < NUM_balls; i++) {
    int v = analogRead(pin[i]);
    if (v < _th) {
      value[i] = _th - v;
      num++;
      if (value[i] > max) {
        max = value[i];
        maxn = i;
      }
    } else {
      value[i] = 0;
    }
    x = x + (SIN16_1000[i] * ((double)value[i] / 1000.0));
    y = y + (SIN16_1000[(i + 4) % 16] * ((double)value[i] / 1000.0));
  }

  //dir = atan2(x,y) * 57.3;
  distance = sqrt(x * x + y * y);
  if (num > 1) {
    isExist = true;
    x=0;y=0;
    for(int i=maxn+15;i<=maxn+17;i++){
      x+=(SIN16_1000[i%16] * ((double)value[i%16] / 1000.0));
      y+=(SIN16_1000[(i + 4) % 16] * ((double)value[i%16] / 1000.0));
    }
    dir = atan2(x,y) * 57.3;
  } else {
    isExist = false;
    dir=1000;
    distance = 1000;
  }

  // if (maxn >= 0) {
  //   dir = maxn * 360 / NUM_balls;
  //   if(dir > 180)dir-=360;
  // } else {
  //   dir = 1000;
  // }

#ifdef ball_debug
if(Serial.read()=='B'){
  Serial.print('B');
  for (int i = 0; i < NUM_balls; i++) {
    Serial.print(value[i] / 4);
    Serial.print(',');
  }
  Serial.print(dir);
  Serial.print(',');
  Serial.print((int)distance);
  Serial.print(',');
  Serial.print('\n');
  // Serial.println("");
  // Serial.print("  ");
  // Serial.print(x);
  // Serial.print("  ");
  // Serial.println(y);
}
#endif
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
  if (dir > 180)
    dir -= 360;
  else if (dir < -179)
    dir += 360;
}

void BNO::reset() {  // 攻め方向リセット
  this->get();
  dir0 = ypr[0];
}

void LINE::get_state() {
  for (int i = 0; i < NUM_lines; i++) {
    state[i]=digitalRead(_pin[i]);
  }
}

void LINE::LEDset(int s = -1) {  // ラインのLED操作
  if (s == -1) {
    s = this->_LED;
  }
  digitalWrite(ledpin, s);
}

int ULTRASONIC::get(int n) {
  // ピンをOUTPUTに設定（パルス送信のため）
  pinMode(trig_pin[n], OUTPUT);
  // LOWパルスを送信
  digitalWrite(trig_pin[n], LOW);
  delayMicroseconds(2);
  // HIGHパルスを送信
  digitalWrite(trig_pin[n], HIGH);
  // 5uSパルスを送信してPingSensorを起動
  delayMicroseconds(5);
  digitalWrite(trig_pin[n], LOW);

  // 入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
  pinMode(echo_pin[n], INPUT);

  // 入力パルスの長さを測定
  int duration = pulseIn(echo_pin[n], HIGH,timeout);  //応答がなかったら0

  // パルスの長さを半分に分割
  duration = duration / 2;
  // cmに変換
  value[n] = int(duration / 29);
  return value[n];
}

void ULTRASONIC::get_all() {
  for(int i=0;i<4;i++){
    get(i);
  }
}
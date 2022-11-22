#include "sensors.h"

// HardwareSerial Serial_arduino(Serial2);   //サブマイコン用のUARTの番号

Adafruit_BNO055 bno055 = Adafruit_BNO055(-1, 0x28);
MPU6050 mpu;
static uint8_t mpuIntStatus;
static bool dmpReady = false;  // set true if DMP init was successful
static uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)

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

void MPU::setup() {
  mpu.initialize();
  if (mpu.testConnection() != true) {
    Serial.println("MPU disconnection");
    while (true) {
    }
  }
  if (mpu.dmpInitialize() != 0) {
    Serial.println("MPU break");
    while (true) {
    }
  }
  mpu.setXGyroOffset(Gyro_X);
  mpu.setYGyroOffset(Gyro_Y);
  mpu.setZGyroOffset(Gyro_Z);
  mpu.setZAccelOffset(Accel_Z);
  mpu.setDMPEnabled(true);
  mpuIntStatus = mpu.getIntStatus();
  dmpReady = true;
  packetSize = mpu.dmpGetFIFOPacketSize();
}

void MPU::get() {
  mpuIntStatus = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
  } else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    dir = degrees(ypr[0]);
  }
}

void MPU::reset() {
  this->get();
  dir0 = dir;
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
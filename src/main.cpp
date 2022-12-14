#include "Arduino.h"

#include "functions.h"
#include "move.h"
#include "sensors.h"
#include "UI.h"

BNO bno;
BALL ball;
MOTOR motor;
TIMER timer;
SOUND buzzer;
Adafruit_SSD1306 display(128, 64, &Wire, -1);


void setup() {
  bno.setup();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //ディスプレイ初期化処理
  Serial.begin(9600);
  Serial2.begin(9600);

  buzzer.windowsXP();
  // pinMode(10, OUTPUT);
  // // buzzer.windowsXP();
  // digitalWrite(10, HIGH);
  // delay(1000);
  // digitalWrite(10, LOW);
  // delay(1000);
  // digitalWrite(10, HIGH);
  // delay(1000);
  // for (int i = 0; i < 3; i++) {
  //   delay(100);
  //   digitalWrite(10, LOW);
  //   delay(100);
  //   digitalWrite(10, HIGH);
  // }
}


void loop() {
  //Serial.println(analogRead(A0));
  ball.get();
  //Serial.println(ball.dir);
  delay(100);
}

// void loop() {
//   if(timer.get()>50){
//     timer.reset();
//     char str[64];
//     //sprintf(str,"$%d,%d,%d,%d,%d,%d,%d,%d",B1,B2,B3,B4,B5,B6,B7,B8);
//     //Serial.println(str);
//     //Serial2.print(str);
//     ball.get();
//     Serial2.print(ball.dir);
//   }
//   if(Serial.available()){
//     Serial2.write(Serial.read());
//   }
//   if(Serial2.available()){
//     Serial.write(Serial2.read());
//   }
//   // bno.get();
//   // Serial.println(bno.dir);
//   // //delay(500);

//   // motor.set_power(bno.dir,bno.dir,bno.dir,bno.dir);
//   // motor.pwm_out();
// }
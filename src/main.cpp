#include "Arduino.h"
#include "UI.h"
#include "functions.h"
#include "move.h"
#include "sensors.h"

BNO bno;
BALL ball;
MOTOR motor;
TIMER timer;
TIMER linet;
SOUND buzzer;
LINE line;
ULTRASONIC ping;
MOVE move;
PID pid;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
int kickerpin = 9;
void setup() {
  bno.setup();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // ディスプレイ初期化処理
  Serial.begin(9600);
  Serial2.begin(9600);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 28);
  display.print("Singlarity");
  display.display();
  // buzzer.windowsXP();
  pinMode(10, OUTPUT);
  // // buzzer.windowsXP();
  digitalWrite(10, LOW);
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
  pinMode(9, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(Pin_sw1, INPUT_PULLUP);
  pinMode(Pin_sw2, INPUT_PULLUP);
  pinMode(Pin_sw3, INPUT_PULLUP);
  pinMode(Pin_sw4, INPUT_PULLUP);
  // digitalWrite(kickerpin, 1);
  delay(100);
  digitalWrite(kickerpin, 0);
  line.begin();
}

int dir = 0, speed = 0;

void loop() {
  if (SW4) {
    bno.reset();
  }
  // Serial.println(ball.dir);
  if (digitalRead(4)) {  //トグル
    if (linet.get() > 50 || 1) move.carryball(ball.dir);
    move.speed = 80;
    if (!ball.isExist) {
      move.speed = 0;
      // if (ping.get(2) > 50 ) {
      //   move.dir = 180;
      //   move.speed = 50;
      // }
    }
    //ライン
    // if (line.state[0] || line.state[1] || line.state[2]) {
    //   move.dir = 180;
    //   move.speed = 80;
    //   linet.reset();
    // } else if (line.state[3] || line.state[4] || line.state[5]) {
    //   move.dir = -90;
    //   move.speed = 80;
    //   linet.reset();
    // } else if (line.state[6] || line.state[7] || line.state[8]) {
    //   move.dir = 0;
    //   move.speed = 80;
    //   linet.reset();
    // } else if (line.state[9] || (line.state[10] && 0) || line.state[11]) {
    //   move.dir = 90;
    //   move.speed = 80;
    //   linet.reset();
    // }
    motor.cal_power(move.dir, move.speed, pid.run(bno.dir));
  } else
    motor.set_power(0, 0, 0, 0);

  motor.pwm_out();
  line.get_state();

  if(digitalRead(13)){
    digitalWrite(kickerpin,1);
    delay(100);
    digitalWrite(kickerpin,0);
    delay(200);
  }

  if (timer.get() > 50) {
    ball.get();
    line.get_state();
    Serial.print('L');
    for (int i = 0; i < NUM_lines; i++) {
      Serial.print(line.state[i]);
    }
    Serial.println();
    // ping.get_all();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5, 28);
    display.print("Singlarity");
    // display.println(digitalRead(16));
    // display.println(digitalRead(17));
    // display.println(digitalRead(18));
    // display.println(digitalRead(19));
    // ping.get_all();
    // display.println(ping.value[0]);
    // display.println(ping.value[1]);
    // display.println(ping.value[2]);
    // display.println(ping.value[3]);
    display.display();
    timer.reset();
  }

  // ping.get_all();
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 0);
  // display.println(ping.value[0]);
  // display.println(ping.value[1]);
  // display.println(ping.value[2]);
  // display.println(ping.value[3]);
  // display.display();
  bno.get();
  if (bno.ypr[2] > 20 || bno.ypr[2] < -20) {
    digitalWrite(10, 0);
  } else {
    digitalWrite(10, 1);
  }
}

// void loop() {
//   // Serial.print(digitalRead(A0));
//   // Serial.print("  ");
//   // Serial.println(analogRead(A0));
//   // ball.get();
//   // Serial.println(ball.dir);
//   // ping.get_all();
//   if (Serial.available()) {
//     digitalWrite(13,1);
//     display.clearDisplay();
//     display.display();
//     int v[2] = {0, 0};
//     int i = 0;
//     char tex = 0;
//     while (true) {
//       tex = Serial.read();
//       int value = tex - '0';
//       if (value <= 9 && value >= 0) {
//         v[i] *= 10;
//         v[i] += value;
//       } else if (tex == ',' || tex == 254) {
//         i = 1;
//       }else if(tex == '$'  || tex == 255){
//         break;
//       }
//     }
//     int x = v[0], y = v[1];
//     dir = degrees(atan2(x, y));
//     speed = sqrt(x * x + y * y);
//     while(Serial.available())Serial.read();
//   }
//   display.clearDisplay();
//   display.setCursor(20, 30);
//   display.setTextColor(WHITE);
//   display.setTextSize(2);
//   display.print(dir);
//   display.print("  ");
//   display.print(speed);
//   display.display();
//   motor.cal_power(dir, speed,50);

//   motor.pwm_out();
//   // delay(100);
// }

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
#include <Arduino.h>
#include "move.h"
#include "sensors.h"
#include "functions.h"


BNO bno;
MOTOR motor;

void setup() {
  bno.setup();
  Serial.begin(9600);
  buzzer.windowsXP();
}

void loop() {
  bno.get();
  Serial.println(bno.dir);
  //delay(500);

  motor.set_power(bno.dir,bno.dir,bno.dir,bno.dir);
  motor.pwm_out();
}
#include <Arduino.h>
#include "sensors.hpp"
#include "connectivity.hpp"


void setup() {
  Serial.begin(9600);
  setup_wifi();
  setup_mqtt();
  setup_bme680();
  setup_as5600_wind_direction();
  setup_hallsensor();
}



void loop() {
  // put your main code here, to run repeatedly:
  // Check for over the air update request and (if present) flash it
  //ArduinoOTA.handle();
  //delay(25);
  read_bme680();
  read_as5600_wind_direction();


  //int digitalVal = digitalRead(pin_hallsensor);
  //Serial.println(digitalVal);
  delay(100);

}



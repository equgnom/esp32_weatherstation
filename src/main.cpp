#include <Arduino.h>
#include "sensors.hpp"
#include "connectivity.hpp"


#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */




void setup() {
  Serial.begin(9600);
  setup_wifi();
  setup_mqtt();
  setup_bme680();
  setup_as5600_wind_direction();
  setup_hallsensor();
}



void loop() {
  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  //ArduinoOTA.handle();
  //delay(25);
  read_bme680();
  read_as5600_wind_direction();
  //transmit_mqtt();

  //int digitalVal = digitalRead(pin_hallsensor);
  //Serial.println(digitalVal);
  delay(5000);

  //Serial.flush(); 
  //esp_deep_sleep_start();

}



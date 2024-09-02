#include <Arduino.h>
#include <ArduinoOTA.h>
#include "sensors.hpp"

const char *SSID = "KiMiFi";              // WLAN name
const char *PSK = "16685622148011483387";           // WLAN password

void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("  WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  ArduinoOTA.begin();
}


void setup() {
  Serial.begin(9600);
  setup_wifi();
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



#include "connectivity.hpp"
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient pubSub(espClient);

/* WiFi Settings */
const char *SSID = "KiMiFi";                              // WLAN name
const char *PSK = "16685622148011483387";                 // WLAN password


/* MQTT Settings */
#define CLIENT_ID "ESP32_WeatherStation"                  // MQTT Client-ID
const char *MQTT_BROKER = "192.168.178.104";              // MQTT broker address
#define MQTT_PORT 1883                                    // MQTT port number
const char *MQTT_MAIN_TOPIC = "/home/sensors/power/main"; // MQTT topic to post to
#define MSG_BUF_LEN 200                                   // JSON preparation


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

void setup_mqtt()
{
    pubSub.setServer(MQTT_BROKER, MQTT_PORT);
}

void reconnectMqtt() {
  while (!pubSub.connected()) {
    Serial.print("(Re)connecting MQTT...");
    if (!pubSub.connect(CLIENT_ID)) {
      Serial.print("failed, rc=");
      Serial.print(pubSub.state());
      Serial.println(" retrying in 300 seconds");
      delay(300000);
    }
  }
}

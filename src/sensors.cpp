#include <sensors.hpp>

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "AS5600.h"



/* General Configuration Parameters */
#define SENSORS_ENABLE_DEBUG_PRINT 1

/* I2C Wire 0 Configuration Parameters */
#define I2C_WIRE0_SDA_PIN 21
#define I2C_WIRE0_SCL_PIN 22

/* I2C Wire 1 Configuration Parameters */
#define I2C_WIRE1_SDA_PIN 99
#define I2C_WIRE1_SCL_PIN 99

/* BME680 - Temperature Sensor -Configuration Parameters */
#define SEALEVELPRESSURE_HPA (1013.25)

/* AS5600 - Wind Speed - Configuration Parameters */

/* AS5600 - Wind Direction - Configuration Parameters */

/* A3144 - Hall Sensor - Configuration Parameters*/
#define PIN_INPUT_HALL_SENSOR 26


/* Definition of global Variables */
TwoWire I2C_Wire0 = TwoWire(0);
TwoWire I2C_Wire1 = TwoWire(1);

Adafruit_BME680 bme(&I2C_Wire0);                 // I2C Wire 0
AS5600 as5600_wind_direction(&I2C_Wire0);        // I2C Wire 0

sensor_results_struct sensor_results{ -1, -1, -1, -1, -1, -1, -1, -1};


void setup_i2c()
{
  I2C_Wire0.begin(I2C_WIRE0_SDA_PIN, I2C_WIRE0_SCL_PIN); 
  //I2C_Wire1.begin(I2C_WIRE1_SDA_PIN, I2C_WIRE1_SCL_PIN); // Not yet used
}

void setup_bme680()
{
  while (!Serial);

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void setup_as5600_wind_direction(){
  as5600_wind_direction.begin();
  as5600_wind_direction.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.
  delay(500);
  as5600_wind_direction.resetCumulativePosition(777);
}

void setup_hallsensor() { 
  pinMode(PIN_INPUT_HALL_SENSOR, INPUT); 
}


void read_bme680()
{
  // Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    #if SENSORS_ENABLE_DEBUG_PRINT > 0
      Serial.println(F("Failed to begin reading :("));
    #endif
    return;
  }

  // Wait until reading has finished
  if (!bme.endReading()) {
    #if SENSORS_ENABLE_DEBUG_PRINT > 0
      Serial.println(F("Failed to complete reading :("));
    #endif
    return;
  }
  
  // Write Data to result struct
  sensor_results.bme680_temperature_degc = bme.temperature;
  sensor_results.bme680_pressure_hpa = bme.pressure / 100;
  sensor_results.bme680_humidity_rel = bme.humidity;
  sensor_results.bme680_gas_resistance_kohms = bme.gas_resistance / 1000.0;
  sensor_results.bme680_altitude_m = bme.readAltitude(SEALEVELPRESSURE_HPA);

  #if SENSORS_ENABLE_DEBUG_PRINT > 0
    Serial.print(F("BME680 Reading completed at "));
    Serial.println(millis());
    Serial.print(F("Temperature = "));
    Serial.print(sensor_results.bme680_temperature_degc);
    Serial.println(F(" *C"));
    Serial.print(F("Pressure = "));
    Serial.print(sensor_results.bme680_pressure_hpa);
    Serial.println(F(" hPa"));
    Serial.print(F("Humidity = "));
    Serial.print(sensor_results.bme680_humidity_rel);
    Serial.println(F(" %"));
    Serial.print(F("Gas = "));
    Serial.print(sensor_results.bme680_gas_resistance_kohms);
    Serial.println(F(" KOhms"));
    Serial.print(F("Approx. Altitude = "));
    Serial.print(sensor_results.bme680_altitude_m);
    Serial.println(F(" m"));
    Serial.println();
  #endif
}

void read_as5600_wind_direction(){
  // Read sensor value and write to result struct
  sensor_results.as5600_winddirection_deg = as5600_wind_direction.getCumulativePosition();
  
  #if SENSORS_ENABLE_DEBUG_PRINT > 0
    Serial.print(F("AS5600 Winddirection = "));
    Serial.println(sensor_results.as5600_winddirection_deg);
    Serial.println(F(" deg"));
    Serial.println();
  #endif
}
#include <sensors.hpp>

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "AS5600.h"

TwoWire I2C_Wire0 = TwoWire(0);
TwoWire I2C_Wire1 = TwoWire(1);

Adafruit_BME680 bme(&I2C_Wire0);                 // I2C Wire 0
AS5600 as5600_wind_direction(&I2C_Wire0);        // I2C Wire 0


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
    Serial.println(F("Failed to begin reading :("));
    return;
  }

  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  Serial.print(F("Reading completed at "));
  Serial.println(millis());

  Serial.print(F("Temperature = "));
  Serial.print(bme.temperature);
  Serial.println(F(" *C"));

  Serial.print(F("Pressure = "));
  Serial.print(bme.pressure / 100.0);
  Serial.println(F(" hPa"));

  Serial.print(F("Humidity = "));
  Serial.print(bme.humidity);
  Serial.println(F(" %"));

  Serial.print(F("Gas = "));
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(F(" KOhms"));

  Serial.print(F("Approx. Altitude = "));
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(F(" m"));

  Serial.println();
}

void read_as5600_wind_direction(){
  as5600_wind_direction.getCumulativePosition();
  //  update every 100 ms
  Serial.println(as5600_wind_direction.getCumulativePosition());
}
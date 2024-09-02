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
  Serial.println(F("BME680 async test"));

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
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  as5600_wind_direction.begin();

  as5600_wind_direction.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.
  delay(1000);
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
  Serial.print(F("Reading started at "));
  Serial.print(millis());
  Serial.print(F(" and will finish at "));
  Serial.println(endTime);

  Serial.println(F("You can do other work during BME680 measurement."));
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
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
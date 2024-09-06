
/* Function Prototypes */
void setup_i2c();
void setup_bme680();
void setup_as5600_wind_direction();
void setup_hallsensor();

void read_bme680();
void read_as5600_wind_direction();

/* Global Variables */
struct sensor_results;

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
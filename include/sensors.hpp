/* Function Prototypes */
void setup_i2c();
void setup_bme680();
void setup_as5600_wind_direction();
void setup_hallsensor();

void read_bme680();
void read_as5600_wind_direction();


/* Type Definitions */
struct sensor_results_struct{
    float bme680_temperature_degc;
    float bme680_pressure_hpa;
    float bme680_humidity_rel;
    float bme680_gas_resistance_kohms;
    float bme680_altitude_m;
    float as5600_winddirection_deg;
    float as5600_windspeed_kph;
    float A3144_rain_lpm;
};

/* Global Variables */
extern sensor_results_struct sensor_results;
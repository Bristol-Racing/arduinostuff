#include "sensor/loadCell.hpp"
#include "sensor/sensorManager.hpp"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int time_per_reading = 100;
const int readings = 10;

const double arm_length = 142.5 / 1000.0;  //  meters

int currentReadings = 0;
long reading = 0;

int sensorCount = 1;
Sensor::LoadCell scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, arm_length);

Sensor::SensorManager manager(sensorCount, time_per_reading * readings);

void setup() {
    Serial.begin(57600);
    scale.setTickRate(time_per_reading);

    manager.addSensor(&scale);
    manager.setReadCallback(&readCallback);
}

void loop() {
    manager.spin();
}

void readCallback(double * results) {
    Serial.println(results[0]);
}

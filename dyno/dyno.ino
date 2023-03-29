#include "sensor/loadCell.hpp"
#include "sensor/hallEffect.hpp"
#include "sensor/current.hpp"
#include "sensor/voltage.hpp"
#include "sensor/sensorManager.hpp"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 4;

#define CURRENT_VIN A0
#define VOLTAGE_VIN A4

const int time_per_reading = 100;
const int readings = 10;

const double arm_length = 142.5 / 1000.0;  //  meters

int currentReadings = 0;
long reading = 0;

int sensorCount = 4;
Sensor::LoadCell scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, arm_length);
Sensor::HallEffect hallEffect;
Sensor::CurrentSensor currentSensor(CURRENT_VIN);
Sensor::VoltageSensor voltageSensor(VOLTAGE_VIN, 1000000.0, 220000.0);

Sensor::SensorManager manager(sensorCount, time_per_reading * readings);

void setup() {
    Serial.begin(57600);
    scale.setTickRate(time_per_reading);
    currentSensor.setTickRate(time_per_reading);
    hallEffect.setTickRate(1);

    manager.addSensor(&scale);
    manager.addSensor(&hallEffect);
    manager.addSensor(&currentSensor);
    manager.addSensor(&voltageSensor);
    manager.setReadCallback(&readCallback);
}

void loop() {
    manager.spin();
}

void readCallback(double * results) {
    for (int i = 0; i < sensorCount; i++) {
        if (i > 0) {
            Serial.print(",");
        }
        Serial.print(results[i]);
    }
    Serial.println();
}

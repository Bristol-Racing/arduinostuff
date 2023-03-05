#include "sensor/loadCell.hpp"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int time_per_reading = 100;
const int readings = 10;

const double arm_length = 142.5 / 1000.0;  //  meters

int currentReadings = 0;
long reading = 0;

Sensor::LoadCell scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, arm_length);

void setup() {
    Serial.begin(9600);
    scale.setTickRate(time_per_reading);
    scale.setReadRate(time_per_reading * readings);
}

void loop() {
    scale.tick();
    currentReadings++;

    if (currentReadings >= readings) {
        Serial.println(scale.read());
    }

    delay(time_per_reading);
    
}

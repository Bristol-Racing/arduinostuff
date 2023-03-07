#include "sensor/loadCell.hpp"
#include "sensor/sensorManager.hpp"

// int freeRam() {
//   extern int __heap_start,*__brkval;
//   int v;
//   return (int)&v - (__brkval == 0  
//     ? (int)&__heap_start : (int) __brkval);  
// }

// void display_freeram() {
//   Serial.print(F("- SRAM left: "));
//   Serial.println(freeRam());
// }

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int time_per_reading = 100;
const int readings = 10;

const double arm_length = 142.5 / 1000.0;  //  meters

int currentReadings = 0;
long reading = 0;

Sensor::LoadCell scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, arm_length);

Sensor::SensorManager manager(1, 5, time_per_reading * readings);

void setup() {
    Serial.begin(57600);
    scale.setTickRate(time_per_reading);
    scale.setReadRate(time_per_reading * readings);

    manager.addSensor(&scale);
    manager.setReadCallback(&readCallback);
}

void loop() {
    // scale.tick();
    // currentReadings++;

    // if (currentReadings >= readings) {
    //     Serial.println(scale.read());
    // }

    // delay(time_per_reading);
    
    // Serial.println("spun");
    manager.spin();
    // manager.spin(2000);
    // delay(2000);
    // Serial.println("unspun");
}

void readCallback(double * results) {
    // Serial.println("call");
    Serial.println(results[0]);
}

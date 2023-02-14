#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int time_per_reading = 100;
const int readings = 10;

int currentReadings = 0;
long reading = 0;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    reading += scale.read();
    currentReadings++;

    if (currentReadings >= readings) {
      Serial.println(reading / readings);
      reading = 0;
      currentReadings = 0;
    }
  } else {
    Serial.println("HX711 not found.");
  }

  delay(time_per_reading);
  
}

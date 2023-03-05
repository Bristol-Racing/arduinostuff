#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int time_per_reading = 100;
const int readings = 10;

const double arm_length = 142.5 / 1000.0;  //  meters

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
      long average = reading / readings;
      double weight = 0.0022 * (double)average + 147.39;  //  grams
      double force = (weight / 1000.0) * 9.8066500286389; //  newtons
      double torque = force * arm_length;                 //  newton-meters
      
      Serial.println(weight);
      reading = 0;
      currentReadings = 0;
    }
  } else {
    Serial.println("HX711 not found.");
  }

  delay(time_per_reading);
  
}

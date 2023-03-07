
#ifndef LOADCELL_H
#define LOADCELL_H

int freeRam() {
  extern int __heap_start,*__brkval;
  int v;
  return (int)&v - (__brkval == 0  
    ? (int)&__heap_start : (int) __brkval);  
}

void display_freeram() {
  Serial.print(F("- SRAM left: "));
  Serial.println(freeRam());
}

#include "sensor.hpp"

#include <HX711.h>

namespace Sensor {
    class LoadCell : public Sensor {
    private:
        HX711 scale;

        long totalReading;
        int readings;

        double length;

    public:
        LoadCell(int dout, int sck, double armLength);
        ~LoadCell();

        void tick();
        double read();
    };

    LoadCell::LoadCell(int dout, int sck, double armLength) {
        totalReading = 0;
        readings = 0;
        scale.begin(dout, sck);

        length = armLength;
    }

    LoadCell::~LoadCell() {

    }

    void LoadCell::tick() {
        if (scale.is_ready()) {
            totalReading += scale.read();
            readings++;
        }
    }

    double LoadCell::read() {
        long average = totalReading / readings;
        double weight = 0.0022 * (double)average + 147.39;  //  grams
        double force = (weight / 1000.0) * 9.8066500286389; //  newtons
        double torque = force * length;                     //  newton-meters
        
        totalReading = 0;
        readings = 0;

        return torque;
    }
}

#endif

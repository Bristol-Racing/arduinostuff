

#ifndef CURRENT_H
#define CURRENT_H

#include <Wire.h>
#include <Adafruit_ADS1X15.h>


#include "sensor.hpp"

namespace Sensor {
    class CurrentSensor : public Sensor {
    private:
        uint8_t vin;

        long totalReading;
        int readings;
        Adafruit_ADS1115 ads1115;
    public:
        CurrentSensor(uint8_t pin);
        ~CurrentSensor();

        void tick();
        double read();
    };

    CurrentSensor::CurrentSensor(uint8_t) {
        ads1115.begin();

        //  ads1115.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)

        // ads1115.setGain(GAIN_ONE);     // 1x gain   +/- 4.096V  1 bit = 2mV
        // ads1115.setGain(GAIN_TWO);     // 2x gain   +/- 2.048V  1 bit = 1mV
         ads1115.setGain(GAIN_FOUR);    // 4x gain   +/- 1.024V  1 bit = 0.5mV
        // ads1115.setGain(GAIN_EIGHT);   // 8x gain   +/- 0.512V  1 bit = 0.25mV
        // ads1115.setGain(GAIN_SIXTEEN); // 16x gain  +/- 0.256V  1 bit = 0.125mV
        totalReading = 0;
        readings = 0;
    }

    CurrentSensor::~CurrentSensor() {

    }

    void CurrentSensor::tick() {
        int16_t results;

  results = ads1115.readADC_Differential_0_1();
        totalReading += results;
        readings++;
    }

    double CurrentSensor::read() {
        //Robojax.com ACS758 Current Sensor 
        double average = (double)totalReading / (double)readings;
        // double voltage = (5.0 / 1023.0) * (double)average;// Read the voltage from sensor
        // double a = voltage - (vcc * 0.5) + 0.007;// 0.007 is a value to make voltage zero when there is no current
        // double current = voltage / a;

        totalReading = 0;
        readings = 0;

        // return current;
        return average;
    }
}

#endif

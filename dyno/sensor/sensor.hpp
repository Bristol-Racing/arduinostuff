
#ifndef SENSOR_H
#define SENSOR_H

namespace Sensor {
    class Sensor {
    private:
        int tickRate = -1;
        int readRate = -1;
    public:
        Sensor() {}
        ~Sensor() {}

        virtual void tick() = 0;
        virtual double read() = 0;

        void setTickRate(int tickRate);
        int getTickRate();

        void setReadRate(int readRate);
        int getReadRate();
    };

    void Sensor::setTickRate(int newTickRate) {
        //  Skip if newTickRate is invalid (less than 1)
        if (newTickRate <= 0) return;

        //  Skip if tickRate is already set
        if (tickRate > 0) return;

        tickRate = newTickRate;
    }

    int Sensor::getTickRate() {
        return tickRate;
    }

    void Sensor::setReadRate(int newReadRate) {
        //  Skip if newReadRate is invalid (less than 1)
        if (newReadRate <= 0) return;

        //  Skip if readRate is already set
        if (readRate > 0) return;

        readRate = newReadRate;
    }

    int Sensor::getReadRate() {
        return readRate;
    }
}

#endif

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#define HALL_PIN 7

const int ticksPerRev = 2;
const int calcTime = 10;

double currentTime = 0;
int ticks = 0;

bool inTick = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(HALL_PIN, INPUT);
}

// the loop function runs over and over again forever
void loop() {
   if (!digitalRead(HALL_PIN)) {
      if (!inTick) {
        ticks++;  
        inTick = true;
      }
   }
   else {
    inTick = false;
   }

   if (currentTime >= calcTime) {
      double rpm = ((double)ticks / (double)ticksPerRev) / (currentTime / 60.0);
      Serial.println(rpm);

      currentTime = 0;
      ticks = 0;
   }

   delay(1);
   currentTime += 1.0 / 1000.0;
}

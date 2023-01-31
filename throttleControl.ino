
#include <Servo.h>

#define MOTOR_PWM_PIN 10

#define THROTTLE_PIN A0
#define THROTTLE_CAP_PIN A1

//  PWM limits for the ESC
#define MIN_PWM 1000
#define MAX_PWM 2000

//  Weights for a weighted average of the old PWM and the new PWM
//  (reduces noise from the throttle)
#define OLD_PWM_WEIGHT 2
#define NEW_PWM_WEIGHT 1

//  Limits how fast the PWM can change. (Some ESCs don't like sudden changes)
#define MAX_PWM_CHANGE 10

Servo motor; // Yes I know we aren't using a servo but this works

long throttlePWM = MIN_PWM;
long outputPWM = MIN_PWM;

void setup() {
    Serial.begin(9600);
    pinMode(THROTTLE_PIN, INPUT);
    pinMode(THROTTLE_CAP_PIN, INPUT);
    motor.attach(MOTOR_PWM_PIN);
}

void loop() {
    int throttle = analogRead(THROTTLE_PIN);
    int throttleCap = analogRead(THROTTLE_CAP_PIN);

    //  Throttle value
    throttle = min(throttle, throttleCap);

    //  Convert throttle to PWM
    long newThrottlePWM = ((long)throttle * (MAX_PWM - MIN_PWM)) / 1024 + MIN_PWM;

    //  Weighted average of previous and new PWM
    throttlePWM = (throttlePWM * OLD_PWM_WEIGHT + newThrottlePWM * NEW_PWM_WEIGHT) / (OLD_PWM_WEIGHT + NEW_PWM_WEIGHT);

    //  Limit PWM change
    if (throttlePWM > outputPWM + MAX_PWM_CHANGE) {
        outputPWM += MAX_PWM_CHANGE;
    }
    else if (throttlePWM < outputPWM - MAX_PWM_CHANGE) {
        outputPWM -= MAX_PWM_CHANGE;
    }
    else {
        outputPWM = throttlePWM;
    }

    //  Output PWM
    motor.writeMicroseconds(outputPWM);
    delay(1);
}
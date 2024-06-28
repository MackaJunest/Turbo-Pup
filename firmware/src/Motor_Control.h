#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <driver/mcpwm.h>
#include <soc/mcpwm_periph.h>

class BLDC
{
public:
    BLDC(int motor, int dirPin, int escPin);
    void speed(float speedValue);

private:
    int motor;
    int dirPin;
    int escPin;
    int change;
    
    void setMotorSpeed(float speed);
    double mapf(double val, double in_min, double in_max, double out_min, double out_max);

};

class Servo
{
private:
    int DIR = 1;
    int servoPin;
    int servoChannel;
    int currentAngle;
    bool isAttached;
    const int minPulseWidth = 500;   // Minimum pulse width in microseconds
    const int maxPulseWidth = 2500;  // Maximum pulse width in microseconds
    const int maxAngle = 270;        // Maximum angle for servo

    void writeMicroseconds(int value);

public:
    Servo();
    ~Servo();
    void setDIR(bool REVERSE);
    void attach2(int PWM_PIN, int channel);
    void detach();
    void Move2(int angle);
    int read();
    bool attached();
};

#endif

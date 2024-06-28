#ifndef CURRENT_SENSING_H
#define CURRENT_SENSING_H

#include <Arduino.h>

class CurrentSensing
{
  public:
    // Constructor to initialize the sensor
    CurrentSensing(int pin);

    // Method to read the current
    float readCurrent();

  private:
    int sensorPin;
    float shuntResistor = 0.010;
    float gain = 50.0;
    float referenceVoltage = 3.3;
    int adcMaxValue = 4095;
    int numReadings = 150;
    float alpha = 0.02; // Smoothing factor for low-pass filter
    float lastFilteredValue = 0; // Previous filtered value
};
/*
  // Read the current value from each sensor
  float current1 = currentSensor1.readCurrent();
  float current2 = currentSensor2.readCurrent();
  float current3 = currentSensor3.readCurrent();
  float current4 = currentSensor4.readCurrent();
  //Calculate the mean current
  float meanCurrent = (current1 + current2 + current3 + current4) / 4.0;

// PID control logic to adjust servo angles
  for (int i = 0; i < 4; i++) {
    float current = (i == 0) ? current1 : (i == 1) ? current2 : (i == 2) ? current3 : current4;
    float error = meanCurrent - current;
    integral[i] += error * 0.1; // Integral term
    float derivative = (error - prevError[i]) / 0.1; // Derivative term
    prevError[i] = error;

    // Calculate the servo angle adjustment
    float adjustment = Kp * error + Ki * integral[i] + Kd * derivative;
    constrain(adjustment,-10,10);
    // Adjust the servo angles
    servoAngles[i] = constrain(initialAngles[i] + adjustment,25,35);
    Serial.print(servoAngles[i]);
  }
  Serial.println("    ");*/
#endif
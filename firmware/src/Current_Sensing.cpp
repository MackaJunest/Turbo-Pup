#include "Current_Sensing.h"

// Constructor to initialize the sensor
CurrentSensing::CurrentSensing(int pin)
{
  sensorPin = pin;
}

float CurrentSensing::readCurrent() {
  unsigned long sum = 0;

  // Average the analog readings
  for (int i = 0; i < numReadings; i++) {
    // Read the analog voltage from the sensor
    sum += analogRead(sensorPin);
  }

  // Calculate the average
  float averageValue = sum / (float)numReadings;

  // Apply a simple low-pass filter
  float filteredValue = (alpha * averageValue) + ((1 - alpha) * lastFilteredValue);
  lastFilteredValue = filteredValue;

  // Convert the filtered analog value to voltage
  float voltage = filteredValue * (referenceVoltage / adcMaxValue);

  // Calculate the current through the shunt resistor
  // Vout = Current * ShuntResistor * Gain
  // Current = Vout / (ShuntResistor * Gain)
  float current = voltage / (shuntResistor * gain);

  return current;
}

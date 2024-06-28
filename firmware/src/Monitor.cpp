#include "Monitor.h"


void OBMonitor::MonitorINIT()
{
    Wire.begin(17, 18);
    _display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    _display.display();
    _display.setTextSize(1);
    _display.setTextColor(WHITE);
    _display.clearDisplay();
    _display.setCursor(0, 0);     // Start at top-left corner
}

int OBMonitor::VBatt()
{
    const float alpha = 0.99;  // Adjust this value based on the desired smoothing effect

    int sensorValue = analogRead(_pin);
    float voltageAtPin = sensorValue * (3.3 / 4095.0); // ESP32 ADC is 12-bit, and reference voltage is 3.3V
    float inputVoltage = voltageAtPin * ((_r1 + _r2) / _r2);

    // Piecewise linear mapping points (Voltage, Percentage)
    const float voltagePoints[] = {10.5, 11.18, 11.39, 11.62, 12.07, 12.33, 12.6};
    const int percentagePoints[] = {0, 20, 40, 60, 80, 90, 100};
    const int numPoints = sizeof(voltagePoints) / sizeof(voltagePoints[0]);


    int rawPercentage = 0;

    // Find the appropriate range for inputVoltage and interpolate
    for (int i = 1; i < numPoints; ++i) {
        if (inputVoltage <= voltagePoints[i]) {
            float slope = (percentagePoints[i] - percentagePoints[i - 1]) / (voltagePoints[i] - voltagePoints[i - 1]);
            rawPercentage = percentagePoints[i - 1] + slope * (inputVoltage - voltagePoints[i - 1]);
            break;
        }
    }

    // Handle the case when voltage is above the highest point
    if (inputVoltage > voltagePoints[numPoints - 1]) {
        rawPercentage = 100;
    }
    // Handle the case when voltage is below the lowest point
    else if (inputVoltage < voltagePoints[0]) {
        rawPercentage = 0;
    }

    static int filteredPercentage = rawPercentage;

    // Apply low-pass filter to percentage
    filteredPercentage = static_cast<int>(alpha * rawPercentage + (1 - alpha) * filteredPercentage);

    return filteredPercentage;
}

void OBMonitor::drawBatteryLevel(int x, int y, int width, int height, int percent) {
    // Calculate fill width based on percentage
    int fillWidth = map(percent, 0, 100, 0, width - 2);
    
    // Draw filled part of battery
    _display.fillRect(x + 1, y + 1, fillWidth, height - 2, WHITE);
}

void OBMonitor::drawBatteryOutline(int x, int y, int width, int height) {
    // Draw battery outline
    _display.drawRect(x, y, width, height, WHITE);
    // Draw battery terminals
    _display.fillRect(x + width, y + height / 4, 4, height / 2, WHITE);
}

void OBMonitor::display()
{
    int batteryPercentage = VBatt();
    _display.clearDisplay();
    drawBatteryOutline(5, 7, 40, 20);
    drawBatteryLevel(7, 9, 36, 16, batteryPercentage);
    _display.setCursor(55, 16);
    _display.print("Battery:");
    _display.print(batteryPercentage);
    _display.println("%");
    _display.display();
}
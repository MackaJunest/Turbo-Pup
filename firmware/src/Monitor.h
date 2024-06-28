#ifndef MONITOR_H
#define MONITOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
class OBMonitor
{
public:
    int VBatt();
    void MonitorINIT();
    void display();
    void drawBatteryLevel(int x, int y, int width, int height, int percent);
    void drawBatteryOutline(int x, int y, int width, int height);
private:
    int _pin=2;
    float _r1=27000.0;
    float _r2=9100.0;
    float _fullVoltage=12.6;
    float _emptyVoltage=10.5;
    int _i2cAddress=0x3c;
    Adafruit_SH1106 _display = Adafruit_SH1106(40); // Adjust parameters based on your setup
};

#endif // MONITOR_H
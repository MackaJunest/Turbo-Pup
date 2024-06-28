#ifndef COMMANDER_H
#define COMMANDER_H

#include <Arduino.h>

class Commander
{
    public:
        void Init(int Baudrate, long int timeout);
        void readSerialData();
        void send(char* data);
        int getDataCount();
        int getData(int index);
    private:
        int index;
        int data[7];
        int dataCount = 0;
        String input;
        char* str = NULL;
        char* token = NULL;
        const char* seperator= ",";
};
#endif
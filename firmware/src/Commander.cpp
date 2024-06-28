#include <Commander.h>

void Commander::Init(int Baudrate, long int timeout)
{
    Serial.begin(Baudrate);
    Serial.setTimeout(timeout);
}

void Commander::readSerialData()
{
    if (Serial.available() > 0)
    {
        dataCount = 0;
        // Read the incoming data until a newline character is received
        input = Serial.readStringUntil('\n');
        // Use a StringTokenizer to parse the input
        str = strdup(input.c_str()); // Duplicate the input string
        token = strtok(str, seperator);

        // Loop through each token and parse as integer
        while (token != NULL)
        {
            data[dataCount] = atoi(token);
            dataCount++;
            // Check if we have reached the maximum expected data count
            if (dataCount >= 10)
            { // Adjust the condition as needed
                    break;
            }
            token = strtok(NULL, ",");
        }
        free(str); // Free the memory allocated by strdup
    }
}

// Method to return the number of parsed integers
int Commander::getDataCount()
{
    return dataCount;
}

// Method to access a specific parsed integer by index
int Commander::getData(int index)
{
    if (index >= 0 && index < dataCount)
    {
        return data[index];
    }
    return 0; // or any default value indicating out of bounds
}
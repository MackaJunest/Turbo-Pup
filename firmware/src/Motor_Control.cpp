#include "Motor_Control.h"


double BLDC::mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

BLDC::BLDC(int motor, int dirPin, int escPin) : motor(motor), dirPin(dirPin), escPin(escPin), change(0) 
{
    pinMode(dirPin, OUTPUT);

    // Initialize MCPWM GPIO pin for this motor
    if (motor == 1) mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, escPin);
    if (motor == 2) mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, escPin);
    if (motor == 3) mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, escPin);
    if (motor == 4) mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, escPin);
}

void BLDC::speed(float speedValue) {
    if (speedValue > 0)
        speedValue = mapf(speedValue, 1, 100, 15, 100);
    else if (speedValue < 0)
        speedValue = mapf(speedValue, -1, -100, -15, -100);
    
    speedValue = constrain(speedValue, -100, 100);
    
    if (speedValue > 0) {
        if (change == 1) {
            setMotorSpeed(0);
            vTaskDelay(400/portTICK_PERIOD_MS);
            change = 0;
        }
        digitalWrite(dirPin, HIGH); // Set direction to forward
        setMotorSpeed(speedValue);
    } else if (speedValue < 0) {
        if (change == 0) {
            setMotorSpeed(0);
            vTaskDelay(400/portTICK_PERIOD_MS);
            change = 1;
        }
        digitalWrite(dirPin, LOW); // Set direction to reverse
        setMotorSpeed(speedValue);
    } else {
        setMotorSpeed(0);
    }
}

void BLDC::setMotorSpeed(float speed) {
    float duty_cycle = roundf(abs(speed));
    switch (motor) {
        case 1:
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
            mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_1);
            break;
        case 2:
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty_cycle);
            mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_1);
            break;
        case 3:
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, duty_cycle);
            mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_1);
            break;
        case 4:
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, duty_cycle);
            mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_1);
            break;
    }
}

Servo::Servo() : servoPin(255), servoChannel(-1), currentAngle(0), isAttached(false) {}

Servo::~Servo()
{
    detach();
}

void Servo::attach2(int PWM_PIN, int channel)
{
    servoPin = PWM_PIN;
    servoChannel = channel;
    if (ledcSetup(servoChannel, 50, 13))  // 50 Hz frequency, 13-bit resolution
    {
        ledcAttachPin(servoPin, servoChannel);
        isAttached = true;
    }
    else
    {
        Serial.println("Error: LEDC setup failed");
    }
}

void Servo::setDIR(bool REVERSE)
{
    DIR = REVERSE ? -1 : 1;
}

void Servo::writeMicroseconds(int value)
{
    if (isAttached)
    {
        int dutyCycle = (value * 8191) / 20000; // Convert microseconds to duty cycle (0-8191 for 13-bit resolution)
        ledcWrite(servoChannel, dutyCycle);
    }
}

void Servo::Move2(int angle)
{
    angle = constrain(angle, 0, maxAngle);
    currentAngle = angle;
    int pulseWidth = DIR == -1 ? map(angle, 0, maxAngle, maxPulseWidth, minPulseWidth)
                               : map(angle, 0, maxAngle, minPulseWidth, maxPulseWidth);
    writeMicroseconds(pulseWidth);
}

void Servo::detach()
{
    if (isAttached)
    {
        ledcDetachPin(servoPin);
        isAttached = false;
    }
}

int Servo::read()
{
    return currentAngle;
}

bool Servo::attached()
{
    return isAttached;
}

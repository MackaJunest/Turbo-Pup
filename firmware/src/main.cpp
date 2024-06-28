#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include "Motor_Control.h"
#include "Maths_Solvers.h"
#include "Current_Sensing.h"
#include "Commander.h"
#include "Monitor.h"

// Pin Definitions
const int ServoPin[8] = {9, 10, 11, 12, 13, 14, 15, 16};
const int MDIRPin[4] = {48, 38, 40, 42};
const int MESCPin[4] = {47, 45, 39, 41};
const int CSFD_PIN[4] = {4, 5, 6, 7};
const int EM_Brake = 21;

// PID controller parameters (adjust as needed)
const float Kp = 150; // Proportional gain

// Variables for PID control
float prevError[4] = {0, 0, 0, 0};
float integral[4] = {0, 0, 0, 0};

// Initial angles for servos
float xcoord[4] = {0, 0, 0, 0};
float yinit[4] = {195, 210, 203, 200};
float ytarget[4] = {195, 210, 203, 200};
float hamAngles[4] = {30, 30, 30, 30}; // Current angles for H1-H4
float shankAngles[4] = {75, 75, 75, 75}; // Current angles for H1-H4

// Inital speed for BLDCs
int Wheelspeed[4] = {0,0,0,0};
int Speed_diff=0;

// Init Commander and Serial
Commander Commander1;
int values[7];

// Init onboard monitor
OBMonitor OBMON;

// Servo Objects
Servo H1;
Servo S1;
Servo H2;
Servo S2;
Servo H3;
Servo S3;
Servo H4;
Servo S4;

// Create a CurrentSensor object
CurrentSensing currentSensor1(CSFD_PIN[0]);
CurrentSensing currentSensor2(CSFD_PIN[1]);
CurrentSensing currentSensor3(CSFD_PIN[2]);
CurrentSensing currentSensor4(CSFD_PIN[3]);

// Motor Objects
BLDC motor1(1, MDIRPin[0], MESCPin[0]);
BLDC motor2(2, MDIRPin[1], MESCPin[1]);
BLDC motor3(3, MDIRPin[2], MESCPin[2]);
BLDC motor4(4, MDIRPin[3], MESCPin[3]);

// Solver Init
Solver Motion_Solver;

// Function Declarations
void motorTask1(void *pvParameters);
void motorTask2(void *pvParameters);
void motorTask3(void *pvParameters);
void motorTask4(void *pvParameters);
void servoTask(void *pvParameters);
void commanderTask(void *pvParameters);


void setup()
{
  pinMode(EM_Brake,OUTPUT);
  Commander1.Init(115200,20);
  // Attach Servos
  H1.attach2(ServoPin[0], 0);
  S1.attach2(ServoPin[1], 1);
  H2.attach2(ServoPin[2], 2);
  S2.attach2(ServoPin[3], 3);
  H3.attach2(ServoPin[5], 4);
  S3.attach2(ServoPin[4], 5);
  H4.attach2(ServoPin[6], 6);
  S4.attach2(ServoPin[7], 7);

  // Set Servo Directions
  H1.setDIR(true);
  S1.setDIR(true);
  H2.setDIR(false);
  S2.setDIR(false);
  H3.setDIR(false);
  S3.setDIR(true);
  H4.setDIR(false);
  S4.setDIR(false);

  // Configure MCPWM
  mcpwm_config_t pwm_config;
  pwm_config.frequency = 500;
  pwm_config.cmpr_a = 0;
  pwm_config.cmpr_b = 0;
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_1;

  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);

  OBMON.MonitorINIT();
  // Create tasks
  xTaskCreate(motorTask1, "Motor Task 1", 2048, NULL, 0, NULL);
  xTaskCreate(motorTask2, "Motor Task 2", 2048, NULL, 0, NULL);
  xTaskCreate(motorTask3, "Motor Task 3", 2048, NULL, 0, NULL);
  xTaskCreate(motorTask4, "Motor Task 4", 2048, NULL, 0, NULL);
  xTaskCreate(servoTask, "Servo Task", 2048, NULL, 0, NULL);
  xTaskCreate(commanderTask, "Servo Task", 2048, NULL, 0, NULL);
}

// Motor Control Task for motor 1
void motorTask1(void *pvParameters)
{
  while (1) 
  {
    motor1.speed(-values[1]);
    vTaskDelay(1/portTICK_PERIOD_MS);
  }
}

// Motor Control Task for motor 2
void motorTask2(void *pvParameters)
{
  while (1)
  {
    motor2.speed(values[0]);
    vTaskDelay(1/portTICK_PERIOD_MS);
  }
}

// Motor Control Task for motor 3
void motorTask3(void *pvParameters)
{
  while (1)
  {
    motor3.speed(-values[1]);
    vTaskDelay(1/portTICK_PERIOD_MS);
  }
}

// Motor Control Task for motor 4
void motorTask4(void *pvParameters)
{
  while (1)
  {
    motor4.speed(values[0]);
    vTaskDelay(1/portTICK_PERIOD_MS);
  }
}

// Servo Control Task
void servoTask(void *pvParameters)
{
  while (1)
  {
    for (int i=0; i<4; i++)
    {
      Motion_Solver.IK_Solver(xcoord[i], ytarget[i], shankAngles[i], hamAngles[i]);
      Serial.print(hamAngles[i]);
      Serial.print("\t");
      Serial.print(shankAngles[i]);
    }
    Serial.println();
    H1.Move2(hamAngles[0]);
    S1.Move2((shankAngles[0]+hamAngles[0]-86)*2);
    H2.Move2(hamAngles[1]);
    S2.Move2((shankAngles[1]+hamAngles[1]-86)*2);
    H3.Move2(hamAngles[2]);
    S3.Move2((shankAngles[2]+hamAngles[2]-86)*2);
    H4.Move2(hamAngles[3]);
    S4.Move2((shankAngles[3]+hamAngles[3]-86)*2);
    vTaskDelay(100/portTICK_PERIOD_MS); // Adjust this delay as needed
  }
}

void commanderTask(void *pvParameters)
{
  while (1) 
  {
    Commander1.readSerialData();
    // Example: Get and use parsed data
    int count = Commander1.getDataCount();
    for (int i = 0; i < count; ++i)
    {
      values[i] = Commander1.getData(i);
    }
    if (values[2]==1)
    {
      digitalWrite(EM_Brake,HIGH);
    }
    else
      digitalWrite(EM_Brake,LOW);
  }
}

void loop()
{
  OBMON.display();
  if (values[0] > 0 && values[1] > 0)
  {
    Speed_diff=values[0]-values[1];
    constrain(Speed_diff,-25,25);
    ytarget[0]=yinit[0]-Speed_diff;
    ytarget[1]=yinit[1]+Speed_diff;
    ytarget[2]=yinit[2]-Speed_diff;
    ytarget[3]=yinit[3]+Speed_diff;
  }
  else if (values[0] < 0 && values[1] < 0)
  {
    Speed_diff=values[0]-values[1];
    constrain(Speed_diff,-25,25);
    ytarget[0]=yinit[0]+Speed_diff;
    ytarget[1]=yinit[1]-Speed_diff;
    ytarget[2]=yinit[2]+Speed_diff;
    ytarget[3]=yinit[3]-Speed_diff;
  }
  else
  {
    for(int i = 0; i < 3; i++)
    {
      ytarget[i]=yinit[i];
    }
  }
}
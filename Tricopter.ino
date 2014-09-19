#include <I2Cdev.h>
#include <Wire.h>
#include <Servo.h>

#include "Variables.h"

#include <helper_3dmath.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <MPU6050.h>

#include "Config.h"
//Changes the interupt pins
#include "PinChangeInt.h"
#include "RCControl.h"
#include "Gyroscope.h"
#include "Motors.h"
#include "PID.h"
#include "Controller.h"

//Timekeeping

unsigned long t100Hz;
unsigned long t10Hz;
unsigned long t2Hz;
unsigned long t1Hz;

bool ledBlink = HIGH;

bool throttleOff = 1;
uint32_t armTime;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  
  motorsSetup();
  
  //Setup RC
  RCSetup();
  
  //Setup Gyro
  gyroSetup();
  
  controllerSetup();
}

void process100HzTask(){
  
}

void process10HzTask(){
  
  Serial.print(yprAngle[0]); Serial.print('\t');
  Serial.print(yprAngle[1]); Serial.print('\t');
  Serial.print(yprAngle[2]); Serial.print('\t');
  
  Serial.print(gx); Serial.print('\t');
  Serial.print(gy); Serial.print('\t');
  Serial.print(gz); Serial.print('\t');
  
  Serial.print(throttle.getValue()); Serial.print('\t');
  Serial.print(rudder.getValue()); Serial.print('\t');
  Serial.print(aileron.getValue()); Serial.print('\t');
  Serial.print(elevator.getValue()); Serial.print('\t');
  
  Serial.print(armed?"ARMED":"NOT ARMED"); Serial.print('\t');
  
  Serial.print(targetRoll); Serial.print('\t');
  Serial.print(targetPitch); Serial.print('\t');
  Serial.print(targetYaw); Serial.print('\t');
  
  Serial.print(outputRoll); Serial.print('\t');
  Serial.print(outputPitch); Serial.print('\t');
  Serial.print(outputYaw); Serial.print('\t');
  
  Serial.println();
  
  if(armed){
    //Check if throttle is off
    if( throttle.getValue() < MIN_THROTTLE ){
      
      //If not flying anymore, check arm timer
      if(inFlight){
        armTime = currentTime;
      }
      inFlight = 0;
      
    }else{
      inFlight = 1;
    }
  }
}

void process2HzTask(){
  if(!inFlight){
    //Listen for arm signal
    if(!armed){
      //Throttle and elevator in the lowest position, aileron and rudder can be either right or left
      //Make sure throttle is not zero because the remote is not connected
      if( throttle.getValue() != 0 && throttle.getValue() < MIN_THROTTLE && elevator.getValue() < MIN_ELEVATOR && (aileron.getValue() < MIN_AILERON || aileron.getValue() > MAX_AILERON) && (rudder.getValue() < MIN_RUDDER || rudder.getValue() > MAX_RUDDER)){
        armed = true;
        armTime = currentTime;
      }
    }else{
      //Armed, check for disarm
      if(currentTime - armTime > MAX_ARM_TIME){
        armed = false;
        inFlight = 0;
      }
    }
  }
  
  if(!gyroIsStable() && !armed){
    digitalWrite(LED_PIN, ledBlink);
    ledBlink = !ledBlink;
  }else{
    if(armed)
      digitalWrite(LED_PIN, HIGH);
    else
      digitalWrite(LED_PIN, LOW);
  }
}

void process1HzTask(){
  gyroCheckStable();
}

void loop()
{
  currentTime = micros();
  dt = currentTime - previousTime;
  previousTime = currentTime;
  
  //Process RC controls
  RCLoop();
  
  //Process gyroscope data
  
  //unsigned long gyroBM = micros();
  gyroLoop();
  //Serial.println(micros() - gyroBM);
  
  if(currentTime - t100Hz > 10000){
    process100HzTask();
    t100Hz = currentTime;
  }
  
  if(currentTime - t10Hz > 100000){
    process10HzTask();
    t10Hz = currentTime;
  }
  
  if(currentTime - t2Hz > 500000){
    process2HzTask();
    t2Hz = currentTime;
  }
  
  if(currentTime - t1Hz > 1000000){
    process1HzTask();
    t1Hz = currentTime;
  }
  
  controllerLoop();
  
  motorsLoop();
}

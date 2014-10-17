#ifndef _RCControl_h
#define _RCControl_h

#include "RCChannel.h"

RCChannel throttle(THROTTLE_IN_PIN, MIN_THROTTLE, MAX_THROTTLE, THROTTLE_TRIM);
RCChannel rudder(RUDDER_IN_PIN, MIN_RUDDER, MAX_RUDDER, RUDDER_TRIM);
RCChannel aileron(AILERON_IN_PIN, MIN_AILERON, MAX_AILERON, AILERON_TRIM);
RCChannel elevator(ELEVATOR_IN_PIN, MIN_ELEVATOR, MAX_ELEVATOR, ELEVATOR_TRIM);
RCChannel aux1(AUX1_IN_PIN, MIN_AUX1, MAX_AUX1, 0);

//RC Interupts
void calcThrottle(){
  throttle.calcPin();
}

void calcRudder(){
  rudder.calcPin();
}

void calcAileron(){
  aileron.calcPin();
}

void calcElevator(){
  elevator.calcPin();
}

void calcAux1(){
  aux1.calcPin();
}

void RCSetup() {
  PCintPort::attachInterrupt(THROTTLE_IN_PIN, calcThrottle, CHANGE); 
  PCintPort::attachInterrupt(RUDDER_IN_PIN, calcRudder, CHANGE); 
  PCintPort::attachInterrupt(AILERON_IN_PIN, calcAileron, CHANGE); 
  PCintPort::attachInterrupt(ELEVATOR_IN_PIN, calcElevator, CHANGE);
  PCintPort::attachInterrupt(AUX1_IN_PIN, calcAux1, CHANGE); 
};

void RCLoop(){
  //Check if any data is recorded from the RC controller
  throttle.copyValue();
  rudder.copyValue();
  aileron.copyValue();
  elevator.copyValue();
  aux1.copyValue();
}


#endif



#ifndef _RCChannel_h
#define _RCChannel_h

class RCChannel {
public:
RCChannel(int p, int minV, int maxV) {
  pin = p;
  value = 0;
  minValue = minV;
  maxValue = maxV;
};

void calcPin(){
  //Rising Edge, Record time
  if(digitalRead(pin) == HIGH){ 
    startTime = micros();
  } else {
    //Falling edge, record time and get the difference
    shared = (uint16_t)(micros() - startTime);
  }
}

void copyValue(){
  value = shared;
  scaledValue = constrain( map(value, minValue, maxValue, 1000, 2000), 1000, 2000);
}

uint32_t getValue(){
  return value;
}

uint32_t getScaledValue(){
  return scaledValue;
}

private:
  uint8_t pin;
  uint32_t startTime;
  volatile uint32_t shared;
  uint32_t value;
  uint32_t scaledValue;
  uint32_t minValue;
  uint32_t maxValue;
};

#endif



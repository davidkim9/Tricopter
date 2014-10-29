long rcyaw, rcpit, rcroll; 

volatile uint8_t atomicServo = 125;

void motorsSetup(){
  
  pinMode(LEFT_MOTOR_OUT_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_OUT_PIN, OUTPUT);
  pinMode(REAR_MOTOR_OUT_PIN, OUTPUT);
  
  pinMode(YAW_MOTOR_OUT_PIN, OUTPUT);
  
  //Add interrupt for servo on timer0
  TCCR0A = 0; // normal counting mode
  TIMSK0 |= (1<<OCIE0A); // Enable CTC interrupt
  
  //Set servo to middle
  atomicServo = (MIDCOMMAND-1000)/4;
  
  //Arm the motors
  analogWrite(LEFT_MOTOR_OUT_PIN, MINCOMMAND / 8);
  analogWrite(RIGHT_MOTOR_OUT_PIN, MINCOMMAND / 8);
  analogWrite(REAR_MOTOR_OUT_PIN, MINCOMMAND / 8);
}

long lastDethrottleTime = 0;

void motorsLoop(){
  
  if(inFlight){
    
    if(signalPresent){
      //Cap the throttle so we can at least have some control
      throttleValue = constrain(throttle.getScaledValue(), 1000, 1900);
    }else{
      //Decrease throttle every 50ms
      if(currentTime - lastDethrottleTime > 100000){
        throttleValue = constrain(throttleValue - 1, 1000, 1900);
        lastDethrottleTime - currentTime;
        //Shut off motor, but stay armed.
        if(throttleValue == 1000){
          inFlight = 0;
          armed = 1;
          armTime = currentTime;
        }
      }
    }
    
    //throttleValue = 1500;
    int frontLeftValue = throttleValue - outputRoll + outputPitch*2/3;
    int frontRightValue = throttleValue + outputRoll + outputPitch*2/3;
    int rearValue = throttleValue - outputPitch*4/3;
    int yawCommand = constrain(MIDCOMMAND - outputYaw, 1100, 1900);
    
    //Make sure the motors dont turn off in flight and PWM size isnt greater than 2000
    frontLeftValue = constrain(frontLeftValue, MINTHRUST, MAXCOMMAND);
    frontRightValue = constrain(frontRightValue, MINTHRUST, MAXCOMMAND);
    rearValue = constrain(rearValue, MINTHRUST, MAXCOMMAND);
    
    analogWrite(LEFT_MOTOR_OUT_PIN, frontLeftValue / 8);
    analogWrite(RIGHT_MOTOR_OUT_PIN, frontRightValue / 8);
    analogWrite(REAR_MOTOR_OUT_PIN, rearValue / 8);
    
    atomicServo = (yawCommand-1000)/4;
    /*
    Serial.print(frontLeftValue); Serial.print('\t');
    Serial.print(frontRightValue); Serial.print('\t');
    
    Serial.print(outputRoll); Serial.print('\t');
    Serial.print(outputYaw); Serial.print('\t');
    
    Serial.println();
    */
  }else{
    //Turn off motors
    analogWrite(LEFT_MOTOR_OUT_PIN, MINCOMMAND / 8);
    analogWrite(RIGHT_MOTOR_OUT_PIN, MINCOMMAND / 8);
    analogWrite(REAR_MOTOR_OUT_PIN, MINCOMMAND / 8);
  }
  
}

//AeroQuad tricopter servo interrupt service routine
//This will limit the servo output to 50hz
ISR(TIMER0_COMPA_vect) {
  static uint8_t state = 0;
  
  if (state == 0) {
    //http://billgrundmann.wordpress.com/2009/03/03/to-use-or-not-use-writedigital/
    //Turn on pin
    PORTD |= 1<<5;
    OCR0A+= 250;
    state++;
  } else if (state == 1) {
    //Keep pin turned on for a duration
    OCR0A+= atomicServo; // 1000 + [0-1020] us
    state++;
  } else if (state == 2) {
    //Turn off pin
    PORTD &= ~(1<<5);
    OCR0A+= 250;
    state++;
  }else{
    //On even states
    if(!state & 0x1){
      OCR0A+= 250;
    }
    if(state == 19){
      state = 0;
      OCR0A+= 250;
    }else{
      state++;
    }
  }
}

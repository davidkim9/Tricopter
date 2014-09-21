Servo leftServo;
Servo rightServo;
Servo rearServo;
Servo yawServo;

long rcyaw, rcpit, rcroll; 

void motorsSetup(){
  
  leftServo.attach(LEFT_MOTOR_OUT_PIN);
  rightServo.attach(RIGHT_MOTOR_OUT_PIN);
  rearServo.attach(REAR_MOTOR_OUT_PIN);
  yawServo.attach(YAW_MOTOR_OUT_PIN);
  
  yawServo.writeMicroseconds(1500);
  
  //Arm the motors
  leftServo.writeMicroseconds(1000);
  rightServo.writeMicroseconds(1000);
  rearServo.writeMicroseconds(1000);
}

void motorsLoop(){
  if(inFlight){
    //Cap the throttle so we can at least have some control
    int throttleValue = constrain(throttle.getScaledValue(), 1000, 1900);
    
    int frontLeftValue = throttleValue - outputRoll + outputPitch*2/3;
    int frontRightValue = throttleValue + outputRoll + outputPitch*2/3;
    int rearValue = throttleValue - outputPitch*4/3;
    int yawCommand = constrain(MIDCOMMAND + outputYaw, 1250, 1750);
    
    //Make sure the motors dont turn off in flight
    frontLeftValue = max(frontLeftValue, MINTHRUST);
    frontRightValue = max(frontRightValue, MINTHRUST);
    rearValue = max(rearValue, MINTHRUST);
    
    if(leftServo.readMicroseconds() != frontLeftValue){
      leftServo.writeMicroseconds(frontLeftValue);
    }
    
    if(rightServo.readMicroseconds() != frontRightValue){
      rightServo.writeMicroseconds(frontRightValue);
    }
    
    if(rearServo.readMicroseconds() != rearValue){
      rearServo.writeMicroseconds(rearValue);
    }
    
    if(yawServo.readMicroseconds() != yawCommand){
      yawServo.writeMicroseconds(yawCommand);
    }
    
  }else{
    if(leftServo.readMicroseconds() != MINCOMMAND)
      leftServo.writeMicroseconds(MINCOMMAND);
    if(rightServo.readMicroseconds() != MINCOMMAND)
      rightServo.writeMicroseconds(MINCOMMAND);
    if(rearServo.readMicroseconds() != MINCOMMAND)
      rearServo.writeMicroseconds(MINCOMMAND);
  }
  
}

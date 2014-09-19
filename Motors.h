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
    int throttleValue = throttle.getScaledValue();
    
    int frontLeftValue = throttleValue - outputRoll + outputPitch*2/3;
    int frontRightValue = throttleValue + outputRoll + outputPitch*2/3;
    int rearValue = throttleValue - outputPitch*4/3;
    int yawCommand = constrain(MIDCOMMAND + outputYaw, 1300, 1700);
    
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
    

    /*
    Serial.print(yprAngle[0]); Serial.print('\t');
    Serial.print(yprAngle[1]); Serial.print('\t');
    Serial.print(yprAngle[2]); Serial.print('\t');
    
    Serial.print(gx); Serial.print('\t');
    Serial.print(gy); Serial.print('\t');
    Serial.print(gz); Serial.print('\t');
    
    Serial.print(frontLeftValue); Serial.print('\t');
    Serial.print(frontRightValue); Serial.print('\t');
    Serial.print(rearValue); Serial.print('\t');
    Serial.println();
    
    Serial.print(frontLeftValue); Serial.print('\t');
    Serial.print(frontRightValue); Serial.print('\t');
    Serial.print(rearValue); Serial.print('\t');
    Serial.print(yawCommand); Serial.print('\t');
    Serial.println();
    */
  }else{
    if(leftServo.readMicroseconds() != MINCOMMAND)
      leftServo.writeMicroseconds(MINCOMMAND);
    if(rightServo.readMicroseconds() != MINCOMMAND)
      rightServo.writeMicroseconds(MINCOMMAND);
    if(rearServo.readMicroseconds() != MINCOMMAND)
      rearServo.writeMicroseconds(MINCOMMAND);
  }
  
}

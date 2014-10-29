PIDdata pidRateRoll;
PIDdata pidRatePitch;
PIDdata pidRateYaw;

PIDdata pidStableRoll;
PIDdata pidStablePitch;
PIDdata pidStableYaw;

void controllerSetup(){
  //PID VALUES
  pidRateRoll.P = ROLL_PITCH_P;
  pidRateRoll.I = ROLL_PITCH_I;
  pidRateRoll.D = ROLL_PITCH_D;
  pidRateRoll.lastError = 0;
  pidRateRoll.previousPIDTime = 0;
  pidRateRoll.integratedError = 0;
  pidRateRoll.pGuard = ROLL_PITCH_P_GUARD;
  pidRateRoll.windupGuard = ROLL_PITCH_I_GUARD;
  
  pidRatePitch.P = ROLL_PITCH_P;
  pidRatePitch.I = ROLL_PITCH_I;
  pidRatePitch.D = ROLL_PITCH_D;
  pidRatePitch.lastError = 0;
  pidRatePitch.previousPIDTime = 0;
  pidRatePitch.integratedError = 0;
  pidRatePitch.pGuard = ROLL_PITCH_P_GUARD;
  pidRatePitch.windupGuard = ROLL_PITCH_I_GUARD;
  
  pidRateYaw.P = YAW_P;
  pidRateYaw.I = YAW_I;
  pidRateYaw.D = YAW_D;
  pidRateYaw.lastError = 0;
  pidRateYaw.previousPIDTime = 0;
  pidRateYaw.integratedError = 0;
  pidRateYaw.pGuard = 1000;
  pidRateYaw.windupGuard = 1000;
  
  pidStableRoll.P = 1;
  pidStableRoll.I = 0;
  pidStableRoll.D = 0;
  pidStableRoll.lastError = 0;
  pidStableRoll.previousPIDTime = 0;
  pidStableRoll.integratedError = 0;
  pidStableRoll.pGuard = 100;
  pidStableRoll.windupGuard = 500;
  
  pidStablePitch.P = 1;
  pidStablePitch.I = 0;
  pidStablePitch.D = 0;
  pidStablePitch.lastError = 0;
  pidStablePitch.previousPIDTime = 0;
  pidStablePitch.integratedError = 0;
  pidStablePitch.pGuard = 100;
  pidStablePitch.windupGuard = 500;
}

float yawSmooth;
//Low pass filter
//http://playground.arduino.cc/main/smooth
int smooth(int data, float filterVal, float smoothedVal){
  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}

double getExpo(long input, float expo, int deviation){
  float expoPitch = map(input, 1000, 2000, -1000, 1000) / 1000.0;
  if(expoPitch >= 0)
    return pow(abs(expoPitch), expo) * deviation;
  return -pow(abs(expoPitch), expo) * deviation;
}

//http://aeroquad.com/showthread.php?1167-Stable-Mode-Explained
void controllerLoop(){
  
  //Stable mode if not switched
  stableMode = 1400 < aux1.getValue() && 1600 > aux1.getValue();
  
  //Controls are backwards
  //Apply exponentials, more sensitive controls around centered sticks
  targetYaw = getExpo(rudder.getScaledValue(), EXPO_YAW, 360);
  targetPitch = -getExpo(elevator.getScaledValue(), EXPO_ROLL_PITCH, 55);
  targetRoll = -getExpo(aileron.getScaledValue(), EXPO_ROLL_PITCH, 55);
  
  //Override when signal is not present
  if(!signalPresent){
    stableMode = 1;
    targetYaw = 0;
    targetPitch = 0;
    targetRoll = 0;
  }
  
  if(stableMode){
    //Stable mode input
    outputRoll = updatePID(targetRoll, yprAngle[2], &pidStableRoll);
    outputPitch = updatePID(targetPitch, yprAngle[1], &pidStablePitch);
    //Gyro
    outputRoll = updatePID(outputRoll, -gx, &pidRateRoll);
    outputPitch = updatePID(outputPitch, gy, &pidRatePitch);
    outputYaw = updatePID(targetYaw, -gz, &pidRateYaw);
  }else{
    outputRoll = updatePID(targetRoll, -gx, &pidRateRoll);
    outputPitch = updatePID(targetPitch, gy, &pidRatePitch);
    outputYaw = updatePID(targetYaw, -gz, &pidRateYaw);
  }
  
  //ADD LOW PASS FILTER TO SERVO
  //Without this, the rear servo will jitter on tricopters
  outputYaw = smooth(outputYaw, SERVO_FILTER, yawSmooth);
  
  outputRoll = constrain(outputRoll, -300, 300);
  outputPitch = constrain(outputPitch, -300, 300);
  outputYaw = constrain(outputYaw, -320, 320);
}

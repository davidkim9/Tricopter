PIDdata pidRateRoll;
PIDdata pidRatePitch;
PIDdata pidRateYaw;

PIDdata pidStableRoll;
PIDdata pidStablePitch;
PIDdata pidStableYaw;

void controllerSetup(){
  pidRateRoll.P = 1;
  pidRateRoll.I = 0.7;
  pidRateRoll.D = -2;
  pidRateRoll.lastError = 0;
  pidRateRoll.previousPIDTime = 0;
  pidRateRoll.integratedError = 0;
  pidRateRoll.windupGuard = 500;
  
  pidRatePitch.P = 1;
  pidRatePitch.I = 0.7;
  pidRatePitch.D = -2;
  pidRatePitch.lastError = 0;
  pidRatePitch.previousPIDTime = 0;
  pidRatePitch.integratedError = 0;
  pidRatePitch.windupGuard = 500;
  
  pidRateYaw.P = 2;
  pidRateYaw.I = 1.5;
  pidRateYaw.D = -3;
  pidRateYaw.lastError = 0;
  pidRateYaw.previousPIDTime = 0;
  pidRateYaw.integratedError = 0;
  pidRateYaw.windupGuard = 500;
  
  pidStableRoll.P = 0.5;
  pidStableRoll.I = 0;
  pidStableRoll.D = 0;
  pidStableRoll.lastError = 0;
  pidStableRoll.previousPIDTime = 0;
  pidStableRoll.integratedError = 0;
  pidStableRoll.windupGuard = 500;
  
  pidStablePitch.P = 0.5;
  pidStablePitch.I = 0;
  pidStablePitch.D = 0;
  pidStablePitch.lastError = 0;
  pidStablePitch.previousPIDTime = 0;
  pidStablePitch.integratedError = 0;
  pidStablePitch.windupGuard = 500;
}

//http://aeroquad.com/showthread.php?1167-Stable-Mode-Explained
void controllerLoop(){
  //Controls are backwards
  targetYaw = map(rudder.getScaledValue(), 1000, 2000, -180, 180);
  targetPitch = map(elevator.getScaledValue(), 1000, 2000, 45, -45);
  targetRoll = map(aileron.getScaledValue(), 1000, 2000, 45, -45);
  /*
  targetYaw = 0;
  targetPitch = 0;
  targetRoll = 0;
  
  //Stable mode input
  targetRoll = updatePID(targetRoll, yprAngle[2], &pidStableRoll);
  targetPitch = updatePID(targetPitch, yprAngle[1], &pidStablePitch);
  */
  outputRoll = updatePID(targetRoll, -gx, &pidRateRoll);
  outputPitch = updatePID(targetPitch, gy, &pidRatePitch);
  outputYaw = updatePID(targetYaw, gz, &pidRateYaw);
  
  outputRoll = constrain(outputRoll, -200, 200);
  outputPitch = constrain(outputPitch, -200, 200);
  outputYaw = constrain(outputYaw, -300, 300);
}

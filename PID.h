#ifndef _PID_h
#define _PID_h

//// PID Variables
struct PIDdata {
  double P, I, D;
  double lastError;
  // AKA experiments with PID
  double previousPIDTime;
  double integratedError;
  double windupGuard;
};

double updatePID(double targetPosition, double currentPosition, struct PIDdata *PIDparameters) {

  // AKA PID experiments
  const double deltaPIDTime = (currentTime - PIDparameters->previousPIDTime) / 1000000.0;

  PIDparameters->previousPIDTime = currentTime;  // AKA PID experiments
  double error = targetPosition - currentPosition;

  if (inFlight) {
    PIDparameters->integratedError += error * deltaPIDTime;
  } else {
    PIDparameters->integratedError = 0.0;
  }
  
  PIDparameters->integratedError = constrain(PIDparameters->integratedError, -PIDparameters->windupGuard, PIDparameters->windupGuard);
  double dTerm = PIDparameters->D * (currentPosition - PIDparameters->lastError) / (deltaPIDTime * 100); // dT fix from Honk
  PIDparameters->lastError = currentPosition;

  return (PIDparameters->P * error) + (PIDparameters->I * PIDparameters->integratedError) + dTerm;
}

#endif

#include <Arduino.h>
#include <PID_v1.h>
#include "pid_control.h"

// === Variables globales del PID (declaradas en arduino.ino) ===
extern PID myPID;
extern double Input;
extern double Output;
extern double Setpoint;

double calculatePID(float temp) {
  Input = temp;
  myPID.Compute();
  if (Output < 0) Output = 0;
  if (Output > 100) Output = 100;
  return Output;
}

double getSetpoint() {
  return Setpoint;
}
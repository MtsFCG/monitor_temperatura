#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <PID_v1.h>

extern PID myPID;

double calculatePID(float temp);
double getSetpoint();

#endif
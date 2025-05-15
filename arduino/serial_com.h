#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include <Arduino.h>

void serialEvent();
String checkSerialCommand();
void handleSerialCommand(String command);

extern double Setpoint;

#endif

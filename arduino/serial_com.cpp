#include "serial_com.h"
#include <Arduino.h>
#include "defines.h"
String inputString = "";
bool stringComplete = false;

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') stringComplete = true;
  }
}

String checkSerialCommand() {
  if (stringComplete) {
    String cmd = inputString;
    inputString = "";
    stringComplete = false;
    return cmd;
  }
  return "";
}

void handleSerialCommand(String command) {
  if (command.startsWith("SETPOINT ")) {
    String valueStr = command.substring(9);
    valueStr.trim();
    if (valueStr.toFloat() >= 10 && valueStr.toFloat() <= 40) {
      Setpoint = valueStr.toFloat();
      Serial.print("Nuevo Setpoint: ");
      Serial.println(Setpoint);
    } else {
      Serial.println("Setpoint fuera de rango (10 - 40)");
    }
  }
}

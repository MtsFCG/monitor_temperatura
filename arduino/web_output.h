#ifndef WEB_OUTPUT_H
#define WEB_OUTPUT_H

#include <Arduino.h>

void enviarJSON(
  float temp_actual, float humedad,
  double setpoint, double pid_output,
  bool r1, bool r2, int zona,
  const char* mensaje_estado = "",
  const char* error_code = nullptr,
  const char* error_message = nullptr,
  const char* error_details = nullptr,
  const char* error_level = nullptr
);

#endif
#include <Arduino.h>
#include "web_output.h"
#include "defines.h"

// Devuelve el valor exacto de millis() como unsigned long
unsigned long obtenerTimestamp() {
  return millis();
}

void enviarJSON(
  float temp_actual, float humedad,
  double setpoint, double pid_output,
  bool r1, bool r2, int zona,
  const char* mensaje_estado,
  const char* error_code,
  const char* error_message,
  const char* error_details,
  const char* error_level
) {
  // Buffers temporales para convertir números con decimales
  char tempStr[10], humStr[10];
  char spStr[10], outStr[10];
  char kpStr[10], kiStr[10], kdStr[10];

  dtostrf(temp_actual, 6, 2, tempStr);     // Formato: "25.50"
  dtostrf(humedad, 6, 2, humStr);
  dtostrf(setpoint, 6, 2, spStr);
  dtostrf(pid_output, 6, 2, outStr);
  dtostrf(Kp, 6, 2, kpStr);
  dtostrf(Ki, 6, 2, kiStr);
  dtostrf(Kd, 6, 2, kdStr);

  // Buffer general del JSON
  char json[512];

  // Buffer para el timestamp
  char timestampStr[15];
  sprintf(timestampStr, "%lu", obtenerTimestamp());

  if (error_code != nullptr) {
    snprintf_P(json, sizeof(json), PSTR(
      "{"
        "\"timestamp\": %s,"
        "\"status\": \"error\","
        "\"error\": {"
          "\"code\": \"%s\","
          "\"message\": \"%s\","
          "\"details\": \"%s\","
          "\"level\": \"%s\""
        "},"
        "\"data\": {"
          "\"temp_actual\": null,"
          "\"humedad\": null,"
          "\"setpoint\": %.2f,"
          "\"pid_output\": %.2f,"
          "\"Kp\": %s,"
          "\"Ki\": %s,"
          "\"Kd\": %s,"
          "\"relay1\": %s,"
          "\"relay2\": %s,"
          "\"zona\": %d"
        "},"
        "\"meta\": {"
          "\"baud_rate\": 9600,"
          "\"version_firmware\": \"1.0.0\","
          "\"dispositivo\": \"calentador-r1175\""
        "}"
      "}"),
      timestampStr,
      error_code, error_message, error_details, error_level,
      setpoint, pid_output,
      kpStr, kiStr, kdStr,
      r1 ? "true" : "false", r2 ? "true" : "false", zona);

  } else {
    snprintf_P(json, sizeof(json), PSTR(
      "{"
        "\"timestamp\": %s,"
        "\"status\": \"ok\","
        "\"error\": null,"
        "\"data\": {"
          "\"temp_actual\": %s,"
          "\"humedad\": %s,"
          "\"setpoint\": %s,"
          "\"pid_output\": %s,"
          "\"Kp\": %s,"
          "\"Ki\": %s,"
          "\"Kd\": %s,"
          "\"relay1\": %s,"
          "\"relay2\": %s,"
          "\"zona\": %d,"
          "\"mensaje_estado\": \"%s\""
        "},"
        "\"meta\": {"
          "\"baud_rate\": 9600,"
          "\"version_firmware\": \"1.0.0\","
          "\"dispositivo\": \"calentador-r1175\""
        "}"
      "}"),
      timestampStr,
      tempStr, humStr, spStr, outStr,
      kpStr, kiStr, kdStr,
      r1 ? "true" : "false", r2 ? "true" : "false", zona,
      mensaje_estado);
  }

  Serial.println(json);
}
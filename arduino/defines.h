#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>

// Pines
#define RELAY1_PIN 2
#define RELAY2_PIN 3

// Constantes del sistema
extern const double ZONA_1_MIN;
extern const double ZONA_2_MIN;
extern const double ZONA_3_MIN;

// Parámetros PID
extern const double Kp;
extern const double Ki;
extern const double Kd;

// Estado de relés
extern bool relay1_estado;
extern bool relay2_estado;

#endif
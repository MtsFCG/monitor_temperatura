#ifndef RELAY_CONTROL_H
#define RELAY_CONTROL_H

#include <Arduino.h>

// Extern declarations
extern bool relay1_estado;
extern bool relay2_estado;

void initRelays();
void updateRelays(double output);
int getZonaActual(double output);

#endif
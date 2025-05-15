#include <Arduino.h>
#include <PID_v1.h>
#include "relay_control.h"
#include "defines.h"

void initRelays() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH); // Apagado inicial (lógica invertida)
  digitalWrite(RELAY2_PIN, LOW); // Apagado inicial
}

void updateRelays(double output) {
  int zona = getZonaActual(output);

  if (zona == 0) {
    if (relay1_estado == false || relay2_estado == true) {
      digitalWrite(RELAY1_PIN, HIGH);
      digitalWrite(RELAY2_PIN, LOW);
      relay1_estado = HIGH;
      relay2_estado = LOW;
    }
  } else if (zona == 1) {
    if (relay1_estado == HIGH) {
      digitalWrite(RELAY1_PIN, LOW);
      relay1_estado = LOW;
    }
    if (relay2_estado == HIGH) {
      digitalWrite(RELAY2_PIN, LOW);
      relay2_estado = LOW;
    }
  } else if (zona == 2) {
    if (relay1_estado == HIGH) {
      digitalWrite(RELAY1_PIN, LOW);
      relay1_estado = LOW;
    }
    if (relay2_estado == LOW) {
      digitalWrite(RELAY2_PIN, HIGH);
      relay2_estado = HIGH;
    }
  } else {
    if (relay1_estado == HIGH) {
      digitalWrite(RELAY1_PIN, LOW);
      relay1_estado = LOW;
    }
    if (relay2_estado == LOW) {
      digitalWrite(RELAY2_PIN, HIGH);
      relay2_estado = HIGH;
    }
  }
}

int getZonaActual(double output) {
  if (output <= ZONA_1_MIN) return 0;
  if (output <= ZONA_2_MIN) return 1;
  if (output <= ZONA_3_MIN) return 2;
  return 3;
}
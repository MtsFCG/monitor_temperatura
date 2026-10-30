#include <Arduino.h>
#include <DHT.h>
#include "sensor_dht.h"

extern DHT dht;

float readTemperature() {
  return dht.readTemperature();
}

float readHumidity() {
  return dht.readHumidity();
}
#include <Arduino.h>
#include <PID_v1.h>
#include <DHT.h>
#include "defines.h"

// === Definiciones compartidas ===
#define RELAY1_PIN 2
#define RELAY2_PIN 3
#define DHTPIN 4
#define DHTTYPE DHT11

// === Variables globales ===
double Setpoint = 25.0;
double Input;
double Output;

const double Kp = 3.5;
const double Ki = 0.2;
const double Kd = 2.0;

// === Objetos ===
DHT dht(DHTPIN, DHTTYPE);
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// === Zonas térmicas ===
const double ZONA_1_MIN = 2.0;
const double ZONA_2_MIN = 50.0;
const double ZONA_3_MIN = 80.0;

// === Estados de relés ===
bool relay1_estado = HIGH;
bool relay2_estado = LOW;

// === Declaraciones de funciones externas ===
void initRelays();
void updateRelays(double output);
int getZonaActual(double output);
void enviarJSON(float temp_actual, float humedad, double setpoint, double pid_output, bool r1, bool r2, int zona, const char* mensaje_estado, const char* error_code = NULL, const char* error_message = NULL, const char* error_details = NULL, const char* error_level = NULL);
float readTemperature();
float readHumidity();
String obtenerTimestamp();

void setup() {
  Serial.begin(9600);
  dht.begin();
  initRelays();
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 100);
}

void loop() {
  float temperature = readTemperature();
  float humidity = readHumidity();

  if (isnan(temperature)) {
    enviarJSON(
      temperature, humidity,
      Setpoint, Output,
      relay1_estado, relay2_estado,
      getZonaActual(Output),
      "Error al leer el sensor DHT11",
      "DHT_READ_FAILED", 
      "Error al leer el sensor DHT11", 
      "Sensor desconectado o timeout", 
      "critical"
    );
    return;
  }

  Input = temperature;
  myPID.Compute();
  Output = constrain(Output, 0, 100);
  updateRelays(Output);

  const char* mensaje_estado = "";
  int zona = getZonaActual(Output);
  switch(zona) {
    case 0: mensaje_estado = "Zona 0: Sin calefacción necesaria"; break;
    case 1: mensaje_estado = "Zona 1: Solo primer nivel encendido"; break;
    case 2: mensaje_estado = "Zona 2: Ambos niveles encendidos"; break;
    case 3: mensaje_estado = "Zona 3: Máxima potencia. ¡Posible fallo o ambiente muy frío!"; break;
    default: mensaje_estado = "Zona desconocida";
  }

  enviarJSON(
    temperature, humidity,
    Setpoint, Output,
    relay1_estado, relay2_estado,
    zona, mensaje_estado
  );

  delay(2000);
}
//Control de ventilación (temperatura)
//- El valor de referencia de temperatura se establecerá mediante el potenciómetro.
//- Si la temperatura medida supera el valor de referencia → encender un LED indicando que
//el sistema de ventilación se activó.

// Potenciometro.cpp
#include "Potenciometro.h"

Potenciometro::Potenciometro(int pinAnalogico, float minValor, float maxValor) {
  pin = pinAnalogico;
  minTemp = minValor;
  maxTemp = maxValor;
}

void Potenciometro::init() {
  pinMode(pin, INPUT);
}

float Potenciometro::leerTemperaturaReferencia() {
  int lectura = analogRead(pin); // valor de 0 a 4095 en ESP32
  float referencia = map(lectura, 0, 4095, minTemp * 10, maxTemp * 10); 
  return referencia / 10.0; // lo devuelvo como float
}

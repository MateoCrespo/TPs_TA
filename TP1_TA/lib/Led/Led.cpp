// Led.cpp
#include "Led.h"

Led::Led(int pin) {
  pinLed = pin;
  tiempoAnterior = 0;
  estado = LOW;
}

void Led::init() {
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);
}

void Led::encender() {
  digitalWrite(pinLed, HIGH);
  estado = HIGH;
}

void Led::apagar() {
  digitalWrite(pinLed, LOW);
  estado = LOW;
}

void Led::parpadear(unsigned long intervalo) {
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    estado = !estado;
    digitalWrite(pinLed, estado);
    tiempoAnterior = tiempoActual;
  }
}

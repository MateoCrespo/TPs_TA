#include "Boton.h"

Boton::Boton(int pin) {
  _pinBTN = pin;
  _ultimoEstado = HIGH; // con pull-up interno, HIGH = no presionado
}

void Boton::begin() {
  pinMode(_pinBTN, INPUT_PULLUP); // usamos resistencia pull-up interna
}

bool Boton::estaPulsado() {
  return (digitalRead(_pinBTN) == LOW); // LOW = presionado
}


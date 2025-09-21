#include "Boton.h"

Boton::Boton(int pin) {
  _pinBTN = pin;
  _ultimoEstado = HIGH; // con pull-up, HIGH = no presionado
}

void Boton::begin() {
  pinMode(_pinBTN, INPUT_PULLUP);
}

bool Boton::fuePresionado() {
  bool estadoActual = digitalRead(_pinBTN);
  bool resultado = false;

  if (_ultimoEstado == HIGH && estadoActual == LOW) {
    // Se detectó una transición: botón recién presionado
    resultado = true;
  }

  _ultimoEstado = estadoActual; // actualizar estado
  return resultado;
}

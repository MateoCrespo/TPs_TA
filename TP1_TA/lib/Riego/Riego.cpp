#include <Arduino.h>
#include "Riego.h"

Riego::Riego(int pinLed) {
    ledPin = pinLed;
    pinMode(ledPin, OUTPUT);
    riegoEncendido = false;
    tiempoAnterior = 0;
    umbral = 50.0; // ejemplo
}


void Riego::init() {
    digitalWrite(ledPin, LOW); // arranca apagado
}

void Riego::actualizar(float humedadActual) {
    if (humedadActual < umbral) {
        digitalWrite(ledPin, HIGH);
        riegoEncendido = true;
    } else {
        digitalWrite(ledPin, LOW);
        riegoEncendido = false;
    }
}

float Riego::getHumedadUmbral() {
    return umbral;
}

bool Riego::getRiegoActivo() {
    return riegoEncendido;
}
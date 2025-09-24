#include "Buzzer.h"

Buzzer::Buzzer(int pinBuzzer) {
  pin = pinBuzzer;
}

void Buzzer::init() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Buzzer::encender() {
  digitalWrite(pin, HIGH);
  tone(pin, 1000); // Emitir tono de 1000 Hz
}

void Buzzer::apagar() {
  digitalWrite(pin, LOW);
}

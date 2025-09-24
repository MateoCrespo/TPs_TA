#include "Buzzer.h"

Buzzer::Buzzer(int pinBuzzer) {
  pin = pinBuzzer;
}

void Buzzer::init() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Buzzer::encender() {
  tone(pin, 1000);
}

void Buzzer::apagar() {
  noTone(pin);
}

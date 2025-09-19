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
}

void Buzzer::apagar() {
  digitalWrite(pin, LOW);
}

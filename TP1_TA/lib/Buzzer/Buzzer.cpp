#include "Buzzer.h"

Buzzer::Buzzer(int pinBuzzer) {
  pin = pinBuzzer;
}

void Buzzer::init() {
  pinMode(pin, OUTPUT);
  ledcSetup(0, 1000, 8);       // canal, frecuencia inicial, resolución
  ledcAttachPin(pin, 0);     
}

void Buzzer::encender() {
  ledcWriteTone(0, 1000); // canal y frecuencia en Hz
}

void Buzzer::apagar() {
  ledcWriteTone(0, 0);          // corta el tono
}

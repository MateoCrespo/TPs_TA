// Potenciometro.h
#ifndef POTENCIOMETRO_H
#define POTENCIOMETRO_H

#include <Arduino.h>

class Potenciometro {
  public:
    Potenciometro(int pinAnalogico, float minValor = -40.0, float maxValor = 80.0);
    void init();
    float leerTemperaturaReferencia();

    // Leer voltaje directo (0-3.3V) para el comando /potc
    float leerVoltaje();

  private:
    int pin;
    float minTemp;
    float maxTemp;
};

#endif

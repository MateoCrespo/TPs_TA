#ifndef BOTON_H
#define BOTON_H

#include <Arduino.h>

class Boton {
  public:
    Boton(int pinBTN);

    void begin();               // Inicializa el pin
    bool fuePresionado();       // Devuelve true SOLO cuando se detecta un flanco (pulsación)

  private:
    int _pinBTN;
    bool _ultimoEstado;
};

#endif

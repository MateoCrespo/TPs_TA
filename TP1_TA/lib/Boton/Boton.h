#ifndef BOTON_H
#define BOTON_H

#include <Arduino.h>

class Boton {
  public:
    Boton(int pinBTN);

    void begin();          // Inicializa el pin
    bool estaPulsado();      // Devuelve true si el botón está presionado
 
  private:
    int _pinBTN;
    bool _ultimoEstado;
};

#endif

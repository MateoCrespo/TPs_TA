#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
  public:
    Led(int pin);
    void init();
    void encender();
    void apagar();
    void parpadear(unsigned long intervalo = 200);

  private:
    int pinLed;
    unsigned long tiempoAnterior;
    bool estado;
};

#endif

#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
  public:
    Buzzer(int pin);
    void init();
    void encender();
    void apagar();

  private:
    int pin;
};

#endif

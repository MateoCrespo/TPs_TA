#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
  private:
    int pin;
    
  public:
    Buzzer(int pinBuzzer);
    void init();
    void encender();
    void apagar();
};

#endif

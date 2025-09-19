#ifndef RIEGO_H
#define RIEGO_H

#include <Arduino.h>
#include "Led.h"

class Riego {
  public:
    Riego();   
    void init();               // Inicializa el sistema de riego
    float getHumedadUmbral();  // Devuelve el umbral generado

  private: 
    float umbral;              // Umbral aleatorio generado
};

#endif

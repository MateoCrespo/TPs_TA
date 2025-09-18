#ifndef SENSOR_T_H
#define SENSOR_T_H

#include <Arduino.h>
#include "DHTesp.h" // Librería para sensores DHT

class SensorT_H {
  public:
    SensorT_H(int pinDHT);

   void begin();         // Inicializar el sensor
    void updateValues();  // Actualizar valores de temperatura y humedad

    float getTemp();      // Obtener última temperatura
    float getHum();       // Obtener última humedad

  private:
    int _pinDHT;
    float _temp;
    float _hum;
    DHTesp* _dht; 
};

#endif
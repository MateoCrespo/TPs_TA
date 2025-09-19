#ifndef SENSOR_T_H
#define SENSOR_T_H

#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <DHT.h> // Librería para sensores DHT

class SensorT_H {
  public:
    SensorT_H(int pinDHT, int sensorType);

   void begin();         // Inicializar el sensor
   // void updateValues();  // Actualizar valores de temperatura y humedad

    float getTemp();      // Obtener última temperatura
    float getHum();       // Obtener última humedad

  private:
    int _pinDHT;
    int _sensorType;
    float _temp;
    float _hum;
    DHT _dht; 
};

#endif
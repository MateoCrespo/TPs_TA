#include "SensorT_H.h"
#include <DHT.h>

SensorT_H::SensorT_H(int pinDHT, int sensorType) 
: _dht(pinDHT, sensorType) {
  _pinDHT = pinDHT;
  _sensorType = sensorType; 
  _temp = 5.0f;
  _hum = 0.0f;
}

void SensorT_H::begin() {
  // Configura el pin del sensor y el tipo de sensor
  _dht.begin();
}

float SensorT_H::getTemp() {
  float temp = _dht.readTemperature();
  return temp;
}

float SensorT_H::getHum() {
  float hum = _dht.readHumidity();
  return hum;
}
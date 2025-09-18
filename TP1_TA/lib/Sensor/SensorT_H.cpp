#include "SensorT_H.h"
#include "DHTesp.h"

SensorT_H::SensorT_H(int pinDHT) {
  _pinDHT = pinDHT;
  _dht = new DHTesp(); // ¡Cambia esto!
  _temp = 0.0f;
  _hum = 0.0f;
}

void SensorT_H::begin() {
  // Configura el pin del sensor y el tipo de sensor
  _dht->setup(_pinDHT, DHTesp::DHT22);
}

void SensorT_H::updateValues() {
  TempAndHumidity data = _dht->getTempAndHumidity();

  // Verifica si las lecturas son válidas antes de actualizarlas
  if (!isnan(data.temperature)) {
    _temp = data.temperature;
  }
  if (!isnan(data.humidity)) {
    _hum = data.humidity;
  }
}

float SensorT_H::getTemp() {
  return _temp;
}

float SensorT_H::getHum() {
  return _hum;
}
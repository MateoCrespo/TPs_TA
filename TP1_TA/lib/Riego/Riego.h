#ifndef RIEGO_H   // <-- esto faltaba
#define RIEGO_H

#include <Arduino.h>

// Definición de la clase Riego
class Riego {
  public:
    Riego(int pinLed);
    void init(); // Inicializa el pin del LED
    void actualizar(float humedadActual);// Actualiza el estado del riego según la humedad actual
    float getHumedadUmbral();// Devuelve el umbral de humedad
    bool getRiegoActivo();// Devuelve si el riego está activo o no

  private:
    int ledPin;
    const unsigned long intervalo = 500; // Intervalo de tiempo para el riego (500 ms)
    unsigned long tiempoAnterior; // Variable para almacenar el tiempo anterior
    bool riegoEncendido;// Estado actual del riego
    float umbral;// Umbral de humedad para activar el riego
};

#endif

#ifndef PANTALLA_OLED_H
#define PANTALLA_OLED_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

class PantallaOLED {
  public:
    PantallaOLED(int w, int h, int reset);

    void init();                                // Inicializar pantalla
    void mostrarDatosTempHum(float temp, float hum); // Mostrar datos
    void showDisplay(const char* text);          // Mostrar texto

  private:
    int width, height, resetPin;                // Parámetros de pantalla
    Adafruit_SH1106G display;                   // Objeto de la librería
};

#endif

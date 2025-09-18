#include "PantallaOLED.h"

// Constructor: inicializa el objeto "display" con los parámetros
PantallaOLED::PantallaOLED(int w, int h, int reset): display(w, h, &Wire, reset) {
  width = w;
  height = h;
  resetPin = reset;
}

// Inicializar pantalla
void PantallaOLED::init() {
  display.begin(0x3C, true);  // Dirección I2C típica del SH1106
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Pantalla lista");
  display.display();
  delay(1000);
}

// Mostrar temperatura y humedad
void PantallaOLED::mostrarDatosTempHum(float temp, float hum) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 10);
  display.print("Hum: ");
  display.print(hum);
  display.println(" %");

  display.display();
}

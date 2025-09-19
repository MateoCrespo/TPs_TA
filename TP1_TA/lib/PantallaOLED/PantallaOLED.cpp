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
}

void PantallaOLED::showDisplay(const char* text) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(text);
  display.display();
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

void PantallaOLED::mostrarPantalla1(float temp, float tempReferencia, boolean estadoVentilacion) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.print("Temperatura:");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 20);
  display.print("Temp Referencia: ");
  display.setCursor(0, 30);
  display.print(tempReferencia);
  display.println(" C");

  display.setCursor(0, 50);
  display.print("Estado Ventilacion: ");
  display.setCursor(0, 60);
  display.print(estadoVentilacion ? "Encendido" : "Apagado");

  display.display();
}

void PantallaOLED::mostrarPantalla2(float hum, float humReferencia, boolean estadoRiego) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  
  display.setCursor(0, 0);
  display.print("Humedad: ");
  display.print(hum);
  display.println("%");

  display.setCursor(0, 20);
  display.print("Humedad Referencia: ");
  display.setCursor(0, 30);
  display.print(humReferencia);
  display.println("%");

  display.setCursor(0, 50);
  display.print("Estado Riego: ");
  display.setCursor(0, 60);
  display.print(estadoRiego ? "Encendido" : "Apagado");

  display.display();
}

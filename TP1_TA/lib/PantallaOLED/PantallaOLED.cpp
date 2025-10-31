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

  display.setCursor(0, 40);
  display.print("Estado Ventilacion: ");
  display.setCursor(0, 50);
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
  display.print("Humedad Refe: ");
  display.setCursor(0, 30);
  display.print(humReferencia);
  display.println("%");

  display.setCursor(0, 40);
  display.print("Estado Riego: ");
  display.setCursor(0, 50);
  display.print(estadoRiego ? "Encendido" : "Apagado");

  display.display();
}

// ===== MÉTODOS NUEVOS PARA TELEGRAM =====

// Mostrar estado de los LEDs en pantalla
void PantallaOLED::mostrarEstadoLeds(bool ledVerde, bool ledAzul) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  
  display.setCursor(0, 0);
  display.println("=== ESTADO LEDS ===");
  
  display.setCursor(0, 20);
  display.print("LED Verde (23): ");
  display.println(ledVerde ? "ON" : "OFF");
  
  display.setCursor(0, 35);
  display.print("LED Azul (2): ");
  display.println(ledAzul ? "ON" : "OFF");
  
  display.display();
}

// Mostrar datos del sensor DHT22
void PantallaOLED::mostrarDatosSensor(float temp, float hum) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  
  display.setCursor(0, 0);
  display.println("=== SENSOR DHT22 ===");
  
  display.setCursor(0, 20);
  display.print("Temperatura: ");
  display.print(temp, 1);
  display.println(" C");
  
  display.setCursor(0, 35);
  display.print("Humedad: ");
  display.print(hum, 1);
  display.println(" %");
  
  display.display();
}

// Mostrar voltaje del potenciómetro
void PantallaOLED::mostrarVoltaje(float voltaje) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  
  display.setCursor(0, 0);
  display.println("=== POTENCIOMETRO ===");
  
  display.setCursor(0, 25);
  display.print("Voltaje: ");
  display.print(voltaje, 2);
  display.println(" V");
  
  display.display();
}

// Mostrar mensaje personalizado (para /displayMensaje)
void PantallaOLED::mostrarMensajePersonalizado(String mensaje) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  
  // Dividir mensaje en líneas si es muy largo
  int startIndex = 0;
  int lineHeight = 10;
  int currentLine = 0;
  int maxLines = 6; // Aproximadamente 6 líneas en una pantalla de 64px
  
  while (startIndex < mensaje.length() && currentLine < maxLines) {
    int endIndex = startIndex + 21; // Aprox 21 caracteres por línea
    if (endIndex > mensaje.length()) {
      endIndex = mensaje.length();
    }
    
    String linea = mensaje.substring(startIndex, endIndex);
    display.println(linea);
    
    startIndex = endIndex;
    currentLine++;
  }
  
  display.display();
}
#include "PantallaOLED.h"

// Constructor: inicializa el objeto "display" con los parámetros
PantallaOLED::PantallaOLED(int w, int h, int reset): display(w, h, &Wire, reset) {
  width = w;
  height = h;
  resetPin = reset;
}

// Inicializar pantalla
void PantallaOLED::init() {
  // Inicializar I2C SOLO UNA VEZ
  Wire.begin(21, 22);  // SDA=21, SCL=22
  delay(100);
  
  Serial.println("Iniciando display SH1106...");
  
  if (!display.begin(0x3C, true)) {
    Serial.println("ERROR: No pudo inicializar pantalla!");
    return;
  }
  
  Serial.println("Pantalla OK");
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Pantalla\nlista");
  display.display();
  delay(500);
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

void PantallaOLED::showDisplay(const char* text) {
  Serial.print("Mostrando: ");
  Serial.println(text);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print(text);
  display.display();
}




#include <Arduino.h>

// Pines del circuito
// --- Sensor Temperatura DHT22 ---
#define PIN_DHT     15      // Pin de datos 
#define DHT_TYPE    DHT22    // Tipo de sensor DHT 

// --- Pantalla OLED ---
#define OLED_WIDTH   128     // Ancho de la pantalla en pixeles
#define OLED_HEIGHT   64     // Alto de la pantalla en pixeles
#define OLED_RESET   -1      // Pin de reset 
#define OLED_SDA     21      // Pin SDA (data)
#define OLED_SCL     22      // Pin SCL ( clock)

// --- Potenciómetro ---
#define POT_PIN      34   // Pin analógico del potenciómetro 

// --- LEDs indicadores ---
#define LED_VENT     25      // LED rojo → ventilador
#define LED_RIEGO    26      // LED azul → riego

// --- Botón---
#define BTN_PIN      27      // Botón 

// --- Buzzer ---
#define BUZZER_PIN 32

void escribirPantalla(String texto);


void setup() {

}

void loop() {
 
  delay(2000);  // leer cada 2s
}
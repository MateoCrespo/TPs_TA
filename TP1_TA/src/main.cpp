#include <Arduino.h>
#include <DHT.h> // Librería para sensores DHT
#include <Wire.h> // Librería para comunicación I2C
#include "SensorT_H.h"
#include "PantallaOLED.h"
#include "Riego.h"
#include "Boton.h"
#include "Potenciometro.h"
#include "Led.h"
#include "Buzzer.h"

//DEFINICIÓN DE PINES
// --- Sensor Temperatura DHT22 ---
#define PIN_DHT 14      // Pin de datos 
#define DHT_TYPE DHT22    // Tipo de sensor DHT 

// --- Pantalla OLED ---
#define OLED_WIDTH 128    // Ancho de la pantalla en pixeles
#define OLED_HEIGHT 64    // Alto de la pantalla en pixeles
#define OLED_RESET -1     // Pin de reset 
#define OLED_SDA 21      // Pin SDA (data)
#define OLED_SCL 22      // Pin SCL ( clock)

// --- Potenciómetro ---
#define POT_PIN 34   // Pin analógico del potenciómetro 

// --- LEDs indicadores ---
#define LED_VENT 25      // LED rojo → ventilador
#define LED_RIEGO 26      // LED azul → riego

// --- Botón---
#define BTN_PIN 27      // Botón 

// --- Buzzer ---
#define BUZZER_PIN 32



// DECLARACIÓN DE OBJETOS 
PantallaOLED pantalla(OLED_WIDTH, OLED_HEIGHT, OLED_RESET); // Objeto pantalla OLED
SensorT_H sensor(PIN_DHT, DHT_TYPE);  // Objeto sensor DHT22
Boton boton(BTN_PIN);          
Potenciometro potenciometro(POT_PIN);
Led ledVentilacion(LED_VENT);
Led ledRiego(LED_RIEGO);
Riego riego;
Buzzer buzzer(BUZZER_PIN);

//VARIABLES GLOBALES
int pantallaActual = 2; 
bool estadoVentilacion = false; // false = apagada, true = encendida
bool estadoRiego = false;    
int umbralInicial = 0;   // false = apagado, true = encendido

void setup() {
  Serial.begin(115200);
  delay(100);
  sensor.begin();
  boton.begin();
  pantalla.init();
  buzzer.init();
  potenciometro.init();
  ledVentilacion.init();
  ledRiego.init();
  Serial.println("Sistema iniciado.");
  umbralInicial = riego.getHumedadUmbral(); // 
  Serial.print("Umbral de riego generado: ");
  Serial.print(umbralInicial);
  Serial.println(" %");
}

// Bucle principal
void loop() {
 // sensor.updateValues(); // Actualizar valores del sensor
  char buffer[64];
  float temp = sensor.getTemp();
  float hum = sensor.getHum();
  float tempReferencia = potenciometro.leerTemperaturaReferencia(); 

  if (boton.fuePresionado()) {
    pantallaActual = pantallaActual == 1 ? 2 : 1;
    Serial.print("Evento: Cambio de pantalla -> ");
    Serial.println(pantallaActual);
  }
  
  // Muestra los valores en el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C | Humedad: ");
  Serial.print(hum);
  Serial.print(" % | Temp ref: ");
  Serial.println(tempReferencia);

  // Pantalla
  if (pantallaActual == 1){
    pantalla.mostrarPantalla1(temp, tempReferencia, estadoVentilacion);
  }
  else{
    pantalla.mostrarPantalla2(hum, umbralInicial, estadoRiego);
  }

  // --- Ventilación ---
  if (temp > tempReferencia) {
    if (!estadoVentilacion) { // solo cuando cambia
      Serial.println("Evento: Ventilador ENCENDIDO");
    }
    ledVentilacion.encender();
    estadoVentilacion = true;
  } else {
    if (estadoVentilacion) { // solo cuando cambia
      Serial.println("Evento: Ventilador APAGADO");
    }
    ledVentilacion.apagar();
    estadoVentilacion = false;
  }

  // --- Alarma (Buzzer) ---
  if (temp > 50 or temp < -10){
    buzzer.encender();
    Serial.println("Evento: Buzzer ACTIVADO (temperatura fuera de rango)");
  } else{
    buzzer.apagar();
  }

  // --- Riego ---
  if (hum < umbralInicial) {
    if (!estadoRiego) { // solo cuando cambia
      Serial.println("Evento: Riego ACTIVADO (LED intermitente)");
    }
    ledRiego.parpadear(50);
    estadoRiego = true;
  } else {
    if (estadoRiego) { // solo cuando cambia
      Serial.println("Evento: Riego DESACTIVADO");
    }
    ledRiego.apagar();
    estadoRiego = false;
  }
  
  delay(100);
}




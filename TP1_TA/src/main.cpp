#include <Arduino.h>
#include <DHT.h> // Librería para sensores DHT
#include <Wire.h> // Librería para comunicación I2C
#include "SensorT_H.h"
#include "PantallaOLED.h"
#include "Riego.h"
#include "Boton.h"

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
Riego riego(LED_RIEGO);     // Objeto riego
Boton boton(BTN_PIN);          


//VARIABLES GLOBALES
float humedadActual = 0;               // Humedad actual medida por el sensor
int pantallaActual = 2; 
void setup() {
  Serial.begin(9600);
  sensor.begin();
  pantalla.init();
  riego.init();
  boton.begin();
  Serial.println("Sistema iniciado.");
  delay(2000);
}


// Bucle principal
void loop() {
 // sensor.updateValues(); // Actualizar valores del sensor
  float temp = sensor.getTemp();
  float hum = sensor.getHum();
  float tempReferencia = 20.0;
  float humReferencia = 50.0;
  boolean estadoVentilacion = false;
  boolean estadoRiego = false;

  if (boton.estaPulsado()) {
    pantallaActual = pantallaActual == 1 ? 2 : 1;
  }

// Muestra los valores en el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C");

  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.print(" %");
  

  // Pantalla - 
  if (pantallaActual == 1){
     pantalla.mostrarPantalla1(temp, tempReferencia, estadoVentilacion);
  }
  else{
      pantalla.mostrarPantalla2(hum, humReferencia, estadoRiego);
  }
  


  // Riego - riego.actualizar(hum);

  delay(1000);
}




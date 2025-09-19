#include <Arduino.h>
#include <DHT.h> // Librería para sensores DHT
#include <Wire.h> // Librería para comunicación I2C
#include "SensorT_H.h"
#include "PantallaOLED.h"
#include "Riego.h"
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
Potenciometro potenciometro(POT_PIN);
Led ledVentilacion(LED_VENT);
Led ledRiego(LED_RIEGO);
Riego riego;
Buzzer buzzer(BUZZER_PIN);
//VARIABLES GLOBALES
float humedadActual = 0;               // Humedad actual medida por el sensor
void setup() {
  Serial.begin(9600);
  sensor.begin();
  pantalla.init();
  potenciometro.init();
  ledVentilacion.init();
  ledRiego.init();
  Serial.println("Sistema iniciado.");
  delay(2000);
}


// Bucle principal
void loop() {
 // sensor.updateValues(); // Actualizar valores del sensor
  char buffer[64]; 
  float temp = sensor.getTemp();
  float hum = sensor.getHum();
  float tempReferencia = potenciometro.leerTemperaturaReferencia();
  float umbralRiego = riego.getHumedadUmbral();
  delay(1000);

// Muestra los valores en el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C");

  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.print(" %");

  Serial.print("Temp ref: ");
  Serial.println(tempReferencia);
  // Pantalla -  
  
  pantalla.mostrarPantalla1(temp, tempReferencia, estadoVentilacion);
  delay(4000);
  pantalla.mostrarPantalla2(hum, humReferencia, estadoRiego);

  // pantalla.mostrarDatosTempHum(temp, hum);

  //Para probar si tomaba el potenciometro cambie el parametro de la temperatura
  sprintf(buffer, "Temp: %.1f C\nHum: %.1f %%", tempReferencia, hum);
  pantalla.showDisplay(buffer);

 
  if (temp > tempReferencia) {
    ledVentilacion.encender();
  } else {
    ledVentilacion.apagar();
  }
  if (temp > 50 or temp < -10){
    buzzer.encender();
  } else{
    buzzer.apagar();
  }
  // Riego - riego.actualizar(hum);
  if (humedadActual < umbralRiego) {
    ledRiego.parpadear(50);
  } else {
    ledRiego.apagar();
  }
  

  delay(500);
}




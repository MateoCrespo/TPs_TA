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
bool ventilacionEstado = false; // false = apagada, true = encendida
bool riegoEstado = false;    
int umbralInicial = 0;   // false = apagado, true = encendido

void setup() {
  Serial.begin(9600);
  delay(100);
  sensor.begin();
  boton.begin();
  pantalla.init();
  potenciometro.init();
  ledVentilacion.init();
  ledRiego.init();
  Serial.println("Sistema iniciado.");
  int umbralInicial = riego.getHumedadUmbral(); // asumo int
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
  float humReferencia = riego.getHumedadUmbral();
  float tempReferencia = potenciometro.leerTemperaturaReferencia();
  float umbralRiego = umbralInicial; // umbral fijo para riego
  bool estadoVentilacion = false; // Estado del ventilador
  bool estadoRiego = false; // Estado del sistema de riego

  if (boton.fuePresionado()) {
    pantallaActual = pantallaActual == 1 ? 2 : 1;
  }
  
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
  if (pantallaActual == 1){
    pantalla.mostrarPantalla1(temp, tempReferencia, estadoVentilacion);
  }
  else{
      pantalla.mostrarPantalla2(hum, umbralRiego, estadoRiego);
  }

  if (temp > tempReferencia) {
    ledVentilacion.encender();
    estadoVentilacion = true;
  } else {
    ledVentilacion.apagar();
    estadoVentilacion = false;
  }
  if (temp > 50 or temp < -10){
    buzzer.encender();
  } else{
    buzzer.apagar();
  }
  // Riego - riego.actualizar(hum);
  if (hum < umbralRiego) {
    ledRiego.parpadear(50);
    estadoRiego = true;
  } else {
    ledRiego.apagar();
    estadoRiego = false;
  }
  
  delay(100);

}




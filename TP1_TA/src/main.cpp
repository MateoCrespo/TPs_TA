#include <Arduino.h>
#include <HTTPClient.h>
#include "TelegramBot.h"
#include "SensorT_H.h"
#include "PantallaOLED.h"
#include "Boton.h"
#include "Potenciometro.h"
#include "Led.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


// ===== CONFIGURACIÓN DE PINES =====
// Sensor DHT22
#define PIN_DHT 12
#define DHT_TYPE DHT22

// Pantalla OLED (I2C)
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
#define OLED_SDA 21
#define OLED_SCL 22
// Potenciómetro
#define POT_PIN 34
// LEDs (según TP2)
#define LED_VERDE 23  // LED verde (GPIO 23)
#define LED_AZUL 2    // LED azul (GPIO 2)
// Botón
#define BTN_PIN 27

// ===== CONFIGURACIÓN WIFI Y TELEGRAM =====
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASS = "";
const char* BOT_TOKEN = "8288437846:AAHlPQUkgKfZKgzFh-uPugug_yZIxPcCa5I";

// ===== CONFIGURACIÓN THINGSPEAK =====
const String THINGSPEAK_API_KEY = "L0MKW3JEMF0H0RKJ";
const String THINGSPEAK_URL = "https://api.thingspeak.com/update";

// ===== DECLARACIÓN DE OBJETOS =====
TelegramBot bot(BOT_TOKEN, WIFI_SSID, WIFI_PASS, 1000);
PantallaOLED pantalla(OLED_WIDTH, OLED_HEIGHT, OLED_RESET);
SensorT_H sensor(PIN_DHT, DHT_TYPE);
Boton boton(BTN_PIN);
Potenciometro potenciometro(POT_PIN);
Led ledVerde(LED_VERDE);
Led ledAzul(LED_AZUL);


// ===== VARIABLES GLOBALES =====
bool estadoVentilacion = false;
int umbralInicial = 0;

// Estados de los LEDs para Telegram
bool estadoLedVerde = false;
bool estadoLedAzul = false;

// ===== FUNCIONES AUXILIARES =====
// Convierte un float a String con decimales específicos
String floatToString(float valor, int decimales) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%.*f", decimales, valor);
  return String(buffer);
}

// Envía datos a ThingSpeak
bool enviarAThingSpeak(float valor) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Error: WiFi desconectado");
    return false;
  }

  HTTPClient http;
  String url = THINGSPEAK_URL + "?api_key=" + THINGSPEAK_API_KEY + "&field1=" + String(valor);
  
  http.begin(url);
  int httpCode = http.GET();
  http.end();

  if (httpCode == 200) {
    Serial.println("✓ Datos enviados a ThingSpeak: " + String(valor));
    return true;
  } else {
    Serial.println("✗ Error al enviar a ThingSpeak. Código: " + String(httpCode));
    return false;
  }
}

// Procesa los comandos recibidos de Telegram
void procesarComandosTelegram(int numMensajes) {
  for (int i = 0; i < numMensajes; i++) {
    String chatId = bot.obtenerChatId(i);
    String texto = bot.obtenerTextoMensaje(i);
    Serial.println("Comando recibido: " + texto);

    // ===== COMANDO /start =====
    if (texto == "/start") {
      String mensaje = "Bienvenido al Bot TP2\n\n";
      mensaje += "*Comandos disponibles:*\n\n";
      mensaje += "*Control de LEDs:*\n";
      mensaje += "/led23on - Encender LED verde\n";
      mensaje += "/led23off - Apagar LED verde\n";
      mensaje += "/led2on - Encender LED azul\n";
      mensaje += "/led2off - Apagar LED azul\n\n";
      mensaje += "*Sensores:*\n";
      mensaje += "/dht22 - Leer temperatura y humedad\n";
      mensaje += "/potc - Leer voltaje del potenciómetro\n\n";
      mensaje += "*Display:*\n";
      mensaje += "/displayled - Mostrar estado de LEDs\n";
      mensaje += "/displaydht22 - Mostrar datos del sensor\n";
      mensaje += "/displaypote - Mostrar voltaje\n\n";
      mensaje += "*Plataforma IoT:*\n";
      mensaje += "/platiot - Enviar datos a ThingSpeak";
      bot.enviarMensaje(chatId, mensaje);
    }
    
    // ===== COMANDOS DE LEDS =====
    else if (texto == "/led23on") {
      ledVerde.encender();
      estadoLedVerde = true;
      bot.enviarMensaje(chatId, "LED verde (GPIO 23) encendido");
      Serial.println("LED verde encendido via Telegram");
    }
    else if (texto == "/led23off") {
      ledVerde.apagar();
      estadoLedVerde = false;
      bot.enviarMensaje(chatId, "LED verde (GPIO 23) apagado");
      Serial.println("LED verde apagado via Telegram");
    }
    else if (texto == "/led2on") {
      ledAzul.encender();
      estadoLedAzul = true;
      bot.enviarMensaje(chatId, "LED azul (GPIO 2) encendido");
      Serial.println("LED azul encendido via Telegram");
    }
    else if (texto == "/led2off") {
      ledAzul.apagar();
      estadoLedAzul = false;
      bot.enviarMensaje(chatId, "LED azul (GPIO 2) apagado");
      Serial.println("LED azul apagado via Telegram");
    }
    
    // ===== COMANDO /dht22 =====
    else if (texto == "/dht22") {
      float temp = sensor.getTemp();
      float hum = sensor.getHum();
      
      String mensaje = "🌡️ *Sensor DHT22:*\n";
      mensaje += "Temperatura: " + floatToString(temp, 1) + " °C\n";
      mensaje += "Humedad: " + floatToString(hum, 1) + " %";
      
      bot.enviarMensaje(chatId, mensaje);
      Serial.println("Datos DHT22 enviados via Telegram");
    }
    
    // ===== COMANDO /potc =====
    else if (texto == "/potc") {
      float voltaje = potenciometro.leerVoltaje();
      
      String mensaje = "*Potenciómetro:*\n";
      mensaje += "Voltaje: " + floatToString(voltaje, 2) + " V";
      
      bot.enviarMensaje(chatId, mensaje);
      Serial.println("Voltaje del potenciómetro enviado via Telegram");
    }
    
    // ===== COMANDOS /display =====
    else if (texto == "/displayled") {
      Serial.println("Ejecutando /displayled");
      // Mostrar estado de ambos LEDs
      pantalla.mostrarEstadoLeds(estadoLedVerde, estadoLedAzul);
      
      bot.enviarMensaje(chatId, "Estado de LEDs mostrado en pantalla OLED");
      Serial.println("Estado de LEDs mostrado en display");
    }
    else if (texto == "/displaydht22") {
      Serial.println("Ejecutando /displaydht22");
      float temp = sensor.getTemp();
      float hum = sensor.getHum();
      
      Serial.print("Temp: "); Serial.print(temp);
      Serial.print(" Hum: "); Serial.println(hum);
      
      // Usar el método específico para sensor
      pantalla.mostrarDatosSensor(temp, hum);
      
      bot.enviarMensaje(chatId, "Datos del sensor mostrados en pantalla OLED");
      Serial.println("Datos DHT22 mostrados en display");
    }
    else if (texto == "/displaypote") {
      Serial.println("Ejecutando /displaypote");
      float voltaje = potenciometro.leerVoltaje();
      
      Serial.print("Voltaje: "); Serial.println(voltaje);
      
      // Usar el método específico para voltaje
      pantalla.mostrarVoltaje(voltaje);
      
      bot.enviarMensaje(chatId, "Voltaje del potenciómetro mostrado en pantalla OLED");
      Serial.println("Voltaje mostrado en display");
    }
    
    // ===== COMANDO /platiot =====
    else if (texto == "/platiot") {
      float temp = sensor.getTemp();
      
      if (enviarAThingSpeak(temp)) {
        String mensaje = "*Datos enviados a ThingSpeak*\n";
        mensaje += "Temperatura: " + floatToString(temp, 1) + " °C";
        bot.enviarMensaje(chatId, mensaje);
      } else {
        bot.enviarMensaje(chatId, "Error al enviar datos a ThingSpeak");
      }
    }
    
    // ===== COMANDO /display NO RECONOCIDO =====
    else if (texto.startsWith("/display")) {
      pantalla.showDisplay("Comando no\nreconocido");
      bot.enviarMensaje(chatId, "Comando display no reconocido");
      Serial.println("Comando display no reconocido: " + texto);
    }
    
    // ===== COMANDO NO RECONOCIDO =====
    else {
      bot.enviarMensaje(chatId, "Comando no reconocido. Usa /start para ver los comandos disponibles.");
    }
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== INICIANDO SISTEMA ===");

  // Inicializar I2C explícitamente
  Wire.begin(OLED_SDA, OLED_SCL);
  delay(100);
  
  Serial.println("Inicializando pantalla OLED...");
  pantalla.init();
  delay(500);
  
  Serial.println("Probando escritura en pantalla...");
  pantalla.showDisplay("Iniciando...");
  delay(2000);
  
  // Inicializar componentes
  sensor.begin();
  boton.begin();
  potenciometro.init();
  ledVerde.init();
  ledAzul.init();
  Serial.println("✓ Componentes inicializados");
  
  // Inicializar Bot de Telegram (conecta WiFi)
  pantalla.showDisplay("Conectando\nWiFi...");
  delay(500);
  
  if (bot.begin()) {
    Serial.println("✓ Bot de Telegram listo");
    pantalla.showDisplay("Bot OK!\nListo");
    delay(2000);
    
    // Mensaje final
    pantalla.showDisplay("Esperando\ncomandos...");
    delay(3000);
    pantalla.showDisplay("..."); 
  } else {
    Serial.println("✗ Error al iniciar bot");
    pantalla.showDisplay("Error Bot!");
    while(1) { delay(1000); } // Detener si falla el bot
  }
  
  Serial.println("=== SISTEMA LISTO ===");
}

// ===== LOOP =====
void loop() {
  // CRÍTICO: NO actualizar la pantalla aquí
  // Solo procesar comandos de Telegram
  
  int numMensajes = bot.verificarMensajes();
  if (numMensajes > 0) {
    procesarComandosTelegram(numMensajes);
  }
  
  delay(200);
}

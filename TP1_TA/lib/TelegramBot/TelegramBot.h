
// Implementa todos los métodos declarados en el .h
// Maneja la conexión WiFi automáticamente
// Verifica mensajes nuevos cada cierto intervalo
// Envía respuestas a los usuarios
// Gestiona el certificado SSL para conexión segura con Telegram


#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TelegramBot {
private:
    // Cliente seguro para conexión HTTPS con Telegram
    WiFiClientSecure client;
    UniversalTelegramBot* bot;
    
    // Credenciales WiFi
    const char* ssid;
    const char* password;
    
    // Token del bot de Telegram
    const char* botToken;
    
    // Control de tiempo para polling (verificar mensajes nuevos)
    unsigned long tiempoAnterior;
    unsigned long intervaloChequeo; // Intervalo en milisegundos entre chequeos
    
    // ID del último chat (para respuestas)
    String ultimoChatId;

public:
    /**
     * Constructor de la clase TelegramBot
     * @param token Token del bot de Telegram (obtenido de @BotFather)
     * @param wifi_ssid Nombre de la red WiFi
     * @param wifi_pass Contraseña de la red WiFi
     * @param intervalo Intervalo de chequeo de mensajes en ms (default: 1000ms)
     */
    TelegramBot(const char* token, const char* wifi_ssid, const char* wifi_pass, unsigned long intervalo = 1000);
    
    /**
     * Inicializa la conexión WiFi y configura el bot
     * @return true si la conexión fue exitosa, false en caso contrario
     */
    bool begin();
    
    /**
     * Verifica si hay mensajes nuevos y los procesa
     * Debe llamarse continuamente en el loop()
     * @return Número de mensajes nuevos procesados
     */
    int verificarMensajes();
    
    /**
     * Envía un mensaje de texto al chat actual
     * @param mensaje Texto a enviar
     * @return true si el mensaje se envió correctamente
     */
    bool enviarMensaje(String mensaje);
    
    /**
     * Envía un mensaje a un chat específico
     * @param chatId ID del chat destino
     * @param mensaje Texto a enviar
     * @return true si el mensaje se envió correctamente
     */
    bool enviarMensaje(String chatId, String mensaje);
    
    /**
     * Obtiene el ID del último chat que envió un mensaje
     * @return String con el chat_id
     */
    String obtenerUltimoChatId();
    
    /**
     * Obtiene el último mensaje de texto recibido
     * @param index Índice del mensaje (0 = más reciente)
     * @return String con el texto del mensaje
     */
    String obtenerTextoMensaje(int index = 0);
    
    /**
     * Obtiene el chat_id de un mensaje específico
     * @param index Índice del mensaje (0 = más reciente)
     * @return String con el chat_id
     */
    String obtenerChatId(int index = 0);
    
    /**
     * Verifica si hay conexión WiFi
     * @return true si está conectado
     */
    bool estaConectado();
    
    /**
     * Obtiene el número de mensajes recibidos en el último chequeo
     * @return Cantidad de mensajes
     */
    int obtenerNumeroMensajes();

    // Destructor
    ~TelegramBot();
};

#endif
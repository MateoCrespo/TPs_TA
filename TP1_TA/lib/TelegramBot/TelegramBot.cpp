#include "TelegramBot.h"

// Constructor
TelegramBot::TelegramBot(const char* token, const char* wifi_ssid, const char* wifi_pass, unsigned long intervalo) {
    this->botToken = token;
    this->ssid = wifi_ssid;
    this->password = wifi_pass;
    this->intervaloChequeo = intervalo;
    this->tiempoAnterior = 0;
    this->ultimoChatId = "";
    
    // Inicializar el bot (se crea dinámicamente)
    this->bot = new UniversalTelegramBot(botToken, client);
}

// Destructor
TelegramBot::~TelegramBot() {
    // Liberar memoria del bot
    if (bot != nullptr) {
        delete bot;
    }
}

// Inicializa WiFi y configura el bot
bool TelegramBot::begin() {
    Serial.println("=== Iniciando Bot de Telegram ===");
    
    // CAMBIO CRÍTICO: Desactivar verificación SSL para Wokwi
    client.setInsecure();
    
    // Intentar conectar a WiFi
    Serial.print("Conectando a WiFi: ");
    Serial.println(ssid);
    
    WiFi.mode(WIFI_STA); // Modo estación (cliente)
    WiFi.begin(ssid, password);
    
    // Esperar conexión (timeout de 20 segundos)
    int intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 40) {
        delay(500);
        Serial.print(".");
        intentos++;
    }
    
    // Verificar si se conectó
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✓ WiFi conectado exitosamente");
        Serial.print("Dirección IP: ");
        Serial.println(WiFi.localIP());
        Serial.println("Bot de Telegram listo para recibir comandos");
        return true;
    } else {
        Serial.println("\n✗ Error: No se pudo conectar a WiFi");
        return false;
    }
}

// Verifica si hay mensajes nuevos
int TelegramBot::verificarMensajes() {
    // Solo verificar si pasó el intervalo de tiempo
    if (millis() - tiempoAnterior < intervaloChequeo) {
        return 0;
    }
    
    // Actualizar tiempo
    tiempoAnterior = millis();
    
    // Obtener mensajes nuevos
    int numeroMensajes = bot->getUpdates(bot->last_message_received + 1);
    
    if (numeroMensajes > 0) {
        Serial.print("Mensajes nuevos recibidos: ");
        Serial.println(numeroMensajes);
        
        // Guardar el chat_id del último mensaje
        if (numeroMensajes > 0) {
            ultimoChatId = bot->messages[0].chat_id;
        }
    }
    
    return numeroMensajes;
}

// Envía un mensaje al último chat
bool TelegramBot::enviarMensaje(String mensaje) {
    if (ultimoChatId == "") {
        Serial.println("Error: No hay chat_id disponible");
        return false;
    }
    return enviarMensaje(ultimoChatId, mensaje);
}

// Envía un mensaje a un chat específico
bool TelegramBot::enviarMensaje(String chatId, String mensaje) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Error: WiFi desconectado");
        return false;
    }
    
    bool resultado = bot->sendMessage(chatId, mensaje, "");
    
    if (resultado) {
        Serial.println("✓ Mensaje enviado correctamente");
    } else {
        Serial.println("✗ Error al enviar mensaje");
    }
    
    return resultado;
}

// Obtiene el ID del último chat
String TelegramBot::obtenerUltimoChatId() {
    return ultimoChatId;
}

// Obtiene el texto de un mensaje específico
String TelegramBot::obtenerTextoMensaje(int index) {
    if (bot->messages[index].text != "") {
        return bot->messages[index].text;
    }
    return "";
}

// Obtiene el chat_id de un mensaje específico
String TelegramBot::obtenerChatId(int index) {
    return bot->messages[index].chat_id;
}

// Verifica conexión WiFi
bool TelegramBot::estaConectado() {
    return WiFi.status() == WL_CONNECTED;
}

// Obtiene el número de mensajes (acceso directo al bot)
int TelegramBot::obtenerNumeroMensajes() {
    return bot->getUpdates(bot->last_message_received + 1);
}
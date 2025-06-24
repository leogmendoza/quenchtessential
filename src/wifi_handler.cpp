#include "wifi_handler.hpp"

#include <Arduino.h>
#include "config.hpp"

void WifiHandler::connect( const char* ssid, const char* password ) {
    Serial.print("[Wi-Fi] being beamed up!");

    WiFi.begin( ssid, password );

    while ( WiFi.status() != WL_CONNECTED ) {
        Serial.print(" .");
        delay(500);
    }

    Serial.println();
    Serial.println("[Wi-Fi] is beamed up!");
    Serial.print("[Wi-Fi] IP Address: ");
    Serial.println( WiFi.localIP() );
}

void WifiHandler::maintainConnection(const char* ssid, const char* password) {
    static unsigned long lastReconnectAttempt = 0;
    unsigned long now = millis();

    if ( WiFi.status() != WL_CONNECTED ) {
        if ( ( now - lastReconnectAttempt ) > Config::WIFI_RECONNECT_INTERVAL_MS ) {
            Serial.println("[WiFi] Disconnected. Reconnecting...");
            connect( ssid, password );
            lastReconnectAttempt = now;
        }
    }
}

IPAddress WifiHandler::getLocalIP() const {
    return WiFi.localIP();
}

bool WifiHandler::isConnected() const {
    return (WiFi.status() == WL_CONNECTED);
}

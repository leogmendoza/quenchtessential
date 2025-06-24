#include "wifi_handler.hpp"

#include <Arduino.h>

void WifiHandler::connect( const char* ssid, const char* password ) {
    Serial.print("Beaming it up to Wi-Fi");

    WiFi.begin( ssid, password );

    while ( WiFi.status() != WL_CONNECTED ) {
        Serial.print(" .");
        delay(500);
    }

    Serial.println();
    Serial.println("Wi-Fi is beamed up!");
    Serial.print("IP Address: ");
    Serial.println( WiFi.localIP() );
}

IPAddress WifiHandler::getLocalIP() const {
    return WiFi.localIP();
}

bool WifiHandler::isConnected() const {
    return (WiFi.status() == WL_CONNECTED);
}

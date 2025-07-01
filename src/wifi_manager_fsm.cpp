#include "wifi_manager_fsm.hpp"

#include <Arduino.h>
#include <WiFiManager.h>
#include "config.hpp"

void WifiManagerFSM::begin() {
    Serial.println("[Wi-Fi] Beaming it up . . . ");
    state_ = WifiState::STARTUP;

    WiFiManager wm;

    // If not connected, open access point (AP) for user to configure SSID
    state_ = WifiState::CONFIG;
    connected_ = wm.autoConnect("Quenchtessential-Config");

    if (connected_) {
        Serial.println("[Wi-Fi] Beamed up!");
        Serial.print("[Wi-Fi] IP Address: ");
        Serial.println( WiFi.localIP() );
    } else {
        Serial.println("[Wi-Fi] Failed to connect. Config portal timed out or was exited :<");
        state_ = WifiState::FAILED;
    }
}

void WifiManagerFSM::update() {
    if ( ( state_ == WifiState::CONNECTED ) && ( WiFi.status() != WL_CONNECTED ) ) {
        Serial.println("[Wi-Fi] Lost connection. Attempting to beam it back up . . . ");
        state_ = WifiState::CONNECTING;
        connected_ = false;
        lastReconnectAttempt_ = 0;
    }

    if (state_ == WifiState::CONNECTING) {
        unsigned long now = millis();

        if ( ( now - lastReconnectAttempt_ ) > Config::WIFI_RECONNECT_INTERVAL_MS ) {
            Serial.println("[Wi-Fi] Reconnecting . . . ");
            WiFi.begin();

            lastReconnectAttempt_ = now;
        }

        if ( WiFi.status() == WL_CONNECTED ) {
            Serial.println("[Wi-Fi] Back online!");
            connected_ = true;
            state_ = WifiState::CONNECTED;
        }
    }
}

bool WifiManagerFSM::isConnected() const {
    return ( ( state_ == WifiState::CONNECTED ) && ( WiFi.status() == WL_CONNECTED ) );
}


IPAddress WifiManagerFSM::getLocalIP() const {
    return WiFi.localIP();
}

WifiState WifiManagerFSM::getState() const {
    return state_;
}
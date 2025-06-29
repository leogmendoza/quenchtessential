#pragma once

#define WM_NO_DEBUG  // Avoid WifiManager library's built-in debugging

#include <WiFi.h>

enum class WifiState { 
    STARTUP,
    CONFIG,
    CONNECTING,
    CONNECTED, 
    FAILED
 };

class WifiManagerFSM {
    public:
        void begin();
        void update();

        bool isConnected() const;
        IPAddress getLocalIP() const;
        WifiState getState() const;

    private:
        WifiState state_ = WifiState::STARTUP;
        bool connected_ = false;
        unsigned long lastReconnectAttempt_ = 0;
};

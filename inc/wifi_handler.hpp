#pragma once

#include <WiFi.h>

class WifiHandler {
    public:
        void connect(const char* ssid, const char* password);
        IPAddress getLocalIP() const;
        bool isConnected() const;
};

#pragma once

#include <PubSubClient.h>
#include <WiFiClient.h>

class MqttHandler {
    public:
        MqttHandler(PubSubClient& client);

        void setup();
        void maintainConnection();
        void publish(int moisture);

    private:
        PubSubClient& client_;
        unsigned long lastReconnectAttempt_ = 0;
        unsigned long lastPublish_ = 0;
        char payload_[128];  // Overkill, but here for more sensor support

        void reconnect();
};
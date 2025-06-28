#include "mqtt_handler.hpp"

#include <Arduino.h>
#include <WiFi.h>
#include "config.hpp"

MqttHandler::MqttHandler(PubSubClient& client): client_(client) {}

void MqttHandler::setup() {
    client_.setServer( Config::MQTT_BROKER, Config::MQTT_PORT );
    reconnect();
}

void MqttHandler::maintainConnection() {
    // Check for Wi-Fi status before trying MQTT
    if ( WiFi.status() != WL_CONNECTED ) {
        return;  
    }

    if ( !client_.connected() ) {
        unsigned long now = millis();

        // Guard for MQTT reconnection with throttling to prevent repeated failures
        if ( ( now - lastReconnectAttempt_ ) > Config::MQTT_RECONNECT_INTERVAL_MS ) {
            Serial.println("[MQTT] Reconnecting . . . ");
            reconnect();
        }
    }
}

void MqttHandler::reconnect() {
    lastReconnectAttempt_ = millis();

    if ( client_.connect( Config::MQTT_CLIENT_ID ) ) {
        Serial.println("[MQTT] Connected!");
    } else {
        Serial.print("[MQTT] Failed. State: ");
        Serial.println( client_.state() );
    }
}

void MqttHandler::publish(int moisture) {
    if ( !client_.connected() ) {
        return;
    }

    unsigned long now = millis();
    if ( ( now - lastPublish_ ) < Config::MQTT_PUBLISH_INTERVAL_MS ) {
        return;
    } 

    // Format moisture reading string into payload buffer
    snprintf( payload_, sizeof(payload_), "{\"moisture\": %d}", moisture );  // TODO: Add multiple sensors

    // Test payload formatting--TODO: Remove once full-stack is working
    Serial.print("[MQTT] Publishing: ");
    Serial.println(payload_);

    client_.publish( Config::MQTT_TOPIC, payload_ );
    lastPublish_ = now;
}
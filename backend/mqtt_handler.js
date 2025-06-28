const mqtt = require('mqtt');

const { insertReading } = require('./db');

// Connect to public broker
const client = mqtt.connect('mqtt://test.mosquitto.org');

// Note: Must match ESP32-side code
const topic = 'quenchtessential/plant/status';

// Try to connect to MQTT broker, then subscribe to topic
client.on('connect', () => {
    console.log('Connected to MQTT broker!');
    client.subscribe(topic, (err) => {
        if (err) {
            console.error('Subscription error:', err);
        } else {
            console.log(`Subscribed to topic: ${topic}`);

            // Fake message for testing purpose (unfortunately, im in an ECE 192 lecture rn ;-;)
            client.emit('message', 'quenchtessential/plant/status', Buffer.from(JSON.stringify({ moisture: 6969 })));
        }
    });
});

// Try to receive message from broker
client.on('message', (incomingTopic, messageBuffer) => {
    try {
        if (incomingTopic === topic) {
            const payload = JSON.parse(messageBuffer.toString());

            console.log('Received MQTT message:', payload);

            if (payload.moisture !== undefined) {
                insertReading(payload.moisture);
            }
        }
    } catch (err) {
        console.error('Oh no, failed to parse MQTT message:', err.message);
    }
});

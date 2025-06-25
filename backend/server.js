const express = require('express');
const cors = require('cors');

const mqttHandler = require('./mqtt_handler');

// Set up Express server
const app = express();
const PORT = 3000;

// Allow frontend requests
app.use(cors());

// Testing root route!
app.get('/', (req, res) => {
    res.send('Quenchtessential backend is running!');
});

// Keep server running
app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});

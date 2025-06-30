const express = require('express');
const cors = require('cors');

const mqttHandler = require('./mqtt_handler');
const { getRecentReadings } = require('./db');

// Set up Express server
const app = express();
const PORT = 3000;

// Allow frontend requests
app.use(cors());

// Testing root route!
app.get('/', (req, res) => {
    res.send('Quenchtessential backend is running, woohoo!');
});

// Keep server running
app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});

// Retrieve 20 most recent measurements
app.get('/history', async (req, res) => {
    const range = req.query.range || '24h';

    try {
        const rows = await getRecentReadings(range);
        res.json(rows);
    } catch (err) {
        console.error('Failed to fetch readings:', err);
        res.status(500).json({ error: 'Internal Server Error' });
    }
});


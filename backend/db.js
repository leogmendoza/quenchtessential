require('dotenv').config();

const { Pool } = require('pg');

const pool = new Pool({
    connectionString: process.env.DATABASE_URL,
    ssl: { rejectUnauthorized: false }
});

async function initTables() {
    // Moisture Levels
    await pool.query(`
        CREATE TABLE IF NOT EXISTS readings (
        id SERIAL PRIMARY KEY,
        moisture INTEGER NOT NULL,
        timestamp TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
        )
    `);

    // Last Watered
    await pool.query(`
        CREATE TABLE IF NOT EXISTS watering_events (
        id SERIAL PRIMARY KEY,
        timestamp TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
        )
    `);
}

// Used by mqtt_handler to load measurements into the DB
async function insertReading(moisture) {
    try {
        await pool.query('INSERT INTO readings (moisture) VALUES ($1)', [moisture]);
    } catch (err) {
        console.error('Failed to insert reading:', err);
    }
}

// Used by server to retrieve measurements based on selected range
async function getRecentReadings(range = "24h") {
    let query = `SELECT id, moisture, timestamp FROM readings`;
    const params = [];

    if (range === "24h") {
        query += ` WHERE timestamp >= NOW() - INTERVAL '1 day' ORDER BY timestamp DESC`;
    } else if (range === "7d") {
        query += ` WHERE timestamp >= NOW() - INTERVAL '7 days' ORDER BY timestamp DESC`;
    } else if (range === "live") {
        query += ` ORDER BY timestamp DESC LIMIT 20`;
    } else {
        query += ` ORDER BY timestamp DESC`;
    }

    try {
        const result = await pool.query(query, params);
        return result.rows;
    } catch (err) {
        console.error("Failed to fetch recent readings:", err);
        throw err;
    }
}

async function insertWateringEvent() {
    try {
        await pool.query('INSERT INTO watering_events DEFAULT VALUES');
    } catch (err) {
        console.error('Failed to insert watering event:', err);
    }
}

async function getLastWatered() {
    try {
        const result = await pool.query(
        `SELECT timestamp FROM watering_events ORDER BY timestamp DESC LIMIT 1`
        );
        return result.rows[0]?.timestamp || null;
    } catch (err) {
        console.error('Failed to fetch last watered timestamp:', err);
        throw err;
    }
}

initTables().catch(console.error);


module.exports = {
    insertReading,
    getRecentReadings,
    insertWateringEvent,
    getLastWatered
};

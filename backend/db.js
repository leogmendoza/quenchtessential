const sqlite3 = require('sqlite3').verbose();

// Set  up DB file and table (if they don't already exist) for Moisture Levels
const db = new sqlite3.Database('data.db');
db.run(`
    CREATE TABLE IF NOT EXISTS readings (
        id          INTEGER     PRIMARY KEY AUTOINCREMENT,
        moisture    INTEGER     NOT NULL,
        timestamp   DATETIME    DEFAULT CURRENT_TIMESTAMP
    )
`);

// Set  up DB file and table (if they don't already exist) for Last Watered Info
db.run(`
    CREATE TABLE IF NOT EXISTS watering_events (
        id          INTEGER     PRIMARY KEY AUTOINCREMENT,
        timestamp   DATETIME    DEFAULT CURRENT_TIMESTAMP
    )
`);

// Used by mqtt_handler to load measurements into the DB
function insertReading(moisture) {
    const insertStatement = db.prepare('INSERT INTO readings (moisture) VALUES (?)');
    insertStatement.run(moisture);
    insertStatement.finalize();
}

// Used by server to retrieve last 20 measurements
function getRecentReadings(range = "24h") {
    return new Promise((resolve, reject) => {
        let query = `SELECT id, moisture, timestamp FROM readings`;
        const params = [];

        if (range === "24h") {
            query += ` WHERE timestamp >= datetime('now', '-1 day')`;
        } else if (range === "7d") {
            query += ` WHERE timestamp >= datetime('now', '-7 days')`;
        }

        query += ` ORDER BY timestamp DESC`;

        db.all(query, params, (err, rows) => {
            if (err) reject(err);
            else resolve(rows);
        });
    });
}

function insertWateringEvent() {
    const statement = db.prepare('INSERT INTO watering_events DEFAULT VALUES');
    statement.run();
    statement.finalize();
}

function getLastWatered() {
    return new Promise((resolve, reject) => {
        db.get(
            `SELECT timestamp FROM watering_events ORDER BY timestamp DESC LIMIT 1`,
            [],
            (err, row) => {
                if (err) reject(err);
                else resolve(row?.timestamp || null);
            }
        );
    });
}

module.exports = {
    insertReading,
    getRecentReadings,
    insertWateringEvent,
    getLastWatered
};

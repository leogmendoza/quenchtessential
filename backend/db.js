const sqlite3 = require('sqlite3').verbose();

// Set  up DB file and table (if they don't already exist)
const db = new sqlite3.Database('data.db');
db.run(`
    CREATE TABLE IF NOT EXISTS readings (
        id          INTEGER     PRIMARY KEY AUTOINCREMENT,
        moisture    INTEGER     NOT NULL,
        timestamp   DATETIME    DEFAULT (datetime('now', 'localtime'))
    )
`);

// Used by mqtt_handler to load measurements into the DB
function insertReading(moisture) {
    const insertStatement = db.prepare('INSERT INTO readings (moisture) VALUES (?)');
    insertStatement.run(moisture);
    insertStatement.finalize();
}

// Used by server to retrieve last 20 measurements
function getRecentReadings() {
    return new Promise((resolve, reject) => {
        db.all(
            `SELECT id, moisture, timestamp
            FROM readings
            ORDER BY timestamp DESC
            LIMIT 20`,
            (err, rows) => {
                if (err) reject(err);
                else resolve(rows);
            }
        );
    });
}

module.exports = {
    insertReading,
    getRecentReadings
};

const sqlite3 = require('sqlite3').verbose();

// Set  up DB file and table (if they don't already exist)
const db = new sqlite3.Database('data.db');
db.run(`
    CREATE TABLE IF NOT EXISTS readings (
        id          INTEGER     PRIMARY KEY AUTOINCREMENT,
        moisture    INTEGER     NOT NULL,
        timestamp   DATETIME    DEFAULT CURRENT_TIMESTAMP
    )
`);

// Used by mqtt_handler to load measurements into the DB
function insertReading(moisture) {
    const insertStatement = db.prepare('INSERT INTO readings (moisture) VALUES (?)');
    insertStatement.run(moisture);
    insertStatement.finalize();
}

module.exports = {
    insertReading
};

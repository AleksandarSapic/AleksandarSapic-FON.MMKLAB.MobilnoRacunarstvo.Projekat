const express = require('express');
const mysql = require('mysql');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 3000;

const connection = mysql.createConnection({
    host: process.env.DB_HOST,
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_DATABASE
});

// Middleware to parse JSON bodies
app.use(express.json());

app.post('/api/data', async (req, res) => {
    const { time, message } = req.body;

    // Check if time and message are strings and non-empty
    if (!(typeof time === 'string' && time.trim() !== '') || !(typeof message === 'string' && message.trim() !== '')) {
        return res.status(400).send({ message: 'Invalid JSON format. Time and message must be non-empty strings.' });
    }

    console.log("Received alert:");
    console.log("Time: " + time);
    console.log("Message: " + message);

    connection.connect();

    // Insert data into MySQL database with parameterized query
    const insertQuery = 'INSERT INTO alerts (time, message) VALUES (?, ?)';
    connection.query(insertQuery, [time, message], (error, results, fields) => {
        if (error) {
            console.error("Error inserting alert:", error);
            res.status(500).send({ message: 'Error inserting alert into database' });
        } else {
            console.log("Alert inserted successfully into database");
            res.status(200).send({ message: 'Alert received and saved successfully' });
        }
    });

    connection.end();
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
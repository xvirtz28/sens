const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

// Middleware to parse URL-encoded data
app.use(bodyParser.urlencoded({ extended: true }));

// Endpoint to receive data
app.post('/send-data', (req, res) => {
  const sensorData = req.body.sensorData;
  console.log(`Received sensor data: ${sensorData}`);
  res.send(`Sensor data received: ${sensorData}`);
});

// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});

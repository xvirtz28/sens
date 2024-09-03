// pages/api/data.js

export default function handler(req, res) {
    if (req.method === 'GET') {
      // Handle GET requests: return the current data
      const data = [
        {
          "_id": "66d11bca9d80f3be07fee81c",
          "device": "Neptune-001",
          "value": 12,
          "time": "2024-08-29T13:34:56.000Z",
          "__v": 0
        }
      ];
      res.status(200).json(data);
    } else if (req.method === 'POST') {
      // Handle POST requests: save the data sent in the request
      const newData = req.body; // Assuming the data is sent in the request body
      // Here you can save newData to a database or process it as needed
  
      res.status(201).json({ message: 'Data received', data: newData });
    } else {
      // Handle any other HTTP method
      res.setHeader('Allow', ['GET', 'POST']);
      res.status(405).end(`Method ${req.method} Not Allowed`);
    }
  }
  
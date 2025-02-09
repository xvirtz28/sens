#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "PARAFIBER_96BD-2G";
const char* password = "BDE796BD";
const char* serverName = "http://192.168.1.93:3000/send-data";

const int turbidityPin = 4;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");  // Added newline for cleaner output
}

// void loop() {
//   int sensorValue = analogRead(turbidityPin);
//   int mappedValue = map(sensorValue, 0, 4095, 1000, 0);  // Corrected the map function
//   String detectionStatus;
//   HTTPClient http;

//   // Determine the detection status based on the mapped value and the 60-unit range
//   if (mappedValue >= 0 && mappedValue < 60) {
//     detectionStatus = "Very Clear Water (0-59)";
//   } else if (mappedValue >= 60 && mappedValue < 100) {
//     detectionStatus = "Very Clear Water (60-99)";
//   } else if (mappedValue >= 100 && mappedValue < 160) {
//     detectionStatus = "Slightly Turbid Water (100-159)";
//   } else if (mappedValue >= 160 && mappedValue < 220) {
//     detectionStatus = "Slightly Turbid Water (160-219)";
//   } else if (mappedValue >= 220 && mappedValue < 300) {
//     detectionStatus = "Slightly Turbid Water (220-299)";
//   } else if (mappedValue >= 300 && mappedValue < 360) {
//     detectionStatus = "Moderately Turbid Water (300-359)";
//   } else if (mappedValue >= 360 && mappedValue < 420) {
//     detectionStatus = "Moderately Turbid Water (360-419)";
//   } else if (mappedValue >= 420 && mappedValue < 500) {
//     detectionStatus = "Moderately Turbid Water (420-499)";
//   } else if (mappedValue >= 500 && mappedValue < 560) {
//     detectionStatus = "Highly Turbid Water (500-559)";
//   } else if (mappedValue >= 560 && mappedValue < 620) {
//     detectionStatus = "Highly Turbid Water (560-619)";
//   } else if (mappedValue >= 620 && mappedValue < 680) {
//     detectionStatus = "Highly Turbid Water (620-679)";
//   } else if (mappedValue >= 680 && mappedValue < 740) {
//     detectionStatus = "Highly Turbid Water (680-739)";
//   } else if (mappedValue >= 740 && mappedValue < 800) {
//     detectionStatus = "Highly Turbid Water (740-799)";
//   } else if (mappedValue >= 800 && mappedValue < 860) {
//     detectionStatus = "Highly Turbid Water (800-859)";
//   } else if (mappedValue >= 860 && mappedValue < 920) {
//     detectionStatus = "Highly Turbid Water (860-919)";
//   } else if (mappedValue >= 920 && mappedValue < 1000) {
//     detectionStatus = "Highly Turbid Water (920-999)";
//   } else {
//     detectionStatus = "Very High Turbidity (1000+)";
//   }

//   // You can add any additional code to process or send the detectionStatus here
// }



//   Serial.println("detectionStatus = " + detectionStatus + ", sensor reading: " + String(mappedValue));

//   // Send data to the server
//   http.begin(serverName);
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");

//   String httpRequestData = "sensorData=" + String(mappedValue) + "&status=" + detectionStatus;
//   int httpResponseCode = http.POST(httpRequestData);

//   if (httpResponseCode > 0) {
//     String response = http.getString();
//     Serial.println("Response Code: " + String(httpResponseCode));
//     Serial.println("Response: " + response);
//   } else {
//     Serial.println("Error sending data, HTTP response code: " + String(httpResponseCode));
//   }

//   http.end();
//   delay(5000);  // Send data every 5 seconds
// }


unsigned long startMillis = 0; // Start time when a new detection status begins
unsigned long currentMillis;
unsigned long duration = 0; // Duration the detection status stays the same
String previousDetectionStatus = ""; // Stores the previous detection status

void loop() {
  int sensorValue = analogRead(turbidityPin);
  int mappedValue = map(sensorValue, 0, 4095, 1000, 0);  // Corrected the map function
  String detectionStatus;
  HTTPClient http;

  // Determine the detection status based on the mapped value and the 60-unit range
  if (mappedValue >= 0 && mappedValue < 60) {
    detectionStatus = "Very Clear Water (0-59)";
  } else if (mappedValue >= 60 && mappedValue < 100) {
    detectionStatus = "Very Clear Water (60-99)";
  } else if (mappedValue >= 100 && mappedValue < 160) {
    detectionStatus = "Slightly Turbid Water (100-159)";
  } else if (mappedValue >= 160 && mappedValue < 220) {
    detectionStatus = "Slightly Turbid Water (160-219)";
  } else if (mappedValue >= 220 && mappedValue < 300) {
    detectionStatus = "Slightly Turbid Water (220-299)";
  } else if (mappedValue >= 300 && mappedValue < 360) {
    detectionStatus = "Moderately Turbid Water (300-359)";
  } else if (mappedValue >= 360 && mappedValue < 420) {
    detectionStatus = "Moderately Turbid Water (360-419)";
  } else if (mappedValue >= 420 && mappedValue < 500) {
    detectionStatus = "Moderately Turbid Water (420-499)";
  } else if (mappedValue >= 500 && mappedValue < 560) {
    detectionStatus = "Highly Turbid Water (500-559)";
  } else if (mappedValue >= 560 && mappedValue < 620) {
    detectionStatus = "Highly Turbid Water (560-619)";
  } else if (mappedValue >= 620 && mappedValue < 680) {
    detectionStatus = "Highly Turbid Water (620-679)";
  } else if (mappedValue >= 680 && mappedValue < 740) {
    detectionStatus = "Highly Turbid Water (680-739)";
  } else if (mappedValue >= 740 && mappedValue < 800) {
    detectionStatus = "Highly Turbid Water (740-799)";
  } else if (mappedValue >= 800 && mappedValue < 860) {
    detectionStatus = "Highly Turbid Water (800-859)";
  } else if (mappedValue >= 860 && mappedValue < 920) {
    detectionStatus = "Highly Turbid Water (860-919)";
  } else if (mappedValue >= 920 && mappedValue < 1000) {
    detectionStatus = "Highly Turbid Water (920-999)";
  } else {
    detectionStatus = "Very High Turbidity (1000+)";
  }

  // Track duration of detection status
  currentMillis = millis();

  if (detectionStatus != previousDetectionStatus) {
    // If the detection status changes, reset the start time
    startMillis = currentMillis;
    previousDetectionStatus = detectionStatus;
  }

  duration = (currentMillis - startMillis) / 1000; // Duration in seconds

  // Output the detection status and duration
  Serial.print("Detection Status: ");
  Serial.print(detectionStatus);
  Serial.print(" | Duration: ");
  Serial.print(duration);
  Serial.println(" seconds");

  // Add any additional code to process or send the detectionStatus and duration here
 delay(1000);  // Send data every 10 seconds
}



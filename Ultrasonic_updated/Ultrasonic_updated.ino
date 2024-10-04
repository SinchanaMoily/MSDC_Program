#include <Ultrasonic.h>
#include <WiFi.h> 
#include <HTTPClient.h> 

Ultrasonic ultrasonic(12, 13);  // Ultrasonic sensor on pins 12 and 13

// WiFi credentials
const char* ssid =  "workspace1"; 
const char* password = "passcode1"; 
// ThingSpeak settings
const char* serverName = "https://api.thingspeak.com/update"; 
const char* apiKey = "20XZLHNKXNMULTR7";

int distance;

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  // Read distance from ultrasonic sensor
  distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);

  // Send data to ThingSpeak (two fields)
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(distance);
    http.begin(url);
    int httpResponseCode = http.GET();
    http.end();

    if (httpResponseCode > 0) {
      Serial.println("Data Received");
    } else {
      Serial.println("Error in sending data");
    }
  } else {
    Serial.println("ERROR IN WIFI CONNECTIVITY");
  }

  delay(1000);  // 1 second delay
}
#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "workspace1";
const char* password = "passcode1";

// ThingSpeak API information
const char* serverName = "https://api.thingspeak.com/update";
const char* apiKey = "XLKIGFGDRPV7A7BO";

// Define IR sensor pin
#define IR_PIN 8

void setup() {
  Serial.begin(9600);

  // Initialize IR sensor pin
  pinMode(IR_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(2000);

  // Get IR sensor data (object detection)
  int irValue = digitalRead(IR_PIN);

  // Display IR sensor value
 if (irValue == LOW) {
    Serial.println("Obstacle detected!");

  delay(100);                      // Short delay to sound the buzzer
  } else {
    Serial.println("Obstacle not detected!");
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(irValue);
    
    http.begin(url);
    int httpResponseCode = http.GET();


    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}

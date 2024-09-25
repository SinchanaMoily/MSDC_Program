#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "workspace1";
const char* password = "passcode1";

// ThingSpeak API information
const char* serverName = "https://api.thingspeak.com/update";
const char* apiKey = "E5THI8IYQMBHWBI9";

// Define LDR sensor pin (analog input)
#define LDR_PIN A0

// Define the light/dark threshold value (adjust based on testing)
int lightThreshold = 5000;

void setup() {
  Serial.begin(9600);

  // Initialize LDR sensor pin
  pinMode(LDR_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(2000);  // 2 second delay between readings

  // Get LDR sensor data (light intensity)
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Determine if it's dark or light based on the threshold
  String lightCondition;
  if (ldrValue > lightThreshold) {
    Serial.println("It's dark.");
    lightCondition = "Dark";
  } else {
    Serial.println("It's bright.");
    lightCondition = "Bright";
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(ldrValue) + "&field2=" + lightCondition;
    
    http.begin(url);
    int httpResponseCode = http.GET();


    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(10000);  // Delay to reduce the loop frequency (10 seconds)
}

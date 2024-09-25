#include <WiFi.h>
#include <HTTPClient.h>

const int trigPin = 8;
const int echoPin = 9;
int buzzerPin = 6;
// defines variables
const char* ssid =  "workspace1";
const char* password = "passcode1";
const char* serverName = "https://api.thingspeak.com/update";
const char* apiKey = "6JIP23IG7MM9877G";

long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  WiFi.begin(ssid, password);
  while(WiFi.status() !=WL_CONNECTED)
  {
    delay(500);
   Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance <= 10){
    digitalWrite(buzzerPin, HIGH);
  }
  else{

    digitalWrite(buzzerPin,LOW);
  }
  if(WiFi.status()== WL_CONNECTED)
  {
    HTTPClient http;
    String url = String(serverName) +"?api_key=" +apiKey + "&field1=" + String(distance);

  http.begin(url);
  int httpResponseCode = http.GET();

  http.end();
  }
  else{
    Serial.println("ERROR IN WIFI CONNECTIVITY");
  }
  
}
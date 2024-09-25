#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "workspace1";
const char* password = "passcode1";

const char* serverName = "https://api.thingspeak.com/update";
const char* apiKey = "PLOGQAQAFJSSWBSW";



#define DHTPIN 8
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
 
  delay(2000);

 
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();


  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");



  
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + "?api_key=" + apiKey + "&field1=" + String(temperature) + "&field2=" + String(humidity);
    
    http.begin(url);
    int httpResponseCode = http.GET();

    // if (httpResponseCode > 0) {
    //   String payload = http.getString();
    //   Serial.println(httpResponseCode);
    //   Serial.println(payload);
    // } else {
    //   Serial.println("Error on HTTP request");
    // }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}

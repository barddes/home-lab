#include <WiFi.h>
#include <HTTPClient.h>

const char* WIFI_NAME = "Bar do Bira Fundos";
const char* WIFI_PASSWORD =  "eaigente?";

void wifiSetup() {
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void log(const char* msg) {
  if(WiFi.status()!= WL_CONNECTED){
    Serial.println("WiFi Disconnected");
    return;
  }
  WiFiClient client;
  HTTPClient http;

  http.begin(client, UPSTREAM + "/esp32");
  http.addHeader("Content-Type", "text/plain");

  String log = "last_reading=";
  log += last_reading;
  log += " ";
  log += msg;

  Serial.println(log);  
  int httpResponseCode = http.POST(log);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
}

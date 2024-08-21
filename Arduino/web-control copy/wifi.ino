#include <WiFi.h>

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
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("Configured WiFi Mode STA");
  Serial.print("Device MAC: ");
  Serial.println(WiFi.macAddress());
}

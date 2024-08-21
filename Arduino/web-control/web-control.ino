#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

/** STATE **/
typedef struct Plant {
    String name;
    unsigned long pump_active_until;
    unsigned long sensor_active_until;
    unsigned long last_checked;
    uint16_t sensor_last_reading;
    uint16_t sensor_last_computed_voltage;
    bool active;
    bool sensor;
    bool pump;
} Plant;

typedef struct State {
  bool loop_active;
  Plant plants[1];
} State;

State state;
void initState();
void ensureState();

/** WIFI **/
const char* ssid = "Bar do Bira Fundos"; // Coloque o nome de sua rede WiFi
const char* password = "eaigente?"; // Coloque a senha da sua rede WiFi

IPAddress ip(192, 168, 3, 142); // Fixe um IP de acordo com sua rede
IPAddress gw(192, 168, 3, 1); // Não esqueça de mudar o gateway caso a faixa de IP seja diferente
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);

void setupWifi();

/** SERVER **/
void startWebServer();
void handleRoot(AsyncWebServerRequest* request);
void handleMetrics(AsyncWebServerRequest* request);
void handleNotFound(AsyncWebServerRequest* request);

/** PLANTS **/
void handlePlant(AsyncWebServerRequest* request);
void handlePump(AsyncWebServerRequest* request);
void handleSensor(AsyncWebServerRequest* request);
void handleCheck(AsyncWebServerRequest* request);
void setupSensors();
void readSensors(Plant& p);

esp_adc_cal_characteristics_t* adc_chars;


/** PROMETHEUS **/

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
String getMetrics();
void setMetric(String *p, String metric, String value);
int getBootCounter();
void incrementBootCounter();
void setupStorage();
void closeStorage();

/** HTML TEMPLATES **/
String templatePlant(Plant plant);

/** ESP32 **/
#define P1_SENSOR 25
#define P1_SENSOR_OUT ADC1_CHANNEL_5  // GPIO33
#define P1_ADC_VREF 2200
#define ADC_MULTISAMPLING 16
#define P1_PUMP 12
#define LED_BUILTIN 2
Preferences preferences;

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(P1_SENSOR, OUTPUT);
  pinMode(P1_SENSOR_OUT, INPUT);
  pinMode(P1_PUMP, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(P1_SENSOR, HIGH);
  digitalWrite(P1_PUMP, LOW);
  Serial.begin(115200);

  setupStorage();
  incrementBootCounter();
  setupSensors();

  setupWifi();
  initState();
  startWebServer();
}

void loop(void) {
  state.loop_active = true;
  unsigned long now = millis();
  for(int i;)
    if(p.last_checked == 0 || now - p.last_checked >= 120000)
      readSensors(p);
  ensureState();
  state.loop_active = false;
  delay(500);
}

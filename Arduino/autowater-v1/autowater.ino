#include <WiFi.h>
#include <HTTPClient.h>

const int LED = 2;
const int PUMP_POWER = 26;
const int SENSOR_POWER = 25;
const int SENSOR_OUTPUT = 32;

const int BUTTON_IN = 18;
const int BUTTON_OUT = 19;

const char* WIFI_NAME = "Bar do Bira Fundos";
const char* WIFI_PASSWORD =  "eaigente?";
String UPSTREAM = "http://192.168.3.104:8080/";

/* Ar~2240 Terra seca~1070 Terra molhada~900 */
const int SENSOR_THRESHOLD =  1200;

const int step = 500;  // 500ms
const int loop_size = 1000 * 60 * 60 * 2;  // 30s
int current_step = 0;
int last_reading = 0;

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

  http.begin(client, UPSTREAM + "/log");
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


void water_plant() {
  digitalWrite(LED, HIGH);
  digitalWrite(PUMP_POWER, HIGH);
  delay(6000);
  digitalWrite(PUMP_POWER, LOW);
  digitalWrite(LED, LOW);
}

int check_sensor() {
  digitalWrite(SENSOR_POWER, HIGH);
  delay(10000);
  last_reading = analogRead(SENSOR_OUTPUT);
  digitalWrite(SENSOR_POWER, LOW);
  return last_reading;
}

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void IRAM_ATTR handle_button() {
  button_time = millis();
  if (button_time - last_button_time > 250) {
    current_step = -1;    
    last_button_time = button_time;
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PUMP_POWER, OUTPUT);
  pinMode(SENSOR_POWER, OUTPUT);
  pinMode(SENSOR_OUTPUT, INPUT);
  pinMode(BUTTON_IN, INPUT_PULLUP);
  pinMode(BUTTON_OUT, OUTPUT);
  digitalWrite(BUTTON_OUT, LOW);

  Serial.begin(115200);
  wifiSetup ();
  log("Start Self Watering");

  // digitalWrite(PUMP_POWER, HIGH);
  // digitalWrite(SENSOR_POWER, HIGH);

  current_step = 0;
  
  attachInterrupt(BUTTON_IN, handle_button, FALLING);
}

void loop() {

  log("new loop");
  if (current_step == -1) {
    log("button");
    current_step=loop_size;

  } 
  if (current_step >= loop_size) {
    current_step = 0;

    log("pre check sensor");
    check_sensor();
    log("sensor done");

    if(last_reading > SENSOR_THRESHOLD) {
      log("the pump shall be powered");
      water_plant();
      log("STOP");
    }
    else {
      log("will not power pump");
    }
  }
  else {
    current_step += step;
  }

  delay(step);
}

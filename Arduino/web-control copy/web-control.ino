#define LED 2
#define SENSOR 13
#define PUMP 12

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("Started");
  wifiSetup ();
  webServerSetup();

  pinMode(LED, OUTPUT);
  pinMode(SENSOR, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

void loop() {
  handleWebConnection();
  
}

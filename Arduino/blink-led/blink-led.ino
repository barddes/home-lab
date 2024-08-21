#define LED 2
#define SENSOR 13
#define PUMP 12

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, OUTPUT);
  pinMode(PUMP, OUTPUT);


}

void loop() {
  digitalWrite(SENSOR, HIGH);
  digitalWrite(PUMP, HIGH);
  delay(500);
  digitalWrite(SENSOR, LOW);
  digitalWrite(PUMP, LOW);
  delay(500);
}

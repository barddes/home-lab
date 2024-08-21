/* Ar~2240 Terra seca~1070 Terra molhada~900 */
const int SENSOR_THRESHOLD =  1200;

int last_reading = 0;

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

void check_plants() {
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

const int LED = 2;
const int PUMP_POWER = 26;
const int SENSOR_POWER = 25;
const int SENSOR_OUTPUT = 32;
const int BUTTON_IN = 18;
const int BUTTON_OUT = 19;

const int step = 500;  // 500ms
const int loop_size = 1000 * 60 * 60 * 2;  // 30s
int current_step = 0;

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

  current_step = 0;
  
  attachInterrupt(BUTTON_IN, handle_button, FALLING);
}

void loop() {
  if (current_step == -1) {
    log("button");
    current_step=loop_size;
  }

  if (current_step >= loop_size) {
    current_step = 0;
    log("main");
    check_plants();
  }

  current_step += step;
  delay(step);
}

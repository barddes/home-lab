void handlePlant(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  String id = "0";
  if(request->getParam("id")) id = request->getParam("id")->value();
  request->send(200, "text/html", templatePlant(state.plants[id.toInt()]));
  digitalWrite(LED_BUILTIN, 0);
}

void handlePump(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  String id = request->getParam("id")->value();
  WebRequestMethodComposite method = request->method();
  String response = "";
  switch(method) {
    case HTTP_GET:
      response = state.plants[id.toInt()].pump_active_until > millis() ? "ON" : "OFF";
      break;

    case HTTP_POST:
      state.plants[id.toInt()].pump_active_until = millis() + 10000;
      response = "OK";
      break;

    case HTTP_DELETE:
      state.plants[id.toInt()].pump_active_until = millis();
      response = "OK";
      break;

    default:
      Serial.print("Unknown method: ");
      Serial.println(method);
      response = "ERROR";
      break;
  }
  request->send(200, "text/plain", response);
  digitalWrite(LED_BUILTIN, 0);
}


void handleSensor(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  String id = request->getParam("id")->value();
  WebRequestMethodComposite method = request->method();
  String response = "";
  switch(method) {
    case HTTP_GET:
      response = state.plants[id.toInt()].sensor_active_until > millis() ? "ON" : "OFF";
      break;

    case HTTP_POST:
      state.plants[id.toInt()].sensor_active_until = millis() + 120000;
      response = "OK";
      break;

    case HTTP_DELETE:
      state.plants[id.toInt()].sensor_active_until = millis();
      response = "OK";
      break;

    default:
      Serial.print("Unknown method: ");
      Serial.println(method);
      response = "ERROR";
      break;
  }
  request->send(200, "text/plain", response);
  digitalWrite(LED_BUILTIN, 0);
}

Plant& getPlantById(int id) {
  return state.plants[id];
}

void handleCheck(AsyncWebServerRequest* request) {
  digitalWrite(LED_BUILTIN, 1);
  String id = request->getParam("id")->value();
  getPlantById(id.toInt()).last_checked = 0;
  request->send(200, "text/plain", "OK");
  digitalWrite(LED_BUILTIN, 0);
}

void setupSensors() {
  Serial.println("Setup Sensors");
  // Configure ADC
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(P1_SENSOR_OUT, ADC_ATTEN_DB_12);

  adc_chars = (esp_adc_cal_characteristics_t*) calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, P1_ADC_VREF, adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    printf("eFuse Vref");
  } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
    printf("Two Point");
  } else {
    printf("Default");
  }
}

void readSensors(Plant& p) {
  printf("Reading sensors\n");
  if(!p.sensor) {
    printf("Sensor not active. Activating sensors...\n");
    p.sensor_active_until = millis() + 15000;
    p.sensor = true;
    ensureState();
    delay(10000);
  }

  p.last_checked = millis();
  uint16_t adc_reading = 0;

  //Multisampling
  printf("ADC Multisampling %d\n", ADC_MULTISAMPLING);
  for (int i = 0; i < ADC_MULTISAMPLING; i++) 
    adc_reading += adc1_get_raw((adc1_channel_t) P1_SENSOR_OUT);
  adc_reading /= ADC_MULTISAMPLING;

  //Convert adc_reading to voltage in mV
  uint16_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
  p.sensor_last_reading = adc_reading;
  p.sensor_last_computed_voltage = voltage;
  printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
}
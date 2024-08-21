void initState() {
  state.loop_active = false;
  state.n_plants
    state.plants[0]
      .name = "Gertrudes";
  state.plants[0].pump_active_until = 0;
  state.plants[0].sensor_active_until = 0;
  state.plants[0].sensor_last_reading = 0;
  state.plants[0].sensor_last_computed_voltage = 0;
  state.plants[0].active = true;
  state.plants[0].sensor = false;
  state.plants[0].pump = false;
}

void ensureState() {
  for (int i = 0; i < sizeof(state.plants); i++) {
    unsigned long now = millis();
    if (now >= state.plants[i].pump_active_until) {
      digitalWrite(P1_PUMP, LOW);
      state.plants[i].pump = false;
    } else {
      digitalWrite(P1_PUMP, HIGH);
      state.plants[i].pump = true;
    }

    if (now >= state.plants[i].sensor_active_until) {
      digitalWrite(P1_SENSOR, LOW);
      state.plants[i].sensor = false;
    } else {
      digitalWrite(P1_SENSOR, HIGH);
      state.plants[i].sensor = true;
    }
  }
}
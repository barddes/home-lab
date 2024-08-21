typedef struct Plant{
  uint8_t pump_active_for;
  uint8_t sensor_active_for;
  uint16_t humidity;
  bool active;
} Plant;

typedef struct State{
  Plant plant1;
  Plant plant2;
} State;

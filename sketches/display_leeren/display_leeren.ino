// tüftelPark – Sensorkit zurücksetzen: OLED-Display leeren, sonst nichts
#include "Arduino_SensorKit.h"

void setup() {
  Oled.begin();
  Oled.clearDisplay();
}

void loop() {
}

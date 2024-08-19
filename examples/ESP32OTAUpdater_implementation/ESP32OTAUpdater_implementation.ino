#include <Arduino.h>
#include "ESP32OTAUpdater.h"

ESP32OTAUpdater otaUpdater("esp32", "abc", "123");

void setup() {
  otaUpdater.BEGIN();
}

void loop() {
  otaUpdater.HANDLECLIENT();
}

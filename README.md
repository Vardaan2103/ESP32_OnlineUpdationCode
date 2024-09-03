# ESP32WebConfig Library
The ESP32WebConfig library is designed to provide a web-based interface for configuring Wi-Fi credentials, performing firmware updates, and handling device resets on an ESP32 microcontroller. This makes it easy to manage your ESP32 device over a local network without needing physical access to the device for reconfiguration or firmware updates.

#Features:
(1)Wi-Fi Configuration: Configure and save Wi-Fi credentials via a web interface.
(2)Firmware Update: Perform Over-The-Air (OTA) firmware updates using a web-based file upload.
(3)Reset Configuration: Clear stored Wi-Fi credentials and reset the device to Access Point (AP) mode.
(4)Debugging: Debug messages are output via the serial interface for easy troubleshooting.

#Installation:
Download or clone this repository.
Copy the ESP32WebConfig directory into your Arduino libraries directory (usually located at Documents/Arduino/libraries).

#Usage:
#Include the Library
In your Arduino sketch, include the ESP32WebConfig library:
#include <Arduino.h>
#include "ESP32WebConfig.h"

#Initialize the Library
Create an instance of the ESP32WebConfig class by passing the hostname, Wi-Fi SSID, and password to the constructor:
ESP32WebConfig webConfig("hostname", "SSID", "password");

#Setup
In the setup() function of your sketch, call the BEGIN() method to initialize the web server and Wi-Fi:
void setup() {
  webConfig.BEGIN();
}
#Loop
In the loop() function, call the HANDLECLIENT() method repeatedly to process incoming HTTP requests:
void loop() {
  webConfig.HANDLECLIENT();
}

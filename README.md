# ESP32WebConfig Library

The `ESP32WebConfig` library provides a web-based interface for configuring Wi-Fi credentials, performing firmware updates, and handling device resets on an ESP32 microcontroller.

## Features

- **Wi-Fi Configuration:** Configure and save Wi-Fi credentials via a web interface.
- **Firmware Update:** Perform Over-The-Air (OTA) firmware updates using a web-based file upload.
- **Reset Configuration:** Clear stored Wi-Fi credentials and reset the device to Access Point (AP) mode.
- **Debugging:** Serial output for debugging.

## Installation

1. Download or clone this repository.
2. Copy the `ESP32WebConfig` directory into your Arduino libraries directory, typically found at:

   ```plaintext
   Documents/Arduino/libraries
##mDNS Configuration
If your router or local network supports mDNS, you can access the ESP32 by typing http://esp32.local/ in your web browser. Otherwise, you'll need to use the IP address assigned by your router.

##Debugging
Debug messages are printed to the serial monitor at 115200 baud. This can help you troubleshoot issues with Wi-Fi connectivity, mDNS setup, or other aspects of the web configuration process.

##Future Improvements
Add support for more advanced configuration options (e.g., static IP setup).
Implement additional security features (e.g., HTTP authentication).

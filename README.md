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

## Web Interface

After uploading the sketch to your ESP32:

### Access Point Mode:

- If the ESP32 cannot connect to the specified Wi-Fi network, it will start in Access Point mode with the SSID Enetra2 and password MyPassword.
- Connect to this network using your computer or mobile device.

### Access the Web Interface:

Once connected, open a web browser and navigate to http://esp32.local/ (or the IP address assigned to the device).

### Configure Wi-Fi:

Click on the Configure Wi-Fi button and enter your desired Wi-Fi credentials.

### Firmware Update:

Click on the Firmware Update button to upload a new firmware file.

### Reset Configuration:

Click on the Reset Wi-Fi Credentials link on the Wi-Fi configuration page to reset the saved Wi-Fi settings.

## mDNS Configuration

If your router or local network supports mDNS, you can access the ESP32 by typing http://esp32.local/ in your web browser. Otherwise, you'll need to use the IP address assigned by your router.

## Debugging

Debug messages are printed to the serial monitor at 115200 baud. This can help you troubleshoot issues with Wi-Fi connectivity, mDNS setup, or other aspects of the web configuration process.

## Future Improvements

- Add support for more advanced configuration options (e.g., static IP setup).
- Implement additional security features (e.g., HTTP authentication).

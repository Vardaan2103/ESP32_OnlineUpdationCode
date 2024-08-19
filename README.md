# esp32-ota-updater

An Arduino library for ESP32 that adds a small web UI for configuring Wi-Fi credentials and pushing over-the-air (OTA) firmware updates — no serial cable or reflash needed after the first upload.

## Features

- **Wi-Fi configuration over the web** — set your network's SSID/password from a browser instead of hardcoding and reflashing
- **OTA firmware updates** — upload a new `.bin` directly through the browser
- **Automatic AP fallback** — if the configured network is unreachable, the board starts its own Access Point so you can still reach the config page
- **mDNS support** — reach the device at `http://esp32.local/` instead of hunting for its IP

## Installation

**Manual (works today):**
1. Download or clone this repository
2. Copy the whole folder into your Arduino libraries directory (typically `Documents/Arduino/libraries/`)
3. Restart the Arduino IDE

**Arduino Library Manager:** not yet published there — `library.properties` is included and ready, so this can be submitted to the Library Manager index in the future if you want it discoverable that way.

## Usage

```cpp
#include <ESP32OTAUpdater.h>

ESP32OTAUpdater otaUpdater("esp32", "your-default-ssid", "your-default-password");

void setup() {
  otaUpdater.BEGIN();
}

void loop() {
  otaUpdater.HANDLECLIENT();
}
```

The constructor takes:
1. `HOSTNAME` — used for mDNS (`http://<hostname>.local/`)
2. `SSID` / `PASSWORD` — fallback credentials used only the very first time the board boots, before anything has been saved via the web UI

After first boot, once you've saved real credentials through the `/wifi-config` page, those are what persist (in flash, via `Preferences`) — the constructor values are never used again unless you hit "Reset Wi-Fi Credentials."

See `examples/ESP32OTAUpdater_implementation/` for the full minimal example.

## Web interface

| Route | Purpose |
|---|---|
| `/` | Landing page with links to the two tools below |
| `/wifi-config` | Form to view/update the current SSID and password |
| `/firmware-update` | Upload a new `.bin` for OTA update |
| `/reset` | Clears saved credentials, restarts into AP mode |

If the board can't connect to its configured network, it starts an Access Point (`SampleAP` / `MyPassword` by default) so you can still reach `/wifi-config` and fix it.

## Project structure

```
esp32-ota-updater/
├── library.properties
├── src/
│   ├── ESP32OTAUpdater.h
│   ├── ESP32OTAUpdater.cpp
│   └── html/
│       ├── CommonStyles.h          # Shared CSS across all pages
│       ├── RootPage.h              # Landing page
│       ├── WifiConfigPage.h        # Wi-Fi config form
│       └── FirmwareUpdatePage.h    # OTA upload page + working progress bar
├── examples/
│   └── ESP32OTAUpdater_implementation/
│       └── ESP32OTAUpdater_implementation.ino
└── README.md
```
## Possible next steps

- Publish to the Arduino Library Manager index
- Add HTTP authentication on the config/update pages (currently open to anyone on the network)
- Support static IP configuration
- Add a captive portal so AP-mode clients are redirected to the config page automatically

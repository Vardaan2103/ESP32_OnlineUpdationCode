#ifndef ESP32OTAUPDATER_ROOT_PAGE_H
#define ESP32OTAUPDATER_ROOT_PAGE_H

#include <Arduino.h>

const char ROOT_PAGE_HTML[] PROGMEM = R"rawliteral(
<html><head><style>
%STYLE%
</style></head><body>
<h1>Welcome</h1>
<a class='button' href='/wifi-config'>Configure Wi-Fi</a>
<a class='button' href='/firmware-update'>Firmware Update</a>
</body></html>
)rawliteral";

#endif

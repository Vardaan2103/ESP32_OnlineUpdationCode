#ifndef ESP32OTAUPDATER_WIFI_CONFIG_PAGE_H
#define ESP32OTAUPDATER_WIFI_CONFIG_PAGE_H

#include <Arduino.h>

// %SSID% is replaced at runtime with the currently active SSID (HTML-escaped
// before substitution). The password field is intentionally left blank in
// the template itself — the saved password is never sent back to the browser.
const char WIFI_CONFIG_PAGE_HTML[] PROGMEM = R"rawliteral(
<html><head><style>
%STYLE%
</style></head><body>
<h1>Wi-Fi Configuration</h1>
<div class='form-container'>
<form method='post' action='/save'>
<label for='SSID'>SSID:</label>
<input type='text' name='SSID' id='SSID' value='%SSID%'><br>
<label for='PASSWORD'>Password:</label>
<input type='password' name='PASSWORD' id='PASSWORD' value='' placeholder='Leave blank to keep current password'><br>
<p class='hint'>Leave the password field blank to keep your current password.</p>
<input type='submit' value='Save'>
</form>
<p><a href='/reset'>Reset Wi-Fi Credentials</a></p>
</div></body></html>
)rawliteral";

#endif

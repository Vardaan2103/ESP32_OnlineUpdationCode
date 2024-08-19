#ifndef ESP32OTAUPDATER_COMMON_STYLES_H
#define ESP32OTAUPDATER_COMMON_STYLES_H

#include <Arduino.h>

// Shared base styles, reused across all pages via the %STYLE% placeholder.
// Previously each page repeated the same body/h1/button/form rules inline.
const char COMMON_STYLE[] PROGMEM = R"rawliteral(
body { font-family: Arial, sans-serif; text-align: center; margin: 20px; }
h1 { color: #333; }
a { color: #0074D9; text-decoration: none; }
a:hover { text-decoration: underline; }
.button { display: inline-block; background-color: #0074D9; color: #fff; padding: 10px 20px; margin: 10px; text-align: center; text-decoration: none; border-radius: 4px; cursor: pointer; }
.form-container { max-width: 400px; margin: 0 auto; text-align: left; }
.form-container label { display: block; margin-bottom: 5px; }
.form-container input[type='text'], .form-container input[type='password'] { width: 100%; padding: 10px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box; }
.form-container input[type='submit'], .form-container .btn { background-color: #0074D9; color: #fff; padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer; }
.hint { font-size: 0.85em; color: #666; margin-top: -8px; margin-bottom: 10px; }
)rawliteral";

#endif

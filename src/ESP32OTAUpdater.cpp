#include "ESP32OTAUpdater.h"
#include "html/CommonStyles.h"
#include "html/RootPage.h"
#include "html/WifiConfigPage.h"
#include "html/FirmwareUpdatePage.h"

ESP32OTAUpdater::ESP32OTAUpdater(const char* HOSTNAME, const char* SSID, const char* PASSWORD) : _HOSTNAME(HOSTNAME), _SSID(SSID), _PASSWORD(PASSWORD), _SERVER(80), _PREFERENCES()
{
  DEBUG_FLAG = true;
}

void ESP32OTAUpdater::BEGIN()
{
  Serial.begin(115200);
  int attempts = 0;

  // Open preferences with a namespace called "wifi"
  _PREFERENCES.begin("wifi", false);

  // Try to read Wi-Fi credentials from preferences, falling back to the
  // constructor defaults if nothing has been saved yet
  String savedSsid = _PREFERENCES.getString("SSID", _SSID);
  String savedPassword = _PREFERENCES.getString("PASSWORD", _PASSWORD);
  _currentSsid = savedSsid;
  debugPrint("Saved SSID: ");
  debugPrintln(savedSsid.c_str());

  WiFi.begin(savedSsid, savedPassword);
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_WIFI_CONNECT_ATTEMPTS)
  {
    delay(1000);
    debugPrintln("Connecting to WiFi...");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    debugPrint("Connected to WiFi SSID: ");
    debugPrintln(savedSsid.c_str());
    debugPrint("IP address: ");
    debugPrintln(WiFi.localIP().toString().c_str());
  }
  else
  {
    debugPrintln("Connection to saved Wi-Fi failed. Switching to AP mode...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("SampleAP", "MyPassword");  // Set your desired AP SSID and password
    debugPrint("AP IP address: ");
    debugPrintln(WiFi.softAPIP().toString().c_str());
  }
  // Setup mDNS
  if (!MDNS.begin(_HOSTNAME))
  {
    debugPrintln("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }
  debugPrintln("mDNS responder started");

  _SERVER.on("/", HTTP_GET, [this](){ this->HANDLEROOT(); });
  _SERVER.on("/save", HTTP_POST, [this](){ this->HANDLESAVE(); });
  _SERVER.on("/reset", HTTP_GET, [this](){ this->HANDLERESET(); });
  _SERVER.on("/update", HTTP_POST, [this](){ this->SENDUPDATERESPONSEANDRESTART(); }, [this](){ this->HANDLEFIRMWAREUPDATE(); });
  _SERVER.on("/wifi-config", HTTP_GET, [this](){ this->HANDLEWIFICONFIG(); });
  _SERVER.on("/firmware-update", HTTP_GET, [this](){ this->HANDLEFIRMWAREUPDATEPAGE(); });
  _SERVER.begin();
}

void ESP32OTAUpdater::debugPrint(const char* MESSAGE1)
{
  if (DEBUG_FLAG)
  {
    Serial.print(MESSAGE1);
  }
}

void ESP32OTAUpdater::debugPrintln(const char* MESSAGE2)
{
  if (DEBUG_FLAG)
  {
    Serial.println(MESSAGE2);
  }
}

void ESP32OTAUpdater::HANDLECLIENT()
{
  _SERVER.handleClient();
}

// Minimal HTML-escaping so user-controlled values (SSID) can't inject
// markup/script into a page served to anyone on the local network.
String ESP32OTAUpdater::escapeHtml(const String& input)
{
  String output = input;
  output.replace("&", "&amp;");
  output.replace("<", "&lt;");
  output.replace(">", "&gt;");
  output.replace("\"", "&quot;");
  output.replace("'", "&#39;");
  return output;
}

void ESP32OTAUpdater::HANDLEROOT()
{
  String html = FPSTR(ROOT_PAGE_HTML);
  html.replace("%STYLE%", FPSTR(COMMON_STYLE));

  _SERVER.send(200, "text/html", html);
}

void ESP32OTAUpdater::HANDLEWIFICONFIG()
{
  String html = FPSTR(WIFI_CONFIG_PAGE_HTML);
  html.replace("%STYLE%", FPSTR(COMMON_STYLE));
  // Shows the SSID actually in use right now (not secret, safe to display).
  html.replace("%SSID%", escapeHtml(_currentSsid));

  _SERVER.send(200, "text/html", html);
}

void ESP32OTAUpdater::HANDLEFIRMWAREUPDATEPAGE()
{
  String html = FPSTR(FIRMWARE_UPDATE_PAGE_HTML);
  html.replace("%STYLE%", FPSTR(COMMON_STYLE));

  _SERVER.send(200, "text/html", html);
}

void ESP32OTAUpdater::HANDLESAVE()
{
  if (_SERVER.method() == HTTP_POST)
  {
    String newSsid = _SERVER.arg("SSID");
    String newPassword = _SERVER.arg("PASSWORD");

    // If the password field was left blank, keep whatever password is
    // already saved instead of overwriting it with an empty string.
    if (newPassword.length() == 0)
    {
      newPassword = _PREFERENCES.getString("PASSWORD", _PASSWORD);
    }

    _PREFERENCES.putString("SSID", newSsid);
    _PREFERENCES.putString("PASSWORD", newPassword);
    _currentSsid = newSsid;

    _SERVER.send(200, "text/plain", "Wi-Fi credentials saved. Rebooting...");
    delay(1000);
    ESP.restart();
  }
}

void ESP32OTAUpdater::HANDLERESET()
{
  // Clear the Wi-Fi credentials from preferences
  _PREFERENCES.clear();
  _SERVER.send(200, "text/plain", "Wi-Fi credentials reset. Rebooting...");
  delay(1000);
  ESP.restart();
}

void ESP32OTAUpdater::SENDUPDATERESPONSEANDRESTART()
{
  _SERVER.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
  delay(1000);
  ESP.restart();
}

void ESP32OTAUpdater::HANDLEFIRMWAREUPDATE()
{
  HTTPUpload& upload = _SERVER.upload();
  Update.begin(UPDATE_SIZE_UNKNOWN);
  if (upload.status == UPLOAD_FILE_WRITE)
  {
    Update.write(upload.buf, upload.currentSize);
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    Update.end(true);
  }
}

#ifndef ESP32OTAUPDATER_H
#define ESP32OTAUPDATER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ESPmDNS.h>
#include <Update.h>

class ESP32OTAUpdater {
public:
  ESP32OTAUpdater(const char* HOSTNAME, const char* SSID, const char* PASSWORD);
  void BEGIN();
  void HANDLECLIENT();

private:
  const char* _HOSTNAME;
  const char* _SSID;      // Fallback/default SSID passed at construction time
  const char* _PASSWORD;  // Fallback/default password passed at construction time
  const int MAX_WIFI_CONNECT_ATTEMPTS = 8;
  WebServer _SERVER;
  Preferences _PREFERENCES;
  bool DEBUG_FLAG;

  // Tracks whatever SSID is actually active right now (loaded from flash on
  // boot, updated whenever the user saves new credentials) — kept separate
  // from _SSID/_PASSWORD above, which are just the constructor's defaults.
  // Previously the config page always displayed the constructor defaults,
  // even after a user saved different credentials through the web form.
  String _currentSsid;

  void debugPrint(const char* MESSAGE1);
  void debugPrintln(const char* MESSAGE2);
  void HANDLEROOT();
  void HANDLEWIFICONFIG();
  void HANDLEFIRMWAREUPDATEPAGE();
  void HANDLESAVE();
  void HANDLERESET();
  void SENDUPDATERESPONSEANDRESTART();
  void HANDLEFIRMWAREUPDATE();
  String escapeHtml(const String& input);
};

#endif

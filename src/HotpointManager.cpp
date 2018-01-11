#include "HotpointManager.h"
#include <WiFiManager.h>
#include "config/configuration.h"

bool HotpointManager::connectOnWifi() {
    wifiManager.autoConnect(HOTPOINT_SSID, HOTPOINT_PASSWORD);
    return true;
}

void HotpointManager::setCallBack(void (*callback)(WiFiManager* myWiFiManager) ) {
    wifiManager.setAPCallback(callback);
}

void HotpointManager::reset() {
    wifiManager.resetSettings();
}
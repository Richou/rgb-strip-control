#include "RGBControl.h"
#include <Arduino.h>

// Yes that's ugly, but I had to do like so ...
void configModeCallback(WiFiManager *myWiFiManager) {
    LCDScreenManager* screen = new LCDScreenManager();
    screen->initialize();
    screen->clear();
    screen->println("Configure WiFi On");
    screen->print("SSID : ");
    screen->println(myWiFiManager->getConfigPortalSSID());
    screen->print("IP : ");
    screen->println(WiFi.softAPIP().toString());
}

void RGBControl::initialize() {
    Serial.begin(9600);
    screen = new LCDScreenManager();
    screen->initialize();
    screen->displaySplashscreen();
    delay(3000);
    hotpointManager = new HotpointManager();
    hotpointManager->setCallBack(configModeCallback);
    screen->clear();
    screen->println("Connecting to WiFi ...");
    if (hotpointManager->connectOnWifi()) {
        server = new ESP8266WebServer(80);
        analogWriteRange(RGB_PWMRANGE);
        screen->clear();
        screen->println("Connected on : ");
        screen->println(WiFi.SSID());
        screen->print("Ip : ");
        screen->println(WiFi.localIP().toString());
    }
}

void RGBControl::handleClient() {
    server->handleClient();
}

void RGBControl::perform() {
    _set_color_route();
    _set_reset_settings_route();
    server->begin();
}

void RGBControl::_set_color_route() {
    server->on("/color", [&]() {        
        if (server->hasArg(red_param_key) && server->hasArg(blue_param_key) && server->hasArg(blue_param_key)) {
            int redRange = _convert_string_to_int(server->arg(red_param_key));
            int greenRange = _convert_string_to_int(server->arg(green_param_key));
            int blueRange = _convert_string_to_int(server->arg(blue_param_key));

            if (redRange > RGB_PWMRANGE) redRange = RGB_PWMRANGE;
            if (greenRange > RGB_PWMRANGE) greenRange = RGB_PWMRANGE;
            if (blueRange > RGB_PWMRANGE) blueRange = RGB_PWMRANGE;
            
            analogWrite(red_output_pin, redRange);
            analogWrite(green_output_pin, greenRange);
            analogWrite(blue_output_pin, blueRange);
            server->send(200, "application/json", "{}");
        } else {
            server->send(400, "application/json", "{\"code\": \"ERR001\", \"message\": \"One of the argument red|green|blue is missing.\"}");
        }
      });
}

void RGBControl::_set_reset_settings_route() {
    server->on("/reset-settings", [&]() {
        hotpointManager->reset();
        server->send(200, "application/json", "{}");
    });
}

int RGBControl::_convert_string_to_int(String toConvert) {
    int toConvertLength = toConvert.length() + 1;
    char convertedChar[toConvertLength];
    toConvert.toCharArray(convertedChar, toConvertLength);
    return atoi(convertedChar);
}
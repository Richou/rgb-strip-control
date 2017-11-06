#include "RGBControl.h"
#include <Arduino.h>

void RGBControl::initialize() {
    hotpointManager = new HotpointManager();
    if (hotpointManager->connectOnWifi()) {
        server = new ESP8266WebServer(80);
        analogWriteRange(RGB_PWMRANGE);
    }
}

void RGBControl::start() {
    server->begin();
}

void RGBControl::handleClient() {
    server->handleClient();
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
            server->send(400, "application/json", "{}");
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
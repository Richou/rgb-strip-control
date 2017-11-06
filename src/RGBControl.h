#include "HotpointManager.h"
#include <ESP8266WebServer.h>

#define RGB_PWMRANGE 255

class RGBControl {
    private:
        HotpointManager* hotpointManager;
        ESP8266WebServer* server;
        const uint8_t red_output_pin = D6;
        const uint8_t green_output_pin = D7;
        const uint8_t blue_output_pin = D5;
        const String red_param_key = "red";
        const String green_param_key = "green";
        const String blue_param_key = "blue";
        int _convert_string_to_int(String toConvert);
        void _set_color_route();
        void _set_reset_settings_route();
    public:
        void initialize();
        void start();
        void setRoutes();
        void handleClient();
};
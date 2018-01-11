#include "WiFiManager.h"

class HotpointManager {
    private:
        WiFiManager wifiManager;
    public:
        void setCallBack(void (*callback)(WiFiManager* myWiFiManager));
        bool connectOnWifi();
        void reset();
};
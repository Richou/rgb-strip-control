#include "WiFiManager.h"

class HotpointManager {
    private:
        WiFiManager wifiManager;
    public:
        bool connectOnWifi();
        void reset();
};
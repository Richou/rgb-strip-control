#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN
#define I2C_ADDRESS 0x3C

class LCDScreenManager {
    private:
        Adafruit_SSD1306* display;
    public:
        void initialize();
        void clear();
        void println(const String &text);
        void print(const String &text);
};
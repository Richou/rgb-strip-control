#include "LCDScreenManager.h"

void LCDScreenManager::initialize() {
    display = new Adafruit_SSD1306(OLED_RESET);
    display->begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS);
    display->clearDisplay();
    display->setCursor(0,0);
}

void LCDScreenManager::clear() {
    display->clearDisplay();
    display->setCursor(0,0);
}

void LCDScreenManager::println(const String &text) {
    _setDefaultTextAndColor();
    display->println(text);
    display->display();
}

void LCDScreenManager::print(const String &text) {
    _setDefaultTextAndColor();
    display->print(text);
    display->display();
}

void LCDScreenManager::_setDefaultTextAndColor() {
    display->setTextSize(1);
    display->setTextColor(WHITE);
}
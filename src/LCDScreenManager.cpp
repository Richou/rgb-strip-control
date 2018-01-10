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

void LCDScreenManager::printText(const String &text) {
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->println(text);
    display->display();
}
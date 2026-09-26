#ifndef LOGO_H
#define LOGO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

inline void drawLogo(Adafruit_SSD1306 &display) {
  display.clearDisplay();

  // Estrella
  display.fillTriangle(64, 2, 76, 42, 110, 42, SSD1306_WHITE);
  display.fillTriangle(64, 2, 52, 42, 18, 42, SSD1306_WHITE);
  display.fillTriangle(18, 42, 46, 48, 36, 62, SSD1306_WHITE);
  display.fillTriangle(110, 42, 82, 48, 92, 62, SSD1306_WHITE);

  display.display();
}

#endif
/**
 * ============================================================================
 * LOGO.H — PANTALLA DE CARGA / ANIMACIÓN INICIAL DE LLAMA (32x32)
 * Soporte Técnico (3° BGU Técnico) — Unidad Educativa Técnico Salesiano
 * ============================================================================
 * Almacena el bitmap monocromático de un fueguito centrado y optimizado.
 * ============================================================================
 */

#ifndef LOGO_H
#define LOGO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 128
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 64
#endif

// Dimensiones de la imagen del fueguito
#define FLAME_WIDTH  32
#define FLAME_HEIGHT 32

// ============================================================================
// BITMAP MONOCROMÁTICO DE UNA LLAMA (32x32 píxeles) - Optimizado para PROGMEM
// ============================================================================
const unsigned char fueguito_32x32[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xe0, 0x00, 
  0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xd8, 0x00, 
  0x00, 0x1f, 0xdc, 0x00, 0x00, 0x3f, 0xce, 0x00, 0x00, 0x7f, 0xce, 0x00, 0x00, 0x7f, 0xcf, 0x00, 
  0x00, 0xff, 0x8f, 0x00, 0x01, 0xff, 0x0f, 0x80, 0x03, 0xfe, 0x07, 0x80, 0x03, 0xfc, 0x07, 0xc0, 
  0x07, 0xf8, 0x03, 0xc0, 0x07, 0xf0, 0x03, 0xe0, 0x0f, 0xe0, 0x01, 0xe0, 0x0f, 0xc0, 0x01, 0xf0, 
  0x1f, 0x80, 0x00, 0xf0, 0x1f, 0x00, 0x00, 0xf8, 0x3f, 0x00, 0x00, 0x78, 0x3e, 0x00, 0x00, 0x7c, 
  0x3e, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x3e, 0x3c, 0x00, 0x00, 0x1e, 0x1e, 0x00, 0x00, 0x1f, 
  0x0f, 0x00, 0x00, 0x0f, 0x07, 0x80, 0x00, 0x1f, 0x03, 0xc0, 0x00, 0x3e, 0x00, 0xff, 0xff, 0xfc
};

/**
 * Dibuja el fueguito perfectamente centrado en la pantalla OLED de 128x64.
 *
 * @param disp Referencia al objeto display del archivo principal.
 */
inline void drawWelcomeLogo(Adafruit_SSD1306 &disp) {
  disp.clearDisplay();

  // Cálculo matemático para centrar un elemento de 32x32 en una pantalla de 128x64
  // X = (128 - 32) / 2 = 48
  // Y = (64 - 32) / 2 = 16
  int16_t x_centro = (SCREEN_WIDTH - FLAME_WIDTH) / 2;
  int16_t y_centro = (SCREEN_HEIGHT - FLAME_HEIGHT) / 2;

  // Dibuja el bitmap usando la librería oficial Adafruit_GFX
  disp.drawBitmap(x_centro, y_centro, fueguito_32x32, FLAME_WIDTH, FLAME_HEIGHT, SSD1306_WHITE);
  disp.display();
  
  delay(3000); // Mantiene el fueguito visible por 3 segundos exactos
  
  disp.clearDisplay();
  disp.display();
}

#endif // LOGO_H

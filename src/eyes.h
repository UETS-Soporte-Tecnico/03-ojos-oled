/**
 * ============================================================================
 * EYES.H — CATÁLOGO DE EXPRESIONES OCULARES OLED (128x64)
 * Soporte Técnico (3° BGU Técnico) — Unidad Educativa Técnico Salesiano
 * ============================================================================
 * Wrapper modular de la librería oficial Irisoled para ESP32 y SSD1306.
 * ============================================================================
 */

#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Irisoled.h>
#include <IrisoledAnimation.h>

// Dimensiones estándar del display OLED
#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 128  
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 64
#endif

// ============================================================================
// ALIAS AMIGABLES A LAS MATRICES EN PROGMEM DE IRISOLED
// ============================================================================
#define eye_normal     Irisoled::normal
#define eye_happy      Irisoled::happy
#define eye_alert      Irisoled::alert
#define eye_sleepy     Irisoled::sleepy
#define eye_blink      Irisoled::blink
#define eye_blink_down Irisoled::blink_down
#define eye_look_left  Irisoled::look_left
#define eye_look_right Irisoled::look_right
#define eye_excited    Irisoled::excited

/**
 * Renderiza de forma inmediata un bitmap de expresión en la pantalla OLED.
 */
inline void drawEyeExpression(Adafruit_SSD1306 &display, const unsigned char* eyeBitmap) {
  display.clearDisplay();
  display.drawBitmap(0, 0, eyeBitmap, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

#endif // EYES_H

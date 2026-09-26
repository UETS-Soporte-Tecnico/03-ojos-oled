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

// ALIAS AMIGABLES A LAS MATRICES EN PROGMEM DE IRISOLED

#define eye_normal     Irisoled::normal
#define eye_happy      Irisoled::happy
#define eye_alert      Irisoled::alert
#define eye_sleepy     Irisoled::sleepy
#define eye_blink      Irisoled::blink
#define eye_blink_down Irisoled::blink_down
#define eye_look_left  Irisoled::look_left
#define eye_look_right Irisoled::look_right
#define eye_excited    Irisoled::excited

//ALIAS PARA ANIMACIONES NUEVAS
#define eye_bored      Irisoled::bored
#define eye_focused    Irisoled::focused
#define eye_wink_left  Irisoled::wink_left
#define eye_sad        Irisoled::sad
#define eye_angry      Irisoled::angry

#define eye_look_up    Irisoled::look_up
#define eye_look_down  Irisoled::look_down
#define eye_wink_left    Irisoled::wink_left

#define eye_look_down    Irisoled::look_down
#define eye_look_up      Irisoled::look_up
#define eye_worried      Irisoled::worried
#define eye_focused      Irisoled::focused
#define eye_furious      Irisoled::furious
#define icon_battery_full Irisoled::battery_full
/**
 * Renderiza de forma inmediata un bitmap de expresión en la pantalla OLED.
 * Limpia el buffer previo, dibuja el bitmap monocromático y vuelca el buffer.
 *
 * @param display Referencia a la instancia de Adafruit_SSD1306.
 * @param eyeBitmap Puntero a la matriz del bitmap almacenada en PROGMEM.
 */
inline void drawEyeExpression(Adafruit_SSD1306 &display, const unsigned char* eyeBitmap) {
  display.clearDisplay();
  display.drawBitmap(0, 0, eyeBitmap, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

#endif // EYES_H

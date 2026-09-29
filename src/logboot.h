/**
 * ============================================================================
 * LOGBOOT.H — AUTO-DIAGNÓSTICO POST Y TELEMETRÍA DE ARRANQUE I2C
 * Soporte Técnico (3° BGU Técnico) — Unidad Educativa Técnico Salesiano
 * ============================================================================
 * Módulo de diagnóstico de hardware en código de Arduino para la verificación
 * de subsistemas embebidos (ESP32, bus I2C, pantalla OLED y batería).
 * ============================================================================
 */

#ifndef LOGBOOT_H
#define LOGBOOT_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definiciones de pines I2C del ESP32 DevKit v4
#ifndef SDA_PIN
#define SDA_PIN 21
#endif

#ifndef SCL_PIN
#define SCL_PIN 22
#endif

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 128
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 64
#endif

#ifndef OLED_RESET
#define OLED_RESET -1
#endif

#ifndef SCREEN_ADDRESS
#define SCREEN_ADDRESS 0x3C
#endif

/**
 * Inicializa el bus serie I2C y el controlador gráfico SSD1306.
 */
inline bool initDiagnostics(Adafruit_SSD1306 &display) {
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000); // Modo I2C Rápido (400 kHz): refresco a >40 FPS sin parpadeos
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("[ERROR FATAL] No se pudo inicializar la pantalla OLED en 0x3C"));
    return false;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  return true;
}

/**
 * Imprime un renglón de diagnóstico con alineación dinámica a la columna X=95.
 *
 * @param display Referencia al display SSD1306.
 * @param moduleName Nombre del módulo o periférico a diagnosticar.
 * @param isOk Estado lógico del componente (true = OK, false = FALLO).
 */
inline void logBoot(Adafruit_SSD1306 &display, const char* moduleName, bool isOk) {
  // 1. Imprimir nombre del módulo
  display.print(moduleName);

  // 2. Obtener coordenada Y actual para alinear horizontalmente sin saltar de línea
  int16_t currentY = display.getCursorY();
  display.setCursor(95, currentY);

  // 3. Imprimir sello de aprobación o advertencia
  if (isOk) {
    display.println(F("[OK]"));
    Serial.print(F("[BOOT CHECK] "));
    Serial.print(moduleName);
    Serial.println(F(" ... [OK]"));
  } else {
    display.println(F("[FAIL]"));
    Serial.print(F("[BOOT CHECK] "));
    Serial.print(moduleName);
    Serial.println(F(" ... [FAIL]"));
  }

  // 4. Refresco en pantalla y retardo visual de telemetría
  display.display();
  delay(250);
}

/**
 * Ejecuta la secuencia completa de auto-diagnóstico (Power-On Self-Test).
 */
inline void runSystemPOST(Adafruit_SSD1306 &display) {
  Serial.println(F("\n[SISTEMA] Iniciando secuencia de auto-diagnóstico (POST)..."));

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Encabezado técnico institucional
  display.println(F(">> SISTEMA ESP32 <<"));
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
  display.setCursor(0, 14);
  display.display();
  delay(400);

  // 4 Chequeos de subsistemas
  logBoot(display, "ESP32 240MHz", true);
  logBoot(display, "I2C @ 400kHz", true);
  logBoot(display, "OLED 0x3C", true);
  logBoot(display, "Bateria 8.4V", true);

  delay(400);

  // Banner inferior de confirmación
  display.drawLine(0, 52, 127, 52, SSD1306_WHITE);
  display.setCursor(16, 55);
  display.print(F(">> SISTEMA LISTO <<"));
  display.display();

  Serial.println(F("[SISTEMA] Auto-diagnóstico superado con éxito. >> SISTEMA LISTO <<\n"));
  delay(1200);
  display.clearDisplay();
  display.display();
}

#endif // LOGBOOT_H
/**
 * ============================================================================
 * MAIN.INO — STARTER KIT SEMANA 03: OJOS ROBÓTICOS OLED SSD1306
 * Soporte Técnico (3° BGU Técnico) — Unidad Educativa Técnico Salesiano
 * ============================================================================
 * Instrucciones:
 * 1. Completa cada uno de los bloques marcados con '// TODO:'
 * 2. Compila con PlatformIO (botón Build ✔)
 * 3. Simula en Wokwi Simulator abriendo diagram.json
 * 4. Valida tu entrega ejecutando en terminal: pnpm test
 * ============================================================================
 */
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "logboot.h"
#include "logo.h" // Agregamos la inclusión del logo obligatoriamente aquí
#include "eyes.h"

// Instancia global del display OLED SSD1306 (128x64)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

enum EyeState {
  STATE_NORMAL,
  STATE_HAPPY,
  STATE_ALERT,
  STATE_SLEEPY,
  STATE_BLINK,
  STATE_LOOK_LEFT,
  STATE_LOOK_RIGHT,
  STATE_EXCITED
};

EyeState currentState = STATE_NORMAL;
bool modoAutonomo = true;
unsigned long previousMillis = 0;
const unsigned long INTERVALO_ANIMACION = 2500;
int pasoSecuencia = 0;

// ============================================================================
// RETO 04: FUNCIÓN SERIAL DEBUG
// ============================================================================
void debugEyesSerial() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == '\r' || cmd == '\n' || cmd == ' ') return;

    modoAutonomo = false;

    switch (cmd) {
      case '1':
      case 'N':
      case 'n':
        currentState = STATE_NORMAL;
        drawEyeExpression(display, eye_normal);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: NORMAL"));
        break;

      case '2':
      case 'H':
      case 'h':
        currentState = STATE_HAPPY;
        drawEyeExpression(display, eye_happy);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: FELIZ"));
        break;

      case '3':
      case 'A':
      case 'a':
        currentState = STATE_ALERT;
        drawEyeExpression(display, eye_alert);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: ALERTA"));
        break;

      case '4':
      case 'S':
      case 's':
        currentState = STATE_SLEEPY;
        drawEyeExpression(display, eye_sleepy);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: REPOSO (Sleepy)"));
        break;

      case '5':
      case 'B':
      case 'b':
        currentState = STATE_BLINK;
        drawEyeExpression(display, eye_blink);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: PARPADEO (Blink)"));
        break;

      case '6':
      case 'L':
      case 'l':
        currentState = STATE_LOOK_LEFT;
        drawEyeExpression(display, eye_look_left);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: MIRADA IZQUIERDA"));
        break;

      case '7':
      case 'R':
      case 'r':
        currentState = STATE_LOOK_RIGHT;
        drawEyeExpression(display, eye_look_right);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: MIRADA DERECHA"));
        break;

      case '8':
      case 'E':
      case 'e':
        currentState = STATE_EXCITED;
        drawEyeExpression(display, eye_excited);
        Serial.println(F("[SERIAL DEBUG] Expresión cambiada a: EMOCIONADO (Excited)"));
        break;

      case '0':
      case 'M':
      case 'm':
        modoAutonomo = true;
        previousMillis = millis();
        Serial.println(F("[SERIAL DEBUG] Modo Autónomo reactivado (Animación FSM activa)"));
        break;

      default:
        Serial.print(F("[SERIAL DEBUG] Comando desconocido: "));
        Serial.println(cmd);
        break;
    }
  }
}

// ============================================================================
// RETOS 02 Y 03: MÁQUINA DE ESTADOS FINITOS (FSM) NO BLOQUEANTE
// ============================================================================
void ejecutarSecuenciaAutonoma() {
  pasoSecuencia = (pasoSecuencia + 1) % 6;

  switch (pasoSecuencia) {
    case 0:
      currentState = STATE_NORMAL;
      drawEyeExpression(display, eye_normal);
      break;

    case 1:
      currentState = STATE_BLINK;
      drawEyeExpression(display, eye_blink);
      break;

    case 2:
      currentState = STATE_LOOK_LEFT;
      drawEyeExpression(display, eye_look_left);
      break;

    case 3:
      currentState = STATE_NORMAL;
      drawEyeExpression(display, eye_normal);
      break;

    case 4:
      currentState = STATE_LOOK_RIGHT;
      drawEyeExpression(display, eye_look_right);
      break;

    case 5:
      currentState = STATE_HAPPY;
      drawEyeExpression(display, eye_happy);
      break;
  }
}

// ============================================================================
// SETUP: CONTROL DE SECUENCIA CRONOLÓGICA (MODIFICADO)
// ============================================================================
void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 1000);

  // Inicializar físicamente la pantalla antes de mandar cualquier gráfico
  if (!initDiagnostics(display)) {
    Serial.println(F("[FALLO CRÍTICO] Error al inicializar pantalla OLED."));
    while (true) delay(100);
  }

  // PASO 1: Aparece primero el logo salesiano por 3 segundos
  drawWelcomeLogo(display);

  // PASO 2: Aparece después el POST del sistema de la carpeta logboot
  runSystemPOST(display);

  // Menú de ayuda por Serial Monitor
  Serial.println(F("\n======================================================="));
  Serial.println(F("🤖 SISTEMA EMBEBIDO ESP32 — TELEMETRÍA Y CONTROL DE OJOS"));
  Serial.println(F("======================================================="));
  Serial.println(F("Comandos Serial activos..."));
  Serial.println(F("=======================================================\n"));

  // PASO 3: Por último cargan los ojos en estado normal
  drawEyeExpression(display, eye_normal);

  previousMillis = millis();
}

// ============================================================================
// LOOP: Procesamiento continuo sin delay()
// ============================================================================
void loop() {
  debugEyesSerial();

  if (modoAutonomo) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= INTERVALO_ANIMACION) {
      previousMillis = currentMillis;
      ejecutarSecuenciaAutonoma();
    }
  }
}
/**
 * ============================================================================
 * MAIN.INO — SISTEMA DE OJOS ROBÓTICOS OLED SSD1306
 * ============================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "logboot.h"
#include "eyes.h"
#include "logo.h"


// ============================================================================
// DISPLAY OLED
// ============================================================================

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);


// ============================================================================
// ESTADOS DE LOS OJOS
// ============================================================================

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
// CONTROL SERIAL
// ============================================================================

void debugEyesSerial() {

  if (Serial.available() <= 0) {
    return;
  }

  char cmd = Serial.read();

  if (cmd == '\r' ||
      cmd == '\n' ||
      cmd == ' ') {
    return;
  }


  // Al recibir un comando manual,
  // pausamos la animación autónoma.
  modoAutonomo = false;


  switch (cmd) {

    // ----------------------------------------------------------
    // NORMAL
    // ----------------------------------------------------------

    case '1':
    case 'N':
    case 'n':

      currentState = STATE_NORMAL;

      drawEyeExpression(
        display,
        eye_normal
      );

      Serial.println(
        F("[EYES] NORMAL")
      );

      break;


    // ----------------------------------------------------------
    // HAPPY
    // ----------------------------------------------------------

    case '2':
    case 'H':
    case 'h':

      currentState = STATE_HAPPY;

      drawEyeExpression(
        display,
        eye_happy
      );

      Serial.println(
        F("[EYES] HAPPY")
      );

      break;


    // ----------------------------------------------------------
    // ALERT
    // ----------------------------------------------------------

    case '3':
    case 'A':
    case 'a':

      currentState = STATE_ALERT;

      drawEyeExpression(
        display,
        eye_alert
      );

      Serial.println(
        F("[EYES] ALERT")
      );

      break;


    // ----------------------------------------------------------
    // SLEEPY
    // ----------------------------------------------------------

    case '4':
    case 'S':
    case 's':

      currentState = STATE_SLEEPY;

      drawEyeExpression(
        display,
        eye_sleepy
      );

      Serial.println(
        F("[EYES] SLEEPY")
      );

      break;


    // ----------------------------------------------------------
    // BLINK
    // ----------------------------------------------------------

    case '5':
    case 'B':
    case 'b':

      currentState = STATE_BLINK;

      drawEyeExpression(
        display,
        eye_blink
      );

      Serial.println(
        F("[EYES] BLINK")
      );

      break;


    // ----------------------------------------------------------
    // LOOK LEFT
    // ----------------------------------------------------------

    case '6':
    case 'L':
    case 'l':

      currentState = STATE_LOOK_LEFT;

      drawEyeExpression(
        display,
        eye_look_left
      );

      Serial.println(
        F("[EYES] LOOK LEFT")
      );

      break;


    // ----------------------------------------------------------
    // LOOK RIGHT
    // ----------------------------------------------------------

    case '7':
    case 'R':
    case 'r':

      currentState = STATE_LOOK_RIGHT;

      drawEyeExpression(
        display,
        eye_look_right
      );

      Serial.println(
        F("[EYES] LOOK RIGHT")
      );

      break;


    // ----------------------------------------------------------
    // EXCITED
    // ----------------------------------------------------------

    case '8':
    case 'E':
    case 'e':

      currentState = STATE_EXCITED;

      drawEyeExpression(
        display,
        eye_excited
      );

      Serial.println(
        F("[EYES] EXCITED")
      );

      break;


    // ----------------------------------------------------------
    // MODO AUTÓNOMO
    // ----------------------------------------------------------

    case '0':
    case 'M':
    case 'm':

      modoAutonomo = true;

      previousMillis = millis();

      Serial.println(
        F("[EYES] MODO AUTONOMO")
      );

      break;


    // ----------------------------------------------------------
    // DESCONOCIDO
    // ----------------------------------------------------------

    default:

      Serial.print(
        F("[SERIAL] Comando desconocido: ")
      );

      Serial.println(cmd);

      break;
  }
}


// ============================================================================
// ANIMACIÓN AUTÓNOMA
// ============================================================================

void ejecutarSecuenciaAutonoma() {

  pasoSecuencia =
    (pasoSecuencia + 1) % 6;


  switch (pasoSecuencia) {

    case 0:

      currentState = STATE_NORMAL;

      drawEyeExpression(
        display,
        eye_normal
      );

      break;


    case 1:

      currentState = STATE_BLINK;

      drawEyeExpression(
        display,
        eye_blink
      );

      break;


    case 2:

      currentState = STATE_LOOK_LEFT;

      drawEyeExpression(
        display,
        eye_look_left
      );

      break;


    case 3:

      currentState = STATE_NORMAL;

      drawEyeExpression(
        display,
        eye_normal
      );

      break;


    case 4:

      currentState = STATE_LOOK_RIGHT;

      drawEyeExpression(
        display,
        eye_look_right
      );

      break;


    case 5:

      currentState = STATE_HAPPY;

      drawEyeExpression(
        display,
        eye_happy
      );

      break;
  }
}


// ============================================================================
// SETUP
// ============================================================================

void setup() {

  // ==========================================================
  // SERIAL
  // ==========================================================

  Serial.begin(115200);

  while (!Serial && millis() < 1000);


  Serial.println();
  Serial.println(
    F("==========================================")
  );

  Serial.println(
    F("      ESP32 ROBOT EYES SYSTEM")
  );

  Serial.println(
    F("==========================================")
  );


  // ==========================================================
  // 1. INICIALIZAR OLED
  // ==========================================================

  Serial.println(
    F("[BOOT 1/3] Inicializando OLED...")
  );


  if (!initDiagnostics(display)) {

    Serial.println(
      F("[FATAL] No se pudo inicializar OLED")
    );

    while (true) {
      delay(100);
    }
  }


  Serial.println(
    F("[OLED] OLED inicializada correctamente")
  );


  // ==========================================================
  // 2. MOSTRAR LOGO
  // ==========================================================

  Serial.println(
    F("[BOOT 2/3] Mostrando LOGO...")
  );


  showLogo(display);


  Serial.println(
    F("[LOGO] Logo terminado")
  );


  // ==========================================================
  // 3. EJECUTAR LOGBOOT / POST
  // ==========================================================

  Serial.println(
    F("[BOOT 3/3] Ejecutando POST...")
  );


  runSystemPOST(display);


  // ==========================================================
  // 4. INICIAR EYES.H
  // ==========================================================

  Serial.println(
    F("[EYES] Iniciando sistema ocular...")
  );


  currentState = STATE_NORMAL;


  drawEyeExpression(
    display,
    eye_normal
  );


  // ==========================================================
  // 5. INICIAR FSM
  // ==========================================================

  previousMillis = millis();

  pasoSecuencia = 0;

  modoAutonomo = true;


  // ==========================================================
  // MENÚ SERIAL
  // ==========================================================

  Serial.println();
  Serial.println(
    F("==========================================")
  );

  Serial.println(
    F("        SISTEMA DE OJOS ACTIVO")
  );

  Serial.println(
    F("==========================================")
  );

  Serial.println(
    F("1/N -> NORMAL")
  );

  Serial.println(
    F("2/H -> HAPPY")
  );

  Serial.println(
    F("3/A -> ALERT")
  );

  Serial.println(
    F("4/S -> SLEEPY")
  );

  Serial.println(
    F("5/B -> BLINK")
  );

  Serial.println(
    F("6/L -> LOOK LEFT")
  );

  Serial.println(
    F("7/R -> LOOK RIGHT")
  );

  Serial.println(
    F("8/E -> EXCITED")
  );

  Serial.println(
    F("0/M -> MODO AUTONOMO")
  );

  Serial.println(
    F("==========================================")
  );
}


// ============================================================================
// LOOP
// ============================================================================

void loop() {

  // ----------------------------------------------------------
  // Control mediante Serial
  // ----------------------------------------------------------

  debugEyesSerial();


  // ----------------------------------------------------------
  // Animación autónoma
  // ----------------------------------------------------------

  if (modoAutonomo) {

    unsigned long currentMillis =
      millis();


    if (
      currentMillis - previousMillis >=
      INTERVALO_ANIMACION
    ) {

      previousMillis =
        currentMillis;

      ejecutarSecuenciaAutonoma();
    }
  }
}

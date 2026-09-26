#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "logboot.h"
#include "eyes.h"

// DISPLAY

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// ESTADOS TOTALES (Nuevos de eyes.h)

enum EyeState {

  STATE_NORMAL,
  STATE_HAPPY,
  STATE_ALERT,
  STATE_SLEEPY,
  STATE_BLINK,

  STATE_LOOK_LEFT,
  STATE_LOOK_RIGHT,
  STATE_LOOK_DOWN,
  STATE_LOOK_UP,

  STATE_EXCITED,

  STATE_WINK_LEFT,
  STATE_WORRIED,
  STATE_FOCUSED,
  STATE_FURIOUS
};

EyeState currentState = STATE_NORMAL;

// CONTROL FSM

bool modoAutonomo = true;

unsigned long previousMillis = 0;

// Velocidad general de cambio de expresiones
const unsigned long INTERVALO_ANIMACION = 500;

int pasoSecuencia = 0;


// INICIALES + TRANSICIÓN

void mostrarInicialesYTransicion() {

  // MOSTRAR "AS"

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(5);

  display.setCursor(20, 15);

  display.print(F("AS"));

  display.display();

  delay(1200);


  // PANTALLA COMPLETAMENTE BLANCA

  display.clearDisplay();

  display.fillRect(
    0,
    0,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SSD1306_WHITE
  );

  display.display();

  delay(350);


  // LIMPIAR PANTALLA

  display.clearDisplay();
  display.display();

  delay(150);
}


// DEBUG SERIAL

void debugEyesSerial() {

  if (Serial.available() > 0) {

    char cmd = Serial.read();

    if (
      cmd == '\r' ||
      cmd == '\n' ||
      cmd == ' '
    ) {
      return;
    }


    // Al usar control manual se pausa la FSM
    modoAutonomo = false;


    switch (cmd) {

      // NORMAL

      case '1':
      case 'N':
      case 'n':

        currentState = STATE_NORMAL;

        drawEyeExpression(
          display,
          eye_normal
        );

        Serial.println(
          F("[SERIAL DEBUG] NORMAL")
        );

        break;


      // HAPPY

      case '2':
      case 'H':
      case 'h':

        currentState = STATE_HAPPY;

        drawEyeExpression(
          display,
          eye_happy
        );

        Serial.println(
          F("[SERIAL DEBUG] FELIZ")
        );

        break;


      // ALERT

      case '3':
      case 'A':
      case 'a':

        currentState = STATE_ALERT;

        drawEyeExpression(
          display,
          eye_alert
        );

        Serial.println(
          F("[SERIAL DEBUG] ALERTA")
        );

        break;


      // SLEEPY

      case '4':
      case 'S':
      case 's':

        currentState = STATE_SLEEPY;

        drawEyeExpression(
          display,
          eye_sleepy
        );

        Serial.println(
          F("[SERIAL DEBUG] SLEEPY")
        );

        break;


      // BLINK

      case '5':
      case 'B':
      case 'b':

        currentState = STATE_BLINK;

        drawEyeExpression(
          display,
          eye_blink
        );

        Serial.println(
          F("[SERIAL DEBUG] BLINK")
        );

        break;


      // LOOK LEFT

      case '6':
      case 'L':
      case 'l':

        currentState = STATE_LOOK_LEFT;

        drawEyeExpression(
          display,
          eye_look_left
        );

        Serial.println(
          F("[SERIAL DEBUG] MIRADA IZQUIERDA")
        );

        break;


      // LOOK RIGHT

      case '7':
      case 'R':
      case 'r':

        currentState = STATE_LOOK_RIGHT;

        drawEyeExpression(
          display,
          eye_look_right
        );

        Serial.println(
          F("[SERIAL DEBUG] MIRADA DERECHA")
        );

        break;


      // EXCITED

      case '8':
      case 'E':
      case 'e':

        currentState = STATE_EXCITED;

        drawEyeExpression(
          display,
          eye_excited
        );

        Serial.println(
          F("[SERIAL DEBUG] EMOCIONADO")
        );

        break;


      // REACTIVAR MODO AUTÓNOMO

      case '0':
      case 'M':
      case 'm':

        modoAutonomo = true;

        previousMillis = millis();

        Serial.println(
          F("[SERIAL DEBUG] MODO AUTONOMO ACTIVADO")
        );

        break;


      // COMANDO DESCONOCIDO

      default:

        Serial.print(
          F("[SERIAL DEBUG] Comando desconocido: ")
        );

        Serial.println(cmd);

        break;
    }
  }
}


// SECUENCIA AUTÓNOMA

void ejecutarSecuenciaAutonoma() {

  pasoSecuencia = (pasoSecuencia + 1) % 14;


  switch (pasoSecuencia) {

    // NORMAL

    case 0:

      currentState = STATE_NORMAL;

      drawEyeExpression(
        display,
        eye_normal
      );

      break;


    // WINK LEFT

    case 1:

      currentState = STATE_WINK_LEFT;

      drawEyeExpression(
        display,
        eye_wink_left
      );

      break;


    // BLINK

    case 2:

      currentState = STATE_BLINK;

      drawEyeExpression(
        display,
        eye_blink
      );

      break;


    // ALERT

    case 3:

      currentState = STATE_ALERT;

      drawEyeExpression(
        display,
        eye_alert
      );

      break;


    // LOOK LEFT

    case 4:

      currentState = STATE_LOOK_LEFT;

      drawEyeExpression(
        display,
        eye_look_left
      );

      break;


    // LOOK RIGHT

    case 5:

      currentState = STATE_LOOK_RIGHT;

      drawEyeExpression(
        display,
        eye_look_right
      );

      break;


    // LOOK DOWN

    case 6:

      currentState = STATE_LOOK_DOWN;

      drawEyeExpression(
        display,
        eye_look_down
      );

      break;


    // LOOK UP

    case 7:

      currentState = STATE_LOOK_UP;

      drawEyeExpression(
        display,
        eye_look_up
      );

      break;


    // WORRIED

    case 8:

      currentState = STATE_WORRIED;

      drawEyeExpression(
        display,
        eye_worried
      );

      break;


    // FOCUSED

    case 9:

      currentState = STATE_FOCUSED;

      drawEyeExpression(
        display,
        eye_focused
      );

      break;


    // SLEEPY

    case 10:

      currentState = STATE_SLEEPY;

      drawEyeExpression(
        display,
        eye_sleepy
      );

      break;


    // FOCUSED

    case 11:

      currentState = STATE_FOCUSED;

      drawEyeExpression(
        display,
        eye_focused
      );

      break;


    // FURIOUS

    case 12:

      currentState = STATE_FURIOUS;

      drawEyeExpression(
        display,
        eye_furious
      );

      break;


    // NORMAL

    case 13:

      currentState = STATE_NORMAL;

      drawEyeExpression(
        display,
        eye_normal
      );

      break;
  }
}


// SETUP

void setup() {

  // INICIAR SERIAL

  Serial.begin(115200);

  while (
    !Serial &&
    millis() < 1000
  );


  // INICIALIZACIÓN I2C + OLED

  if (!initDiagnostics(display)) {

    Serial.println(
      F("[FALLO CRITICO] No se pudo inicializar OLED.")
    );

    while (true) {
      delay(100);
    }
  }


  // TODO 1.1 - POST

  runSystemPOST(display);


  // INICIALES AS + TRANSICIÓN

  mostrarInicialesYTransicion();


  // BATTERY FULL

  drawEyeExpression(
    display,
    icon_battery_full
  );

  delay(800);


  // TODO 1.2 - EXPRESIÓN NORMAL

  currentState = STATE_NORMAL;

  drawEyeExpression(
    display,
    eye_normal
  );


  // MENÚ SERIAL

  Serial.println(
    F("\n==============================================")
  );

  Serial.println(
    F("ESP32 - CONTROL OJOS OLED")
  );

  Serial.println(
    F("==============================================")
  );

  Serial.println(
    F("1 / N -> Normal")
  );

  Serial.println(
    F("2 / H -> Happy")
  );

  Serial.println(
    F("3 / A -> Alert")
  );

  Serial.println(
    F("4 / S -> Sleepy")
  );

  Serial.println(
    F("5 / B -> Blink")
  );

  Serial.println(
    F("6 / L -> Look Left")
  );

  Serial.println(
    F("7 / R -> Look Right")
  );

  Serial.println(
    F("8 / E -> Excited")
  );

  Serial.println(
    F("0 / M -> Modo autonomo")
  );

  Serial.println(
    F("==============================================\n")
  );


  previousMillis = millis();
}


// LOOP

void loop() {

  // Control manual por Serial
  debugEyesSerial();


  // Máquina de estados automática
  if (modoAutonomo) {

    unsigned long currentMillis = millis();


    if (
      currentMillis - previousMillis
      >= INTERVALO_ANIMACION
    ) {

      previousMillis = currentMillis;

      ejecutarSecuenciaAutonoma();
    }
  }
}
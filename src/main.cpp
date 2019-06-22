#include <Arduino.h>
#include "pins/pins.h"
#include "counter/counter.h"
#include "lcd/lcd.h"
#include "modes/modes.h"

#define AUTOMATIC 0
#define MANUAL_FORWARD 1
#define MANUAL_REVERSE 2

int currentMode = 2;

void checkMode() {
  int automaticButtonState = checkIfPinIsActive(AUTOMATIC_MODE_BUTTON_PIN, AUTOMATIC_MODE_BUTTON_PIN_ACTIVE, AUTOMATIC_MODE_BUTTON_PIN_INACTIVE);
  int manualButtonState = checkIfPinIsActive(MANUAL_MODE_BUTTON_PIN, MANUAL_MODE_BUTTON_PIN_ACTIVE, MANUAL_MODE_BUTTON_PIN_INACTIVE);

  if (automaticButtonState == AUTOMATIC_MODE_BUTTON_PIN_ACTIVE) {
    currentMode = AUTOMATIC;
  }
  else if (manualButtonState == MANUAL_MODE_BUTTON_PIN_ACTIVE) {
    currentMode = MANUAL_FORWARD;
  }
  else {
    currentMode = MANUAL_REVERSE;
  }
}

void setup() {
  setupPins();
  setupInterrupt();
  setupLcd();
  setImpulsPerMeter();

  char message[20];
  sprintf(message, "Gotowy do pracy.");
  printLcd(message);
}

void loop() {
  checkMode();

  switch (currentMode) {
    case AUTOMATIC:
      automaticMode();
      currentMode = MANUAL_REVERSE;
      break;
    case MANUAL_FORWARD:
      manualForwardMode();
      char message[20];
      sprintf(message, "Gotowy do pracy.");
      printLcd(message);
      currentMode = MANUAL_REVERSE;
      break;
    default:
      manualReverseMode();
      break;
  }
}
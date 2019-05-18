#include <Arduino.h>
#include "engine/engine.h"
#include "pins/pins.h"
#include "counter/counter.h"
#include "lcd/lcd.h"

#define IS_AUTOMATIC 1
#define IS_NOT_AUTOMATIC 0

/*
############################# HELPER FUNCTIONS ######################################
*/


bool checkAbortPinIsActive() {
 return checkIfPinIsActive(ABORT_PIN, ABORT_PIN_ACTIVE, ABORT_PIN_INACTIVE, 1) == ABORT_PIN_ACTIVE;
}

bool checkOperationalButtonIsActive() {
  return checkIfPinIsActive(OPERATIONAL_BUTTON_PIN, OPERATIONAL_BUTTON_PIN_ACTIVE, OPERATIONAL_BUTTON_PIN_INACTIVE, 1) == OPERATIONAL_BUTTON_PIN_ACTIVE;
}

void automaticModeEndState() {
  stopEngine();

  const float lenght = caluclateLenght();
  char message[20];

  sprintf(message, "Dlugosc dyw. ");
  printLcd(message, lenght);

  setCurrentDirection(REVERSE);
  delay(2000);
}

void resolveModeEndState(int isAutomaticMode) {
  if (isAutomaticMode == IS_AUTOMATIC) {
    automaticModeEndState();
  }
  else {
    setCurrentDirection(REVERSE);
  }
}

int resolveModeState(int isAutomaticMode) {
  resolveDirection();

  if (getCurrentDirection() == FORWARD && checkOperationalButtonIsActive()) {
    startEngineForward();
  }
  else if (getCurrentDirection() == REVERSE && checkOperationalButtonIsActive()) {
    setCanCount(CAN_NOT_INCREMENT);
    startEngineReverse();
  }
  else if (getCurrentDirection() == END_STATE) {
    resolveModeEndState(isAutomaticMode);
    return 0;
  }

  return 1;
}

void forwardModsSetup(int lampPin, int lampPinActiveState, int canIncrement, const char* message) {
  char output[20];
  sprintf(output, message);
  printLcd(output);

  setEngineStateForForwardMode();
  
  digitalWrite(lampPin, lampPinActiveState);
  
  setCanCount(canIncrement);
  
}


/*
############################# EXPORTED FUNCTIONS ####################################
*/


void automaticMode() {
  int modeInProggress = 1;
  bool abortPinIsActive = checkAbortPinIsActive();

  forwardModsSetup(AUTOMATIC_MODE_LAMP_PIN, AUTOMATIC_MODE_LAMP_PIN_ACTIVE, CAN_INCREMENT, "Tryb automatyczny..");
  resetCounter();

  while (modeInProggress && !abortPinIsActive) {
    if (checkOperationalButtonIsActive() && !abortPinIsActive) {
      modeInProggress = resolveModeState(IS_AUTOMATIC);
    }
    else {
      stopEngine();
    }

    abortPinIsActive = checkAbortPinIsActive();
  }

  if (abortPinIsActive) {
    printLcd("Gotowy do pracy.");
  }

  digitalWrite(AUTOMATIC_MODE_LAMP_PIN, AUTOMATIC_MODE_LAMP_PIN_INACTIVE);
}

void manualForwardMode() {
  int modeInProggress = 1;
  bool abortPinIsActive = checkAbortPinIsActive();

  forwardModsSetup(MANUAL_MODE_LAMP_PIN, MANUAL_MODE_LAMP_PIN_ACTIVE, CAN_NOT_INCREMENT, "Tryb man. w przod..");
  
  while (modeInProggress && !abortPinIsActive) {
    if (checkOperationalButtonIsActive() && !abortPinIsActive) {
      modeInProggress = resolveModeState(IS_NOT_AUTOMATIC);
    }
    else {
      stopEngine();
    }

    abortPinIsActive = checkAbortPinIsActive();
  }

  digitalWrite(MANUAL_MODE_LAMP_PIN, MANUAL_MODE_LAMP_PIN_INACTIVE);
}

void manualReverseMode() {
  setEngineStateForManualReverseMode();

  bool operationalButtonIsActive = checkOperationalButtonIsActive();

  while (operationalButtonIsActive) {
    if (operationalButtonIsActive) {
      startEngineReverse();
    }
    else {
      stopEngine();
    }

    operationalButtonIsActive = checkOperationalButtonIsActive();
  }
}
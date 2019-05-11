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


bool checkEmergencyPinIsActive() {
 return checkIfPinIsActive(EMERGENCY_STOP_PIN, EMERGENCY_STOP_PIN_ACTIVE, EMERGENCY_STOP_PIN_INACTIVE, 0) == EMERGENCY_STOP_PIN_ACTIVE;
}

bool checkSecurityButtonIsActive() {
  return checkIfPinIsActive(SECURITY_BUTTON_PIN, SECURITY_BUTTON_PIN_ACTIVE, SECURITY_BUTTON_PIN_INACTIVE, 1) == SECURITY_BUTTON_PIN_ACTIVE;
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

  if (getCurrentDirection() == FORWARD && checkSecurityButtonIsActive()) {
    startEngineForward();
  }
  else if (getCurrentDirection() == REVERSE && checkSecurityButtonIsActive()) {
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
  bool emergencyPinIsActive = checkEmergencyPinIsActive();

  forwardModsSetup(AUTOMATIC_MODE_LAMP_PIN, AUTOMATIC_MODE_LAMP_PIN_ACTIVE, CAN_INCREMENT, "Tryb automatyczny..");

  while (modeInProggress && !emergencyPinIsActive) {
    emergencyPinIsActive = checkEmergencyPinIsActive();

    if (checkSecurityButtonIsActive() && !emergencyPinIsActive) {
      modeInProggress = resolveModeState(IS_AUTOMATIC);
    }
    else {
      stopEngine();
    }
  }

  digitalWrite(AUTOMATIC_MODE_LAMP_PIN, AUTOMATIC_MODE_LAMP_PIN_INACTIVE);
}

void manualForwardMode() {
  int modeInProggress = 1;
  bool emergencyPinIsActive = checkEmergencyPinIsActive();

  forwardModsSetup(MANUAL_MODE_LAMP_PIN, MANUAL_MODE_LAMP_PIN_ACTIVE, CAN_NOT_INCREMENT, "Tryb man. w przod..");
  
  while (modeInProggress && !emergencyPinIsActive) {
    if (checkSecurityButtonIsActive() && !emergencyPinIsActive) {
      modeInProggress = resolveModeState(IS_NOT_AUTOMATIC);
    }
    else {
      stopEngine();
    }

    emergencyPinIsActive = checkEmergencyPinIsActive();
  }

  digitalWrite(MANUAL_MODE_LAMP_PIN, MANUAL_MODE_LAMP_PIN_INACTIVE);
}

void manualReverseMode() {
  setEngineStateForManualReverseMode();

  bool securityButtonIsActive = checkSecurityButtonIsActive();
  bool emergencyPinIsActive = checkEmergencyPinIsActive();

  while (securityButtonIsActive && !emergencyPinIsActive) {
    if (securityButtonIsActive && !emergencyPinIsActive) {
      startEngineReverse();
    }
    else {
      stopEngine();
    }

    securityButtonIsActive = checkSecurityButtonIsActive();
    emergencyPinIsActive = checkEmergencyPinIsActive();
  }
}
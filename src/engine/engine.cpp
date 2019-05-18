#include <Arduino.h>
#include "pins/pins.h"
#include "engine.h"

#define DIRECTION_CHANGE_DELAY 100

// state variables
static char engineNotRun;
static int enginePreviousDirection;
static int currentDirection;

static int opticalSensorPrevState;

void resolveDirection() {
  int opticalSensorVal = checkIfPinIsActive(OPTICAL_SENSOR_PIN, OPTICAL_SENSOR_PIN_ACTIVE, OPTICAL_SENSOR_PIN_INACTIVE);

  if (currentDirection == FORWARD) { 
    if (opticalSensorVal != opticalSensorPrevState && opticalSensorPrevState == OPTICAL_SENSOR_PIN_ACTIVE) {
      currentDirection = REVERSE;
    }
  }
  else if (currentDirection == REVERSE) {
    if (opticalSensorVal != opticalSensorPrevState && opticalSensorPrevState == OPTICAL_SENSOR_PIN_ACTIVE) {
      currentDirection = END_STATE;
    }
  }

  opticalSensorPrevState = opticalSensorVal;
}

void stopEngine() {
  engineNotRun = 1;
  digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_INACTIVE);
}

void startEngineForward() {
  if (enginePreviousDirection == REVERSE) {
    digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_INACTIVE);

    delay(DIRECTION_CHANGE_DELAY);

    digitalWrite(ENGINE_REVERS_PIN, ENGINE_REVERS_PIN_INACTIVE);

    delay(DIRECTION_CHANGE_DELAY);

    digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_ACTIVE);
  }
  else if (engineNotRun) {
    digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_ACTIVE);
  }

  engineNotRun = 0;
  enginePreviousDirection = FORWARD;
}

void startEngineReverse() {
  if (enginePreviousDirection == FORWARD) {
    digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_INACTIVE);

    delay(DIRECTION_CHANGE_DELAY);

    digitalWrite(ENGINE_REVERS_PIN, ENGINE_REVERS_PIN_ACTIVE);

    delay(DIRECTION_CHANGE_DELAY);

    digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_ACTIVE);
  }
  else if (engineNotRun) {
    digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_ACTIVE);
  }

  engineNotRun = 0;
  enginePreviousDirection = REVERSE;
}

int getCurrentDirection() {
  return currentDirection;
}

void setCurrentDirection(int direction) {
   currentDirection = direction;
}

void setEngineStateForForwardMode() {
  engineNotRun = 1;
  currentDirection = FORWARD;
  enginePreviousDirection = currentDirection;
  opticalSensorPrevState = OPTICAL_SENSOR_PIN_INACTIVE;

  digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_INACTIVE);
  digitalWrite(ENGINE_REVERS_PIN, ENGINE_REVERS_PIN_INACTIVE);
}

void setEngineStateForManualReverseMode() {
  engineNotRun = 1;
  currentDirection = REVERSE;
  enginePreviousDirection = currentDirection;
  opticalSensorPrevState = OPTICAL_SENSOR_PIN_INACTIVE;

  digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_INACTIVE);
  digitalWrite(ENGINE_REVERS_PIN, ENGINE_REVERS_PIN_ACTIVE);
}
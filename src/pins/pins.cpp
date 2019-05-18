 #include <Arduino.h>
 #include "pins.h"

void pinStartupConfig() {
  digitalWrite(ENGINE_RUN_PIN, ENGINE_RUN_PIN_INACTIVE);
  digitalWrite(ENGINE_REVERS_PIN, ENGINE_REVERS_PIN_ACTIVE);
  digitalWrite(AUTOMATIC_MODE_LAMP_PIN, AUTOMATIC_MODE_LAMP_PIN_INACTIVE);
  digitalWrite(MANUAL_MODE_LAMP_PIN, MANUAL_MODE_LAMP_PIN_INACTIVE);
}

void setupPins() {
  // Iterrupt
  pinMode(INTERRUPT_COUNTER_PIN, INPUT);
  
  // outputs
  pinMode(ENGINE_RUN_PIN, OUTPUT);
  pinMode(ENGINE_REVERS_PIN, OUTPUT);
  pinMode(AUTOMATIC_MODE_LAMP_PIN, OUTPUT);
  pinMode(MANUAL_MODE_LAMP_PIN, OUTPUT);

  // Inputs
  pinMode(OPERATIONAL_BUTTON_PIN, INPUT);
  pinMode(OPTICAL_SENSOR_PIN, INPUT);
  pinMode(AUTOMATIC_MODE_BUTTON_PIN, INPUT);
  pinMode(MANUAL_MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ABORT_PIN, INPUT);
  pinMode(CALIBRATION_BUTTON_PIN, INPUT);

  pinStartupConfig();
}

int checkIfPinIsActive(int pinNo, int pinActiveState, int pinInctiveState, uint8_t checkDelay) {
  int val = 0;
  int counter = 0;
  int controlCount = 10;

  for (int i = 0; i < controlCount; i++) {
    delay(checkDelay);
    val = digitalRead(pinNo);
    if (val == pinActiveState) {
      counter++;
    }
  }

  if (counter == controlCount) {
    return pinActiveState;
  }

  return HIGH;
}
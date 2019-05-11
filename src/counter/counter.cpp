#include <Arduino.h>
#include <EEPROM.h>
#include "counter.h"
#include "pins/pins.h"
#include "lcd/lcd.h"

volatile unsigned int counter;
volatile static int canCount = CAN_NOT_INCREMENT;

int impulsPerMeter;
const int impulsPerMeterAddress = 0;

/*
######################### HELPER FUNCTIONS #########################
*/



void EEPROMWriteInt(int address, int value) {
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
  
  EEPROM.update(address, two);
  EEPROM.update(address + 1, one);
}
 
int EEPROMReadInt(int address) {
  long two = EEPROM.read(address);
  long one = EEPROM.read(address + 1);
 
  return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
}

void displayImpulsPerMeterMessage(char message[20]) {
  clearLcd();
  sprintf(message, "Impuls per meter:");
  printlnLcd(message);
  printlnLcd(impulsPerMeter);
}

void incrementCounter() {
  int pinValue = digitalRead(INTERRUPT_COUNTER_PIN);
  
  if (canCount == CAN_INCREMENT && pinValue == INTERRUPT_COUNTER_PIN_ACTIVE) {
    counter++;
  }
}

void calibrationMode() {
  int prevValue = impulsPerMeter; 
  char message[20];
  int incrementButton;
  int decrementButton;
  int notConfirmed = CALIBRATION_BUTTON_PIN_INACTIVE;

  displayImpulsPerMeterMessage(message);

  while (notConfirmed) {
    notConfirmed = checkIfPinIsActive(CALIBRATION_BUTTON_PIN, CALIBRATION_BUTTON_PIN_ACTIVE, CALIBRATION_BUTTON_PIN_INACTIVE);
    decrementButton = checkIfPinIsActive(MANUAL_MODE_BUTTON_PIN, MANUAL_MODE_BUTTON_PIN_ACTIVE, MANUAL_MODE_BUTTON_PIN_INACTIVE);
    incrementButton = checkIfPinIsActive(AUTOMATIC_MODE_BUTTON_PIN, AUTOMATIC_MODE_BUTTON_PIN_ACTIVE, AUTOMATIC_MODE_BUTTON_PIN_INACTIVE);

    if (decrementButton == MANUAL_MODE_BUTTON_PIN_ACTIVE && impulsPerMeter > 1) {
      impulsPerMeter--;
    }
    if (incrementButton == AUTOMATIC_MODE_BUTTON_PIN_ACTIVE) {
      impulsPerMeter++;
    }

    if (impulsPerMeter != prevValue) {
      displayImpulsPerMeterMessage(message);
    }

    prevValue = impulsPerMeter;
  }

  EEPROMWriteInt(impulsPerMeterAddress, impulsPerMeter);
  
  sprintf(message, "Value saved.");
  printLcd(message);
  delay(1000);
}



/*
######################### EXPORTED FUNCTIONS #######################
*/



void setupInterrupt() {
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_COUNTER_PIN), incrementCounter, RISING);
}

void setCanCount(int value) {
  canCount = value;
}

void setImpulsPerMeter() {
  int calibrationButtonState = checkIfPinIsActive(CALIBRATION_BUTTON_PIN, CALIBRATION_BUTTON_PIN_ACTIVE, CALIBRATION_BUTTON_PIN_INACTIVE);
  impulsPerMeter = EEPROMReadInt(impulsPerMeterAddress);

  if (impulsPerMeter < 0) {
    impulsPerMeter = 1;
  }

  if (calibrationButtonState == CALIBRATION_BUTTON_PIN_ACTIVE) {
    printlnLcd("Calibration mode.");
    printlnLcd("Release button.");
    printlnLcd("Pleas wait...");
    delay(3000);
    calibrationMode();
  }
}

float caluclateLenght() {
  return (float) counter / (float) impulsPerMeter;
}
#include <LiquidCrystal_I2C.h>
#include "lcd.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

static uint8_t currentRow = 0;


void setupLcd() {
  // setup lcd
  lcd.begin(4, 20);
  clearLcd();
}

void printLcd(const char* output) {
  clearLcd();
  currentRow = 0;
  lcd.print(output);
}

void printLcd(int output) {
  clearLcd();
  currentRow = 0;
  lcd.print(output);
}

void printLcd(unsigned int output) {
  clearLcd();
  currentRow = 0;
  lcd.print(output);
}

void printLcd(float output) {
  clearLcd();
  currentRow = 0;
  lcd.print(output);
}

void printLcd(const char* text, float value) {
  clearLcd();
  currentRow = 0;
  lcd.print(text);
  lcd.print(value, 2);
}

void printLcd(const char* text, int value) {
  clearLcd();
  currentRow = 0;
  lcd.print(text);
  lcd.print(value);
}

void printlnLcd(const char* text) {
  lcd.print(text);
  currentRow++;
  lcd.setCursor(0, currentRow);
}

void printlnLcd(int val) {
  lcd.print(val);
  currentRow++;
  lcd.setCursor(0, currentRow);
}

void clearLcd() {
  lcd.clear();
  currentRow = 0;
  lcd.setCursor(0,0);
}
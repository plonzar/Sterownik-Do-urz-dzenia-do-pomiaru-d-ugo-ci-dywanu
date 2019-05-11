/**
 *   Setup LCD for work, LCD size is 20 x 4
*/
extern void setupLcd();

/**
 *  Print passed input on LCD
*/
extern void printLcd(const char* output);

extern void printLcd(int output);

extern void printLcd(float output);

extern void printLcd(unsigned int output);

extern void printLcd(const char* text, float value);

extern void printLcd(const char* text, int value);

extern void printlnLcd(const char* text);

extern void printlnLcd(int val);

/**
 * Clear LCD and set cursor on position (0, 0)
*/
extern void clearLcd();
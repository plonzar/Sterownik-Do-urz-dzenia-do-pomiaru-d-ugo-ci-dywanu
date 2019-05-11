
//########################################### PIN DELCARATIONS ##`###########################################

// Outputs:
const int ENGINE_RUN_PIN = 4;
const int ENGINE_REVERS_PIN = 5;
const int AUTOMATIC_MODE_LAMP_PIN = 6;
const int MANUAL_MODE_LAMP_PIN = 7;

// Inputs:

// Interrrupt pin
/* Input from encoder */
const int INTERRUPT_COUNTER_PIN = 2; 

const int OPTICAL_SENSOR_PIN = 8;
const int AUTOMATIC_MODE_BUTTON_PIN = 9;
const int MANUAL_MODE_BUTTON_PIN = 10;
const int EMERGENCY_STOP_PIN = 11;
const int SECURITY_BUTTON_PIN = 12;
const int CALIBRATION_BUTTON_PIN = 13;

extern void setupPins();

extern int checkIfPinIsActive(int pinNo, int pinActiveState, int pinInctiveState, uint8_t checkDelay = 3);

//########################################## PIN LOGICAL CONFIG ###########################################

//Production:

const int EMERGENCY_STOP_PIN_ACTIVE = LOW;
const int EMERGENCY_STOP_PIN_INACTIVE = HIGH;

const int SECURITY_BUTTON_PIN_ACTIVE = LOW;
const int SECURITY_BUTTON_PIN_INACTIVE = HIGH;

const int AUTOMATIC_MODE_BUTTON_PIN_ACTIVE = LOW;
const int AUTOMATIC_MODE_BUTTON_PIN_INACTIVE = HIGH;

const int MANUAL_MODE_BUTTON_PIN_ACTIVE = LOW;
const int MANUAL_MODE_BUTTON_PIN_INACTIVE = HIGH;

const int OPTICAL_SENSOR_PIN_ACTIVE = LOW;
const int OPTICAL_SENSOR_PIN_INACTIVE = HIGH;

const int INTERRUPT_COUNTER_PIN_ACTIVE = HIGH;
const int INTERRUPT_COUNTER_PIN_INACTIVE = LOW;

const int ENGINE_RUN_PIN_ACTIVE = HIGH;
const int ENGINE_RUN_PIN_INACTIVE = LOW;

const int ENGINE_REVERS_PIN_ACTIVE = HIGH;
const int ENGINE_REVERS_PIN_INACTIVE = LOW;

const int AUTOMATIC_MODE_LAMP_PIN_ACTIVE = HIGH;
const int AUTOMATIC_MODE_LAMP_PIN_INACTIVE = LOW;

const int MANUAL_MODE_LAMP_PIN_ACTIVE = HIGH;
const int MANUAL_MODE_LAMP_PIN_INACTIVE = LOW;

const int CALIBRATION_BUTTON_PIN_ACTIVE = LOW;
const int CALIBRATION_BUTTON_PIN_INACTIVE = HIGH;

// Development:

// const int EMERGENCY_STOP_PIN_ACTIVE = LOW;
// const int EMERGENCY_STOP_PIN_INACTIVE = HIGH;

// const int SECURITY_BUTTON_PIN_ACTIVE = LOW;
// const int SECURITY_BUTTON_PIN_INACTIVE = HIGH;

// const int MANUAL_MODE_BUTTON_PIN_ACTIVE = LOW;
// const int MANUAL_MODE_BUTTON_PIN_INACTIVE = HIGH;

// const int AUTOMATIC_MODE_BUTTON_PIN_ACTIVE = LOW;
// const int AUTOMATIC_MODE_BUTTON_PIN_INACTIVE = HIGH;

// const int OPTICAL_SENSOR_PIN_ACTIVE = LOW;
// const int OPTICAL_SENSOR_PIN_INACTIVE = HIGH;

// const int INTERRUPT_COUNTER_PIN_ACTIVE = LOW;
// const int INTERRUPT_COUNTER_PIN_INACTIVE = HIGH;

// const int ENGINE_RUN_PIN_ACTIVE = HIGH;
// const int ENGINE_RUN_PIN_INACTIVE = LOW;

// const int ENGINE_REVERS_PIN_ACTIVE = HIGH;
// const int ENGINE_REVERS_PIN_INACTIVE = LOW;

// const int AUTOMATIC_MODE_LAMP_PIN_ACTIVE = HIGH;
// const int AUTOMATIC_MODE_LAMP_PIN_INACTIVE = LOW;

// const int MANUAL_MODE_LAMP_PIN_ACTIVE = HIGH;
// const int MANUAL_MODE_LAMP_PIN_INACTIVE = LOW;

// const int CALIBRATION_BUTTON_PIN_ACTIVE = LOW;
// const int CALIBRATION_BUTTON_PIN_INACTIVE = HIGH;
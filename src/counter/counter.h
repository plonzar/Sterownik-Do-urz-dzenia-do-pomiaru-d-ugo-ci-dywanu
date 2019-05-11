#define CAN_NOT_INCREMENT 0
#define CAN_INCREMENT 1

/**
 *  Setup external interrupt for encoder
*/
extern void setupInterrupt();

/**
 *  Set if ticks counter can be incremented.
 * 
 *  @param value: possible values are:
 *  0 => cannot increment
 *  1 => can increment
*/
extern void setCanCount(int value);

/**
 * Set correction value for caluclation. Value describes impuls count per meter.
*/
extern void setImpulsPerMeter();

/**
 * Calulate carpet lenght in meters, based on number of ticks from encoder.
*/
extern float caluclateLenght();
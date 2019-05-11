#define FORWARD 0
#define REVERSE 1
#define END_STATE 2

/**
 * Resolve direction, based on current optical sensor value and it's previous state.
 * Possible states: FORWARD (0), REVERSE (1), END_STATE (2).
*/
extern void resolveDirection();

/**
 * Stops engine. set ENGINE_RUN_PIN to LOW.
*/
extern void stopEngine();

/**
 * Starts or keep runing engine forward. 
 * If engine was running reverse set ENGINE_REVERS_PIN to LOW,
 * then with delay start engine forward.
*/
extern void startEngineForward();

/**
 * Starts or keep runing engine reverse. 
 * If engine was running forward set ENGINE_REVERS_PIN to HIGH,
 * then with delay start engine reverse.
*/
extern void startEngineReverse();

/**
 * Return current engine direction. Possible directions:
 * FORWARD (0), REVERSE (1), END_STATE (2).
*/
extern int getCurrentDirection();

/**
 * Set current engine direction. Possible directions:
 * FORWARD (0), REVERSE (1), END_STATE (2).
*/
extern void setCurrentDirection(int direction);

/**
 * Set engine state for automatic and manual forward mode.
*/
extern void setEngineStateForForwardMode();

/**
 * Set engine state for manual reverse mode.
*/
extern void setEngineStateForManualReverseMode();
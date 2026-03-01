/*
 * BehaviorPumpkin.ino
 * 
 * Pumpkin behavior implementation for animatronic eyes
 * Demonstrates sequence-based behavior with smooth state transitions
 */

#include "Globals.h"

// Current pumpkin state
PumpkinState currentPumpkinState = PUMPKIN_IDLE;

// State timing
unsigned long stateStartTime = 0;
unsigned long lastActionTime = 0;

// Timing constants for pumpkin behavior
const unsigned long STATE_DURATION_IDLE = 5000;        // 5 seconds idle
const unsigned long STATE_DURATION_SCANNING = 4000;    // 4 seconds scanning
const unsigned long STATE_DURATION_CURIOUS = 3000;     // 3 seconds curious
const unsigned long STATE_DURATION_PLAYFUL = 4000;     // 4 seconds playful
const unsigned long ACTION_INTERVAL_BLINK = 3000;      // Blink every 3s
const unsigned long ACTION_INTERVAL_MOVEMENT = 1500;   // Move every 1.5s

// Sequence action index for tracking
uint8_t currentSequenceIndex = 0;

/*
 * Pumpkin behavior handler
 * Manages state machine and sequences
 */
void handleBehaviorPumpkin() {
  unsigned long currentTime = millis();
  
  // Handle current pumpkin state
  switch (currentPumpkinState) {
    case PUMPKIN_IDLE:
      performIdleState(currentTime);
      break;
      
    case PUMPKIN_SCANNING:
      performScanningState(currentTime);
      break;
      
    case PUMPKIN_CURIOUS:
      performCuriousState(currentTime);
      break;
      
    case PUMPKIN_PLAYFUL:
      performPlayfulState(currentTime);
      break;
      
    case PUMPKIN_RETURN:
      performReturnState(currentTime);
      break;
  }
}

/*
 * Initialize pumpkin behavior
 * Sets up initial state and positions
 */
void initializePumpkinBehavior() {
  Serial.println("Initializing Pumpkin Behavior...");
  
  // Set initial state
  currentPumpkinState = PUMPKIN_IDLE;
  stateStartTime = millis();
  
  // Set initial look forward position
  OpenLookForward();
  
  Serial.println("Pumpkin behavior initialized - starting in IDLE state");
}

/*
 * Perform idle state - resting with occasional blinks
 */
void performIdleState(unsigned long currentTime) {
  // Perform occasional blinks
  if (currentTime - lastActionTime >= ACTION_INTERVAL_BLINK) {
    lastActionTime = currentTime;
    blink(200);
  }
  
  // Transition to scanning after idle duration
  if (currentTime - stateStartTime >= STATE_DURATION_IDLE) {
    transitionToState(PUMPKIN_SCANNING);
  }
}

/*
 * Perform scanning state - looking around
 */
void performScanningState(unsigned long currentTime) {
  // Perform scanning movements
  if (currentTime - lastActionTime >= ACTION_INTERVAL_MOVEMENT) {
    lastActionTime = currentTime;
    
    // Random look direction
    float x = random(-100, 101) / 100.0;  // -1.0 to 1.0
    float y = random(-50, 51) / 100.0;    // -0.5 to 0.5
    moveEyeTo(x, y);
    
    Serial.print("Scanning - looking at (");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.println(")");
  }
  
  // Transition to curious after scanning duration
  if (currentTime - stateStartTime >= STATE_DURATION_SCANNING) {
    transitionToState(PUMPKIN_CURIOUS);
  }
}

/*
 * Perform curious state - focusing on something interesting
 */
void performCuriousState(unsigned long currentTime) {
  // Look in a specific direction and hold
  if (currentTime - stateStartTime < 1000 && lastActionTime == 0) {
    // Initial look
    moveEyeTo(0.7, 0.0);  // Look right
    lastActionTime = currentTime;
    Serial.println("Curious - focusing on something");
  } else if (currentTime - lastActionTime >= 1000) {
    // Subsequent blinks
    lastActionTime = currentTime;
    blink(150);
  }
  
  // Transition to playful after curious duration
  if (currentTime - stateStartTime >= STATE_DURATION_CURIOUS) {
    transitionToState(PUMPKIN_PLAYFUL);
  }
}

/*
 * Perform playful state - expressive reactions
 */
void performPlayfulState(unsigned long currentTime) {
  // Perform playful sequences
  if (currentTime - lastActionTime >= 2000) {
    lastActionTime = currentTime;
    
    // Random playful action
    uint8_t action = random(0, 3);
    switch (action) {
      case 0:
        // Wink left
        wink(true);
        Serial.println("Playful - winking left");
        break;
      case 1:
        // Wink right
        wink(false);
        Serial.println("Playful - winking right");
        break;
      case 2:
        // Move eyes quickly
        moveEyeTo(-0.5, 0.0);
        Serial.println("Playful - quick eye movement");
        break;
    }
  }
  
  // Transition to return after playful duration
  if (currentTime - stateStartTime >= STATE_DURATION_PLAYFUL) {
    transitionToState(PUMPKIN_RETURN);
  }
}

/*
 * Perform return state - smoothly return to idle
 */
void performReturnState(unsigned long currentTime) {
  // Return to center
  if (lastActionTime == 0) {
    moveEyeTo(0.0, 0.0);
    lastActionTime = currentTime;
    blink(200);
    Serial.println("Returning to idle");
  }
  
  // Transition back to idle after brief return
  if (currentTime - stateStartTime >= 1500) {
    transitionToState(PUMPKIN_IDLE);
  }
}

/*
 * Transition to a new state
 */
void transitionToState(PumpkinState newState) {
  Serial.print("Pumpkin State Transition: ");
  Serial.print(getPumpkinStateName(currentPumpkinState));
  Serial.print(" -> ");
  Serial.println(getPumpkinStateName(newState));
  
  currentPumpkinState = newState;
  stateStartTime = millis();
  lastActionTime = 0;  // Reset action timing
}

/*
 * Get pumpkin state name as string
 */
String getPumpkinStateName(PumpkinState state) {
  switch (state) {
    case PUMPKIN_IDLE: return "IDLE";
    case PUMPKIN_SCANNING: return "SCANNING";
    case PUMPKIN_CURIOUS: return "CURIOUS";
    case PUMPKIN_PLAYFUL: return "PLAYFUL";
    case PUMPKIN_RETURN: return "RETURN";
    default: return "UNKNOWN";
  }
}



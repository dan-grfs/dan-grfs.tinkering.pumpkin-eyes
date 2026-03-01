/*
 * BehaviorPostInvasion.ino
 * 
 * Post invasion behavior implementation for animatronic eyes
 * Uses pumpkin behavior state machine - active and expressive behavior
 * After 10 seconds, switches to sleeping behavior
 */

#include "Globals.h"

// Current post invasion state (using PumpkinState enum)
PumpkinState currentPostInvasionState = PUMPKIN_IDLE;

// State timing
unsigned long postInvasionStateStartTime = 0;
unsigned long postInvasionLastActionTime = 0;
unsigned long postInvasionStartTime = 0;  // When post invasion behavior started

// Speed multiplier for post invasion behavior (1.0 = normal, <1.0 = faster, >1.0 = slower)
// Adjust this to make all actions quicker or slower proportionally
const float POST_INVASION_SPEED_MULTIPLIER = 0.7;  // 0.7 = 30% faster (fewer pauses)

// Base timing constants for post invasion behavior (will be scaled by speed multiplier)
const unsigned long BASE_POST_INVASION_STATE_DURATION_IDLE = 5000;        // 5 seconds idle
const unsigned long BASE_POST_INVASION_STATE_DURATION_SCANNING = 4000;    // 4 seconds scanning
const unsigned long BASE_POST_INVASION_STATE_DURATION_CURIOUS = 3000;     // 3 seconds curious
const unsigned long BASE_POST_INVASION_STATE_DURATION_PLAYFUL = 4000;     // 4 seconds playful
const unsigned long BASE_POST_INVASION_ACTION_INTERVAL_BLINK = 3000;      // Blink every 3s
const unsigned long BASE_POST_INVASION_ACTION_INTERVAL_MOVEMENT = 1500;   // Move every 1.5s
const unsigned long POST_INVASION_TO_SLEEPING_DURATION = 10000;  // 10 seconds before switching to sleeping (not scaled)

// Scaled timing constants (calculated from base values and speed multiplier)
const unsigned long POST_INVASION_STATE_DURATION_IDLE = (unsigned long)(BASE_POST_INVASION_STATE_DURATION_IDLE * POST_INVASION_SPEED_MULTIPLIER);
const unsigned long POST_INVASION_STATE_DURATION_SCANNING = (unsigned long)(BASE_POST_INVASION_STATE_DURATION_SCANNING * POST_INVASION_SPEED_MULTIPLIER);
const unsigned long POST_INVASION_STATE_DURATION_CURIOUS = (unsigned long)(BASE_POST_INVASION_STATE_DURATION_CURIOUS * POST_INVASION_SPEED_MULTIPLIER);
const unsigned long POST_INVASION_STATE_DURATION_PLAYFUL = (unsigned long)(BASE_POST_INVASION_STATE_DURATION_PLAYFUL * POST_INVASION_SPEED_MULTIPLIER);
const unsigned long POST_INVASION_ACTION_INTERVAL_BLINK = (unsigned long)(BASE_POST_INVASION_ACTION_INTERVAL_BLINK * POST_INVASION_SPEED_MULTIPLIER);
const unsigned long POST_INVASION_ACTION_INTERVAL_MOVEMENT = (unsigned long)(BASE_POST_INVASION_ACTION_INTERVAL_MOVEMENT * POST_INVASION_SPEED_MULTIPLIER);

/*
 * Post invasion behavior handler
 * Manages state machine and sequences (based on pumpkin behavior)
 */
void handleBehaviorPostInvasion() {
  unsigned long currentTime = millis();
  
  // Check if 10 seconds have passed - switch to sleeping behavior
  if (postInvasionStartTime > 0 && (currentTime - postInvasionStartTime >= POST_INVASION_TO_SLEEPING_DURATION)) {
    setBehavior(BEHAVIOR_SLEEPING);
    return;  // Exit early after switching behavior
  }
  
  // Handle current post invasion state
  switch (currentPostInvasionState) {
    case PUMPKIN_IDLE:
      performPostInvasionIdleState(currentTime);
      break;
      
    case PUMPKIN_SCANNING:
      performPostInvasionScanningState(currentTime);
      break;
      
    case PUMPKIN_CURIOUS:
      performPostInvasionCuriousState(currentTime);
      break;
      
    case PUMPKIN_PLAYFUL:
      performPostInvasionPlayfulState(currentTime);
      break;
      
    case PUMPKIN_RETURN:
      performPostInvasionReturnState(currentTime);
      break;
  }
}

/*
 * Initialize post invasion behavior
 * Sets up initial state and positions
 */
void initializePostInvasionBehavior() {
  Serial.println("Initializing Post Invasion Behavior (Pumpkin-style)...");
  
  // Set initial state
  currentPostInvasionState = PUMPKIN_IDLE;
  postInvasionStateStartTime = millis();
  postInvasionStartTime = millis();  // Record when post invasion behavior started
  postInvasionLastActionTime = 0;
  
  // Set smooth movement speed for active behavior
  setSmoothMovementSpeed(13);
  
  // Set initial look forward position
  OpenLookForward();
  
  Serial.println("Post invasion behavior initialized - starting in IDLE state");
}

/*
 * Perform idle state - resting with occasional blinks
 */
void performPostInvasionIdleState(unsigned long currentTime) {
  // Perform occasional blinks
  if (currentTime - postInvasionLastActionTime >= POST_INVASION_ACTION_INTERVAL_BLINK) {
    postInvasionLastActionTime = currentTime;
    blink(200);
  }
  
  // Transition to scanning after idle duration
  if (currentTime - postInvasionStateStartTime >= POST_INVASION_STATE_DURATION_IDLE) {
    transitionToPostInvasionState(PUMPKIN_SCANNING);
  }
}

/*
 * Perform scanning state - looking around
 */
void performPostInvasionScanningState(unsigned long currentTime) {
  // Perform scanning movements
  if (currentTime - postInvasionLastActionTime >= POST_INVASION_ACTION_INTERVAL_MOVEMENT) {
    postInvasionLastActionTime = currentTime;
    
    // Random look direction
    float x = random(-100, 101) / 100.0;  // -1.0 to 1.0
    float y = random(-50, 51) / 100.0;    // -0.5 to 0.5
    moveEyeTo(x, y);
    
    Serial.print("Post Invasion Scanning - looking at (");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.println(")");
  }
  
  // Transition to curious after scanning duration
  if (currentTime - postInvasionStateStartTime >= POST_INVASION_STATE_DURATION_SCANNING) {
    transitionToPostInvasionState(PUMPKIN_CURIOUS);
  }
}

/*
 * Perform curious state - focusing on something interesting
 */
void performPostInvasionCuriousState(unsigned long currentTime) {
  // Look in a specific direction and hold (timings scaled by speed multiplier)
  unsigned long curiousInitialLookTime = (unsigned long)(1000 * POST_INVASION_SPEED_MULTIPLIER);
  unsigned long curiousBlinkInterval = (unsigned long)(1000 * POST_INVASION_SPEED_MULTIPLIER);
  
  if (currentTime - postInvasionStateStartTime < curiousInitialLookTime && postInvasionLastActionTime == 0) {
    // Initial look
    moveEyeTo(0.7, 0.0);  // Look right
    postInvasionLastActionTime = currentTime;
    Serial.println("Post Invasion Curious - focusing on something");
  } else if (currentTime - postInvasionLastActionTime >= curiousBlinkInterval) {
    // Subsequent blinks
    postInvasionLastActionTime = currentTime;
    blink(150);
  }
  
  // Transition to playful after curious duration
  if (currentTime - postInvasionStateStartTime >= POST_INVASION_STATE_DURATION_CURIOUS) {
    transitionToPostInvasionState(PUMPKIN_PLAYFUL);
  }
}

/*
 * Perform playful state - expressive reactions
 */
void performPostInvasionPlayfulState(unsigned long currentTime) {
  // Perform playful sequences (timing scaled by speed multiplier)
  unsigned long playfulActionInterval = (unsigned long)(2000 * POST_INVASION_SPEED_MULTIPLIER);
  if (currentTime - postInvasionLastActionTime >= playfulActionInterval) {
    postInvasionLastActionTime = currentTime;
    
    // Random playful action
    uint8_t action = random(0, 3);
    switch (action) {
      case 0:
        // Wink left - look forward first, then wink
        moveEyeTo(0.0, 0.0);  // Look straight ahead first
        wink(true);
        Serial.println("Post Invasion Playful - winking left");
        break;
      case 1:
        // Wink right - look forward first, then wink
        moveEyeTo(0.0, 0.0);  // Look straight ahead first
        wink(false);
        Serial.println("Post Invasion Playful - winking right");
        break;
      case 2:
        // Move eyes quickly
        moveEyeTo(-0.5, 0.0);
        Serial.println("Post Invasion Playful - quick eye movement");
        break;
    }
  }
  
  // Transition to return after playful duration
  if (currentTime - postInvasionStateStartTime >= POST_INVASION_STATE_DURATION_PLAYFUL) {
    transitionToPostInvasionState(PUMPKIN_RETURN);
  }
}

/*
 * Perform return state - smoothly return to idle
 */
void performPostInvasionReturnState(unsigned long currentTime) {
  // Return to center
  if (postInvasionLastActionTime == 0) {
    moveEyeTo(0.0, 0.0);
    postInvasionLastActionTime = currentTime;
    blink(200);
    Serial.println("Post Invasion Returning to idle");
  }
  
  // Transition back to idle after brief return (timing scaled by speed multiplier)
  // (instead of checking for sleep here, the main handler checks the 10 second duration)
  unsigned long returnDuration = (unsigned long)(1500 * POST_INVASION_SPEED_MULTIPLIER);
  if (currentTime - postInvasionStateStartTime >= returnDuration) {
    transitionToPostInvasionState(PUMPKIN_IDLE);
  }
}

/*
 * Transition to a new post invasion state
 */
void transitionToPostInvasionState(PumpkinState newState) {
  Serial.print("Post Invasion State Transition: ");
  Serial.print(getPostInvasionStateName(currentPostInvasionState));
  Serial.print(" -> ");
  Serial.println(getPostInvasionStateName(newState));
  
  currentPostInvasionState = newState;
  postInvasionStateStartTime = millis();
  postInvasionLastActionTime = 0;  // Reset action timing
}

/*
 * Get post invasion state name as string (local version to avoid conflicts)
 */
String getPostInvasionStateName(PumpkinState state) {
  switch (state) {
    case PUMPKIN_IDLE: return "IDLE";
    case PUMPKIN_SCANNING: return "SCANNING";
    case PUMPKIN_CURIOUS: return "CURIOUS";
    case PUMPKIN_PLAYFUL: return "PLAYFUL";
    case PUMPKIN_RETURN: return "RETURN";
    default: return "UNKNOWN";
  }
}

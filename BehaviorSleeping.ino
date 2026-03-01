/*
 * BehaviorSleeping.ino
 * 
 * Sleeping behavior implementation for animatronic eyes
 * Demonstrates sequence-based sleeping behavior with smooth state transitions
 * 
 * Sequence:
 * 1. Tired blinking with normal eyes
 * 2. Half-closed eyes for a few seconds
 * 3. Slow blinks with half-closed eyes
 * 4. Gradually close eyes completely
 */

#include "Globals.h"

// Current sleeping state
SleepingState currentSleepingState = SLEEPING_TIRED_BLINK;

// State timing
unsigned long sleepingStateStartTime = 0;
unsigned long sleepingLastActionTime = 0;
unsigned long slowBlinkCloseTime = 0;  // Track when slow blink started closing

// Timing constants for sleeping behavior
const unsigned long STATE_DURATION_TIRED_BLINK = 6000;    // 3 seconds tired blinking
const unsigned long STATE_DURATION_HALF_CLOSED = 3000;    // 4 seconds half-closed
const unsigned long STATE_DURATION_SLOW_BLINKS = 6000;    // 5 seconds slow blinks
const unsigned long BLINK_INTERVAL_TIRED = 3000;          // Blink every 3s when tired
const unsigned long BLINK_INTERVAL_SLOW = 3000;           // Blink every 3s slow blink
const unsigned long SLOW_BLINK_CLOSE_DURATION = 1200;      // 1200ms to hold slow blink closed
const unsigned long CLOSING_DURATION = 3000;              // 3 seconds to fully close

// Blink counters
uint8_t tiredBlinkCount = 0;
uint8_t slowBlinkCount = 0;
bool isSlowBlinkClosed = false;  // Track if slow blink is currently closed

/*
 * Sleeping behavior handler
 * Manages state machine and sequences
 */
void handleBehaviorSleeping() {
  unsigned long currentTime = millis();
  
  // Handle current sleeping state
  switch (currentSleepingState) {
    case SLEEPING_TIRED_BLINK:
      performTiredBlinkState(currentTime);
      break;
      
    case SLEEPING_HALF_CLOSED:
      performHalfClosedState(currentTime);
      break;
      
    case SLEEPING_SLOW_BLINKS:
      performSlowBlinksState(currentTime);
      break;
      
    case SLEEPING_CLOSING:
      performClosingState(currentTime);
      break;
      
    case SLEEPING_CLOSED:
      // Eyes fully closed, no action needed
      break;
  }
}

/*
 * Initialize sleeping behavior
 * Sets up initial state and positions
 */
void initializeSleepingBehavior() {
  // Set initial state
  currentSleepingState = SLEEPING_TIRED_BLINK;
  sleepingStateStartTime = millis();
  sleepingLastActionTime = 0;
  slowBlinkCloseTime = 0;
  tiredBlinkCount = 0;
  slowBlinkCount = 0;
  isSlowBlinkClosed = false;
  
  // Set smooth movement speed for sleepy behavior (slower for tired effect)
  setSmoothMovementSpeed(3);
  
  // Start with eyes open and looking forward
  OpenLookForward();
}

/*
 * Perform tired blink state - blinking like tired with drooping and fatigue
 */
void performTiredBlinkState(unsigned long currentTime) {
  // Calculate time elapsed since state started
  unsigned long elapsedTime = currentTime - sleepingStateStartTime;
  
  // 1. Gradual eye drooping - eyes slowly droop down over time
  float droopAmount = (elapsedTime / 1000.0) * 0.05; // 0.05 per second
  float eyePosition = constrain(-droopAmount, -0.3, 0.0); // Max droop of 0.3
  moveEyeVertical(eyePosition);
  
  // 2. Eyelid fatigue - eyelids gradually become more closed
  float eyelidFatigue = (elapsedTime / 1000.0) * 0.02; // 0.02 per second
  float eyelidOpenness = constrain(1.0 - eyelidFatigue, 0.8, 1.0);
  moveEyelids(eyelidOpenness, eyelidOpenness);
  
  // 3. Micro-movements - small random drift to simulate "trying to stay awake"
  static unsigned long lastMicroMove = 0;
  if (currentTime - lastMicroMove >= 2000) { // Every 2 seconds
    lastMicroMove = currentTime;
    float microDrift = (random(-10, 11) / 100.0); // ±0.1 units
    moveEyeHorizontal(microDrift);
  }
  
  // 4. Slower, heavier blinks while eyes are open
  if (currentTime - sleepingLastActionTime >= BLINK_INTERVAL_TIRED) {
    sleepingLastActionTime = currentTime;
    blink(400);  // Longer, heavier blink (was 200ms)
    tiredBlinkCount++;
  }
  
  // Transition to half-closed after tired blink duration
  if (elapsedTime >= STATE_DURATION_TIRED_BLINK) {
    transitionToSleepingState(SLEEPING_HALF_CLOSED);
  }
}

/*
 * Perform half-closed state - eyes partially closed
 */
void performHalfClosedState(unsigned long currentTime) {
  // Initial half-close
  if (sleepingLastActionTime == 0) {
    // Close eyes to half position (0.5 = halfway between open and closed)
    moveEyelids(0.5, 0.5);
    sleepingLastActionTime = currentTime;
  }
  
  // Transition to slow blinks after half-closed duration
  if (currentTime - sleepingStateStartTime >= STATE_DURATION_HALF_CLOSED) {
    transitionToSleepingState(SLEEPING_SLOW_BLINKS);
  }
}

/*
 * Perform slow blinks state - slow blinks with half-closed eyes
 */
void performSlowBlinksState(unsigned long currentTime) {
  // Slow blinks with non-blocking implementation
  if (!isSlowBlinkClosed) {
    // Not currently blinking - check if it's time to start a slow blink
    if (currentTime - sleepingLastActionTime >= BLINK_INTERVAL_SLOW) {
      // Start slow blink - close eyes
      moveEyelids(0.0, 0.0);
      slowBlinkCloseTime = currentTime;
      isSlowBlinkClosed = true;
    }
  } else {
    // Currently blinking - check if it's time to open eyes again
    if (currentTime - slowBlinkCloseTime >= SLOW_BLINK_CLOSE_DURATION) {
      // Open eyes back to half-closed
      moveEyelids(0.5, 0.5);
      sleepingLastActionTime = currentTime;
      isSlowBlinkClosed = false;
      slowBlinkCount++;
    }
  }
  
  // Transition to closing after slow blink duration
  if (currentTime - sleepingStateStartTime >= STATE_DURATION_SLOW_BLINKS) {
    transitionToSleepingState(SLEEPING_CLOSING);
  }
}

/*
 * Perform closing state - gradually close eyes
 */
void performClosingState(unsigned long currentTime) {
  // Gradually close eyes over the closing duration
  if (sleepingLastActionTime == 0) {
    sleepingLastActionTime = currentTime;
  }
  
  unsigned long elapsedTime = currentTime - sleepingStateStartTime;
  
  // Calculate closing progress (0.0 to 1.0)
  float closingProgress = (float)elapsedTime / CLOSING_DURATION;
  
  if (closingProgress < 1.0) {
    // Gradually reduce from 0.5 (half-closed) to 0.0 (fully closed)
    float eyelidPosition = 0.5 * (1.0 - closingProgress);
    moveEyelids(eyelidPosition, eyelidPosition);
  } else {
    // Fully closed
    moveEyelids(0.0, 0.0);
    transitionToSleepingState(SLEEPING_CLOSED);
  }
}

/*
 * Transition to a new sleeping state
 */
void transitionToSleepingState(SleepingState newState) {
  currentSleepingState = newState;
  sleepingStateStartTime = millis();
  sleepingLastActionTime = 0;  // Reset action timing
  slowBlinkCloseTime = 0;      // Reset slow blink timing
  isSlowBlinkClosed = false;   // Reset slow blink state
}

/*
 * Get sleeping state name as string
 */
String getSleepingStateName(SleepingState state) {
  switch (state) {
    case SLEEPING_TIRED_BLINK: return "TIRED_BLINK";
    case SLEEPING_HALF_CLOSED: return "HALF_CLOSED";
    case SLEEPING_SLOW_BLINKS: return "SLOW_BLINKS";
    case SLEEPING_CLOSING: return "CLOSING";
    case SLEEPING_CLOSED: return "CLOSED";
    default: return "UNKNOWN";
  }
}
